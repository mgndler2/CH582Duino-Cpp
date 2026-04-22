#ifndef __CH58x_PWM_H__
#define __CH58x_PWM_H__
#include "CH58x_PWM_SFR.h"
namespace ns_PWM {
	enum CYC_RES {
		BIT_8,
		BIT_7,
		BIT_6,
		BIT_5
	};
}

class PWMx {
public:
	PWMx();
	void setResolution(ns_PWM::CYC_RES res);
	int setResolution(uint8_t res);
	void setDivider(uint16_t Freq);
	void enablePWM(int8_t channel);
	void disablePWM(int8_t channel);
	void setVal(int8_t channel, uint8_t val);
private:
	uint16_t _cycle;
};
extern PWMx SqureWave;

#endif // !__CH58x_PWM_H__