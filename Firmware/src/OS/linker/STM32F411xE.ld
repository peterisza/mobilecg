/**
 * linker script for STM32F405, STM32F407, STM32F415 
 * and STM32F417 microcontrollers
 */ 

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  128K       /* Main RAM (can be accessed by DMA) */
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH =  512k       /* Flash */
	BATTRAM (rw): ORIGIN = 0x40024000, LENGTH =    4K       /* Battery backed RAM */
	CCRAM (rw)	: ORIGIN = 0x10000000, LENGTH =    0K       /* Core coupled RAM (can NOT be accessed by DMA) */
}

INCLUDE "stm32.ld"
