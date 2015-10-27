//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ADuC70xx (Analog Devices)
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 529 $
//*     $Date:: 2012-04-04 #$
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
//*
//*     Permission is hereby granted, free of charge, to any person
//*     obtaining  a copy of this software and associated documentation
//*     files (the "Software"), to deal in the Software without restriction,
//*     including without limitation the rights to use, copy, modify, merge,
//*     publish, distribute, sublicense, and/or sell copies of the Software,
//*     and to permit persons to whom the Software is furnished to do so,
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************
//*     ARM port by Sergey A. Borshch, Copyright (c) 2006-2012
//*     ADuC70xx port maintenance: Anton B. Gusev aka AHTOXA, Copyright (c) 2011-2012

#include <scmRTOS.h>
#include "pin.h"
#include "display.hpp"
#include <cstring>
#include "logo.hpp"
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

typedef OS::process<OS::pr0, 400> TProc1;
TProc1 Proc1;

volatile int pina;
int main()
{
    // run OS
    OS::run();
}

bool flow=true;

TDisplay<0,2,0,0> display;
Framebuffer fb;
TextRenderer tr(fb);
ADC ad;
DAC da;

//float num[]={0.965080986344734,-1.930161972689468,0.965080986344734};

//float den[]={-1.9289422632520337,0.9313816821269029};

//1st order, 1Hz
//float num[]={0.9408092961815946,-0.9408092961815946};
//float den[]={-0.8816185923631891};

//1st order, 0.5Hz
float num[]={0.9695312529087462,-0.9695312529087462};
float den[]={-0.9390625058174924};

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
		
		
		sleep(100);
		
		da.set(0xFFF);
		
		ad.setRate(50);
		ad.setGain(4);
		ad.start();		
		ad.setDivider(-300);
		
		int32_t oldval=0;
		
		uint32_t fpsTmp=0;
		uint32_t fps=0;
		time_t timer=startTimer();
		time_t resetTimer=0;
		

		
		
		
        for(;;)
        {
			int32_t newval=ad.get();
			
			if (abs(oldval-newval)>64*2){
				resetTimer=startTimer();
			}
			
			if (resetTimer && msPassed(resetTimer, 20)){
				resetTimer=0;
				filter.reset(newval,true);
				#ifdef BACK_FILTER
				filterBack.reset(newval, true);
				#endif
			}
			
			oldval = newval;
			
			fb.clear();
			ecgData[buffPos] = saturate8(filter.filter(newval));
			
			buffPos++;
			if (buffPos==ECGBUF_LEN){
				buffPos=0;
			}
			
			
			fpsTmp++;
			if (msPassed(timer,1000)){
				timer=startTimer();
				//-1: when this code runs, plus 1 frames must be rendered.
				//Do not count the current frame.
				fps=fpsTmp-1;
				fpsTmp=0;
			}
			
			tr.printf(0,0,"%d fps", fps);
			
			
			int32_t prewdata=getEcgdata(ECGBUF_LEN-1);
			#ifdef BACK_FILTER
			//	filterBack.reset(prewdata, true);
			#endif
			for (int a=ECGBUF_LEN-1; a>0; a--){
				int32_t data=getEcgdata(a);
				
				if (a<(fb.width-1)){
					int32_t avg=(data+prewdata)>>1;
					fb.vLine(a+1, prewdata, avg);
					fb.vLine(a, avg, data);
					//fb.setPixel(a,data);
				}
				
				prewdata=data;
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
	
	//	printf("ISR\r\n");
	
	//Globals::instance().uart.send("P");
	
	HANDLE_ADCINT(irq);
}
