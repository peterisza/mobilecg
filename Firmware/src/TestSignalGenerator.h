#ifndef _TEST_SIGNAL_GENERATOR_HPP
#define _TEST_SIGNAL_GENERATOR_HPP

#include <math.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

class TestSignalGenerator {
	public:
		TestSignalGenerator(int a, int p):
			amplitude(a)
		{
			setPeriod(p);
		}
		
		void setAmplitude(int a) {
			amplitude = a;
		}
		
		void setPeriod(int p) {
			period = p;
		}
		
		int getSample(int phaseOffset = 0) {
			int phase = (index + phaseOffset) % period;
			int r = phase * 2 * amplitude / period;
			if(r > amplitude)
				r = 2*amplitude - r;
			return r;
		}

		void next(){
			index++;
		}
	private:
		int amplitude;
		int period;
		int index;
		/*float phase;
		float delta;*/
};

#endif
