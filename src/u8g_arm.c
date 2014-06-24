/*
  
  u8g_arm.c
  

  u8g utility procedures for LPC11xx

  Universal 8bit Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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

 
  The following delay procedures must be implemented for u8glib. This is done in this file:

  void u8g_Delay(uint16_t val)		Delay by "val" milliseconds
  void u8g_MicroDelay(void)		Delay be one microsecond
  void u8g_10MicroDelay(void)	Delay by 10 microseconds
  
  Additional requirements:
  
*/

#include "u8g_arm.h"

GPIO_InitTypeDef GPIO_InitStructure;

//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin kapali dongu bekleme fonksiyonu
// 32mhz hse optimize-1 ( 10->13us ) (1->2us)
//////////////////////////////////////////////////////////////////////////////////////////////
void delay_micro_seconds(uint32_t us) 
{
	us*=2;
	while(us--)
	{
		__NOP();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen deger kadar X us bekleyen fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void Send_74HC164(uint8_t byte) 
{ 
		 uint8_t i=8; 
	
		while(i--)
		{			
				Hc164_Clk_Low;			
			if(byte&0x80)
				Hc164_Data_High;
			else 
				Hc164_Data_Low;
				byte<<=1;			
				Hc164_Clk_High;
		}
} 
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen deger kadar Ms bekleyen fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_Delay(uint16_t val)
{
  delay_micro_seconds(1000UL*(uint32_t)val);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin sabit 1 us bekleyen fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_MicroDelay(void)
{
  delay_micro_seconds(1);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin sabit 10 us bekleyen fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_10MicroDelay(void)
{
  delay_micro_seconds(10);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// U8Glib pin kriptolamay1 yapan fonksiyon (pin bilgisi 1 byte a saklanir)
//////////////////////////////////////////////////////////////////////////////////////////////
/* convert "port" and "bitpos" to internal pin number */
uint8_t u8g_Pin(uint8_t port, uint8_t bitpos)
{
  port <<= 4;// arm * 16
  port += bitpos;
  return port;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini OUTPUT yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinOutput(uint8_t internal_pin_number)
{	
		uint8_t temp = (internal_pin_number>>4);		
		GPIO_InitStructure.GPIO_Pin = 1<<(internal_pin_number&15);
#ifdef STM32F1
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#else	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#endif	
		if(temp==0xA)
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		else if(temp==0xB)
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		else if(temp==0xC)
			GPIO_Init(GPIOC, &GPIO_InitStructure);
		else if(temp==0xD)
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		else if(temp==0xE)
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		else if(temp==0xF)
			GPIO_Init(GPIOF, &GPIO_InitStructure);			
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini INPUT ve PULL-UP yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinInput(uint8_t internal_pin_number,uint8_t pull)
{
		uint8_t temp = (internal_pin_number>>4);	
		GPIO_InitStructure.GPIO_Pin = 1<<(internal_pin_number&15);
#ifdef STM32F1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
#else	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
#endif
		if(temp==0xA)
			GPIO_Init(GPIOA, &GPIO_InitStructure);
		else if(temp==0xB)
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		else if(temp==0xC)
			GPIO_Init(GPIOC, &GPIO_InitStructure);
		else if(temp==0xD)
			GPIO_Init(GPIOD, &GPIO_InitStructure);
		else if(temp==0xE)
			GPIO_Init(GPIOE, &GPIO_InitStructure);
		else if(temp==0xF)
			GPIO_Init(GPIOF, &GPIO_InitStructure);				
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini HIGH yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinLevel(uint8_t internal_pin_number, uint8_t level)
{
	uint16_t temp_pin=(1<<(internal_pin_number&15)); 				
	uint8_t temp_port = (internal_pin_number>>4);	
	
	if(level)
	{
		if(temp_port==0xA)  // set
					GPIOA->SetBitReg = temp_pin; 
		else if(temp_port==0xB)
					GPIOB->SetBitReg = temp_pin; 
		else if(temp_port==0xC)
					GPIOC->SetBitReg = temp_pin; 
		else if(temp_port==0xD)
					GPIOD->SetBitReg = temp_pin; 
		else if(temp_port==0xE)
 					GPIOE->SetBitReg = temp_pin; 
	 	else if(temp_port==0xF)
		 			GPIOF->SetBitReg = temp_pin; 
	}else
	{
		if(temp_port==0xA)// Reset
					GPIOA->ResetBitReg = temp_pin; 
		else if(temp_port==0xB)
					GPIOB->ResetBitReg = temp_pin;
		else if(temp_port==0xC)
					GPIOC->ResetBitReg = temp_pin; 
		else if(temp_port==0xD)
					GPIOD->ResetBitReg = temp_pin; 
		else if(temp_port==0xE)
					GPIOE->ResetBitReg = temp_pin; 
		else if(temp_port==0xF)
					GPIOF->ResetBitReg = temp_pin; 
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini LOW yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
uint16_t u8g_GetPinLevel(uint8_t internal_pin_number)
{
	uint16_t temp_pin=(1<<(internal_pin_number&15)); 	
	uint8_t temp_port = (internal_pin_number>>4);
	
		if(temp_port==0xA)
	return (GPIOA->ReadInBitReg & temp_pin);
		else if(temp_port==0xB)
	return (GPIOB->ReadInBitReg & temp_pin);
		else if(temp_port==0xC)
	return (GPIOC->ReadInBitReg & temp_pin);
		else if(temp_port==0xD)
	return (GPIOD->ReadInBitReg & temp_pin);
		else if(temp_port==0xE)
	return (GPIOE->ReadInBitReg & temp_pin);
		else if(temp_port==0xF)
	return (GPIOF->ReadInBitReg & temp_pin);	
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin u8glib API haberlesme yapisi
//////////////////////////////////////////////////////////////////////////////////////////////
uint8_t u8g_com_sw_spi_fn(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:
      break;
    
    case U8G_COM_MSG_ADDRESS:   /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
		{
			if( arg_val == 1 ) 
						Lcd_A0_High;
			else 
						Lcd_A0_Low;
			u8g_MicroDelay();
     break;
		}
    case U8G_COM_MSG_CHIP_SELECT:
		{
      if ( arg_val == 1 )
			{
					Lcd_Cs1_High;
					Lcd_Cs2_Low;			
			}
      else if ( arg_val == 2 )
			{
					Lcd_Cs2_High;
					Lcd_Cs1_Low;	
			}else
			{
					Lcd_Cs1_Low;	
					Lcd_Cs2_Low;
			}				
			u8g_MicroDelay();
      break;
		}
    case U8G_COM_MSG_RESET:
		{
			if( arg_val == 1 )
					Lcd_Reset_High;
			else 				
					Lcd_Reset_Low;
      u8g_10MicroDelay();
      break;
		}
    case U8G_COM_MSG_WRITE_BYTE:
		{
			delay_micro_seconds(105);
			Lcd_8bit_Data(arg_val);
      Lcd_E_High;      // E  --> 1 
	  	u8g_MicroDelay();
      Lcd_E_Low;       // E  --> 0		
      break;
		}
    case U8G_COM_MSG_WRITE_SEQ:
		{
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
					delay_micro_seconds(105);
					Lcd_8bit_Data(*ptr++);		
					Lcd_E_High;   // E  --> 1 
					u8g_MicroDelay();
					Lcd_E_Low;    // E  --> 0					
          arg_val--;
        }	
			break;				
		}
    case U8G_COM_MSG_WRITE_SEQ_P:
		{
        register uint8_t *ptr = arg_ptr;
        while( arg_val > 0 )
        {
					delay_micro_seconds(105);
					Lcd_8bit_Data(*ptr++);		
					Lcd_E_High;                     // E  --> 1 
					u8g_MicroDelay();
					Lcd_E_Low;                       // E  --> 0					
          arg_val--;
        }		
      break;				
		}			
  }
  return 1;
}


