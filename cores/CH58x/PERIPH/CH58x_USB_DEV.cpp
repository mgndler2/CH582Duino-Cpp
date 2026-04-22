#include "CH58x_USB_DEV.h"
#include "HardwareSerial.h"

int USB_Base::Recv(uint8_t ep, void* data, int8_t len) {

	Buffer >> pull_data(ep, (uint8_t*)data, len, 1);
	return len;
}

int USB_Base::OUT(uint8_t ep, int8_t len) {

	Buffer << push_data(ep, getEpBuffer(ep), len, 1);
	return len;
}

int USB_Base::Send(uint8_t ep, const void* data, int8_t len) {
	
	Buffer << push_data(ep, (uint8_t*)data, len, 0);
	return len;
}

int USB_Base::IN(uint8_t ep) {

	int8_t len = 0;

	Buffer >> pull_data(ep, getEpBuffer(ep), len, 0);
	return len;
}

uint8_t* USB_Base::getExtendedBuffer(int8_t motion) {
	static uint8_t step = 0;
	//uint8_t maxstep = (_BufferLength / MAX_PACKET_SIZE) - 1;
	switch (motion) {
	case -1:
		step = 0;
		break;
	case 0:
		break;
	case 1:
		step++;
		if (step > 4) step = 0;
		break;
	}
	return Buffer.getExtendedBuffer() + (step * MAX_PACKET_SIZE);
}

uint8_t* USB_Base::getEpBuffer(uint8_t num) {
	return EndPoint[num].EpBuffer;
}

void USB_Base::AttachDevice() {
	Module.USB_CTRL.byte = 0;
	_nop(); _nop();

	assignBuffer(0, const_cast<uint8_t*>(Ep0Buffer));
	EndPoint[0]._CTRL->UEP_R_RES = USB_MASK::ACK; EndPoint[0]._CTRL->UEP_T_RES = USB_MASK::NAK;
	Module.DEV_AD.byte = 0x00;

	Module.UDEV_CTRL.byte = RB_UD_PD_DIS;
	Module.USB_CTRL.byte = RB_UC_DEV_PU_EN | RB_UC_DMA_EN | RB_UC_INT_BUSY;
	Module.UDEV_CTRL.byte |= RB_UD_PORT_EN;

	Module.INT_FG.byte = 0xFF;
	Module.INT_EN.byte = RB_UIE_TRANSFER | RB_UIE_BUS_RST;

	R16_PIN_ANALOG_IE |= RB_PIN_USB_IE;
	PFIC_EnableIRQ(USB_IRQn);
}

_usb_errType_t USB_Base::InitialDevEP(int EP, uint8_t Type) {
	using namespace USB_MASK;
	_usb_errType_t err = -1;
	/*if ((Type == 0b100 || Type == 0b101) && (EP < 1 || EP > 3)) {
		err = Does_Not_Support_Bulk;
		return 0;
	}*/
	uint8_t EP_Type = Type & 0b110;
	uint8_t rx_tx;
	bool double_buffer = 0;
	uint8_t res = 1;
	if (EP_Type == 0b000) {
		rx_tx = 0b11;
		double_buffer = 0;
		res = NAK;
	}
	else {
		if (Type & 0b001) {
			rx_tx = 0b01;
			res = NAK;
		}
		else {
			rx_tx = 0b10;
			res = ACK;
		}
		if (EP_Type == 0b100) {
			//double_buffer = 1;
		}
		else {
			double_buffer = 0;
		}
		if (EP_Type == 0b110) {
			res = No_Response;
		}
	}
	switch (EP)
	{
	case 0:
		Module.UEP0_CTRL.byte = 0;
		Module.UEP0_CTRL.UEP_R_RES = res;
		Module.UEP0_CTRL.UEP_T_RES = res;
		break;
	case 1:
		Module.UEP4_1_MOD.UEP1.BUF_MOD = double_buffer;
		Module.UEP4_1_MOD.UEP1.RX_TX = rx_tx;
		Module.UEP1_CTRL.byte = 0;
		if (EP_Type != 0b110) {
			//Module.xR8_UEP1_CTRL.UEP_AUTO_TOG = 1;
		}
		if (rx_tx == 0b10) {
			Module.UEP1_CTRL.UEP_R_RES = res;
		}
		else if (rx_tx == 0b01) {
			Module.UEP1_CTRL.UEP_T_RES = res;
		}
		break;
	case 2:
		Module.UEP2_3_MOD.UEP2.BUF_MOD = double_buffer;
		Module.UEP2_3_MOD.UEP2.RX_TX = rx_tx;
		Module.UEP2_CTRL.byte = 0;
		if (EP_Type != 0b110) {
			//Module.xR8_UEP2_CTRL.UEP_AUTO_TOG = 1;
		}
		if (rx_tx == 0b10) {
			Module.UEP2_CTRL.UEP_R_RES = res;
		}
		else if (rx_tx == 0b01) {
			Module.UEP2_CTRL.UEP_T_RES = res;
		}
		break;
	case 3:
		Module.UEP2_3_MOD.UEP3.BUF_MOD = double_buffer;
		Module.UEP2_3_MOD.UEP3.RX_TX = rx_tx;
		Module.UEP3_CTRL.byte = 0;
		if (EP_Type != 0b110) {
			//Module.xR8_UEP3_CTRL.UEP_AUTO_TOG = 1;
		}
		if (rx_tx == 0b10) {
			Module.UEP3_CTRL.UEP_R_RES = res;
		}
		else if (rx_tx == 0b01) {
			Module.UEP3_CTRL.UEP_T_RES = res;
		}
		break;
	case 4:
		Module.UEP4_1_MOD.UEP4.RX_TX = rx_tx;
		Module.UEP4_CTRL.byte = 0;
		if (EP_Type != 0b110) {
			//Module.xR8_UEP4_CTRL.UEP_AUTO_TOG = 1;
		}
		if (rx_tx == 0b10) {
			Module.UEP4_CTRL.UEP_R_RES = res;
		}
		else if (rx_tx == 0b01) {
			Module.UEP4_CTRL.UEP_T_RES = res;
		}
		break;
	default:
		return err = EP_Not_set;
		break;
	}
	return err;
}

bool USB_Base::assignBuffer(int EP, uint8_t Buffer[]) {
	EndPoint[EP].EpBuffer = Buffer;
	switch (EP) {
	case 0:
		Module.UEP0_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		EndPoint[4].EpBuffer = &Buffer[64];
		break;
	case 1:
		Module.UEP1_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	case 2:
		Module.UEP2_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	case 3:
		Module.UEP3_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	case 5:
		Module.UEP5_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	case 6:
		Module.UEP6_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	case 7:
		Module.UEP7_DMA.DMA_addr = (uint16_t)(uintptr_t)Buffer;
		break;
	}
	return true;
}

void USB_Base::ResetDevEP() {
	Module.UEP4_1_MOD.byte = 0;
	Module.UEP2_3_MOD.byte = 0;
	Module.UEP1_CTRL.byte = 0x0A;
	Module.UEP2_CTRL.byte = 0x0A;
	Module.UEP3_CTRL.byte = 0x0A;
	Module.UEP4_CTRL.byte = 0x0A;
	Module.UEP5_CTRL.byte = 0x0A;
	Module.UEP6_CTRL.byte = 0x0A;
	Module.UEP7_CTRL.byte = 0x0A;
}

USB_Base::USB_Base(volatile USB_Module_t& eUSB)
	:Module(eUSB) {
	
}

USB_Base::~USB_Base()
{
}