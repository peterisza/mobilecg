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
 
#include <scmRTOS.h>
#include "pin.h"
#include "display.hpp"
#include <cstring>
#include "logo.hpp"
#include "waiting.hpp"
#include "framebuffer.hpp"
#include "TextRenderer.hpp"
#include "printf.hpp"
#include <string>
#include "ADC.hpp"
#include "DAC.hpp"
#include "globals.hpp"
#include "IIRFilter.hpp"
#include "Time.hpp"
#include <stdlib.h>
#include "QRSDetector.hpp"
#include "SignalQuality.hpp"

Pin <0,4> pullup_off;
Pin <2,0> power_on;

typedef OS::process<OS::pr0, 400> TProc1;
TProc1 Proc1;

volatile int pina;
int main()
{
	power_on.direct(OUTPUT);
	power_on.on();

	pullup_off.direct(OUTPUT);
	pullup_off.on();
	
    // run OS
    OS::run();
}

bool flow=true;

TDisplay<0,2,0,0> display;
Framebuffer fb;
TextRenderer tr(fb);
ADC ad;
DAC da;


//1st order, 1Hz
float num[]={0.9408092961815946,-0.9408092961815946};
float den[]={-0.8816185923631891};

//1st order, 0.5Hz
//float num[]={0.9695312529087462,-0.9695312529087462};
//float den[]={-0.9390625058174924};



QRSDetector detector;
SignalQuality signalQuality;

IIRFilter <0x1000000, sizeof(num)/sizeof(float), sizeof(den)/sizeof(float)> filter(num, den);


#define BACK_FILTER

#ifdef BACK_FILTER
IIRFilter <0x1000000, sizeof(num)/sizeof(float), sizeof(den)/sizeof(float)> filterBack(num, den);
#endif


#ifdef BACK_FILTER
	#define BACK_BUF 64
#else
	#define BACK_BUF 0
#endif

#define ECGBUF_LEN (Framebuffer::width+BACK_BUF)
int8_t ecgData[ECGBUF_LEN];
volatile int buffPos=0;

const int turnOffTimeLimit = 4*50;

int8_t saturate8(int32_t data){
	if (data>127)
		return 127;
	if (data<-128)
		return -128;
	
	return data;
}

int8_t getY(int8_t data){
	data+=40;
	
	if (data > 63)
		data=63;
	else if (data<0)
		data=0;
	
	return data;
}

int8_t getEcgdata(uint32_t index){
	if (flow){
		index+=buffPos;
		if (index>=ECGBUF_LEN)
			index-=ECGBUF_LEN;
	}
	
	#ifdef BACK_FILTER
		return getY(filterBack.filter(ecgData[index]));
	#else
		return getY(ecgData[index]);
	#endif
}

namespace OS 
{
 
    template<> 
    OS_PROCESS void TProc1::exec()
    {
		sleep(10);
		display.init();

		printf("BOOT\r\n");
		fb.drawImage(0,0,logo);
		
		display.sendFramebuffer(fb.getImage());
		
		memset(ecgData,0,sizeof(ecgData));
		
		
		da.set(0xFFF);
		
		ad.setRate(50);
		ad.setGain(4);
		ad.start();		

		int32_t oldval=0;
		
		uint32_t fpsTmp=0;
		uint32_t fps=0;
		time_t timer=startTimer();
		time_t resetTimer=0;
		
		int32_t logoCounter = 80;
		
		int32_t reset=0;
		int turnOffCounter = 2;
		
        for(;;)
        {
			int32_t newval=ad.get();
			bool qrs=detector.process(newval);
			newval /= -300;
			
			
			if (abs(oldval-newval)>64*2){
				resetTimer=startTimer();
			}
			
			
			oldval = newval;
			
			ecgData[buffPos] = saturate8(filter.filter(newval));

			signalQuality.processSample(newval, ecgData[buffPos]);
	
			buffPos++;
			if (buffPos==ECGBUF_LEN){
				buffPos=0;
			}
			
			
			fpsTmp++;
			if (msPassed(timer,1000)){
				timer=startTimer();
				//-1: when this code runs, plus 1 frame must be rendered.
				//Do not count the current frame.
				fps=fpsTmp-1;
				fpsTmp=0;
			}
			
			if(logoCounter > 0)
				logoCounter--;
			
			
			if(signalQuality.isSignalGood()) {
				fb.clear();	
				
				int pr = detector.getPulseRate();
				if(pr > 0)
					tr.printf(127 | TextRenderer::ALIGN_RIGHT,0,"%d", pr);
				
				int32_t prevdata=getEcgdata(ECGBUF_LEN-1);
				for (int a=ECGBUF_LEN-1; a>0; a--){
					int32_t data=getEcgdata(a);			
					if (a<(fb.width-1)){
						int32_t avg=(data+prevdata)>>1;
						fb.vLine(a+1, prevdata, avg);
						fb.vLine(a, avg, data);
					}
					prevdata=data;
				}				


				turnOffCounter = 0;
			} else {
				if(turnOffCounter == 1 || logoCounter == 1) {
					fb.drawImage(0,0,waiting);
				}

				if(turnOffCounter == 1) {
					signalQuality.reset();
					pullup_off.off();					
				}
				
				if(turnOffCounter == 20) {
					if(newval > 27000 || newval < -27000) {
						power_on.off();					
					} else {
						pullup_off.on();	
					}		
				}
				
				if(turnOffCounter == 40) {
					power_on.on();
					filter.reset(newval,true);
					detector.reset();
					#ifdef BACK_FILTER
					filterBack.reset(newval, true);	
					#endif					
				}

				
				int sec = (turnOffTimeLimit - turnOffCounter) / 50;
				
				if(logoCounter == 0 && turnOffCounter > 30)
					tr.printf(0,0,"%d", sec);			
				
				turnOffCounter++;
				
				if(turnOffCounter == turnOffTimeLimit) {
					turnOffCounter = 0;
				}
				
				detector.reset();
			}
			display.sendFramebuffer(fb.getImage());
		}
			

		
	}


}   // namespace OS


void OS::system_timer_user_hook()
{
}

void OS::idle_process_user_hook() { }

extern "C" void IRQ_Switch()
{
    uint32_t irq = IRQSTA;
    if(irq & SYSTEM_TIMER_INT)
    {
		   OS::system_timer_isr();
		   currTime++;
    }
	
	HANDLE_ADCINT(irq);
}
