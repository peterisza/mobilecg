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
 
#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include "pin.h"



class TSpiMaster{
	private:
		Pin <0,2> miso;
		Pin <0,3> mosi;
		Pin <0,1> sck;
		Pin <0,0> cs;
	public:
		~TSpiMaster();
		
		enum Type {WRITE_ONLY, READ_ONLY, RW}; 
		enum ClockPolarity {CLK_IDDLE_LOW, CLK_IDDLE_HIGH};
		enum BitOrder {LSB_FIRST, MSB_FIRST};
		enum ClockPhase {TOGGLE_ON_START, TOGGLE_ON_END};
		
		TSpiMaster();
		TSpiMaster(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase,  BitOrder bitOrder, Type linkType=RW, bool useCS=false);
		void init(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase,  BitOrder bitOrder, Type linkType=RW, bool useCS=false);
		void send(uint32_t data);
		
		void waitTx();
};

#endif