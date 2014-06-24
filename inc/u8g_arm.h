/*
  
  u8g_arm.h
  
  Header file for u8g LPC11xx utility procedures 

  Universal 8bit Graphics Library
  
  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/


#ifndef _U8G_ARM_H
#define _U8G_ARM_H

#include "main.h"
#include "u8g.h" 

/////////////////////////////////////////////////////////
//#define STM32F1   // STM32L serisi icin bu sat1r1 kaldir
/////////////////////////////////////////////////////////

#define ReadOutBitReg   	ODR
#define ReadInBitReg    	IDR
#ifdef STM32F1
	#define SetBitReg     	BSRR
	#define ResetBitReg   	BRR
#else
	#define SetBitReg     	BSRRL
	#define ResetBitReg   	BSRRH
#endif

// Lcd Pinlerinin Set/Reset Tanimlamalari
#define	 LCD_A0						GPIO_Pin_8
#define	 LCD_A0_PORT		GPIOD
	 
#define	 LCD_E	 					GPIO_Pin_10
#define	 LCD_E_PORT	  		GPIOD
	 
#define	 LCD_RW						GPIO_Pin_9
#define	 LCD_RW_PORT    	GPIOD
	 
#define	 LCD_RESET					GPIO_Pin_13
#define	 LCD_RESET_PORT 	GPIOD
	 
#define	 LCD_CS1					GPIO_Pin_12
#define	 LCD_CS1_PORT		GPIOD

#define	 LCD_CS2					GPIO_Pin_11
#define	 LCD_CS2_PORT		GPIOD

#define	 LCD_8BIT_PORT		GPIOE
#define	 LCD_BIT_START			0

/////////////////////////////////////////////////////

#define	 LCD_BL						GPIO_Pin_8
#define	 LCD_BL_PORT		 	GPIOA

#define	 LCD_VCC					GPIO_Pin_10
#define	 LCD_VCC_PORT			GPIOA

#define	 HC164_CLK				GPIO_Pin_1
#define	 HC164_CLK_PORT		GPIOC

#define	 HC164_DATA				GPIO_Pin_0
#define	 HC164_DATA_PORT	GPIOC

// Lcd Pinlerinin register degisimleri

#define Lcd_A0_Low   			LCD_A0_PORT->ResetBitReg = LCD_A0
#define Lcd_A0_High   	 		LCD_A0_PORT->SetBitReg = LCD_A0
#define Lcd_E_Low   	  		LCD_E_PORT->ResetBitReg = LCD_E
#define Lcd_E_High   	 		LCD_E_PORT->SetBitReg = LCD_E
#define Lcd_RW_Low   		    LCD_RW_PORT->ResetBitReg = LCD_RW
#define Lcd_RW_High   	 		LCD_RW_PORT->SetBitReg = LCD_RW
#define Lcd_Reset_Low   	  	LCD_RESET_PORT->ResetBitReg = LCD_RESET
#define Lcd_Reset_High   	 	LCD_RESET_PORT->SetBitReg = LCD_RESET
#define Lcd_Cs1_Low   			LCD_CS1_PORT->ResetBitReg = LCD_CS1
#define Lcd_Cs1_High   	 		LCD_CS1_PORT->SetBitReg = LCD_CS1
#define Lcd_Cs2_Low   			LCD_CS2_PORT->ResetBitReg = LCD_CS2
#define Lcd_Cs2_High   	 		LCD_CS2_PORT->SetBitReg = LCD_CS2
#define Lcd_BackLight_Aktif 	LCD_BL_PORT->ResetBitReg = LCD_BL
#define Lcd_BackLight_Pasif 	LCD_BL_PORT->SetBitReg = LCD_BL
#define Lcd_Aktif   			LCD_VCC_PORT->ResetBitReg = LCD_VCC
#define Lcd_Pasif   			LCD_VCC_PORT->SetBitReg = LCD_VCC
#define Lcd_Aktif_K   			((LCD_VCC_PORT->ReadOutBitReg & LCD_VCC) == 0)
#define Hc164_Clk_Low   		HC164_CLK_PORT->ResetBitReg = HC164_CLK
#define Hc164_Clk_High  	 	HC164_CLK_PORT->SetBitReg = HC164_CLK
#define Hc164_Data_Low   		HC164_DATA_PORT->ResetBitReg = HC164_DATA
#define Hc164_Data_High  	 	HC164_DATA_PORT->SetBitReg = HC164_DATA
#define Lcd_8bit_Data(x)   		LCD_8BIT_PORT->ReadOutBitReg=(x<<LCD_BIT_START)

/* system helper procedures */
#define PIN(base,bit) ((base)*16+(bit))
#define DEFAULT_KEY PIN(0,1)

void delay_micro_seconds(uint32_t us);

uint8_t u8g_Pin(uint8_t port, uint8_t bitpos);
void u8g_SetPinOutput(uint8_t internal_pin_number);
void u8g_SetPinInput(uint8_t internal_pin_number,uint8_t pull);
void u8g_SetPinLevel(uint8_t internal_pin_number, uint8_t level);
uint16_t u8g_GetPinLevel(uint8_t internal_pin_number);
uint8_t u8g_com_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr);

#endif


