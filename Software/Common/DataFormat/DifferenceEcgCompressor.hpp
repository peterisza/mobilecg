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
	
		DifferenceEcgCompressor(ecg::BitFifo &bitStream, unsigned numChannels, IEcgPredictor& ecgPredictor);
		bool putSample(const int* channels);
		bool getSample(int *channels);
	private:
		ecg::BitFifo &bitStream;
		unsigned numChannels;
		IEcgPredictor &ecgPredictor;
};

}

#endif
