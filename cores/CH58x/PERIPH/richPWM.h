#ifndef __RichPWM_H__
#define __RichPWM_H__
#include "CH58x_TMR.h"

template<int TMR_NUM>
class RichPWM : public TMR_Base<TMR_NUM> {
public:
	RichPWM(volatile TMR_Module_t& mod) :
		TMR_Base<TMR_NUM>(mod)
	{
	}
	void begin(uint8_t Polar = 0, uint8_t Repeat = 0) {
		this->InitialAsTimer(1, Polar, Repeat);
	}
	void setOut(uint32_t val, uint8_t Cycling = false) { 
		OutputEnable(1);
		_value = val;
		FIFO = _value;
		if (Cycling) {
			AttachInterrupt(5, Reload);
		}		
	}
	using AttachInterrupt(uint8_t Type, void(*Func)(void));
	using DettachInterrupt(uint8_t Type);
	using Start();
	using Stop();
	using ClearAll();
	using OutputEnable(uint8_t EN);
	using setPeriod(uint32_t Count);
#if (TMR_NUM == 1 || TMR_NUM == 2)
	using EnableDMA(uint8_t EN, uint8_t loop);
	using bindDMABuffer(void* buf, uint16_t len);
#endif
	using FIFO;
	using Length;
	using Count;
private:
	void Reload() {
		while (Length < 8) {
			FIFO = _value;
		}
	}
	uint32_t _value;
};

#endif // !__RichPWM_H__
