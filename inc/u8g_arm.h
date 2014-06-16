/*

  u8g_arm.h

*/

#ifndef _U8G_ARM_H
#define _U8G_ARM_H

#include "u8g.h"

////////////////// CPU Core Selection ///////////////////
//#define STM32F1
//#define STM32L1
#define STM32F4
/////////////////////////////////////////////////////////

#define PullUp 1
#define PullDown 2

#define ReadOutBitReg   ODR
#define ReadInBitReg    IDR

#ifdef STM32F1
	#include <stm32f10x.h>
	#define SetBitReg     	BSRR
	#define ResetBitReg   	BRR
#elif STM32L1
	#include <stm32l1xx.h>
	#define SetBitReg     	BSRRL
	#define ResetBitReg   	BSRRH
#else //STM32F4
	#include <stm32f4xx.h>
	#define SetBitReg     	BSRRL
	#define ResetBitReg   	BSRRH
#endif

/* system helper procedures */
#define DEFAULT_KEY PIN(0,1)

void delay_micro_seconds(uint32_t us);
uint8_t u8g_Pin(uint8_t port, uint8_t bitpos);
void u8g_SetPinOutput(uint8_t internal_pin_number);
void u8g_SetPinInput(uint8_t internal_pin_number,uint8_t pull);
void u8g_SetPinLevel(uint8_t internal_pin_number, uint8_t level);
uint16_t u8g_GetPinLevel(uint8_t internal_pin_number);
uint8_t u8g_com_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);
void u8g_Pin_Initalize(uint8_t temp);

#endif


