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
