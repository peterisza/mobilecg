#include "FifoBuffer.hpp"
#include <iostream>

using namespace std;

bool okay = true;

#define EQUALS(a, b) \
	{auto tmp = (a); if((tmp) != (b)) { cout << "FAIL " << #a << " == " << tmp << ", " << #a << " != " << (b) << endl; okay = false;}}
  

void testFifoBuffer() {
	const int size = 8;
	char buffer[size];
	ecg::FifoBuffer fb(buffer, size);
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
	ecg::FifoBuffer fbs[];	
	Serializer
}

int main()
{
	testFifoBuffer();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
