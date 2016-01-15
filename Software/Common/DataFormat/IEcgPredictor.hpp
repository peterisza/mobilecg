#ifndef I_ECG_PREDICTOR_HPP
#define I_ECG_PREDICTOR_HPP

namespace ecg {

class IEcgPredictor {
	public:
		virtual int getPrediction(int channel) = 0;
		virtual void putSample(const int* channels) = 0;
		virtual void reset() = 0;
};

}

#endif
