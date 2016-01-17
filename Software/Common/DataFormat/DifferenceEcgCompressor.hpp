#ifndef DIFFERENCE_ECG_COMPRESSOR_HPP
#define DIFFERENCE_ECG_COMPRESSOR_HPP

#include "BitFifo.hpp"
#include "IEcgPredictor.hpp"

namespace ecg {

class DifferenceEcgCompressor {
	public:
		static const int maxChannels = 8;
		static const int fullBitNum = 24;
		static const int smallBitNum = 10;	
	
		DifferenceEcgCompressor(ecg::BitFifo &bitStream, IEcgPredictor& ecgPredictor);
		bool putSample(const int* channels);
		bool getSample(int *channels);
		void setNumChannels(unsigned numChannels);
	private:
		ecg::BitFifo &bitStream;
		unsigned numChannels;
		IEcgPredictor &ecgPredictor;
		
		static const int smallMin = (1 << (smallBitNum-1)) - (1 << smallBitNum);
		static const int smallMax = -smallMin-1;
		
		static const int fullMin = (1 << (fullBitNum-1)) - (1 << fullBitNum);
		static const int fullMax = -fullMin-1;
		
};

}

#endif
