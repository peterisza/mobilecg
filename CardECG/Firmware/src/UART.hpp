/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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
