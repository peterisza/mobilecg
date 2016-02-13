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
