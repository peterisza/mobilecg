#ifndef SRC_WRAPPERS_GPIO_H_
#define SRC_WRAPPERS_GPIO_H_

extern "C"{
	#include "stm32f4xx_hal.h"
}

class GPIO{
	private:
		GPIO_TypeDef* gpioStruct;
		uint32_t pin;
	public:
		GPIO(char bank, int pin);
		void set(bool val);
		void on();
		void off();
};



#endif /* SRC_WRAPPERS_GPIO_H_ */
