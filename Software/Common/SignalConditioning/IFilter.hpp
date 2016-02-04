#ifndef _I_FILTER_H
#define _I_FILTER_H

#include "FilterConfig.hpp"

class IFilter {
	public:
		virtual FilterNumberType filter(double data) = 0;
		virtual void reset() = 0;
		virtual ~IFilter() {};
};

#endif
