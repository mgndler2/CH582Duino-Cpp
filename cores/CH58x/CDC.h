#pragma once

#ifndef __CDC_H__
#define __CDC_H__

#include <Arduino.h>
#include "PluggableUSB.h"
#include "USBAPI.h"
#include "USBCore.h"
typedef struct
{
	u32	dwDTERate;
	u8	bCharFormat;
	u8 	bParityType;
	u8 	bDataBits;
	u8	lineState;
} LineInfo;
extern volatile LineInfo _usbLineInfo;
extern uint8_t serial_state_notify[];
extern bool need_serial_state_notify;


class CDC_ : public PluggableUSBModule {
public:
	CDC_();
	
protected:
	int getInterface(uint8_t* interfaceCount, int offset) override;
	int getDescriptor(USBSetup& setup) override;
	bool setup(USBSetup& setup) override;
	uint8_t getShortName(char* name) override;
private:
	unsigned int epType[3];
};

CDC_& CDC();

#endif // !__CDC_H___