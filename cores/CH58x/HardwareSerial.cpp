#include "HardwareSerial.h"
#include "CDC.h"

HWSerial::HWSerial(pin_size_t tx, pin_size_t rx, int8_t moduleNum,volatile UART_Module_t& mod) :
	_running(false),
	_part(moduleNum),
	_tx(tx), _rx(rx),
	_baud(9600), _peek(-1),
	UART_Base(mod) {

}

bool HWSerial::setPinout(pin_size_t tx, pin_size_t rx)
{
	_tx = tx;
	_rx = rx;
	//digitalWrite(_tx, HIGH);
	//pinMode(_rx, INPUT_PULLUP);
	//pinMode(_tx, OUTPUT);
	return true;
}

void HWSerial::begin(unsigned long baud, uint16_t config)
{
	using namespace UART_MASK;
	digitalWrite(_tx, HIGH);
	pinMode(_rx, INPUT_PULLUP);
	pinMode(_tx, OUTPUT);
	_baud = baud;
	set_BaudsRate(baud);
	_nop();
	Enable_FIFO(FIFO_Trig::Level1);
	
	set_WordSize((config >> 8) - 1);
	switch (config & SERIAL_PARITY_MASK) {
	case SERIAL_PARITY_ODD:
		set_Parity(Parity_Mode::odd);
		break;
	case SERIAL_PARITY_EVEN:
		set_Parity(Parity_Mode::even);
		break;
	case SERIAL_PARITY_MARK:
		set_Parity(Parity_Mode::mark);
		break;
	case SERIAL_PARITY_SPACE:
		set_Parity(Parity_Mode::space);
		break;
	case SERIAL_PARITY_NONE:
		set_Parity(Parity_Mode::none);
		break;
	}    
	switch (config & SERIAL_STOP_BIT_MASK) {
	case SERIAL_STOP_BIT_1:
		set_StopBit(STOP_Bit::oneBit);
		break;
	case SERIAL_STOP_BIT_2:
		set_StopBit(STOP_Bit::twoBit);
		break;
	}

	UART_.IER.IER_TXD_EN = 1;
	UART_.IER.IER_RECV_RDY = 1;
	UART_.MCR.MCR_INT_OE = 1;
	PFIC_EnableIRQ(UART1_IRQn);
	_running = true;
}

void HWSerial::end()
{
	_running = false;
}

int HWSerial::peek()
{
	return _peek;
}

int HWSerial::read()
{
	return Read(_part);
}

int HWSerial::available()
{
	return Buffer.Available(_part);
}

int HWSerial::availableForWrite()
{
	if (!_running)
	{
		return 0;
	}
	return 8 - UART_.TFC.TFC;
}

void HWSerial::flush()
{

}

size_t HWSerial::write(uint8_t c)
{
	if (!_running)
	{
		return 0;
	}
	while (R8_UART1_TFC >= UART_FIFO_SIZE);
	UART_.THR.THR = c;
	return 1;
}

size_t HWSerial::write(const uint8_t* p, size_t len)
{
	if (!_running)
	{
		return 0;
	}
	size_t cnt = len;
	while (cnt)
	{
		while (x8_UART1_TFC.TFC < UART_FIFO_SIZE && cnt)
		{
			x8_UART1_THR.THR = *p;
			cnt--;
			p++;
		}
	}
	return len;
}

HWSerial::operator bool()
{
	return _running;
}

HWSerial Serial1(PIN_SERIAL1_TX, PIN_SERIAL1_RX, 1, UART1);

extern "C"
__INTERRUPT
void UART1_IRQHandler(void) {
	switch (Serial1.get_IIR()) {
	case 0b0100: {
		Serial1.Recv(Serial1._part);
		break;
	}
	case 0b1100: {
		Serial1.Recv(Serial1._part);
		break;
	}
	case 0b0110: {
		break;
	}
	case 0b0010: {
		break;
	}
	case 0b1110: {
		break;
	}
	case 0b0000:
	case 0b0001: {
		break;
	}
	}
}