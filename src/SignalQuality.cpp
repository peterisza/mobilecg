#include "SignalQuality.hpp"

#define DCLIMIT 15000
#define ACLIMIT 126
#define TIMELIMIT 50
#define NOISELIMIT 4200

SignalQuality::SignalQuality():
	prevSample(0),
	prev2Sample(0),
	lastSampleGood(false),
	howLong(0),
	noiseQuantity(0),
	oobCounter(0)
{
}

void SignalQuality::processSample(int32_t raw, int8_t filtered) {
	lastSampleGood = true;
	
	if(raw > DCLIMIT || raw < -DCLIMIT)
		lastSampleGood = false;
	
	if(filtered > ACLIMIT || filtered < -ACLIMIT)
		oobCounter += 10;
	if(oobCounter > 0)	
		oobCounter--;
	
	if(oobCounter > 100)
		lastSampleGood = false;
		
	
	int noise = 0;
	if(prev2Sample < prevSample && prevSample > filtered)	
		noise = 2*prevSample - prev2Sample - filtered;
	if(prev2Sample > prevSample && prevSample < filtered)	
		noise = -2*prevSample + prev2Sample + filtered;
	noiseQuantity = (noiseQuantity*31 + (noise << 8)) >> 5;
	if(noiseQuantity > NOISELIMIT)
		lastSampleGood = false;
	
	if(lastSampleGood)
		howLong++;
	else
		howLong = 0;
	
	prev2Sample = prevSample;
	prevSample = filtered;
}

bool SignalQuality::isSignalGood() {
	return howLong > TIMELIMIT;
}

int SignalQuality::signalHasBeenGoodFor() {
	return howLong;
}

int SignalQuality::getNoiseQuantity() {
	return noiseQuantity;
}
