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
 
#include "spi.h"
#include "system.h"
#include "device.h"
#include <stdint.h>
#include <stdio.h>

#define SPIEN	(1<<0)
#define SPIMEN	(1<<1)
#define SPICPH	(1<<2)
#define SPICPO	(1<<3)
#define SPIWOM	(1<<4)
#define SPILF	(1<<5)
#define SPITMDE	(1<<6)
#define SPIZEN  (1<<7)
#define SPIROW	(1<<8)
#define SPIOEN	(1<<9)
#define SPILP	(1<<10)
#define SPICONT	(1<<11)
#define SPIRFLH	(1<<12)
#define SPITFLH	(1<<13)
#define SPIMDE_OFFSET	(1<<14)

#define FIQCLR_SPI (1<<12)

#define SPITXIRQ (1<<5)
#define SPIRXIRQ (1<<6)
#define SPITXUF  (1<<4)

TSpiMaster::~TSpiMaster(){
	FIQCLR = FIQCLR_SPI;
	SPICON = 0;
	
	sck.alternate(OFF);
	mosi.alternate(OFF);
	miso.alternate(OFF);
	cs.alternate(OFF);
}

TSpiMaster::TSpiMaster(){
	
}

TSpiMaster::TSpiMaster(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase, BitOrder bitOrder, Type linkType, bool useCS){
	init(baudrate, cpol, phase, bitOrder, linkType, useCS);
}

void TSpiMaster::init(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase, BitOrder bitOrder, Type linkType, bool useCS){
	FIQCLR = FIQCLR_SPI;
	
	SPIDIV = CPU_CLK / (2 * baudrate) - 1;
	
	sck.alternate(ON);
	switch (linkType){
		case (WRITE_ONLY):
			mosi.alternate(ON);
			miso.alternate(OFF);
			break;
		
		case (READ_ONLY):
			mosi.alternate(OFF);
			miso.alternate(ON);
			break;
			
		case (RW):
			mosi.alternate(ON);
			miso.alternate(ON);
			break;
	}
	
	if (useCS){
		cs.alternate(ON);
	}
	SPICON = SPIRFLH | SPITFLH;
	SPICON =	SPIEN | SPIMEN | SPITMDE | SPICONT |
				(phase == TOGGLE_ON_START ? SPICPH : 0) |
				(cpol == CLK_IDDLE_HIGH ? SPICPO : 0) |
				(bitOrder == LSB_FIRST ? SPILF : 0) |
				SPIZEN |
				SPIOEN;
	
}

void TSpiMaster::waitTx(){
	while (SPISTA & 0xE); 
}



void TSpiMaster::send(uint32_t data){
	while (SPISTA & 8);
	SPITX = data;		
}
