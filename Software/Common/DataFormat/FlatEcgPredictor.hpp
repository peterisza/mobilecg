#ifndef FLAT_ECG_PREDICTOR_HPP
#define FLAT_ECG_PREDICTOR_HPP

#include <stdint.h>
#include "IEcgPredictor.hpp"

namespace ecg {

class FlatEcgPredictor: public IEcgPredictor {
	public:
		FlatEcgPredictor();
		virtual void setNumChannels(const int numChannels);
		virtual int32_t getPrediction(int channel);
		virtual void putSample(const int32_t* channels);
		virtual void reset();
		static const int maxChannels = 8;
	private:
		int numChannels;
		int32_t prediction[maxChannels];
};

}

#endif
