/*****< hcitrcfg.h >***********************************************************/
/*      Copyright 2012 - 2013 Stonestreet One.                                */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*      Copyright 2015 Texas Instruments Incorporated.                        */
/*      All Rights Reserved.                                                  */
/*                                                                            */
/*  HCITRCFG - HCI Transport Layer Configuration parameters.                  */
/*                                                                            */
/*  Author:  Marcus Funk                                                      */
/*                                                                            */
/*** MODIFICATION HISTORY *****************************************************/
/*                                                                            */
/*   mm/dd/yy  F. Lastname    Description of Modification                     */
/*   --------  -----------    ------------------------------------------------*/
/*   11/08/12  M. Funk        Initial creation.                               */
/*   11/02/15  D. Keren       Changing nShutdown pin from PC9 to PC8          */
/******************************************************************************/
#ifndef __HCITRCFGH__
#define __HCITRCFGH__


#include "stm32f4xx_hal.h"      /* STM32F GPIO control functions.            */


#include "BTAPITyp.h"            /* Bluetooth API Type Definitions.           */

#include "stm32f4xx.h"           /* STM32F register definitions.              */
#if 0
#include "stm32f4xx_usart.h"     /* STM32F USART control functions.           */
#include "stm32f4xx_rcc.h"       /* STM32F Clock control functions.           */
#include "stm32f4xx_dma.h"       /* STM32F DMA control functions.             */
#include "stm32f4xx_exti.h"      /* STM32F Ext interrupt definitions.         */
#include "stm32f4xx_syscfg.h"    /* STM32F system config definitions.         */
#endif

   /* The following definitions define the UART/USART to be used by the */
   /* HCI transport and the pins that will be used by the UART.  Please */
   /* consult the processor's documentation to determine what pins are  */
   /* available for the desired UART.                                   */
   /* * NOTE * The TXD, RXD, RTS and CTS pins MUST be map-able to the   */
   /*          selected UART.  The RESET pin may be any available GPIO. */
   /* * NOTE * The DMA settinsg (Number = 1 or 2, Stream and channel)   */
   /*          must map to the RXD and TXD streams for the selected     */
   /*          UART.                                                    */
#define HCITR_UART               2

#define HCITR_TXD_PORT           A
#define HCITR_TXD_PIN            2

#define HCITR_RXD_PORT           A
#define HCITR_RXD_PIN            3

#define HCITR_RTS_PORT           A
#define HCITR_RTS_PIN            1

#define HCITR_CTS_PORT           A
#define HCITR_CTS_PIN            0

#define HCITR_RESET_PORT         C
#define HCITR_RESET_PIN          13

   /* The following definitons define the DMA infomation for receive and*/
   /* transmit on the HCI UART.  This includes the DMA number (either 1 */
   /* or 2) as well as the stream and channel.                          */
   /* * NOTE * The DMA information MUST map to the receive and transmit */
   /*          DMA for the specified UART (see the DMA sections of the  */
   /*          processor's User Manual).                                */
#define HCITR_DMA_RXD_NUMBER     1
#define HCITR_DMA_RXD_STREAM     5
#define HCITR_DMA_RXD_CHANNEL    5

#define HCITR_DMA_TXD_NUMBER     1
#define HCITR_DMA_TXD_STREAM     6
#define HCITR_DMA_TXD_CHANNEL    5

   /* Define the following to enable suspend functionality within       */
   /* HCITRANS.  This will shut down the UART when HCITR_COMSuspend() is*/
   /* called and resume normal functionality when data is received in   */
   /* transmitted.                                                      */
   /* * NOTE * This functionality requires using a lower power protocol */
   /*          such as HCILL and the UART should only be suspended when */
   /*          indicated it is safe to do so by the protocol driver.    */
#undef SUPPORT_TRANSPORT_SUSPEND

   /* Define the following if software managed flow control is being    */
   /* used and the NVIC interrupt for the CTS EXTI line is being also   */
   /* used by another EXTI line.  The specified function can then be    */
   /* called by a global interrupt handler when the CTS EXTI interrupt  */
   /* occurs.                                                           */
   /* * NOTE * If defined when software managed flow control is used,   */
   /*          the NVIC interrupt associated with the CTS EXTI line MUST*/
   /*          be handled externally and call this function.  If not    */
   /*          defined, the interrupt will be handled directly by       */
   /*          HCITRANS.                                                */
