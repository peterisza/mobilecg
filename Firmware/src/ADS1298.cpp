#include "ADS1298.h"

ADS1298::ADS1298():
	reset('A', 6, true),
	pwdn('A', 7, true),
	pinStart('B',10),
	diffSel('C',4)
{

}

ADS1298::~ADS1298() {

}

