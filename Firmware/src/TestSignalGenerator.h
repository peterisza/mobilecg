#ifndef _TEST_SIGNAL_GENERATOR_HPP
#define _TEST_SIGNAL_GENERATOR_HPP

#include <math.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

class TestSignalGenerator {
	public:
		TestSignalGenerator(int a, int p):
			amplitude(a), phase(0)
		{
			setPeriod(p);
		}
		
		void setAmplitude(int a) {
			amplitude = a;
		}
		
		void setPeriod(int p) {
			period = p;
			delta = 2*M_PI/period;
		}
		
		int getSample(float phaseDelta=0.0) {
			return sin(phase + phaseDelta) * amplitude;
		}

		void next(){
			phase += delta;
		}
	private:
		int amplitude;
		int period;
		float phase;
		float delta;
};

#endif
