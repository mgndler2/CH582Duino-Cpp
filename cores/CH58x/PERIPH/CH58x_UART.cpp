#include "CH58x_UART.h"
#include "CDC.h"
IO_Buffer UART_Base::Buffer;

void UART_Base::Recv(uint8_t Part) {
	int8_t len = 0;
	uint8_t data[16];
	while (UART_.LSR.LSR_DATA_RDY) {
		data[len] = UART_.RBR.RBR;		
		len++;
	}	
	Buffer << push_data(Part, data, len, 1);
}

uint8_t UART_Base::Read(uint8_t Part) {
	uint8_t data[1];
	int8_t len = 1;
	Buffer >> pull_data(Part, data, len, 1);
	return *data;
}

void UART_Base::set_StopBit(UART_MASK::STOP_Bit Bits) {
	UART_.LCR.LCR_STOP_BIT = Bits;
}

void UART_Base::set_Parity(UART_MASK::Parity_Mode mode) {
	UART_.LCR.LCR_PAR_MOD = mode & 0x03;
	UART_.LCR.LCR_PAR_EN = !((mode >> 2) & 0x01);
}

void UART_Base::set_WordSize(UART_MASK::Word_Size size) {
	UART_.LCR.LCR_WORD_SZ = size;
}

void UART_Base::set_WordSize(uint8_t size) {
	UART_.LCR.LCR_WORD_SZ = size;
}

void UART_Base::Enable_FIFO(UART_MASK::FIFO_Trig level) {
	UART_.FCR.FCR_RX_FIFO_CLR = 1;
	UART_.FCR.FCR_TX_FIFO_CLR = 1;
	UART_.FCR.FCR_FIFO_TRIG = level;
	UART_.FCR.FCR_FIFO_EN = 1;
}

void UART_Base::Disable_FIFO() {
	UART_.FCR.FCR_RX_FIFO_CLR = 1;
	UART_.FCR.FCR_TX_FIFO_CLR = 1;
	UART_.FCR.FCR_FIFO_TRIG = 0;
	UART_.FCR.FCR_FIFO_EN = 0;
}

void UART_Base::set_BaudsRate(unsigned long baud) {
	UART_.DL.DL = CPU_CLK.GetSysClock() * 2 / baud / 16; UART_.DIV.DIV = 1;
}

UART_Base::UART_Base(volatile UART_Module_t& eUART) :
	UART_(eUART)
{

}