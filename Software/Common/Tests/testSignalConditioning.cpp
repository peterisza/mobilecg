#include "EcgFilters.hpp"
#include "IIRFilterChain.hpp"

#include <stdio.h>
#include <math.h>

#include <iostream>

using namespace std;

bool okay = true;

#define EQUALS(a, b) \
	{auto tmp = (a); if((tmp) != (b)) { cout << "FAIL " << #a << " == " << tmp << ", " << #a << " != " << (b) << endl; okay = false;}}


double fs = 500.0*2000.0/2048.0;

float testFrequency(EcgFilter &nf, double freq)
{
	printf("testing frequency %f... ", freq);
	double min = 0;
	double max = 0;
	double amp = 1;
	for(int i = 0; i < 488*100; ++i) {
		double r = amp*cos(i*freq*2.0*M_PI/fs);
		nf.putSample(r);
		if(!nf.isOutputAvailable())
			continue;
		double f = nf.getSample();
		if(i < 488*50)
			continue;
		if(max == 0 || f > max)
			max = f;
		if(min == 0 || f < min)
			min = f;
		//printf("%d %d\n", r, f);
	}
	double r = (max-min) / amp / 2.0;
	printf("%f\n", r);	
	return r;
}

void testEcgFilter()
{
	EcgFilter nf;
	testFrequency(nf, 0);
	testFrequency(nf, 0.2);
	testFrequency(nf, 0.5);
	testFrequency(nf, 0.9);
	testFrequency(nf, 1);
	testFrequency(nf, 2);
	testFrequency(nf, 10);
	testFrequency(nf, 20);
	testFrequency(nf, 30);	
	testFrequency(nf, 40);
	testFrequency(nf, 45);
	testFrequency(nf, 49);	
	testFrequency(nf, 49.97);
	testFrequency(nf, 49.98);
	testFrequency(nf, 49.99);
	testFrequency(nf, 50);
	testFrequency(nf, 50.01);
	testFrequency(nf, 50.02);
	testFrequency(nf, 50.03);
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
	testEcgFilter();
	
	if(okay) {
		cout << "All tests passed." << endl;
		return 0;
	}
	else
		return 1;
}
