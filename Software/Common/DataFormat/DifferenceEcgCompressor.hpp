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
 
#ifndef DIFFERENCE_ECG_COMPRESSOR_HPP
#define DIFFERENCE_ECG_COMPRESSOR_HPP

#include <stdint.h>
#include "BitFifo.hpp"
#include "IEcgPredictor.hpp"

namespace ecg {

class DifferenceEcgCompressor {
	public:
		static const int maxChannels = 8;
		static const int fullBitNum = 19;
		static const int smallBitNum = 8;
	
		DifferenceEcgCompressor(ecg::BitFifo &bitStream, IEcgPredictor& ecgPredictor);
		bool putSample(const int32_t* channels);
		bool getSample(int32_t *channels);
		void setNumChannels(unsigned numChannels);
	private:
		ecg::BitFifo &bitStream;
		unsigned numChannels;
		IEcgPredictor &ecgPredictor;
		
		static const int32_t smallMin = (1 << (smallBitNum-1)) - (1 << smallBitNum);
		static const int32_t smallMax = -smallMin-1;
		
		static const int32_t fullMin = (1 << (fullBitNum-1)) - (1 << fullBitNum);
		static const int32_t fullMax = -fullMin-1;
		
};

}

#endif
