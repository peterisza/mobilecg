#ifndef _TEST_SIGNAL_GENERATOR_HPP
#define _TEST_SIGNAL_GENERATOR_HPP

#include <math.h>

class TestSignalGenerator {
	public:
		TestSignalGenerator(int amplitude, int period):
			amplitude(amplitude), phase(0)
		{
			setPeriod(period);
		}
		
		void setAmplitude(int a) {
			amplitude = a;
		}
		
		void setPeriod(int p) {
			period = p;
			delta = 2*M_PI/period;
		}
		
		int getNextSample() {
			phase += delta;
			return sin(phase) * amplitude;
		}
	private:
		int amplitude;
		int period;
		float phase;
		float delta;
};

#endif
