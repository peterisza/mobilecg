/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Peter Isza, Robert Csordas
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
		
		int getPeriod() {
			return period;
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
};

#endif
