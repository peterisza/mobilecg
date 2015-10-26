#ifndef _IIR_FILTER_HPP_
#define _IIR_FILTER_HPP_

template <typename T, int numlen, int denlen> class IIRFilter{
	private:
		T *num;
		T *den;
		
		T inHistory[numlen];
		T outHistory[denlen];
		
		int inHistoryPos;
		int outHistoryPos;
	public:
		IIRFilter(T *_num, T *_den){
			num = _num;
			den = _den;
			
			outHistoryPos=0;
			inHistoryPos=0;
			
			for (int a=0; a<denlen; a++)
				outHistory[a] = 0;
			
			for (int a=0; a<numlen; a++)
				inHistory[a] = 0;
		}
		
		void reset(T data, bool highpass){
			for (int a=0; a<numlen; a++)
				inHistory[a]=data;
			
			for (int a=0; a<denlen; a++)
				outHistory[a]=highpass ? 0 : data;
		}
		
		T filter(T data){
			int histPos;
			
			inHistory[inHistoryPos]=data;
			histPos = inHistoryPos;
			
			T accu=0;
			for (int inCoeff=0; inCoeff<numlen; inCoeff++){
				accu += inHistory[histPos] * num[inCoeff];
				histPos--;
				if (histPos<0)
					histPos=numlen-1;
			}
			
			histPos = outHistoryPos;
			for (int outCoeff=0; outCoeff<denlen; outCoeff++){
				histPos--;
				if (histPos<0)
					histPos=denlen-1;
				
				accu -= outHistory[histPos] * den[outCoeff];
			}
				
			inHistoryPos++;
			if (inHistoryPos >= numlen)
				inHistoryPos = 0;
			
			
			outHistory[outHistoryPos] = accu;
			outHistoryPos++;
			if (outHistoryPos >= denlen)
				outHistoryPos = 0;
			
			return accu;
		}
};

#endif
