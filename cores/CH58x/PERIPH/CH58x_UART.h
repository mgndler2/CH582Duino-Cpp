#pragma once

#ifndef __CH58x_UART_H__
#define __CH58x_UART_H__
#include "CH58x_UART_SFR.h"
#include "CH58x_SYS.h"
#include "CH58x_IO_BUFFER.h"

namespace UART_MASK {
	enum FIFO_Trig {
		Level1,
		Level2,
		Level4,
		Level7
	};
	enum Parity_Mode {
		odd,
		even,
		mark,
		space,
		none
	};
	enum Word_Size {
		W5,
		W6,
		W7,
		W8
	};
	enum STOP_Bit {
		oneBit,
		twoBit
	};
}

class UART_Base {
public:
	UART_Base(volatile UART_Module_t& eUART);
	void set_BaudsRate(unsigned long baud);
	void Enable_FIFO(UART_MASK::FIFO_Trig level);
	void Disable_FIFO();
	void set_StopBit(UART_MASK::STOP_Bit Bits);
	void set_Parity(UART_MASK::Parity_Mode mode);
	void set_WordSize(UART_MASK::Word_Size size);
	void set_WordSize(uint8_t size);
	inline uint8_t get_IIR() {
		return UART_.IIR.IIR_INT_MASK;
	}
	void Recv(uint8_t Part);
	uint8_t Read(uint8_t Part);
protected:
	volatile UART_Module_t& UART_;
	static IO_Buffer Buffer;
private:
	
};

#endif // !__CH58x_UART_H__
