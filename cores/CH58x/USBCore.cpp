/* Copyright (c) 2010, Peter Barrett
** Sleep/Wakeup support added by Michael Dreher
**
** Permission to use, copy, modify, and/or distribute this software for
** any purpose with or without fee is hereby granted, provided that the
** above copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
** SOFTWARE.
*/

#include "USBCore.h"
#include "PluggableUSB.h"
#include "CDC.h"

#define printLog 0
#define printData 0

//extern const u16 STRING_LANGUAGE[];
//extern const u8 STRING_PRODUCT[];
//extern const u8 STRING_MANUFACTURER[];

//extern const DeviceDescriptor USB_DD;


volatile u8 _usbConfiguration = 0;
volatile u8 _usbCurrentStatus = 0x80; // meaning of bits see usb_20.pdf, Figure 9-4. Information Returned by a GetStatus() Request to a Device
volatile u8 _usbSuspendState = 0; // copy of UDINT to check SUSPI and WAKEUPI bits

const DeviceDescriptor USB_DD = D_DEVICE(0xEF, 0x02, 0x01, 64, 0x1A86, 0x8040, 0x0100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
//												USB_VID, USB_PID 0x0BDA,0x0411
const u16 STRING_LANGUAGE[2] = {
	(3 << 8) | (2 + 2),
	0x0409	// English
};

#if USB_VID == 0x4348
#define USB_MANUFACTURER "WCH"
#else
#define USB_MANUFACTURER "CH58x Dev"
#endif
const u8 STRING_MANUFACTURER[] = USB_MANUFACTURER;

#ifndef USB_PRODUCT
// If no product is provided, use USB IO Board
#define USB_PRODUCT     "USB Dev Board"
#endif
const u8 STRING_PRODUCT[] = USB_PRODUCT;

#ifndef HID_ENABLED
#define HID_ENABLED
#endif // !HID_ENABLED


uint8_t _initEndpoints[] = {
		0,                            // EP0
	#ifdef CDC_ENABLED
		EP_TYPE_INTERRUPT_IN,        // EP1 IN  (通知端點)
		EP_TYPE_BULK_OUT,            // EP2 OUT (資料接收)
		EP_TYPE_BULK_IN,             // EP3 IN  (資料傳送)
	#endif
	#ifdef HID_ENABLED
		EP_TYPE_INTERRUPT_IN,        // EP4 IN  (HID)
	#endif
		0                             // 表尾
};

#define DEVICE_CLASS 0x02


uint8_t	USB_Available(uint8_t ep) {
	return USBDevice.Available(ep);
}

int USB_Send(uint8_t ep, const void* data, int len) {
	if (_usbConfiguration == 0) {
		return -1;
	}

	PFIC_DisableIRQ(USB_IRQn);
	USBDevice.EndPoint[ep]._CTRL->UEP_T_RES = USB_MASK::NAK;
	PFIC_EnableIRQ(USB_IRQn);

	USBDevice.Send(ep, data, len);
	
	PFIC_DisableIRQ(USB_IRQn);
	USBDevice.EndPoint[ep]._CTRL->UEP_T_RES = USB_MASK::ACK;
	PFIC_EnableIRQ(USB_IRQn);
	return len;
}
//	Return number of bytes read
int USB_Recv(uint8_t ep, void* data, int len) {
	if (!_usbConfiguration || len < 0)
		return -1;
	PFIC_DisableIRQ(USB_IRQn);
	USBDevice.Recv(ep, data, len);
	PFIC_EnableIRQ(USB_IRQn);
	return len;
}
int USB_Recv(uint8_t ep) {
	uint8_t c;
	if (USB_Recv(ep, &c, 1) != 1)
		return -1;
	return c;
}

static uint8_t SendInterfaces(int* descriptorLength)
{
	u8 interfaces = 0;
#ifdef PLUGGABLE_USB_ENABLED
	//Serial1.println((uint32_t)PluggableUSB().getRootNode(), HEX);
	*descriptorLength = PluggableUSB().getInterface(&interfaces);
#endif
	return interfaces;
}

int USB_FillBuffer(int offset, const void* d, int len) {
	if (offset < 0 || len < 0 || offset + len > 192) {
		return -1; // or handle error
	}
	uint8_t* Buffer = USBDevice.getExtendedBuffer(-1) + offset; //resetEP0Buf_index重置Buffer回起始位置並回傳uint8_t* 指標，偏移一個headr + config偏移量

	memcpy(Buffer, d, len);
#if(printData)
		for (int i = 0; i < len; i++) {
			Serial1.print(Buffer[i], HEX); Serial1.print(", ");
		}
		Serial1.println("");
#endif
	return len;
}

// Send a USB descriptor string. The string is stored in PROGMEM as a
// plain ASCII string but is sent out as UTF-16 with the correct 2-byte
// prefix
static uint8_t USB_SendStringDescriptor(const u8* string_P, u8 string_len) {
	uint8_t* Ep0Buffer_ = USBDevice.getEpBuffer(0);
	Ep0Buffer_[0] = 2 + string_len * 2;
	Ep0Buffer_[1] = 3;
	for (uint8_t i = 0; i < string_len; ++i) {
		Ep0Buffer_[2 + i * 2] = string_P[i];  // ASCII char
		Ep0Buffer_[3 + i * 2] = 0x00;         // UTF-16LE low byte
	}	
	return Ep0Buffer_[0];
}

static bool ClassInterfaceRequest(USBSetup& setup)
{
#ifdef PLUGGABLE_USB_ENABLED
	return PluggableUSB().setup(setup);
#endif
	return false;
}

static void InitEndpoints() {
#if(printLog)
	Serial1.println("EP initial.");
#endif
	for (int i = 1;_initEndpoints[i] != 0;i++) {
		USBDevice.initialEP(i, _initEndpoints[i]);
#if(printLog)
		Serial1.print("EP");
		Serial1.print(USBDevice.EndPoint[i].Num);
		Serial1.print(" : ");
		Serial1.println(USBDevice.EndPoint[i].dir, BIN);
#endif
	}
	uint8_t* EP1_Buffer = USBDevice.getEpBuffer(1);
	memcpy(EP1_Buffer, serial_state_notify, 10);
	x8_UEP1_T_LEN.length = 10;
	PFIC_DisableIRQ(USB_IRQn);
	R8_UEP1_CTRL = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_NAK | UEP_T_RES_ACK;
	PFIC_EnableIRQ(USB_IRQn);
}

/*======================================================================*/
uint16_t SOF_Count = 0;
/*==========================SETUP Variable==============================*/
uint8_t usb_addr;
//uint8_t bRequest;
/*======================================================================*/
extern "C"
__INTERRUPT
void USB_IRQHandler(void) {
	static USBDevice_& Dev_ = USBDevice;
	static volatile USB_Module_t& USB_ = USB;
	static USBSetup* SetupPack = (USBSetup*)Dev_.getEpBuffer(0);
	static uint8_t ReqType, bRequest, dType, wLen;

	if (USB_.INT_FG.DEVICE.UIF_TRANSFER) {
		if (USB_.INT_ST.DEVICE.UIS_TOKEN != 3) {
			switch (USB_.INT_ST.byte & 0x3F) {
			case UIS_TOKEN_IN | 4: {

				USB_.UEP4_CTRL.UEP_T_RES = USB_MASK::NAK;
				USB_.UEP4_T_LEN.length = Dev_.IN(4);
				USB_.UEP4_CTRL.UEP_T_TOG ^= 1;
				if (USB_.UEP4_T_LEN.length > 0) {
					USB_.UEP4_CTRL.UEP_T_RES = USB_MASK::ACK;
				}
				break;
			}
			case UIS_TOKEN_IN | 3: {
				USB_.UEP3_CTRL.UEP_T_RES = USB_MASK::NAK;
				USB_.UEP3_T_LEN.length = Dev_.IN(3);
				USB_.UEP3_CTRL.UEP_T_TOG ^= 1;
				if (USB_.UEP3_T_LEN.length > 0) {
					USB_.UEP3_CTRL.UEP_T_RES = USB_MASK::ACK;
				}
				break;
			}
			case UIS_TOKEN_OUT | 2: {
				if (USB_.INT_FG.DEVICE.U_TOG_OK) {
					Dev_.OUT(2, USB_.RX_LEN.length);
				}
				USB_.UEP2_CTRL.UEP_R_TOG ^= 1;
				USB_.UEP3_CTRL.UEP_T_RES = USB_MASK::ACK;
				break;
			}
			case UIS_TOKEN_IN | 1: {
				USB_.UEP1_CTRL.UEP_T_TOG ^= 1;
				USB_.UEP1_CTRL.UEP_T_RES = USB_MASK::NAK;
				break;
			}
			case UIS_TOKEN_IN | 0: {
				PFIC_DisableIRQ(USB_IRQn);
				USB_.UEP0_CTRL.UEP_T_RES = USB_MASK::NAK;
				PFIC_EnableIRQ(USB_IRQn);
#if (printLog)
				Serial1.println("IN");
#endif
				switch (bRequest) {
				case GET_DESCRIPTOR: {
					uint16_t len = min(Dev_.RemainLength, MAX_PACKET_SIZE);
					memcpy(Dev_.getEpBuffer(0), Dev_.getExtendedBuffer(1), len);
					Dev_.RemainLength -= len;
					USB_.UEP0_T_LEN.length = len;
					if (Dev_.ExpectedZLP == 1 || len > 0) {
						PFIC_DisableIRQ(USB_IRQn);
						USB_.UEP0_CTRL.UEP_T_TOG ^= 1;
						USB_.UEP0_CTRL.UEP_T_RES = USB_MASK::ACK;
						PFIC_EnableIRQ(USB_IRQn);
					}
					else {
						PFIC_DisableIRQ(USB_IRQn);
						USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
						PFIC_EnableIRQ(USB_IRQn);
					}
					break;
				}
				case SET_ADDRESS: {
					USB_.DEV_AD.USB_ADDR = usb_addr;
#if (printLog)
					Serial1.print("ADDR = ");
					Serial1.println(usb_addr);
#endif
					need_serial_state_notify = 1;
					PFIC_DisableIRQ(USB_IRQn);
					USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
					PFIC_EnableIRQ(USB_IRQn);
					break;
				}
				default: {
					PFIC_DisableIRQ(USB_IRQn);
					USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_NAK;
					PFIC_EnableIRQ(USB_IRQn);
					break;
				}
				}
				break;
			}
			case UIS_TOKEN_OUT | 0: {
#if (printLog)
				Serial1.println("OUT");
				Serial1.println("");
#endif
				if (CDC_SET_LINE_CODING == bRequest)
				{
					memcpy((void*)&_usbLineInfo, Dev_.getEpBuffer(0), 7);
					USB_.UEP0_T_LEN.length = 0;
					PFIC_DisableIRQ(USB_IRQn);
					USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_NAK | UEP_T_RES_ACK;
					PFIC_EnableIRQ(USB_IRQn);
				}
				else {
					PFIC_DisableIRQ(USB_IRQn);
					USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_NAK | UEP_T_RES_NAK;
					PFIC_EnableIRQ(USB_IRQn);
				}
				break;
			}
			}
		}
		USB_.INT_FG.DEVICE.UIF_TRANSFER = 1;
		if (USB_.INT_ST.DEVICE.UIS_SETUP_ACT) {
			ReqType = SetupPack->bmRequestType;
			bRequest = SetupPack->bRequest;
			dType = SetupPack->wValueH;
			wLen = SetupPack->wLength;
			uint8_t len = 0;
			USB_.UEP0_CTRL.byte = RB_UEP_R_TOG | RB_UEP_T_TOG | UEP_R_RES_NAK | UEP_T_RES_NAK;
			Dev_.ExpectedZLP = 0;
			Dev_.RemainLength = 0;
			if ((ReqType & REQUEST_TYPE) == REQUEST_STANDARD) {
				uint16_t wValue = SetupPack->wValueL | (SetupPack->wValueH << 8);
#if (printLog)
				Serial1.print("TYPE: ");
				Serial1.println(bRequest);
#endif
				switch (bRequest) {
				case GET_DESCRIPTOR: {
					if (USB_DEVICE_DESCRIPTOR_TYPE == dType) {
#if (printLog)
						Serial1.println(": USB_DD");
#endif
						len = min(MAX_PACKET_SIZE, sizeof(USB_DD));
						len = min(len, wLen);
						memcpy(Dev_.getEpBuffer(0), &USB_DD, len);
						Dev_.ExpectedZLP = (sizeof(USB_DD) % MAX_PACKET_SIZE == 0) ? 1 : 0;
					}
					else if (USB_CONFIGURATION_DESCRIPTOR_TYPE == dType) {
#if (printLog)
						Serial1.println(": USB_CD");
#endif
						int descriptorLegth = 0;
						uint8_t interfaces = SendInterfaces(&descriptorLegth);
						ConfigDescriptor config = D_CONFIG((uint16_t)(descriptorLegth), interfaces);
						memcpy(Dev_.getExtendedBuffer(-1), &config, sizeof(config));
						len = min(MAX_PACKET_SIZE, descriptorLegth);
						len = min(len, wLen);
						memcpy(Dev_.getEpBuffer(0), Dev_.getExtendedBuffer(-1), len);
						if (wLen == 9) {
						}
						else {
							Dev_.ExpectedZLP = ((descriptorLegth) % MAX_PACKET_SIZE == 0) ? 1 : 0;
							Dev_.RemainLength = descriptorLegth - len;
						}
					}
					else if (USB_STRING_DESCRIPTOR_TYPE == dType) {
						switch (SetupPack->wValueL) {
						case 0: {
#if (printLog)
							Serial1.println(": Lang");
#endif
							memcpy(Dev_.getEpBuffer(0), &STRING_LANGUAGE, 4);
							len = 4;
							break;
						}
						case IMANUFACTURER: {
#if (printLog)
							Serial1.println(": Manu");
#endif
							len = USB_SendStringDescriptor(STRING_MANUFACTURER, strlen(USB_MANUFACTURER));
							break;
						}
						case IPRODUCT: {
#if (printLog)
							Serial1.println(": Prod");
#endif
							len = USB_SendStringDescriptor(STRING_PRODUCT, strlen(USB_PRODUCT));
							break;
						}
						case ISERIAL: {
#if (printLog)
							Serial1.println(": Serl");
#endif
#ifdef PLUGGABLE_USB_ENABLED
							char name[ISERIAL_MAX_LEN];
							PluggableUSB().getShortName(name);
							len = USB_SendStringDescriptor((uint8_t*)name, strlen(name));
#endif
							break;
						}
						}
						len = (len > wLen) ? wLen : len;
					}
					else {
#if (printLog)
						Serial1.println(": SUB Desc");
#endif
						int ret = 0;
#ifdef PLUGGABLE_USB_ENABLED
						ret = PluggableUSB().getDescriptor(*SetupPack);
#endif 
						if (ret > 0) {
							Dev_.ExpectedZLP = (ret % MAX_PACKET_SIZE == 0) ? 1 : 0;
							len = min(ret, MAX_PACKET_SIZE);
							memcpy(Dev_.getEpBuffer(0), Dev_.getExtendedBuffer(-1), len);
							Dev_.RemainLength = ret - len;
							//int len_to_send = min(len, wLen);
							//Dev_.ExpectedZLP = (len_to_send < maxLength) && (len_to_send % MAX_PACKET_SIZE == 0);
						}
						else {
							USB.UEP0_CTRL.UEP_T_RES = USB_MASK::STALL;
							USB.UEP0_CTRL.UEP_R_RES = USB_MASK::STALL;
						}
					}
					break;
				}
				case SET_DESCRIPTOR: { break; }
				case GET_CONFIGURATION: {
#if (printLog)
					Serial1.println(": g_CONF");
#endif
					Dev_.getEpBuffer(0)[0] = _usbConfiguration;
					len = 1;
					break;
				}
				case SET_CONFIGURATION: {
#if (printLog)
					Serial1.println(": s_CONF");
#endif
					if ((ReqType & REQUEST_RECIPIENT) == REQUEST_DEVICE) {
						InitEndpoints();
						_usbConfiguration = SetupPack->wValueL;
						len = 0;
					}
					break;
				}
				case GET_INTERFACE: { break; }
				case SET_INTERFACE: { break; }
				case CLEAR_FEATURE: {
#if (printLog)
					Serial1.println(": c_FEAT");
#endif
					if ((ReqType == (REQUEST_HOSTTODEVICE | REQUEST_STANDARD | REQUEST_DEVICE))
						&& (wValue == DEVICE_REMOTE_WAKEUP)) {
						_usbCurrentStatus &= ~FEATURE_REMOTE_WAKEUP_ENABLED;
						len = 0;
					}
					break;
				}
				case SET_FEATURE: {
#if (printLog)
					Serial1.println(": s_FEAT");
#endif
					if ((ReqType == (REQUEST_HOSTTODEVICE | REQUEST_STANDARD | REQUEST_DEVICE))
						&& (wValue == DEVICE_REMOTE_WAKEUP)) {
						_usbCurrentStatus |= FEATURE_REMOTE_WAKEUP_ENABLED;
						len = 0;
					}
					break;
				}
				case GET_STATUS: {
#if (printLog)
					Serial1.println(": g_STATUS");
#endif
					if (ReqType == (REQUEST_DEVICETOHOST | REQUEST_STANDARD | REQUEST_DEVICE)) {
						Dev_.getEpBuffer(0)[0] = _usbCurrentStatus;
						Dev_.getEpBuffer(0)[1] = 0x00;
					}
					else {
						Dev_.getEpBuffer(0)[0] = 0x00;
						Dev_.getEpBuffer(0)[1] = 0x00;
					}
					len = 2;
					break;
				}
				case SET_ADDRESS: {
#if (printLog)
					Serial1.println(": SET ADDR");
#endif
					usb_addr = SetupPack->wValueL & 0x7F;
					len = 0;
					break;
				}
				}
#if (printLog)
				Serial1.print("Setup Len:");
				Serial1.println(len);
#endif
				USB_.UEP0_T_LEN.length = len;
				USB_.UEP0_CTRL.UEP_T_RES = USB_MASK::ACK;				
			}
			else if ((ReqType & REQUEST_TYPE) == REQUEST_CLASS) {
#if (printLog)
				Serial1.println(": Class");
#endif
				ClassInterfaceRequest(*SetupPack);
			}
			
		}
		USB_.INT_FG.DEVICE.UIF_TRANSFER = 1;
	}	
	else if (USB_.INT_FG.DEVICE.UIF_BUS_RST) {
#if (printLog)
		Serial1.println(": Reset");
#endif
		USB_.DEV_AD.USB_ADDR = 0;
		Dev_.ResetDevEP();
		USB_.UEP0_CTRL.byte = UEP_R_RES_NAK | UEP_T_RES_NAK;
		USB_.INT_FG.DEVICE.UIF_BUS_RST = 1;
	}
}


USBDevice_ USBDevice(USB);

USBDevice_::USBDevice_(volatile USB_Module_t& eUSB) : USB_Base(eUSB),
RemainLength(0),
ExpectedZLP(0)
{
}
bool USBDevice_::configured() {
	 return _usbConfiguration;
}
void USBDevice_::attach() {
	
	assignBuffer(1, Ep1Buffer);
	assignBuffer(2, Ep2Buffer);
	assignBuffer(3, Ep3Buffer);
	InitEndpoints();
	AttachDevice();
}
void USBDevice_::detach() {

}
void USBDevice_::poll() {

}
bool USBDevice_::wakeupHost() {
	 return false;
}
bool USBDevice_::isSuspended() {
	 return x8_USB_MIS_ST.DEVICE.UMS_SUSPEND;
}