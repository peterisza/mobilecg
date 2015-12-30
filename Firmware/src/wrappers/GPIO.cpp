#include "GPIO.h"

GPIO::GPIO(char bank, int iPin, bool iInverter){
	switch (bank){
		case 'A':
			gpioStruct = GPIOA;
			break;
		case 'B':
			gpioStruct = GPIOB;
			break;
		case 'C':
			gpioStruct = GPIOC;
			break;
		case 'D':
			gpioStruct = GPIOD;
			break;
		default:
			gpioStruct = NULL;
	}

	this->inverted = iInverter;
	this->pin = 1<<iPin;
}

void GPIO::set(bool val){
	HAL_GPIO_WritePin(gpioStruct, pin, (val^inverted) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void GPIO::on(){
	set(true);
}

void GPIO::off(){
	set(false);
}