// #define HCITR_CTS_IRQ_HANDLER HCITR_CTS_IrqHandler

   /* Define the following to enable debug logging of HCI traffic.  If  */
   /* this macro is defined, all incomming and outgoing traffic will be */
   /* logged via BTPS_OutputMessage().                                  */
// #define HCITR_ENABLE_DEBUG_LOGGING


/************************************************************************/
/* !!!DO NOT MODIFY PAST THIS POINT!!!                                  */
/************************************************************************/

   /* The following section builds the macros that can be used with the */
   /* STM32F standard peripheral libraries based on the above           */
   /* configuration.                                                    */

   /* Standard C style concatenation macros                             */
#define DEF_CONCAT2(_x_, _y_)          __DEF_CONCAT2__(_x_, _y_)
#define __DEF_CONCAT2__(_x_, _y_)      _x_ ## _y_

#define DEF_CONCAT3(_x_, _y_, _z_)     __DEF_CONCAT3__(_x_, _y_, _z_)
#define __DEF_CONCAT3__(_x_, _y_, _z_) _x_ ## _y_ ## _z_

   /* Determine the Peripheral bus that is used by the UART.            */
#if ((HCITR_UART == 1) ||(HCITR_UART == 6))
   #define HCITR_UART_APB              2
#else
   #define HCITR_UART_APB              1
#endif

   /* Determine the type of UART.                                       */
#if ((HCITR_UART == 1) || (HCITR_UART == 2) || (HCITR_UART == 3) || (HCITR_UART == 6))

   #define HCITR_UART_TYPE             USART

#else
   #error Unknown HCITR_UART or UART not supported
#endif

   /* The following section builds the macro names that can be used with*/
   /* the STM32F standard peripheral libraries.                         */

   /* UART control mapping.                                             */
#define HCITR_UART_BASE                (DEF_CONCAT2(HCITR_UART_TYPE, HCITR_UART))


   /* GPIO mapping.                                                     */
#define HCITR_TXD_GPIO_PORT            (DEF_CONCAT2(GPIO, HCITR_TXD_PORT))
#define HCITR_RXD_GPIO_PORT            (DEF_CONCAT2(GPIO, HCITR_RXD_PORT))
#define HCITR_RTS_GPIO_PORT            (DEF_CONCAT2(GPIO, HCITR_RTS_PORT))
#define HCITR_CTS_GPIO_PORT            (DEF_CONCAT2(GPIO, HCITR_CTS_PORT))
#define HCITR_RESET_GPIO_PORT          (DEF_CONCAT2(GPIO, HCITR_RESET_PORT))

#define HCITR_TXD_GPIO_AHB_BIT         (DEF_CONCAT2(RCC_AHB1Periph_GPIO, HCITR_TXD_PORT))
#define HCITR_RXD_GPIO_AHB_BIT         (DEF_CONCAT2(RCC_AHB1Periph_GPIO, HCITR_RXD_PORT))
#define HCITR_RTS_GPIO_AHB_BIT         (DEF_CONCAT2(RCC_AHB1Periph_GPIO, HCITR_RTS_PORT))
#define HCITR_CTS_GPIO_AHB_BIT         (DEF_CONCAT2(RCC_AHB1Periph_GPIO, HCITR_CTS_PORT))
#define HCITR_RESET_GPIO_AHB_BIT       (DEF_CONCAT2(RCC_AHB1Periph_GPIO, HCITR_RESET_PORT))

   /* DMA Mapping.                                                      */
#define HCITR_TXD_DMA_AHB_BIT          (DEF_CONCAT2(RCC_AHB1Periph_DMA, HCITR_DMA_TXD_NUMBER))
#define HCITR_TXD_DMA_CHANNEL          (DEF_CONCAT2(DMA_CHANNEL_, HCITR_DMA_TXD_CHANNEL))
#define HCITR_TXD_DMA_STREAM           (DEF_CONCAT2(DEF_CONCAT3(DMA, HCITR_DMA_TXD_NUMBER, _Stream), HCITR_DMA_TXD_STREAM))
#define HCITR_RXD_DMA_AHB_BIT          (DEF_CONCAT2(RCC_AHB1Periph_DMA, HCITR_DMA_RXD_NUMBER))
#define HCITR_RXD_DMA_CHANNEL          (DEF_CONCAT2(DMA_CHANNEL_, HCITR_DMA_RXD_CHANNEL))
#define HCITR_RXD_DMA_STREAM           (DEF_CONCAT2(DEF_CONCAT3(DMA, HCITR_DMA_RXD_NUMBER, _Stream), HCITR_DMA_RXD_STREAM))

