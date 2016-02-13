/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "ADC.hpp"
#include "device.h"
#include "globals.hpp"

ADC *ADC::irqHandler=NULL;


ADC::ADC(){
	oldIrqHandler = irqHandler;
	irqHandler=this;
	
	ADCMSKI = 0;
	ADCMDE = ADCCLKSEL_512KHZ;
	ADC0CON = ADC0CON_ADC0EN | ADC0CON_AMP_CM_AVDD_DIV_2 |  ADC0CON_CHANNEL_DIFF_0_1 |
			ADC0CON_REF_INT |  ADC0CON_GAIN_1;
	ADCMSKI |= ADC0RDY_INTEN;
	
	setRate(128);
	ADCCFG = ADCCFG_GNDSW_EN;
}

ADC::~ADC(){
	stop();
	ADC0CON = 0;
	irqHandler = oldIrqHandler;
}

void ADC::start(){
	ADCMDE |= ADCMDE_CONTINUOUS;
	IRQEN |= ADC_BIT;
}

void ADC::stop(){
	ADCMDE &= 0xFFF8;
	IRQEN &= ~ADC_BIT;
}

void ADC::interrupt(){
	
	if (ADCSTA & ADC0RDY){
		int32_t data=ADC0DAT;
		
		if (irqHandler == NULL)
			return;
		
		irqHandler->dataBuffer.push_back(data);
		irqHandler->sampleEvent.signal_isr();
	}
}

int32_t ADC::get(){
	uint8_t cnt;
	int32_t data=0;
		
	while (1){
		//Read data from buffer if available.
		//To do this in a safe way we must disable interrupts
		//to prevent writing the ring buffer in the middle of
		//reading form it.
		
		status_reg_t s=get_interrupt_state();
		if (s) 
			disable_interrupts();
	
		cnt=dataBuffer.get_count();		
		if (cnt)
			data=dataBuffer.pop_front();
		else
			sampleEvent.clear();

		if (s)
			set_interrupt_state(s);
	
		if (cnt){
			data = (data & 0x00800000) ? (0xFF000000 | data) : (data & 0x00FFFFFF);
			return data;
		}
		
		//Wait for the ISR to signal the flag
		sampleEvent.wait();
	}
}


void ADC::setRate(int rate, int averaginigFactor, bool chop){
	if (rate==50){
		ADCFLT = 127;
	} else if (rate==60){
		ADCFLT = 126;
	} else {
		int sf=512000/(rate*64*(averaginigFactor ? (3+averaginigFactor) : 1)+(chop ? 3 : 0))-1;
	
		ADCFLT = (chop ? ADCFLT_CHOP_ENABLE : 0) |
			(averaginigFactor << 8) | sf;
	}
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
