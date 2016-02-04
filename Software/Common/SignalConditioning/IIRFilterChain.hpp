#ifndef _IIR_FILTER_CHAIN_H
#define _IIR_FILTER_CHAIN_H

#include <vector>
#include "IFilter.hpp"

class IIRFilterChain: public IFilter {
public:
	IIRFilterChain() {}
	
	void add(IFilter* f) {
		filters.push_back(f);
	}
	
	FilterNumberType filter(FilterNumberType data) {
		for(int i = 0; i < filters.size(); ++i)
			data = filters[i]->filter(data);
		return data;
	}
	
	void reset() {
		for(int i = 0; i < filters.size(); ++i)
			filters[i]->reset();
	}
	
private:
	std::vector<IFilter*> filters;
};

#endif
