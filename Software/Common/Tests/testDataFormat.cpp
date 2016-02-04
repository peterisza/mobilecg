#include "BitFifo.hpp"
//#include "StreamSerializer.hpp"
#include "DifferenceEcgCompressor.hpp"
#include "FlatEcgPredictor.hpp"
#include "Packetizer.h"
#include "PacketReader.hpp"
#include <iostream>

#include "TestSignalGenerator.hpp"

#include <string.h>

using namespace std;

bool okay = true;

#define EQUALS(a, b) \
	{auto tmp = (a); if((tmp) != (b)) { cout << "FAIL " << #a << " == " << tmp << ", " << #a << " != " << (b) << endl; okay = false;}}
  

void testFifoBuffer() {
	const int size = 8;
	char buffer[size];
	ecg::BitFifo fb(buffer, size);
	EQUALS(fb.getFreeBytes(), 7);
	EQUALS(fb.getFreeBits(), 56);

	for(int trial = 0; trial < 100; trial++) {
		const int testseq[] = {5+256, 69, 1337};
		for(int i = 0; i < 3; ++i)
			EQUALS(fb.pushBits(testseq[i]+trial * 1000, 17), true);
		EQUALS(fb.getFreeBits(), 56-17*3);			
		EQUALS(fb.pushBits(1, 8), false);
		for(int i = 0; i < 3; ++i)
			EQUALS(fb.popBits(17), testseq[i]+trial * 1000);
	}

	EQUALS(fb.getFreeBits(), 56);
}
/*
void testSerialization() {
	const int size1 = 1000;
	const int size2 = 2000;
	const int packetSize = 43;
	const int bits = 10;
	char buffer1[size1], buffer2[size2];
	ecg::BitFifo fb1(buffer1, size1), fb2(buffer2, size2);
	ecg::BitFifo *fbs[2] = {&fb1, &fb2};

	for(int i = 0; i < size1-1; ++i)
		fb1.pushBits(i, bits);
	for(int i = 0; i < size2-1; ++i)
		fb2.pushBits(i, bits);
	
	
	char packet[packetSize];
	char obuffer1[size1], obuffer2[size2];
	ecg::BitFifo ofb1(obuffer1, size1), ofb2(obuffer2, size2);
	ecg::BitFifo *ofbs[2] = {&ofb1, &ofb2};	

	ecg::StreamSerializer ser(fbs, 2);		
	ecg::StreamSerializer deser(ofbs, 2);
	
	int buf1idx = 0, buf2idx = 0;
	while(ser.makePacket(packet, packetSize)) {
		//cout << "packet" << endl;
		deser.readPacket(packet, packetSize);
		while(ofb1.getAvailableBits() >= bits) {
			EQUALS(ofb1.popBits(bits), buf1idx & ((1 << bits) - 1));
			buf1idx++;
		}
		while(ofb2.getAvailableBits() >= bits) {
			EQUALS(ofb2.popBits(bits), buf2idx & ((1 << bits) - 1));
			buf2idx++;
		}
	}	
}
*/
void testEcgCompression() {
	const int bufferSize = 10000;
	char buffer[bufferSize];
	ecg::BitFifo stream(buffer, bufferSize);
	ecg::FlatEcgPredictor predictor;
	ecg::DifferenceEcgCompressor
		compressor(stream, predictor),
		decompressor(stream, predictor);
	
	predictor.setNumChannels(3);
	compressor.setNumChannels(3);
	decompressor.setNumChannels(3);
	
	
	TestSignalGenerator tsg(15000, 500);	
	int ecgdata[1000][3];
	for(int i = 0; i < 1000; ++i) {
		if(i % 100 == 0)
			predictor.reset();
		for(int ch = 0; ch < 3; ++ch) {
			bool small = rand()%10 < 4;
			//printf(small ? "small\n" : "big\n");
			if(small || i == 0)
				ecgdata[i][ch] = rand()%(1 << 19) - (1 << 18);
			else
				ecgdata[i][ch] = ecgdata[i-1][ch] + (rand()%400) - 200;
		}
		ecgdata[i][0] = tsg.getSample(2.4);
		tsg.next();
		compressor.putSample(ecgdata[i]);
	}
	predictor.reset();

	for(int i = 0; i < 1000; ++i) {
		if(i % 100 == 0)
			predictor.reset();
		int sample[3];
		decompressor.getSample(sample);
		//printf("%d %d %d - %d %d %d\n", ecgdata[i][0], ecgdata[i][1], ecgdata[i][2], sample[0], sample[1], sample[2]);
		for(int ch = 0; ch < 3; ++ch) {
			EQUALS(ecgdata[i][ch], sample[ch]);
		}
		//printf("%d\n", sample[0]);
	}
}

char* addPacket(char* buffer, const char* message) {
	static int packetId = 0;
	
	Packetizer packetizer;
	
	int length = strlen(message);
	
	packetizer.startPacket((uint8_t*) buffer, Packetizer::ECG, length);
 	Packetizer::Header *header = (Packetizer::Header*) buffer;
	strcpy(buffer+sizeof(Packetizer::Header), message);
	uint16_t *checkSum = (uint16_t*) &buffer[sizeof(Packetizer::Header) + length];
	packetizer.checksumBlock((uint8_t*) message, strlen(message));  	
 	*checkSum = packetizer.getChecksum();
 	
 	return buffer + sizeof(Packetizer::Header) + length + 2;
}

char* addRandomJunk(char* start, int length) {
	for(int i = 0; i < length; ++i)
		start[i] = i;
	return start + length;
}

void testPacketReader() {
	const int bufferSize = 2048;
	char buffer[bufferSize];
	char* ptr = buffer;
	
	const char* messages[10];
	
	ptr = addRandomJunk(ptr, 15);
	ptr = addPacket(ptr, messages[0] = "A");
	ptr = addPacket(ptr, messages[1] = "Test message 1.");
	ptr = addPacket(ptr, messages[2] = "Test message 2.");
	ptr = addRandomJunk(ptr, 100);
	ptr = addPacket(ptr, messages[3] = "Another packet test message.");
	ptr = addPacket(ptr, "Incomplete packet.") - 10;
	ptr = addPacket(ptr, messages[4] = "The packet following the incomplete one.");
	ptr = addRandomJunk(ptr, 100);	
	ptr = addPacket(ptr, messages[5] = "");
	ptr = addPacket(ptr, "") - 5;
	ptr = addPacket(ptr, messages[6] = "Final packet.");		 	
	
	PacketReader reader;
	int cnt = 0;
	for(int i = 0; i < ptr - buffer; ++i) {
		reader.addByte(buffer[i]);
		if(reader.isPacketReady()) {
			Packetizer::Header* header = reader.getPacketHeader();
			const char* data = reader.getPacketData();
			//printf("Packet received. Length=%d, ID=%d.\n", (int)header->length, (int)header->packetId);
			EQUALS((int)header->length, strlen(messages[cnt]));
			//printf("  data: [");
			for(int i = 0; i < header->length; ++i) {
				//printf("%c", data[i]);
				//EQUALS(data[i], messages[cnt][i]);
			}
			//printf("], expected=[%s]\n\n", messages[cnt]);
			cnt++;
		}
	}
}

int main()
{
	testFifoBuffer();
	//testSerialization();
	testEcgCompression();
	testPacketReader();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
