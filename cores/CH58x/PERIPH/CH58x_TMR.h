#pragma once

#ifndef __CH58x_TMR_H__
#define __CH58x_TMR_H__
#include "CH58x_TMR_SFR.h"
#include "CH58x_SYS.h"

namespace ns_TMR {
	enum INTType
	{
		CYC_END,
		DATA_ACT,
		FIFO_HF,
		DMA_END,
		FIFO_OV
	};

	void (*TMR_Int_Func[4][5])(void);
}

template<int TMR_NUM>
class TMR_Base {
public:
	TMR_Base(volatile TMR_Module_t& mod) :
		_TMR(mod), FIFO(mod.FIFO.DATA),
		Length(mod.FIFO_COUNT.byte), Count(mod.COUNT.COUNT)
	{
		using namespace ns_TMR;
		for (int i = 0; i < 5;i++) {
			TMR_Int_Func[TMR_NUM][i] = nullptr;
		}
	}
	void InitialAsTimer(uint8_t Output = 0, uint8_t Polar = 0, uint8_t Repeat = 0);
	void InitialAsInput(uint8_t Mode, uint8_t Edge);
	void AttachInterrupt(uint8_t Type, void(*Func)(void));
	void DettachInterrupt(uint8_t Type);
	inline void Start() { _TMR.CTRL_MOD.CNT.TMR_COUNT_EN = 1; }
	inline void Stop() { _TMR.CTRL_MOD.CNT.TMR_COUNT_EN = 1; }
	inline void ClearAll() { _TMR.CTRL_MOD.CNT.TMR_ALL_CLEAR = 1; }
	void OutputEnable(uint8_t EN) { _TMR.CTRL_MOD.PWM.TMR_OUT_EN = EN; }
	void setPeriod(uint32_t Count) { _TMR.CNT_END.DATA = Count; }
#if (TMR_NUM == 1 || TMR_NUM == 2)
	void EnableDMA(uint8_t EN, uint8_t loop);
	void bindDMABuffer(void* buf, uint16_t len);
#endif
	volatile uint32_t& FIFO;
	volatile uint8_t& Length;
	volatile uint32_t& Count;
private:
	volatile TMR_Module_t& _TMR;
};

template class TMR_Base<0>;
template class TMR_Base<1>;
template class TMR_Base<2>;
template class TMR_Base<3>;

#endif // !__CH58x_TMR_H__
