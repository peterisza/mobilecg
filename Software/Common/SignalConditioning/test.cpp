#include "488Hz50HzNotchFilter.hpp"

#include <stdio.h>
#include <math.h>

#include <iostream>

using namespace std;

bool okay = true;

#define EQUALS(a, b) \
	{auto tmp = (a); if((tmp) != (b)) { cout << "FAIL " << #a << " == " << tmp << ", " << #a << " != " << (b) << endl; okay = false;}}


float fs = 500*2000/2048;

float testFrequency(NotchFilter &nf, float freq)
{
	printf("testing frequency %f... ", freq);
	float min = 0;
	float max = 0;
	float amp = 100000;
	for(int i = 0; i < 10000; ++i) {
		int32_t r = amp*cos(i*2*M_PI/fs*freq);
		int32_t f = nf.filter(r);
		if(i < 5000)
			continue;
		if(max == 0 || f > max)
			max = f;
		if(min == 0 || f < min)
			min = f;
		//printf("%d %d\n", r, f);
	}
	float r = (max-min) / amp / 2.0;
	printf("%f\n", r);	
	return r;
}

void testNotchFilter()
{
	NotchFilter nf;
	testFrequency(nf, 0);
	testFrequency(nf, 10);
	testFrequency(nf, 20);
	testFrequency(nf, 30);	
	testFrequency(nf, 40);
	testFrequency(nf, 45);
	testFrequency(nf, 49);	
	testFrequency(nf, 50);
	testFrequency(nf, 51);
	testFrequency(nf, 55);	
	testFrequency(nf, 60);	
	testFrequency(nf, 70);
	testFrequency(nf, 80);	
	testFrequency(nf, 100);
	testFrequency(nf, 150);
}

int main()
{
	testNotchFilter();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
