#include "ECGSender.h"
#include "ADS1298.h"
#include "Bluetooth.h"


ECGSender::ECGSender(Packetizer &iPacketizer) {
	packetizer = &iPacketizer;

}

ECGSender::~ECGSender() {
}

void ECGSender::send(){
	//Create header and calculate data size
	uint8_t header[Packetizer::HEADER_SIZE + sizeof(ECGHeader)];
	ECGHeader *ecgHeader = (ECGHeader *)(header + Packetizer::HEADER_SIZE);

	ecgHeader->channelCount = ADS1298::instance().getActiveChannels();

	auto buffer = ADS1298::instance().getBuffer();
	uint32_t size = buffer.used();
	uint32_t blockSize = (ecgHeader->channelCount+1)*24;

	size -= size % blockSize;
	ecgHeader->sampleCount = size / blockSize;

	if (size==0){
		return;
	}

	//Send header
	packetizer->startPacket(header, Packetizer::ECG, (uint16_t)(size + sizeof(ECGHeader)));
	packetizer->checksumBlock((uint8_t*)ecgHeader, sizeof(ECGHeader));
	if (!Bluetooth::instance().send((char*)header, Packetizer::HEADER_SIZE + sizeof(ECGHeader), TIME_INF, false)){
		return;
	}

	//Send data
	while(size){
		uint8_t *buf;
		int currSize = std::min(buffer.getContinousReadBuffer(buf), (int)size);

		packetizer->checksumBlock(buf, currSize);
		int sent=Bluetooth::instance().send((char*)buf, currSize, TIME_INF, false);
		if (sent<=0){
			return;
		}

		buffer.skip(sent);
		size-=sent;
	}

	//Send checksum
	Packetizer::Checksum chksum = packetizer->getChecksum();
	if (!Bluetooth::instance().send((char*)&chksum, sizeof(chksum), TIME_INF, false)){
		return;
	}

	//Start transmit if not running yet
	Bluetooth::instance().send(NULL,0);
}
