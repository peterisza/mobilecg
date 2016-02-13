#ifndef _ADC_HPP_
#define _ADC_HPP_

#include <scmRTOS.h>

#define HANDLE_ADCINT(status) do {if ((status) & ADC_BIT) ADC::interrupt();} while(0)

class ADC{
	private:
		static ADC *irqHandler;
		ADC *oldIrqHandler;
		
		
		usr::ring_buffer<int32_t, 4> dataBuffer;
		OS::TEventFlag sampleEvent;
	public:
		ADC();
		~ADC();
		
		
		
		bool setGain(int gain);
		void setRate(int rate, int averaginigFactor=0, bool chop=false);
		void setRate50Hz();
		void start();
		void stop();
		
		static void interrupt();
		
		int32_t get();
};

#endif
