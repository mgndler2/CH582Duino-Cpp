#include "CH58x_TMR.h"

template<int TMR_NUM>
void TMR_Base<TMR_NUM>::InitialAsTimer(uint8_t Output, uint8_t Polar, uint8_t Repeat) {
	ClearAll();
	_TMR.CTRL_MOD.byte = (Repeat << 6) | (Polar << 4) | (Output << 3);
}

template<int TMR_NUM>
void TMR_Base<TMR_NUM>::InitialAsInput(uint8_t Mode, uint8_t Edge) {
	ClearAll();
	_TMR.CTRL_MOD.byte = (Edge << 6) | (Mode << 4) | 1;
}

template<int TMR_NUM>
void TMR_Base<TMR_NUM>::AttachInterrupt(uint8_t Type, void(*Func)(void)) {
	using namespace ns_TMR;
	switch (Type) {
	case 0:
	{
		TMR_Int_Func[TMR_NUM][0] = Func;
		_TMR.INTER_EN.TMR_IE_CYC_END = 1;
		break;
	}
	case 1:
	{
		TMR_Int_Func[TMR_NUM][1] = Func;
		_TMR.INTER_EN.TMR_IE_DATA_ACT = 1;
		break;
	}
	case 2:
	{
		TMR_Int_Func[TMR_NUM][2] = Func;
		_TMR.INTER_EN.TMR_IE_FIFO_HF = 1;
		break;
	}
#if (TMR_NUM == 1 || TMR_NUM == 2)
	case 3:
	{
		TMR_Int_Func[TMR_NUM][3] = Func;
		_TMR.INTER_EN.TMR_IE_DMA_END = 1;
		break;
	}
#endif
	case 4:
	{
		TMR_Int_Func[TMR_NUM][4] = Func;
		_TMR.INTER_EN.TMR_IE_FIFO_OV = 1;
		break;
	}
	}
	if (_TMR.INTER_EN.byte) {
#if (TMR_NUM == 0)
		PFIC_EnableIRQ(TMR0_IRQn);
#elif (TMR_NUM == 1)
		PFIC_EnableIRQ(TMR1_IRQn);
#elif (TMR_NUM == 2)
		PFIC_EnableIRQ(TMR2_IRQn);
#elif (TMR_NUM == 3)
		PFIC_EnableIRQ(TMR3_IRQn);
#endif
	}
}

template<int TMR_NUM>
void TMR_Base<TMR_NUM>::DettachInterrupt(uint8_t Type) {
	using namespace ns_TMR;
	switch (Type) {
	case 0:
	{
		TMR_Int_Func[TMR_NUM][0] = nullptr;
		_TMR.INTER_EN.TMR_IE_CYC_END = 0;
		break;
	}
	case 1:
	{
		TMR_Int_Func[TMR_NUM][1] = nullptr;
		_TMR.INTER_EN.TMR_IE_DATA_ACT = 0;
		break;
	}
	case 2:
	{
		TMR_Int_Func[TMR_NUM][2] = nullptr;
		_TMR.INTER_EN.TMR_IE_FIFO_HF = 0;
		break;
	}
#if (TMR_NUM == 1 || TMR_NUM == 2)
	case 3:
	{
		TMR_Int_Func[TMR_NUM][3] = nullptr;
		_TMR.INTER_EN.TMR_IE_DMA_END = 0;
		break;
	}
#endif
	case 4:
	{
		TMR_Int_Func[TMR_NUM][4] = nullptr;
		_TMR.INTER_EN.TMR_IE_FIFO_OV = 0;
		break;
	}
	}
	if (_TMR.INTER_EN.byte == 0) {
#if (TMR_NUM == 0)
		PFIC_DisableIRQ(TMR0_IRQn);
#elif (TMR_NUM == 1)
		PFIC_DisableIRQ(TMR1_IRQn);
#elif (TMR_NUM == 2)
		PFIC_DisableIRQ(TMR2_IRQn);
#elif (TMR_NUM == 3)
		PFIC_DisableIRQ(TMR3_IRQn);
#endif
	}
}
#if (TMR_NUM == 1 || TMR_NUM == 2)
template<int TMR_NUM>
void TMR_Base<TMR_NUM>::EnableDMA(uint8_t EN, uint8_t loop)
{ 
	_TMR.CTRL_DMA.byte = (loop << 2) | EN; 
}
template<int TMR_NUM>
void TMR_Base<TMR_NUM>::bindDMABuffer(void* buf, uint16_t len) {
	_TMR.DMA_BEG.ADDR = (uint16_t)(uintptr_t)buf;
	_TMR.DMA_END.ADDR = (uint16_t)(uintptr_t)(buf + 4 * len);
}
#endif

