#ifndef _UART_HPP_
#define _UART_HPP_

#include <stdint.h>
#include "pin.h"
#include <string>

class UART{
	private:
		Pin <1,0> rx;
		Pin <1,1> tx;
		
		void setBaud(uint32_t baudrate);
		uint32_t calcN(uint32_t baudrate, uint32_t DL, uint32_t M=1);
		void setBaudregs(uint16_t M, uint16_t N, uint16_t DL);
	public:
		UART();
		~UART();
		
		UART(uint32_t baudrate);
		void init(uint32_t baudrate);
		
		void send(const char *data, uint32_t cnt);
		void send(const char *data);
		void send(const std::string str);
};

#endif
