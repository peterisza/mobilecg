/*
	octave:2> sf = 500*2000/2048
	sf =  488.28
	octave:3> sf2=sf/2
	sf2 =  244.14
	octave:4> [b,a] = pei_tseng_notch(50/sf2,2/sf2)
	b =
	   0.987185315650924  -1.579618433809495   0.987185315650924
	a =
	   1.000000000000000  -1.579618433809495   0.974370631301847
*/

//1st order, 1Hz

/*
#include "IIRFilter.hpp"

class NotchFilter: public IIRFilter<0x1000000, 3, 3> {
public:
	NotchFilter():
		IIRFilter(num, den)
	{
	}
private:
	float num[3]={0.987185315650924, -1.579618433809495, 0.987185315650924};
	float den[3]={1.000000000000000, -1.579618433809495, 0.974370631301847};
};
*/

class NotchFilter {

public:
	NotchFilter():
		v1m1(0), v2m1(0)
	{
	}

	double filter(double x1)
	{
		double y1 = 0;
		y1 = (b[0] * x1 + v1m1) / a[0];
		v1m = (b[1] * x1 + v2m1) - a[1] * y1;
		v2m = b[2] * x1 - a[2] * y1;
		v1m1 = v1m;
		v2m1 = v2m;
		return y1;
	}
private: 
	const double b[3] = {0.987185315650924, -1.579618433809495, 0.987185315650924};
	const double a[3] = {1.000000000000000, -1.579618433809495, 0.974370631301847}; 
	double v1m1, v2m1, v1m, v2m;
};
