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
 
#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <scmRTOS.h>
#include "pin.h"
#include "displayRegs.h"
#include "spi.h"

template <int portReset, int pinReset, int portCS, int pinCS> class TDisplay{
	public:
		TDisplay(){
			ioInit();
			spi.init(5120000, TSpiMaster::CLK_IDDLE_HIGH, TSpiMaster::TOGGLE_ON_START, TSpiMaster::MSB_FIRST, TSpiMaster::WRITE_ONLY, false);
		}
	private:
		static const int WIDTH = 128;
		static const int HEIGHT = 64;
		enum TTransferType {DATA, COMMAND};
		
		TSpiMaster spi;
			
		Pin<portReset, pinReset> reset;
		Pin<portCS, pinCS> cs;
		
		void ioInit(){
			reset.direct(OUTPUT);
			cs.direct(OUTPUT);
			
			reset.on();
			cs.on();
		}

		void command(uint8_t byte){
			cs.off();
			spi.send(byte>>1);
			spi.send(byte<<7);
			spi.waitTx();
			cs.on();
		}
	
		
		void burstFramebuffer(const uint8_t *data){
			cs.off();
			const int size=WIDTH*HEIGHT>>3;
			
				
			for (int i = 0; i < size; i+=8){
				spi.send((data[i]>>1) | 0x80);
				spi.send((data[i]<<7) | 0x40 | (data[i+1]>>2));
				spi.send((data[i+1]<<6) | 0x20 | (data[i+2]>>3));
				spi.send((data[i+2]<<5) | 0x10 | (data[i+3]>>4));
				spi.send((data[i+3]<<4) | 0x08 | (data[i+4]>>5));
				spi.send((data[i+4]<<3) | 0x04 | (data[i+5]>>6));
				spi.send((data[i+5]<<2) | 0x02 | (data[i+6]>>7));
				spi.send((data[i+6]<<1) | 0x01);
				spi.send(data[i+7]);
			}
			spi.waitTx();
			
			cs.on();
		}
		
		
	public:
		void init(){
			reset.off();
			OS::sleep(2);
			reset.on();
			OS::sleep(2);
			
			command(SSD1306_SETDISPLAYCLOCKDIV);
			command(0x80);
			command(SSD1306_SETMULTIPLEX); 
		    command(0x3F);
		    command(SSD1306_SETDISPLAYOFFSET);
		    command(0x0);
		    command(SSD1306_SETSTARTLINE | 0x0);
		    command(SSD1306_CHARGEPUMP);
		
		    command(0x14);
		    command(SSD1306_MEMORYMODE); 
		    command(0x00);
		    command(SSD1306_SEGREMAP | 0x1);
		    command(SSD1306_COMSCANDEC);
		    command(SSD1306_SETCOMPINS);
		    command(0x12);
		    command(SSD1306_SETCONTRAST); 
		 	command(0xCF);
		    command(SSD1306_SETPRECHARGE);
		   	command(0xF1);
		    command(SSD1306_SETVCOMDETECT);
		    command(0x40);
		    command(SSD1306_DISPLAYALLON_RESUME);
		    command(SSD1306_NORMALDISPLAY);
			
			command(SSD1306_DISPLAYON);
		}
		
		void invert(bool enabled){
			if (enabled)
				command(SSD1306_INVERTDISPLAY);
			else
				command(SSD1306_NORMALDISPLAY);
		}
		
		
		
		void sendFramebuffer(const uint8_t *data){
			command(SSD1306_COLUMNADDR);
			command(0);
			command(WIDTH-1);
			command(SSD1306_PAGEADDR);
			command(0);
			command(7);
			
			burstFramebuffer(data);
		}
};

#endif