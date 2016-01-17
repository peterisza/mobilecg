#ifndef FLAT_ECG_PREDICTOR_HPP
#define FLAT_ECG_PREDICTOR_HPP

#include "IEcgPredictor.hpp"

namespace ecg {

class FlatEcgPredictor: public IEcgPredictor {
	public:
		FlatEcgPredictor();
		virtual void setNumChannels(const int numChannels);
		virtual int getPrediction(int channel);
		virtual void putSample(const int* channels);
		virtual void reset();
		static const int maxChannels = 8;
	private:
		int numChannels;
		int prediction[maxChannels];
};

}

#endif
