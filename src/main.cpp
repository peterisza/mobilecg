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

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 200> TProc1;
typedef OS::process<OS::pr1, 512> TProc2;
typedef OS::process<OS::pr2, 200> TProc3;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
//---------------------------------------------------------------------------
//
//      IO Pins
//
//Pin<1, 1> LED0;
Pin<0, 4> LED1;


OS::TEventFlag ef;
OS::TEventFlag TimerEvent;

volatile int pina;
int main()
{
    // configure IO pins
	//LED0.Alternate(OFF);
	//LED0.direct(OUTPUT);
//	LED0.On();
//	LED1.Direct(OUTPUT);
//	LED1.Off();

	
    // run OS
    OS::run();
}


TDisplay<0,2,0,0> display;
Framebuffer fb;

namespace OS 
{
    template<> 
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            ef.wait();
            //LED0.Off();
        }
    }

    template<> 
    OS_PROCESS void TProc2::exec()
    {
		sleep(10);
		display.init();

		fb.drawImage(0,0,logo);
		
		TextRenderer tr(fb);
		display.sendFramebuffer(fb.getImage());

		
		int n=0;
        for(;;)
        {
			sleep(30);
			//LED0.off();
			printf("Pina %.3d\r\n", n);
			//			u1.send("Pina\r\n");
            sleep(30);
			printf("Punci %.3X\r\n", n);
//			u1.send("Punci\r\n");
            //LED0.on();
   
   		 	//tr.render(10,10,"Pina "+std::to_string(n)+"   ");
			n++;
			
			tr.printf(10,10,"Pina %d", n);
			display.sendFramebuffer(fb.getImage());
            //ef.signal();
        }
		
	//	memset(fb0+128, 0xFF, 1);
		/*
		for (int r=0; r<64; r++){
			SET_PIXEL(r,r,1);
		}*/
		

		
	}

    template<> 
    OS_PROCESS void TProc3::exec()
    {
		for(;;)
        {
			sleep(30);
		    //LED0.on();
   
            //ef.signal();
        }
    }
}   // namespace OS


void OS::system_timer_user_hook()
{
	static int timer_event_counter = 5;
	if (!--timer_event_counter)
	{
		timer_event_counter = 5;
       // TimerEvent.signal_isr();
	}
}

void OS::idle_process_user_hook() { }

extern "C" void IRQ_Switch()
{
    uint32_t irq = IRQSTA;
    if(irq & SYSTEM_TIMER_INT)
    {
		   OS::system_timer_isr();
    }
}
