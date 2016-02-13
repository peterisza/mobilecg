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
 
#include "UART.hpp"
#include "system.h"
#include <cstring>


#define FBEN (1<<15)
#define FBN_OFFSET 0
#define FBM_OFFSET 11

UART::UART(uint32_t baudrate){
	init(baudrate);
}

UART::UART(){
	
}

UART::~UART(){
	tx.alternate(OFF);
	rx.alternate(OFF);
}

void UART::init(uint32_t baudrate){
	tx.alternate(ON);
	rx.alternate(ON);

	
	setBaud(baudrate);
	COMCON0 = COMCON0_DATABITS_8;
	COMCON1 = 0;
	
}

void UART::setBaudregs(uint16_t M, uint16_t N, uint16_t DL){
	uint8_t backup = COMCON0;
	COMCON0 = COMCON0_ACCESS_DL;
	
	COMDIV0 = DL & 0xFF;
	COMDIV1 = (DL >> 8) & 0xFF;
	COMDIV2 = FBEN | (M << FBM_OFFSET) | (N << FBN_OFFSET);
	
	COMCON0 = backup;
}

void UART::setBaud(uint32_t baudrate){
	uint32_t M=1;
	
	for (uint32_t DL=1; DL<65000; DL++){
		uint32_t N = calcN(baudrate, DL);
		if (N<2048){
			setBaudregs(M, N, DL);
			return;
		}
	}
}

uint32_t UART::calcN(uint32_t baudrate, uint32_t DL, uint32_t M){
	return 2048.0f*(((float)CPU_CLK)/(32.0f*baudrate*DL) - M);
}

void UART::send(const char *data, uint32_t cnt){
	for (uint32_t a=0; a<cnt; a++){
		while ((COMSTA0 & TX_BUF_EMPTY) == 0);
		COMTX = data[a];
	}
}

void UART::send(const char *data){
	send(data, strlen(data));
}

void UART::send(const std::string str){
	send(str.c_str(), str.length());
}
