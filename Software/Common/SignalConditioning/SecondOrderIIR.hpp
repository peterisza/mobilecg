#ifndef _IIR_FILTER_HPP_
#define _IIR_FILTER_HPP_

#include <stdint.h>
#include "IFilter.hpp"

class SecondOrderIIR: public IFilter {
public:
	SecondOrderIIR(FilterNumberType b0, FilterNumberType b1, FilterNumberType b2, FilterNumberType a0, FilterNumberType a1, FilterNumberType a2):
		v1m1(0), v2m1(0),
		a0(a0), a1(a1), a2(a2),
		b0(b0), b1(b1), b2(b2)
	{
	}

	FilterNumberType filter(FilterNumberType x1)
	{
		FilterNumberType y1 = 0;
		y1 = (b0 * x1 + v1m1) / a0;
		v1m = (b1 * x1 + v2m1) - a1 * y1;
		v2m = b2 * x1 - a2 * y1;
		v1m1 = v1m;
		v2m1 = v2m;
		return y1;
	}
	
	void reset() {
		v1m1 = v2m1 = 0;
	}
	
protected: 
	FilterNumberType a0, a1, a2, b0, b1, b2;
private:
	FilterNumberType v1m1, v2m1, v1m, v2m;
};


#endif
