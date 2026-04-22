#ifndef W_INTERRUPTS_CPP
#define W_INTERRUPTS_CPP

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <pins_arduino.h>
#include <Arduino.h>

void (*pinIntFuncArray[32])(void);

extern "C" 
__INTERRUPT
void GPIOA_IRQHandler(void) {
	switch (x32_INT_IF.Group & x32_INT_EN.Group) {
	case 0x0001: {
		if (pinIntFuncArray[0] != nullptr) {
			pinIntFuncArray[0]();
		}
		x32_INT_IF.Group |= (1u << 0);
		break;
	}
	case 0x0002: {
		if (pinIntFuncArray[1] != nullptr) {
			pinIntFuncArray[1]();
		}
		x32_INT_IF.Group |= (1u << 1);
		break;
	}
	case 0x0004: {
		if (pinIntFuncArray[2] != nullptr) {
			pinIntFuncArray[2]();
		}
		x32_INT_IF.Group |= (1u << 2);
		break;
	}
	case 0x0008: {
		if (pinIntFuncArray[3] != nullptr) {
			pinIntFuncArray[3]();
		}
		x32_INT_IF.Group |= (1u << 3);
		break;
	}
	case 0x0010: {
		if (pinIntFuncArray[4] != nullptr) {
			pinIntFuncArray[4]();
		}
		x32_INT_IF.Group |= (1u << 4);
		break;
	}
	case 0x0020: {
		if (pinIntFuncArray[5] != nullptr) {
			pinIntFuncArray[5]();
		}
		x32_INT_IF.Group |= (1u << 5);
		break;
	}
	case 0x0040: {
		if (pinIntFuncArray[6] != nullptr) {
			pinIntFuncArray[6]();
		}
		x32_INT_IF.Group |= (1u << 6);
		break;
	}
	case 0x0080: {
		if (pinIntFuncArray[7] != nullptr) {
			pinIntFuncArray[7]();
		}
		x32_INT_IF.Group |= (1u << 7);
		break;
	}
	case 0x0100: {
		if (pinIntFuncArray[8] != nullptr) {
			pinIntFuncArray[8]();
		}
		x32_INT_IF.Group |= (1u << 8);
		break;
	}
	case 0x0200: {
		if (pinIntFuncArray[9] != nullptr) {
			pinIntFuncArray[9]();
		}
		x32_INT_IF.Group |= (1u << 9);
		break;
	}
	case 0x0400: {
		if (pinIntFuncArray[10] != nullptr) {
			pinIntFuncArray[10]();
		}
		x32_INT_IF.Group |= (1u << 10);
		break;
	}
	case 0x0800: {
		if (pinIntFuncArray[11] != nullptr) {
			pinIntFuncArray[11]();
		}
		x32_INT_IF.Group |= (1u << 11);
		break;
	}
	case 0x1000: {
		if (pinIntFuncArray[12] != nullptr) {
			pinIntFuncArray[12]();
		}
		x32_INT_IF.Group |= (1u << 12);
		break;
	}
	case 0x2000: {
		if (pinIntFuncArray[13] != nullptr) {
			pinIntFuncArray[13]();
		}
		x32_INT_IF.Group |= (1u << 13);
		break;
	}
	case 0x4000: {
		if (pinIntFuncArray[14] != nullptr) {
			pinIntFuncArray[14]();
		}
		x32_INT_IF.Group |= (1u << 14);
		break;
	}
	case 0x8000: {
		if (pinIntFuncArray[15] != nullptr) {
			pinIntFuncArray[15]();
		}
		x32_INT_IF.Group |= (1u << 15);
		break;
	}
	}
}

