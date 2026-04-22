/*
  PluggableUSB.cpp
  Copyright (c) 2015 Arduino LLC

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "PluggableUSB.h"
#include "USBCore.h"
extern uint8_t _initEndpoints[];

int PluggableUSB_::getInterface(uint8_t* interfaceCount)
{
	int sent = 9;
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		int res = node->getInterface(interfaceCount, sent);
		if (res < 0)
			return -1;
		sent += res;
	}
	return sent;
}

int PluggableUSB_::getDescriptor(USBSetup& setup)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		int ret = node->getDescriptor(setup);
		// ret!=0 -> request has been processed
		if (ret)
			return ret;
	}
	return 0;
}

void PluggableUSB_::getShortName(char *iSerialNum)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		iSerialNum += node->getShortName(iSerialNum);
	}
	*iSerialNum = 0;
}

bool PluggableUSB_::setup(USBSetup& setup)
{
	PluggableUSBModule* node;
	for (node = rootNode; node; node = node->next) {
		if (node->setup(setup)) {
			return true;
		}
	}
	return false;
}
bool PluggableUSB_::plug(PluggableUSBModule* node)
{
	if ((lastEp + node->numEndpoints) > USB_ENDPOINTS) {
		return false;
	}

	// 先設定 node 的 interface & endpoint
	node->pluggedInterface = lastIf;
	node->pluggedEndpoint = lastEp;
	lastIf += node->numInterfaces;
	for (uint8_t i = 1; i < node->numEndpoints; i++) {
		_initEndpoints[lastEp] = node->endpointType[i];
		lastEp++;
	}

	// 特殊處理 CDC，要放到 HID 前面
	if (node->Type == USB_CDC) {
		if (!rootNode) {
			rootNode = node;
		}
		else {
			// 找第一個 HID
			PluggableUSBModule* prev = nullptr;
			PluggableUSBModule* curr = rootNode;
			while (curr && curr->Type != USB_HID) {
				prev = curr;
				curr = curr->next;
			}

			if (!prev) {
				// HID 在最前面或不存在，CDC 放最前面
				node->next = rootNode;
				rootNode = node;
			}
			else {
				// 插入 prev 和 curr 之間
				prev->next = node;
				node->next = curr;
			}
		}
	}
	else {
		// 一般 append 到尾巴
		if (!rootNode) {
			rootNode = node;
		}
		else {
			PluggableUSBModule* current = rootNode;
			while (current->next) current = current->next;
			current->next = node;
		}
	}

	return true;
}
/*bool PluggableUSB_::plug(PluggableUSBModule* node)
{
	if ((lastEp + node->numEndpoints) > USB_ENDPOINTS) {
		return false;
	}

	if (!rootNode) {
		rootNode = node;
	} else {
		PluggableUSBModule *current = rootNode;
		while (current->next) {
			current = current->next;
		}
		current->next = node;
	}

	node->pluggedInterface = lastIf;
	node->pluggedEndpoint = lastEp;
	lastIf += node->numInterfaces;
	for (uint8_t i = 1; i < node->numEndpoints; i++) {
		_initEndpoints[lastEp] = node->endpointType[i];
		lastEp++;
	}
	return true;
	// restart USB layer???
}*/

PluggableUSB_& PluggableUSB()
{
	static PluggableUSB_ obj;
	return obj;
}

PluggableUSB_::PluggableUSB_() : lastIf(0),
lastEp(0),
rootNode(NULL)
{
}