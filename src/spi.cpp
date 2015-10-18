#include "spi.h"
#include "system.h"
#include "device.h"

#define SPIEN	(1<<0)
#define SPIMEN	(1<<1)
#define SPICPH	(1<<2)
#define SPICPO	(1<<3)
#define SPIWOM	(1<<4)
#define SPILF	(1<<5)
#define SPITMDE	(1<<6)
#define SPIROW	(1<<7)
#define SPIOEN	(1<<8)
#define SPILP	(1<<9)
#define SPICONT	(1<<10)
#define SPIRFLH	(1<<11)
#define SPITFLH	(1<<12)
#define SPIMDE_OFFSET	(1<<13)

#define FIQCLR_SPI (1<<12)

#define SPITXIRQ (1<<5)
#define SPIRXIRQ (1<<6)

TSpiMaster::~TSpiMaster(){
	FIQCLR = FIQCLR_SPI;
	SPICON = 0;
	
	sck.Alternate(OFF);
	mosi.Alternate(OFF);
	miso.Alternate(OFF);
	cs.Alternate(OFF);
}

TSpiMaster(){
	
}

TSpiMaster(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase, BitOrder bitOrder, Type linkType, bool useCS){
	init(baudrate, cpol, bitOrder, phase, linkType, useCS);
}

void TSpiMaster::init(uint32_t baudrate, ClockPolarity cpol, ClockPhase phase, BitOrder bitOrder, Type linkType){
	FIQCLR = FIQCLR_SPI;
	
	SPIDIV = CPU_CLK / (2 * baudrate) - 1;
	
	sck.Alternate(ON);
	switch (linkType){
		case (WRITE_ONLY):
			mosi.Alternate(ON);
			miso.Alternate(OFF);
			break;
		
		case (READ_ONLY):
			mosi.Alternate(OFF);
			miso.Alternate(ON);
			break;
			
		case (RW):
			mosi.Alternate(ON);
			miso.Alternate(ON);
			break;
	}
	
	if (useCS){
		cs.Alternate(ON);
	}
	SPICON = SPIRFLH | SPITFLH;
	SPICON =	SPIEN | SPIMEN | 
				(phase == TOGGLE_ON_START ? SPICPH : 0) |
				(cpol == CLK_IDDLE_HIGH ? SPICPO : 0) |
				(bitOrder == LSB_FIRST ? SPILF : 0) |
				SPIZEN |
				SPIOEN;
	
}

void TSpiMaster::waitTx(){
	while ((SPISTA & SPITXIRQ) == 0); 
}

void TSpiMaster::waitRx(){
	while ((SPISTA & SPIRXIRQ) == 0); 
}

uint32_t TSpiMaster::transfer(uint32_t data){
	waitTx();
	SPITX = data;
	waitTx();
	waitRx();
	return SPIRX;
}

void TSpiMaster::transfer(char *tx, char *rx, int size){
	for (int a=0; a<size; a++){
		char send = rx ? rx[a] : 0;
		char data=waitRx(send);
		if (rx)
			rx[a]=data;
	}
}

void TSpiMaster::transmit(char *tx, int size){
	transfer(tx, NULL, size);
}

void TSpiMaster::receive(char *rx, int size){
	transfer(NULL, rx, size);
}
