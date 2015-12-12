/*
 * support.c
 *
 *  Created on: 2015. dec. 12.
 *      Author: xdever
 */
#include <scmRTOS.h>
#include "stm32f4xx_hal.h"

void LOCK_SYSTEM_TIMER()   { SysTick->CTRL &= SysTick_CTRL_TICKINT_Msk; }
void UNLOCK_SYSTEM_TIMER() { SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; }

static bool osTimerStarted=false;

OS_INTERRUPT void HAL_SYSTICK_Callback(){
	if (osTimerStarted)
		OS::system_timer_isr();
}

extern "C" void __init_system_timer(){
	osTimerStarted=true;
}

extern "C" {
	uint32_t SystemCoreClock;
}
