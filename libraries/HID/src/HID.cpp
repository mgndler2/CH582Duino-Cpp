/*
   Copyright (c) 2015, Arduino LLC
   Original code (pre-library): Copyright (c) 2011, Peter Barrett

   Permission to use, copy, modify, and/or distribute this software for
   any purpose with or without fee is hereby granted, provided that the
   above copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
   BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
   OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
   WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
   ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
   SOFTWARE.
 */

#include "HID.h"

HID_& HID()
{
	static HID_ obj;
	return obj;
}

int HID_::getInterface(uint8_t* interfaceCount, int offset)
{
	my_interface = *interfaceCount;
	HIDDescriptor hidInterface = {
		D_INTERFACE(*interfaceCount/*pluggedInterface*/, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, /*HID_SUBCLASS_BOOT_INTERFACE*/HID_SUBCLASS_NONE, /*HID_PROTOCOL_MOUSE*/HID_PROTOCOL_NONE),
		D_HIDREPORT(descriptorSize),
		D_ENDPOINT(USB_ENDPOINT_IN(4), USB_ENDPOINT_TYPE_INTERRUPT, 0x40, 0x01)
	};
	*interfaceCount += 1; // uses 1
	return USB_FillBuffer(offset, &hidInterface, sizeof(hidInterface));
}

int HID_::getDescriptor(USBSetup& setup)
{
	
	// Check if this is a HID Class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex contains the interface number
	if (setup.wIndex != my_interface) { return 0; }
	int total = 0;
	HIDSubDescriptor* node;
	for (node = rootNode; node; node = node->next) {
		int res = USB_FillBuffer(total, node->data, node->length);
		if (res == -1)
			return -1;
		total += res;
	}

	// Reset the protocol on reenumeration. Normally the host should not assume the state of the protocol
	// due to the USB specs, but Windows and Linux just assumes its in report mode.
	protocol = HID_REPORT_PROTOCOL;

	return total;
}

uint8_t HID_::getShortName(char* name)
{
	name[0] = 'H';
	name[1] = 'I';
	name[2] = 'D';
	name[3] = 'A' + (descriptorSize & 0x0F);
	name[4] = 'A' + ((descriptorSize >> 4) & 0x0F);
	return 0;
}

void HID_::AppendDescriptor(HIDSubDescriptor* node)
{
	if (!rootNode) {
		rootNode = node;
	}
	else {
		HIDSubDescriptor* current = rootNode;
		while (current->next) {
			current = current->next;
		}
		current->next = node;
	}
	descriptorSize += node->length;
}

int HID_::SendReport(uint8_t id, const void* data, int len)
{
	uint8_t b[16];
	b[0] = id;
	memcpy(&b[1], data, len);	
	
	auto ret = USB_Send(4, &b, len+1);	
	
	return ret;
}

bool HID_::setup(USBSetup& setup)
{
	//if (pluggedInterface != setup.wIndex) {
		//return false;
	//}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;
	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == HID_GET_REPORT) {
			// TODO: HID_GetReport();
			return true;
		}
		if (request == HID_GET_PROTOCOL) {
			// TODO: Send8(protocol);
			return true;
		}
		if (request == HID_GET_IDLE) {
			// TODO: Send8(idle);
		}
	}

	if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE)
	{
		if (request == HID_SET_PROTOCOL) {
			// The USB Host tells us if we are in boot or report mode.
			// This only works with a real boot compatible device.
			protocol = setup.wValueL;
			x8_UEP0_T_LEN.length = 0;
			PFIC_DisableIRQ(USB_IRQn);
			x8_UEP0_CTRL.UEP_T_RES = USB_MASK::ACK;
			PFIC_EnableIRQ(USB_IRQn);
			return true;
		}
		if (request == HID_SET_IDLE) {
			idle = setup.wValueL;
			x8_UEP0_T_LEN.length = 0;
			PFIC_DisableIRQ(USB_IRQn);
			x8_UEP0_CTRL.UEP_T_RES = USB_MASK::ACK;
			PFIC_EnableIRQ(USB_IRQn);			
			return true;
		}
		if (request == HID_SET_REPORT)
		{
			//uint8_t reportID = setup.wValueL;
			//uint16_t length = setup.wLength;
			//uint8_t data[length];
			// Make sure to not read more data than USB_EP_SIZE.
			// You can read multiple times through a loop.
			// The first byte (may!) contain the reportID on a multreport.
			//USB_RecvControl(data, length);
		}
	}

	return false;
}

HID_::HID_(void) : PluggableUSBModule(1, 1, epType),
rootNode(NULL), descriptorSize(0),
protocol(HID_REPORT_PROTOCOL), idle(1)
{
	Type = USBModuleType::USB_HID;
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int HID_::begin(void)
{
	return 0;
}