#include "ADS1298.h"
#include <OS.h>
#include <Logger.h>
#include "stm32f4xx_hal.h"
#include <string.h>

extern "C" SPI_HandleTypeDef hspi2;



#define HR 0x80

#define C3_FIXED 0x40
#define C3_INTERNAL_REFERENCE_POWER_ON 0x80
#define C3_INTERNAL_RLD_REFERENCE (1<<3)
#define C3_RLD_POWER_ON (1<<2)
#define C3_RLD_SENSE_ON (1<<1)
#define C3_RLD_LEAD_OFF_STATUS (1<<0)

#define WCT1_WCTA_POWER_ON (1<<3)
#define WCT1_WCTA_CHANNEL1_POS 0
#define WCT1_WCTA_CHANNEL1_NEG 1
#define WCT1_WCTA_CHANNEL2_POS 2
#define WCT1_WCTA_CHANNEL2_NEG 3
#define WCT1_WCTA_CHANNEL3_POS 4
#define WCT1_WCTA_CHANNEL3_NEG 5
#define WCT1_WCTA_CHANNEL4_POS 6
#define WCT1_WCTA_CHANNEL4_NEG 7


ADS1298::ADS1298():
	reset('A', 6, true),
	pwdn('A', 7, true),
	pinStart('B', 10),
	diffSel('C', 4)
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
	ecgBuffer.resize(bufSize-1);

	uint8_t rldChannels = (1 << 1) | (1 << 2);
	writeReg(REG_RLD_SENSN, rldChannels);
	writeReg(REG_RLD_SENSP, rldChannels);

	//Enable internal reference
	writeReg(REG_CONFIG3,
			C3_FIXED |
			C3_INTERNAL_REFERENCE_POWER_ON |
			C3_INTERNAL_RLD_REFERENCE |
			C3_RLD_POWER_ON);

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

	if (dmaRunning) {
		ecgBuffer.added(dataTransferSize);
	}

	if (ecgBuffer.getContinuousWriteBuffer(buffer) < dataTransferSize){
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

int ADS1298::getAvailableData(){
	uint32_t size = ecgBuffer.used();
	uint32_t blockSize = (getActiveChannels()+1)*3;
	return size - size % blockSize;
}

void ADS1298::getSample(int32_t *data){
	uint8_t *src;
	uint8_t *blockStart;
	uint8_t *dest=(uint8_t*)data;

	ecgBuffer.getContinuousReadBuffer(blockStart);

	//Skip the status.
	src=blockStart+3;

	//Read, fix endianness, and sign extend
	for (int c=0; c<selectedChannels; c++, src+=3){
		*(dest++)=src[2];
		*(dest++)=src[1];
		*(dest++)=src[0];
		*(dest++)=(src[0] & 0x80) ? 0xFF : 0x00;
	}

	ecgBuffer.skip(src - blockStart);
}

void ADS1298::clear(){
	dmaRunning=false;
	ecgBuffer.clear();
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
