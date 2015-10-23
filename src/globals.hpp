#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

#include "UART.hpp"

class Globals{
	private:
		Globals();
		static Globals instance_internal;
	public:
		UART uart;
		static Globals &instance();
};

#endif


