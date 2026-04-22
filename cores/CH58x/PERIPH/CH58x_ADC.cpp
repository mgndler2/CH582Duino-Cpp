#include "CH58x_ADC.h"

ADConverter Analog(true);
uint16_t ADConverter::getTemp() {
	uint8_t cfg = ADC.ADC_CFG.byte;

	Touch_Key.CFG.TKEY_PWR_ON = 0;

	ADC.TEM_SENSOR.TEM_SEN_PWR_ON = 1;
	ADC.ADC_CHANNEL.ADC_CH_INX = 15;
	ADC.ADC_CFG.byte = 0b10110101;

	while (ADC.ADC_CONVERT.ADC_START);
	ADC.ADC_CONVERT.ADC_START = 1;
	while (ADC.ADC_CONVERT.ADC_START);
	uint16_t raw = ADC.ADC_DATA.DATA;
	ADC.ADC_CFG.byte = cfg;
	return raw;
}
uint16_t ADConverter::doConversion() {
	ADC.ADC_CFG.ADC_POWER_ON = 1;
	ADC.ADC_CONVERT.ADC_START = 1;
	while (ADC.ADC_CONVERT.ADC_START);
	ADC.ADC_CONVERT.ADC_START = 1;
	while (ADC.ADC_CONVERT.ADC_START);
	uint16_t raw = ADC.ADC_DATA.DATA;
	uint32_t val = raw + _offset;
	if (val < 0) val = 0;
	if (val > 4095) val = 4095;
	if (_powerSafe) ADC.ADC_CFG.ADC_POWER_ON = 0;
	return (uint16_t)val;
}
void ADConverter::setADC_CH(uint8_t channel) {
	 ADC.ADC_CHANNEL.ADC_CH_INX = channel;
}
int16_t ADConverter::calibrateOffset() {
	 uint32_t sum = 0;
	 uint8_t  ch = 0;
	 ch = ADC.ADC_CHANNEL.ADC_CH_INX;
	 ADC.ADC_CHANNEL.ADC_CH_INX = 1;

	 ADC.ADC_CFG.ADC_POWER_ON = 1; ADC.ADC_CFG.ADC_OFS_TEST = 1;
	 ADC.ADC_CONVERT.ADC_START = 1;
	 while (ADC.ADC_CONVERT.ADC_START);
	 for (int i = 0; i < 16; i++)
	 {
		  ADC.ADC_CONVERT.ADC_START = 1;
		  while (ADC.ADC_CONVERT.ADC_START);
		  sum += (~ADC.ADC_DATA.group) & RB_ADC_DATA;
	 }
	 sum = (sum + 8) >> 4;
	 ADC.ADC_CFG.ADC_OFS_TEST = 0;
	 ADC.ADC_CHANNEL.ADC_CH_INX = ch;
	 if (_powerSafe) ADC.ADC_CFG.ADC_POWER_ON = 0;
	 return _offset = (2048 - sum);
}
uint8_t ADConverter::getPGA_GAIN() {
	 return ADC.ADC_CFG.ADC_PGA_GAIN;
}
void ADConverter::setPGA_GAIN(ns_ADC::PGA_GAIN gain, bool calibrate) {
	 ADC.ADC_CFG.ADC_PGA_GAIN = gain;
	 if (calibrate) calibrateOffset();
}
uint8_t ADConverter::getCLK_DIV() {
	 return ADC.ADC_CFG.ADC_CLK_DIV;
}
void ADConverter::setCLK_DIV(ns_ADC::CLK_DIV div, bool calibrate) {
	 ADC.ADC_CFG.ADC_CLK_DIV = div;
	 if (calibrate) calibrateOffset();
}
void ADConverter::setPowerSafe() {
	 _powerSafe = 1;
}
void ADConverter::clrPowerSafe() {
	 _powerSafe = 0;
}