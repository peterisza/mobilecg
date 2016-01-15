#include "BitFifo.hpp"
#include "StreamSerializer.hpp"
#include "DifferenceEcgCompressor.hpp"
#include "FlatEcgPredictor.hpp"
#include <iostream>

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

void testEcgCompression() {
	const int bufferSize = 10000;
	char buffer[bufferSize];
	ecg::BitFifo stream(buffer, bufferSize);
	ecg::FlatEcgPredictor predictor(3);
	ecg::DifferenceEcgCompressor
		compressor(stream, 3, predictor),
		decompressor(stream, 3, predictor);
	
	int ecgdata[1000][3];
	for(int i = 0; i < 1000; ++i) {
		for(int ch = 0; ch < 3; ++ch)
			ecgdata[i][ch] = rand()%(1 << 24) - (1 << 23);
		compressor.putSample(ecgdata[i]);
	}
	predictor.reset();
	for(int i = 0; i < 10; ++i) {
		int sample[3];
		decompressor.getSample(sample);
		printf("%d %d %d - %d %d %d\n", ecgdata[i][0], ecgdata[i][1], ecgdata[i][2], sample[0], sample[1], sample[2]);
	}
	
	
}

int main()
{
	testFifoBuffer();
	testSerialization();
	testEcgCompression();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
