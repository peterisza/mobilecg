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
		uint32_t transfer(uint32_t);
		void transfer(char *tx, char *rx, int size);
		void transmit(char *tx, int size);
		void receive(char *rx, int size);
		
	private:
		void waitTx();
		void waitRx();
};

#endif
