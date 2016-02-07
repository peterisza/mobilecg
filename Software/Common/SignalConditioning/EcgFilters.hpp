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
		0.971607024954110,  -1.943197760476778,   0.971607024954110,
		1.000000000000000,  -1.942391433620420,   0.944020376764578
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
