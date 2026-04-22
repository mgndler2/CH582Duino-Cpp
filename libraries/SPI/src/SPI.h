#ifndef __SPI_H__
#define __SPI_H__
#include "CH58x_SPI.h"

#define SPI_MODE0 0x00
#define SPI_MODE3 0x01

#ifndef LSBFIRST
#define LSBFIRST 1
#endif
#ifndef MSBFIRST
#define MSBFIRST 0
#endif

class SPISettings {
public:
	SPISettings(uint32_t Clock, uint8_t bitOrder, uint8_t Mode) :
		_Clock(Clock), _bitOrder(bitOrder), _Mode(Mode)
	{
	}
	SPISettings() :
		_Clock(1000000U), _bitOrder(MSBFIRST), _Mode(SPI_MODE0)
	{
	}
private:
	uint32_t _Clock;
	uint8_t _bitOrder;
	uint8_t _Mode;
	template <int N>
	friend class SPIClass;
};


template <int SPI_NUM> 
class SPIClass : SPI_Base<SPI_NUM> {
public:
	SPIClass(volatile SPI_Module_t& mod) :
		SPI_Base<SPI_NUM>(mod)
	{
	}
	void beginTransaction(SPISettings settings) {
#if(SPI_NUM == 0)
		//interruptSave = PFIC_GetStatusIRQ(SPI0_IRQn);
		//PFIC_DisableIRQ(SPI0_IRQn);
#elif(SPI_NUM == 1)
		//interruptSave = PFIC_GetStatusIRQ(PWMX_SPI1_IRQn);
		//PFIC_DisableIRQ(PWMX_SPI1_IRQn);
#endif		
		pinMode(_SCK, OUTPUT);
		digitalWrite(_SWCS, LOW);
		this->InitialAsMaster(settings._Clock, settings._bitOrder, settings._Mode);
		
	}

	void endTransaction(void) {
#if(SPI_NUM == 0)
		//if (interruptSave)
			//PFIC_EnableIRQ(SPI0_IRQn);
#elif(SPI_NUM == 1)
		//if (interruptSave)
			//PFIC_EnableIRQ(PWMX_SPI1_IRQn);
#endif
		pinMode(_SCK, INPUT);
		digitalWrite(_SWCS, HIGH);
	}
	uint8_t transfer(uint8_t data) {
		uint8_t buff = data;
		transfer(&buff, 1);
		return buff;
	}
	uint16_t transfer(uint16_t data) {
		uint16_t buff = data;
		transfer(&buff, 1);
		return buff;
	}
	void setCS(uint8_t CS) {
		_SWCS = CS;
		digitalWrite(CS, HIGH);
		pinMode(CS, OUTPUT);
	}
	void setSCK(uint8_t SCK) {
		if (SCK == 13) {
			x16_PIN_ALTERNATE.PIN_SPI0 = 0;
		}
		else if (SCK == 29) {
			x16_PIN_ALTERNATE.PIN_SPI0 = 1;
		}
		_SCK = SCK;
		pinMode(SCK, INPUT);
	}
	void setTX(uint8_t TX) {
		pinMode(TX, OUTPUT);
	}
	void setRX(uint8_t RX) {
		pinMode(RX, INPUT);
	}
	using SPI_Base<SPI_NUM>::transfer;
private:
	uint32_t interruptSave;
	uint8_t _SWCS;
	uint8_t _SCK;
	//uint8_t SlaveMode;
};
extern SPIClass<0> WCHSPI;

#endif // __SPI_H__
