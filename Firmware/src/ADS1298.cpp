#include "ADS1298.h"
#include <OS.h>
#include <Logger.h>
#include "stm32f4xx_hal.h"
#include <string.h>

extern "C" SPI_HandleTypeDef hspi2;

#define nPD_REFBUF 0x80
#define CONFIG3_FIXED 0x40
#define HR 0x80

ADS1298::ADS1298():
	reset('A', 6, true),
	pwdn('A', 7, true),
	pinStart('B',10),
	diffSel('C',4)
{
	memset(zeroBuffer, 0, ADS1298_MAX_PACKET_LENGTH);
	dmaRunning=false;
}

ADS1298& ADS1298::instance(){
	static ADS1298 inst;
	return inst;
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
	reset.off();
	pwdn.off();

	OS::sleep(100);

	reset.on();
	OS::sleep(20);
	reset.off();

	OS::sleep(20);
	sendCommand(CMD_SDATAC);
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

	selectedChannels = nHardwareChannels;
	dataTransferSize = (selectedChannels + 1)*3;
	int bufSize=ecgBuffer.maxSize();
	bufSize -= bufSize % dataTransferSize;
	ecgBuffer.resize(bufSize);

	//Enable internal reference
	writeReg(REG_CONFIG3, CONFIG3_FIXED | nPD_REFBUF );

	setSpeed(DIV_4096);

	//Magic
	writeReg(REG_CONFIG2, 0);

	sendCommand(CMD_START);
	sendCommand(CMD_RDATAC);

	enableIrq();

	return true;
}

float ADS1298::setSpeed(SpeedDiv div, bool highRes){
	float fmod=((float)FCLK) / (highRes ? 4 : 8);

	if (((!highRes) && div==0) || (highRes && div>=DIV_8192))
		Logger::panic("ADS1298::setSpeed(): Invalid params");

	if (!highRes)
		div = (SpeedDiv)(div-1);

	writeReg(REG_CONFIG1, ((uint8_t)div) | (highRes ? HR : 0));

	realFreq = fmod / (1<<(4+div));

	return realFreq;
}

void ADS1298::interrupt(){
	uint8_t *buffer;

	sampleId++;

	if (dmaRunning)
		ecgBuffer.added(dataTransferSize);

	if (ecgBuffer.getContinousWriteBuffer(buffer) < dataTransferSize){
		dmaRunning=false;
		return;
	}

	dmaRunning=true;
	HAL_SPI_TransmitReceive_DMA(&hspi2,  (uint8_t*)zeroBuffer, (uint8_t*)buffer, dataTransferSize);
}

void ADS1298::stop(){
	disableIrq();
	dmaRunning=false;

	sendCommand(CMD_SDATAC);
	OS::sleep(20);
	sendCommand(CMD_STOP);
}

ADS1298::EcgBuffer &ADS1298::getBuffer(){
	return ecgBuffer;
}

uint32_t ADS1298::getSampleId(){
	return sampleId;
}

uint8_t ADS1298::getActiveChannels(){
	return selectedChannels;
}

void ADS1298::disableIrq(){
	HAL_NVIC_DisableIRQ(EXTI4_IRQn);
}

void ADS1298::enableIrq(){
	NVIC_ClearPendingIRQ(EXTI4_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

extern "C" void EXTI4_IRQHandler(void){
	ADS1298::instance().interrupt();
	NVIC_ClearPendingIRQ(EXTI4_IRQn);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
}
