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