extern "C"
__INTERRUPT
void GPIOB_IRQHandler(void) {
	switch (x32_INT_IF.Group & x32_INT_EN.Group) {
	case 0x00010000: {
		if (pinIntFuncArray[16] != nullptr) {
			pinIntFuncArray[16]();
		}
		x32_INT_IF.Group |= (1u << 16);
		break;
	}
	case 0x00020000: {
		if (pinIntFuncArray[17] != nullptr) {
			pinIntFuncArray[17]();
		}
		x32_INT_IF.Group |= (1u << 17);
		break;
	}
	case 0x00040000: {
		if (pinIntFuncArray[18] != nullptr) {
			pinIntFuncArray[18]();
		}
		x32_INT_IF.Group |= (1u << 18);
		break;
	}
	case 0x00080000: {
		if (pinIntFuncArray[19] != nullptr) {
			pinIntFuncArray[19]();
		}
		x32_INT_IF.Group |= (1u << 19);
		break;
	}
	case 0x00100000: {
		if (pinIntFuncArray[20] != nullptr) {
			pinIntFuncArray[20]();
		}
		x32_INT_IF.Group |= (1u << 20);
		break;
	}
	case 0x00200000: {
		if (pinIntFuncArray[21] != nullptr) {
			pinIntFuncArray[21]();
		}
		x32_INT_IF.Group |= (1u << 21);
		break;
	}
	case 0x00400000: {
		if (pinIntFuncArray[22] != nullptr) {
			pinIntFuncArray[22]();
		}
		x32_INT_IF.Group |= (1u << 22);
		break;
	}
	case 0x00800000: {
		if (pinIntFuncArray[23] != nullptr) {
			pinIntFuncArray[23]();
		}
		x32_INT_IF.Group |= (1u << 23);
		break;
	}
	case 0x01000000: {
		if (pinIntFuncArray[24] != nullptr) {
			pinIntFuncArray[24]();
		}
		x32_INT_IF.Group |= (1u << 24);
		break;
	}
	case 0x02000000: {
		if (pinIntFuncArray[25] != nullptr) {
			pinIntFuncArray[25]();
		}
		x32_INT_IF.Group |= (1u << 25);
		break;
	}
	case 0x04000000: {
		if (pinIntFuncArray[26] != nullptr) {
			pinIntFuncArray[26]();
		}
		x32_INT_IF.Group |= (1u << 26);
		break;
	}
	case 0x08000000: {
		if (pinIntFuncArray[27] != nullptr) {
			pinIntFuncArray[27]();
		}
		x32_INT_IF.Group |= (1u << 27);
		break;
	}
	case 0x10000000: {
		if (pinIntFuncArray[28] != nullptr) {
			pinIntFuncArray[28]();
		}
		x32_INT_IF.Group |= (1u << 28);
		break;
	}
	case 0x20000000: {
		if (pinIntFuncArray[29] != nullptr) {
			pinIntFuncArray[29]();
		}
		x32_INT_IF.Group |= (1u << 29);
		break;
	}
	case 0x40000000: {
		if (pinIntFuncArray[30] != nullptr) {
			pinIntFuncArray[30]();
		}
		x32_INT_IF.Group |= (1u << 30);
		break;
	}
	case 0x80000000: {
		if (pinIntFuncArray[31] != nullptr) {
			pinIntFuncArray[31]();
		}
		x32_INT_IF.Group |= (1u << 31);
		break;
	}
	}
}

void attachInterrupt(uint8_t pin, void (*Func)(void), uint8_t Mode) {
	if (pin >= 32) return;
	uint8_t Group = pin / 16, Bit = pin % 16, G = pin / 8, B = pin % 8;
	pinIntFuncArray[pin] = Func;	
	
	switch (Mode) {
	case 3:
	{
		*pinINT_Mode_map[Group].data_reg |= (1u << Bit);
		*pinOut_map[G].data_reg |= (1u << B);
		break;
	}
	case 2:
	{
		*pinINT_Mode_map[Group].data_reg |= (1u << Bit);
		*pinOut_map[G].data_reg &= ~(1u << B);
		break;
	}
	case 1:
	{
		*pinINT_Mode_map[Group].data_reg &= ~(1u << Bit);
		*pinOut_map[G].data_reg |= (1u << B);
		break;
	}
	case 0:
	{
		*pinINT_Mode_map[Group].data_reg &= ~(1u << Bit);
		*pinOut_map[G].data_reg &= ~(1u << B);
		break;
	}
	}
	
	*pinINT_EN_map[Group].data_reg |= (1u << Bit);
	if (pin < 16) {
		PFIC_EnableIRQ(GPIO_A_IRQn);
	}
	else {
		PFIC_EnableIRQ(GPIO_B_IRQn);
	}
	
}

void detachInterrupt(uint8_t pin) {
	if (pin >= 32) return;
	uint8_t Group = pin / 16, Bit = pin % 16;

	*pinINT_EN_map[Group].data_reg &= ~(1u << Bit);
	if (x32_INT_EN.PA_EN == 0) {
		PFIC_DisableIRQ(GPIO_A_IRQn);
	}
	if (x32_INT_EN.PB_EN == 0) {
		PFIC_DisableIRQ(GPIO_B_IRQn);
	}
}
#endif
