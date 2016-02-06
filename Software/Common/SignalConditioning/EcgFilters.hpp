#ifndef _ECG_FILTERS_H
#define _ECG_FILTERS_H

#include "SecondOrderIIR.hpp"
#include "IIRFilterChain.hpp"
#include "BidirectionalFilter.hpp"

class NotchFilter: public SecondOrderIIR {
public:
	NotchFilter(): SecondOrderIIR(
		0.996786427732597,  -1.594981398988209,  0.996786427732597,
		1.000000000000000,  -1.594981398988209,  0.993572855465195
	) {}
};

class BaselineFilter: public SecondOrderIIR {
public:
	BaselineFilter(): SecondOrderIIR(
		0.993618760081109, -1.987236697522908,  0.993618760081109,
		1.000000000000000, -1.987195976877089,  0.987278240808038
	) {}
};

class HalfEcgFilter: public IIRFilterChain {
public:
	HalfEcgFilter(): IIRFilterChain() {
		add(&baselineFilter);
		add(&notchFilter);
	}
private:
	BaselineFilter baselineFilter;
	NotchFilter notchFilter;
};

class EcgFilter: public BidirectionalFilter<1200, 240> {
public:
	EcgFilter():
		BidirectionalFilter(&forward, &backward)
	{}
private:
	HalfEcgFilter forward;
	HalfEcgFilter backward;
};

#endif
