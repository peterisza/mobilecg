#ifndef _ADC_HPP_
#define _ADC_HPP_

class ADC{
	
	public:
		ADC();
		bool setGain(int gain);
		void setRate(int rate, int averaginigFactor=0, bool chop=false);
};

#endif