#define HCITR_TXD_DMA_FLAG_TCIF        (DEF_CONCAT2(DMA_FLAG_TCIF, HCITR_DMA_TXD_STREAM))
#define HCITR_TXD_DMA_FLAG_HTIF        (DEF_CONCAT2(DMA_FLAG_HTIF, HCITR_DMA_TXD_STREAM))
#define HCITR_TXD_DMA_FLAG_TEIF        (DEF_CONCAT2(DMA_FLAG_TEIF, HCITR_DMA_TXD_STREAM))
#define HCITR_TXD_DMA_FLAG_DMEIF       (DEF_CONCAT2(DMA_FLAG_DMEIF, HCITR_DMA_TXD_STREAM))
#define HCITR_TXD_DMA_FLAG_FEIF        (DEF_CONCAT2(DMA_FLAG_FEIF, HCITR_DMA_TXD_STREAM))

#define HCITR_RXD_DMA_FLAG_TCIF        (DEF_CONCAT2(DMA_FLAG_TCIF, HCITR_DMA_RXD_STREAM))
#define HCITR_RXD_DMA_FLAG_HTIF        (DEF_CONCAT2(DMA_FLAG_HTIF, HCITR_DMA_RXD_STREAM))
#define HCITR_RXD_DMA_FLAG_TEIF        (DEF_CONCAT2(DMA_FLAG_TEIF, HCITR_DMA_RXD_STREAM))
#define HCITR_RXD_DMA_FLAG_DMEIF       (DEF_CONCAT2(DMA_FLAG_DMEIF, HCITR_DMA_RXD_STREAM))
#define HCITR_RXD_DMA_FLAG_FEIF        (DEF_CONCAT2(DMA_FLAG_FEIF, HCITR_DMA_RXD_STREAM))

#define HCITR_TXD_IRQ                  (DEF_CONCAT3(DEF_CONCAT3(DMA, HCITR_DMA_TXD_NUMBER, _Stream), HCITR_DMA_TXD_STREAM, _IRQn))
#define HCITR_RXD_IRQ                  (DEF_CONCAT3(DEF_CONCAT3(DMA, HCITR_DMA_RXD_NUMBER, _Stream), HCITR_DMA_RXD_STREAM, _IRQn))

   /* Location of the Data register for the UART in use.                */
#define HCITR_UART_DR_REGISTER_ADDRESS (((unsigned int)(DEF_CONCAT3(HCITR_UART_TYPE, HCITR_UART, _BASE))) + 4)

   /* Interrupt mapping.                                                */
#ifdef SUPPORT_TRANSPORT_SUSPEND

   #if (HCITR_CTS_PIN   < 5)
      #define HCITR_CTS_EXTI_NUMBER    HCITR_CTS_PIN
   #elif (HCITR_CTS_PIN < 10)
      #define HCITR_CTS_EXTI_NUMBER    9_5
   #elif (HCITR_CTS_PIN < 16)
      #define HCITR_CTS_EXTI_NUMBER    15_10
   #endif

   /* NOTE: "EXTI" is defined in the STM32F std periph headers so can   */
   /* not be used directly.                                             */
   #define HCITR_CTS_IRQ               (DEF_CONCAT3(EXT, DEF_CONCAT2(I, HCITR_CTS_EXTI_NUMBER), _IRQn))
   #define HCITR_CTS_EXTI_PORT         (DEF_CONCAT2(EXTI_PortSourceGPIO, HCITR_CTS_PORT))
   #define HCITR_CTS_IRQ_LINE          (DEF_CONCAT2(EXTI_Line, HCITR_CTS_PIN))

   #ifndef HCITR_CTS_IRQ_HANDLER
      #define HCITR_CTS_IRQ_HANDLER    (DEF_CONCAT3(EXT, DEF_CONCAT2(I, HCITR_CTS_EXTI_NUMBER), _IRQHandler))
   #endif

#endif

#endif

