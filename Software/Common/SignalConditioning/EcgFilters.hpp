#ifndef _ECG_FILTERS_H
#define _ECG_FILTERS_H

#include "SecondOrderIIR.hpp"
#include "IIRFilterChain.hpp"
#include "BidirectionalFilter.hpp"

class NotchFilter: public SecondOrderIIR {
public:
	NotchFilter(): SecondOrderIIR(
		0.983997556111600, -1.574517624821521,  0.983997556111600,
		1.000000000000000, -1.574517624821521,  0.967995112223201
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

class EcgFilter: public BidirectionalFilter {
public:
	
private:
	HalfEcgFilter forward;
	HalfEcgFilter backward;
};

#endif
