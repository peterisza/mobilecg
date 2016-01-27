#include "CircularBuffer.h"
#include <iostream>
#include <string.h>

using namespace std;

bool okay = true;

#define EQUALS(a, b) \
	{auto tmp = (a); if((tmp) != (b)) { cout << "FAIL " << #a << " == " << tmp << ", " << #a << " != " << (b) << endl; okay = false;}}
  

void test1() {
	const int sampleSize = 27;
	const int bufferSize = sampleSize * 100;
	const int ECG_MAX_SEND_SIZE = 100;
	
	
	CircularBuffer<uint8_t, 4096, true> buffer;
	buffer.resize(bufferSize);
	
	int space = 0;
	uint8_t *data;
	while(space = buffer.getContinuousWriteBuffer(data)) {
		printf("%d bytes free, adding %d bytes.\n", space, sampleSize);
		buffer.added(sampleSize);
	}
	printf("\n");
	for(int i = 0; i < 300; ++i) {
		uint32_t size = buffer.used();

		if (size>ECG_MAX_SEND_SIZE)
			size=ECG_MAX_SEND_SIZE;

		size -= size % sampleSize;
	
		printf("%d bytes available.\n", size);
		
		uint8_t dummyBuffer[10000];
		for (unsigned pos=0; pos<size; pos+=sampleSize) {
			buffer.get(dummyBuffer, sampleSize);
			printf("    getting %d bytes.\n", sampleSize);
		}
	}
}

int main()
{
	test1();
	//testSerialization();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
