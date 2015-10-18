#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <scmRTOS.h>
#include "pin.h"
#include "displayRegs.h"

template <int portMosi, int pinMosi, int portSck, int pinSck, int portReset, int pinReset, int portCS, int pinCS> class TDisplay{
	public:
		TDisplay(){
			mosi.direct(OUTPUT);
			sck.direct(OUTPUT);
			reset.direct(OUTPUT);
			cs.direct(OUTPUT);
			
			reset.on();
			cs.on();
			sck.on();
		}
	private:
		static const int WIDTH = 128;
		static const int HEIGHT = 64;
		enum TTransferType {DATA, COMMAND};
		
		
		Pin<portMosi, pinMosi> mosi;
		Pin<portSck, pinSck> sck;
		Pin<portReset, pinReset> reset;
		Pin<portCS, pinCS> cs;
		
		void transfer(uint8_t byte, TTransferType type){
			sck.off();
			mosi.set(type == DATA);
			sck.on();
			
			for (int bit=7; bit>=0; bit--){
				sck.off();
				mosi.set(((byte >> bit) & 1) != 0);
				sck.on();
			}
		}
		
		void command(uint8_t byte){
			transfer(byte, COMMAND);
		}
		
		void data(uint8_t byte){
			transfer(byte, DATA);
		}
		
		void start(){
			cs.off();
		}
		
		void end(){
			cs.on();
		}
		
		
	public:
		void init(){
			reset.off();
			OS::sleep(2);
			reset.on();
			OS::sleep(2);
			
			start();
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
			
			
			end();
		
		}
		
		void invert(bool invert){
			start();
			if (invert)
				command(SSD1306_INVERTDISPLAY);
			else
				command(SSD1306_NORMALDISPLAY);
			end();
		}
		
		void sendFramebuffer(char *fb){
			start();
			command(SSD1306_COLUMNADDR);
			command(0);
			command(WIDTH-1);
			command(SSD1306_PAGEADDR);
			command(0);
			command(7);
			
			const int cnt=((WIDTH*HEIGHT) >> 3);
			for (int a=0; a <cnt; a++){
				data(fb[a]);
			}
			end();
		}
};

#endif