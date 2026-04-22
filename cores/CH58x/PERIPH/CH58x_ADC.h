#ifndef __CH58x_ADC_H__
#define __CH58x_ADC_H__
#include "CH58x_ADC_SFR.h"
#include "CH583SFR.h"

namespace ns_ADC {
	 enum PGA_GAIN
	 {
		  GAIN_Quarter,
		  GAIN_Half,
		  GAIN_NoGain,
		  GAIN_Double
	 };
	 enum CLK_DIV
	 {
		  DIV_10,
		  DIV_4,
		  DIV_6,
		  DIV_8
	 };
}

class ADConverter {
public:
	 ADConverter(bool powerSaving = false)
		  :_powerSafe(powerSaving) {		 
	 }
	 void Init() {
		  ADC.ADC_CFG.ADC_BUF_EN = 1;
		  setCLK_DIV(ns_ADC::DIV_6, false);
		  setPGA_GAIN(ns_ADC::GAIN_Quarter);
	 }
	 uint8_t getPGA_GAIN();
	 void setPGA_GAIN(ns_ADC::PGA_GAIN gain, bool calibrate = true);
	 uint8_t getCLK_DIV();
	 void setCLK_DIV(ns_ADC::CLK_DIV div, bool calibrate = true);
	 void setADC_CH(uint8_t channel);
	 uint16_t doConversion();
	 uint16_t getTemp();
	 void setPowerSafe();
	 void clrPowerSafe();
	 int16_t _offset = 0;
private:
	 int16_t calibrateOffset();
	 
	 bool _powerSafe;
};
extern ADConverter Analog;
#endif // !__CH58x_ADC_H__
