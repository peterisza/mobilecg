/*
 * Logger.cpp
 *
 *  Created on: 2015. dec. 22.
 *      Author: xdever
 */

#include "Logger.h"
#include <cmsis_os.h>
#include <helpers.h>

Logger::Logger() {
	// TODO Auto-generated constructor stub

}

Logger::~Logger() {
	// TODO Auto-generated destructor stub
}

void Logger::panic(const char *message){
	UNUSED(message);

	__disable_irq();
	for(;;);
}
