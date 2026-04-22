#pragma once

#ifndef __CH58x_SPI_H__
#define __CH58x_SPI_H__
#include "Arduino.h"
#include "CH58x_SPI_SFR.h"
#include "CH58x_SYS.h"

template<int SPI_NUM>
class SPI_Base {
public:
	SPI_Base(volatile SPI_Module_t& mod) :
		_SPI(mod) {

	}

	void InitialAsMaster(uint32_t Clock, uint8_t bitOrder, uint8_t Mode) {
		_SPI.SPI_MOD.SPI_ALL_CLEAR = 1;
		uint16_t div = CPU_CLK.GetSysClock() / Clock;
		_SPI.CLOCK_DIV.DIV = div;
		_SPI.SPI_CFG.byte = 0b00010000;
		set_Bit_Order(bitOrder);
		_SPI.SPI_MOD.byte = 0b01100000;
		_SPI.SPI_MOD.SPI_MST_SCK_MOD = Mode;
	}	
#if (SPI_NUM == 0)
	void InitialAsSlave(uint8_t bitOrder, uint8_t Mode) {
		_SPI.SPI_MOD.SPI_ALL_CLEAR = 1;
		_SPI.SPI_CFG.byte = 0b00010000;
		set_Bit_Order(bitOrder);
		_SPI.SPI_MOD.byte = 0b10010001;
		_SPI.SPI_MOD.SPI_MST_SCK_MOD = Mode;
	}
#endif
	void transfer(void* data, uint32_t len);
	void sendViaFIFO(void* data, uint16_t len);
	void recvViaFIFO(void* data, uint16_t len);
	void sendViaDMA(void* data, uint16_t len);
	void recvViaDMA(void* data, uint16_t len);
private:
	volatile SPI_Module_t& _SPI;
	void set_Clock_div(uint8_t div) {
		if (div <= 2) {
			div = 2;
			_SPI.SPI_CFG.SPI_MST_DLY_EN = 1;
		}
		else {
			_SPI.SPI_CFG.SPI_MST_DLY_EN = 0;
		}
		_SPI.CLOCK_DIV.DIV = div;
	}
	inline void set_Bit_Order(uint8_t BitOrder) {
		_SPI.SPI_CFG.SPI_BIT_ORDER = BitOrder;
	}
};

template class SPI_Base<0>;

#endif // !__CH58x_SPI_H__
