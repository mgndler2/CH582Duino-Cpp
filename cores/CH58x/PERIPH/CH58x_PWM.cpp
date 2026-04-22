#include "CH58x_PWM.h"
#include "CH583SFR.h"
#include "CH58x_SYS.h"

PWMx SqureWave;

PWMx::PWMx()
	:_cycle(255)
{
	PWM.OUT_EN.byte = 0;
	PWM.POLAR.byte = 0;
	PWM.CONFIG.byte = 0x01;
	setDivider(1000);
}

void PWMx::setResolution(ns_PWM::CYC_RES res) {
	using namespace ns_PWM;

	PWM.CONFIG.CYC_MOD = res;

	switch (res) {
	case BIT_8:
		_cycle = 256 - PWM.CONFIG.CYCLE_SEL;
		break;
	case BIT_7:
		_cycle = 128 - PWM.CONFIG.CYCLE_SEL;
		break;
	case BIT_6:
		_cycle = 64 - PWM.CONFIG.CYCLE_SEL;
		break;
	case BIT_5:
		_cycle = 32 - PWM.CONFIG.CYCLE_SEL;
		break;
	}
}

int PWMx::setResolution(uint8_t res) {
	ns_PWM::CYC_RES tmp;
	switch (res) {
	case 8:
		tmp = ns_PWM::BIT_8;
		break;
	case 7:
		tmp = ns_PWM::BIT_7;
		break;
	case 6:
		tmp = ns_PWM::BIT_6;
		break;
	case 5:
		tmp = ns_PWM::BIT_5;
		break;
	default:
		tmp = ns_PWM::BIT_8;
		res = 8;
		break;
	}
	setResolution(tmp);
	return res;
}

void PWMx::setDivider(uint16_t Freq) {
	uint32_t pre = CPU_CLK.GetSysClock() / Freq / _cycle;
	if (pre > 255) pre = 255;
	PWM.DIV.DIV = pre;

}

void PWMx::enablePWM(int8_t channel) {
	PWM.OUT_EN.byte |= 1u << (channel - 4);
}

void PWMx::disablePWM(int8_t channel) {
	PWM.OUT_EN.byte &= ~(1u << (channel - 4));
}

void PWMx::setVal(int8_t channel, uint8_t val) {
	PWM.DATA.bytes[channel - 4] = val;
}