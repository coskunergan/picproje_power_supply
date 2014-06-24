/************************ (C) ExpKits 2011 STM32 MCU  ***************************
*
* Dosya Adi          : main.h
*
********************************************************************************/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"//
#include "stm32f4xx_rcc.h"//
#include "stm32f4xx_exti.h"//
#include "stm32f4xx_flash.h"
#include "stm32f4xx_dma.h"//
#include "stm32f4xx_spi.h"//
#include "stm32f4xx_tim.h"//
#include "stm32f4xx_usart.h"//
#include "stm32f4xx_syscfg.h"//
#include "misc.h"//

#include "stdio.h"

#include "u8g.h"
#include "u8g_arm.h"

#include "stm32_ub_encoder_tim2.h"//encoder

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void DelayMs(uint32_t nTime);
#endif /* __MAIN_H */

/*******************************************************************************/
