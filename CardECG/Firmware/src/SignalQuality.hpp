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
 
#ifndef _SIGNALQUALITY_H_
#define _SIGNALQUALITY_H_

#include <stdint.h>

class SignalQuality{
	public:
		SignalQuality();
		void processSample(int32_t raw, int8_t filtered);
		bool isSignalGood();
		int signalHasBeenGoodFor();
		int getNoiseQuantity();
		void reset();
	private:
		int32_t prevSample, prev2Sample;
		bool lastSampleGood;
		int howLong;
		int noiseQuantity;
		int oobCounter;
};

#endif
