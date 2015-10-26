#include "DAC.hpp"
#include "device.h"

DAC::DAC(){
	DAC0CON=DAC0_NORMAL_OPERATION ;
}

DAC::~DAC(){
	DAC0CON=0;
}

void DAC::set(uint16_t val){
	DAC0DAT=((uint32_t)val) << 16;
}