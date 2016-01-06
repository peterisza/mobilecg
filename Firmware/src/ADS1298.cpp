#include "ADS1298.h"
#include <OS.h>

extern "C" SPI_HandleTypeDef hspi2;

ADS1298::ADS1298():
	reset('A', 6, true),
	pwdn('A', 7, true),
	pinStart('B',10),
	diffSel('C',4)
{

}

ADS1298::~ADS1298() {

}

void ADS1298::writeReg(Register reg, uint8_t value){
	uint8_t writeBuf[3];
	writeBuf[0]=CMD_WREG | (uint8_t)reg;
	writeBuf[1]=0;
	writeBuf[2]=value;

	HAL_SPI_Transmit(&hspi2, writeBuf, 3, HAL_MAX_DELAY);
}

uint8_t ADS1298::readReg(Register reg){
	uint8_t writeBuf[3];
	writeBuf[0]=CMD_RREG | (uint8_t)reg;
	writeBuf[1]=0;
	writeBuf[2]=0;

	uint8_t readBuf[3];

	HAL_SPI_TransmitReceive(&hspi2, writeBuf, readBuf, 3, HAL_MAX_DELAY);

 	return readBuf[2];
}

void ADS1298::sendCommand(Command cmd){
	uint8_t data=cmd;
	HAL_SPI_Transmit(&hspi2, &data, 1, HAL_MAX_DELAY);
}

bool ADS1298::start(){
	pinStart.off();
	reset.on();
	pwdn.off();

	OS::sleep(20);

	reset.off();
	OS::sleep(20);
	sendCommand(CMD_WAKEUP);
	OS::sleep(20);

	uint8_t id = readReg(REG_ID);
	if ((id >> 3) != 0x12 && (id >> 3)!= 0x1A){
		//Wrong device signature
		stop();
		return false;
	}

	nHardwareChannels = id & 0x07;
	if (nHardwareChannels > 2){
		//Wrong channel number
		stop();
		return false;
	}

	nHardwareChannels = 4+2*nHardwareChannels;

	return true;
}

void ADS1298::stop(){

}
