#ifndef I_ECG_PREDICTOR_HPP
#define I_ECG_PREDICTOR_HPP

#include <stdint.h>

namespace ecg {

//Ugly way to make a pure virtual class, but if =0 is used, GCC tries to link
//random syscalls like _kill, _exit, _getpid, _open, _write, etc, which we don't
//have in the firmware, and we don't want to waste the memory on them.
class IEcgPredictor {
	public:
		virtual int32_t getPrediction(int channel) {(void)(channel); return 0;};
		virtual void putSample(const int32_t* channels) {(void)(channels);};
		virtual void reset() {};
};

}

#endif