extern "C"
__INTERRUPT
void TMR0_IRQHandler(void) {
	using namespace ns_TMR;
	switch (TMR0.INT_FLAG.byte & TMR0.INTER_EN.byte) {
	case 0x01: {
		if (TMR_Int_Func[0][0] != nullptr) {
			TMR_Int_Func[0][0]();
		}
		TMR0.INT_FLAG.TMR_IF_CYC_END = 1;
		break;
	}
	case 0x02: {
		if (TMR_Int_Func[0][1] != nullptr) {
			TMR_Int_Func[0][1]();
		}
		TMR0.INT_FLAG.TMR_IF_DATA_ACT = 1;
		break;
	}
	case 0x04: {
		if (TMR_Int_Func[0][2] != nullptr) {
			TMR_Int_Func[0][2]();
		}
		TMR0.INT_FLAG.TMR_IF_FIFO_HF = 1;
		break;
	}
	case 0x10: {
		if (TMR_Int_Func[0][4] != nullptr) {
			TMR_Int_Func[0][4]();
		}
		TMR0.INT_FLAG.TMR_IF_FIFO_OV = 1;
		break;
	}
	}
}

extern "C"
__INTERRUPT
void TMR1_IRQHandler(void) {
	using namespace ns_TMR;
	switch (TMR1.INT_FLAG.byte & TMR1.INTER_EN.byte) {
	case 0x01: {
		if (TMR_Int_Func[1][0] != nullptr) {
			TMR_Int_Func[1][0]();
		}
		TMR1.INT_FLAG.TMR_IF_CYC_END = 1;
		break;
	}
	case 0x02: {
		if (TMR_Int_Func[1][1] != nullptr) {
			TMR_Int_Func[1][1]();
		}
		TMR1.INT_FLAG.TMR_IF_DATA_ACT = 1;
		break;
	}
	case 0x04: {
		if (TMR_Int_Func[1][2] != nullptr) {
			TMR_Int_Func[1][2]();
		}
		TMR1.INT_FLAG.TMR_IF_FIFO_HF = 1;
		break;
	}
	case 0x08: {
		if (TMR_Int_Func[1][3] != nullptr) {
			TMR_Int_Func[1][3]();
		}
		TMR1.INT_FLAG.TMR_IF_DMA_END = 1;
		break;
	}
	case 0x10: {
		if (TMR_Int_Func[1][4] != nullptr) {
			TMR_Int_Func[1][4]();
		}
		TMR1.INT_FLAG.TMR_IF_FIFO_OV = 1;
		break;
	}
	}
}

extern "C"
__INTERRUPT
void TMR2_IRQHandler(void) {
	using namespace ns_TMR;
	switch (TMR2.INT_FLAG.byte & TMR2.INTER_EN.byte) {
	case 0x01: {
		if (TMR_Int_Func[2][0] != nullptr) {
			TMR_Int_Func[2][0]();
		}
		TMR2.INT_FLAG.TMR_IF_CYC_END = 1;
		break;
	}
	case 0x02: {
		if (TMR_Int_Func[2][1] != nullptr) {
			TMR_Int_Func[2][1]();
		}
		TMR2.INT_FLAG.TMR_IF_DATA_ACT = 1;
		break;
	}
	case 0x04: {
		if (TMR_Int_Func[2][2] != nullptr) {
			TMR_Int_Func[2][2]();
		}
		TMR2.INT_FLAG.TMR_IF_FIFO_HF = 1;
		break;
	}
	case 0x08: {
		if (TMR_Int_Func[2][3] != nullptr) {
			TMR_Int_Func[2][3]();
		}
		TMR2.INT_FLAG.TMR_IF_DMA_END = 1;
		break;
	}
	case 0x10: {
		if (TMR_Int_Func[2][4] != nullptr) {
			TMR_Int_Func[2][4]();
		}
		TMR2.INT_FLAG.TMR_IF_FIFO_OV = 1;
		break;
	}
	}
}

extern "C"
__INTERRUPT
void TMR3_IRQHandler(void) {
	using namespace ns_TMR;
	switch (TMR3.INT_FLAG.byte & TMR3.INTER_EN.byte) {
	case 0x01: {
		if (TMR_Int_Func[3][0] != nullptr) {
			TMR_Int_Func[3][0]();
		}
		TMR3.INT_FLAG.TMR_IF_CYC_END = 1;
		break;
	}
	case 0x02: {
		if (TMR_Int_Func[3][1] != nullptr) {
			TMR_Int_Func[3][1]();
		}
		TMR3.INT_FLAG.TMR_IF_DATA_ACT = 1;
		break;
	}
	case 0x04: {
		if (TMR_Int_Func[3][2] != nullptr) {
			TMR_Int_Func[3][2]();
		}
		TMR3.INT_FLAG.TMR_IF_FIFO_HF = 1;
		break;
	}
	case 0x10: {
		if (TMR_Int_Func[3][4] != nullptr) {
			TMR_Int_Func[3][4]();
		}
		TMR3.INT_FLAG.TMR_IF_FIFO_OV = 1;
		break;
	}
	}
}