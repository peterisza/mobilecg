/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
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
 
#ifndef _IIR_FILTER_HPP_
#define _IIR_FILTER_HPP_

template <int scale, int numlen, int denlen> class IIRFilter{
	private:
		int32_t num[numlen];
		int32_t den[denlen];
		
		int32_t inHistory[numlen];
		int32_t outHistory[denlen];
		
		int inHistoryPos;
		int outHistoryPos;
	public:
		IIRFilter(float *_num, float *_den){
			
			outHistoryPos=0;
			inHistoryPos=0;
			
			for (int a=0; a<denlen; a++){
				den[a]= - _den[a] * (float)scale;
				outHistory[a] = 0;
			}
			
			for (int a=0; a<numlen; a++){
				num[a]=_num[a] * (float)scale;
				inHistory[a] = 0;
			}
		}
		
		void reset(int32_t data, bool highpass){
			for (int a=0; a<numlen; a++)
				inHistory[a]=data;
			
			for (int a=0; a<denlen; a++)
				outHistory[a]=highpass ? 0 : data;
		}
		
		int32_t filter(int32_t data){
			int histPos;
			
			inHistory[inHistoryPos]=data;
			
			
			int64_t accu=0;
			int inCoeff=0;
			histPos = inHistoryPos;
			for (; histPos>=0 && inCoeff<numlen; inCoeff++, histPos--){
				accu += inHistory[histPos] * (int64_t)num[inCoeff];
			}
			
			histPos=numlen-1;
			for (; inCoeff<numlen; inCoeff++, histPos--){
				accu += inHistory[histPos] * (int64_t)num[inCoeff];
			}
			
			histPos = outHistoryPos-1;
			int outCoeff=0;
			for (; histPos>=0 && outCoeff<denlen; outCoeff++, histPos--){
				accu += outHistory[histPos] * (int64_t)den[outCoeff];
			}
			
			histPos=denlen-1;
			for (; outCoeff<denlen; outCoeff++, histPos--){
				accu += outHistory[histPos] * (int64_t)den[outCoeff];
			}

			accu /= scale;
		
			const int32_t a=accu;
				
			inHistoryPos++;
			if (inHistoryPos >= numlen)
				inHistoryPos = 0;
			
			
			outHistory[outHistoryPos] = a;
			outHistoryPos++;
			if (outHistoryPos >= denlen)
				outHistoryPos = 0;
			
			return a;
		}
};

#endif
