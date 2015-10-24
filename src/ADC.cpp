#include "ADC.hpp"
#include "device.h"

ADC::ADC(){
	ADCMDE = ADCCLKSEL_512KHZ | ADCMDE_CONTINUOUS;
	ADC0CON = ADC0CON_ADC0EN | ADC0CON_AMP_CM_AVDD_DIV_2 | ADC0CON_CHANNEL_DIFF_0_1 |
			ADC0CON_REF_INT | ADC0CON_GAIN_1;
	
	setRate(128);
	ADCCFG = ADCCFG_GNDSW_EN;
}



void ADC::setRate(int rate, int averaginigFactor, bool chop){
	int sf=512000/(rate*64*(averaginigFactor ? (3+averaginigFactor) : 1)+(chop ? 3 : 0))-1;
	
	ADCFLT = (chop ? ADCFLT_CHOP_ENABLE : 0) |
		(averaginigFactor << 8) | sf;
}

bool ADC::setGain(int gain){
	uint16_t adcon=ADC0CON;
	adcon &= ~ADC0CON_GAIN;
	
	switch (gain){
		case (1):
			adcon |= ADC0CON_GAIN_1;
			break;
		case (2):
			adcon |= ADC0CON_GAIN_2;
			break;
		case (4):
			adcon |= ADC0CON_GAIN_4;
			break;
		case (8):
			adcon |= ADC0CON_GAIN_8;
			break;
		case (16):
			adcon |= ADC0CON_GAIN_16;
			break;
		case (32):
			adcon |= ADC0CON_GAIN_32;
			break;
		case (64):
			adcon |= ADC0CON_GAIN_64;
			break;
		case (128):
			adcon |= ADC0CON_GAIN_128;
			break;
		case (256):
			adcon |= ADC0CON_GAIN_256;
			break;
		case (512):
			adcon |= ADC0CON_GAIN_512;
			break;
													
		default: 
			return false;
	}
	
	ADC0CON=adcon;
	return true;
}