#ifndef _DAC_HPP_
#define _DAC_HPP_

#include <stdint.h>


class DAC{
	public:
		DAC();
		~DAC();
		
		void set(uint16_t val);
};

#endif
