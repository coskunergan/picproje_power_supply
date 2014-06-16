/*

  u8g_dev_null.c

  Universal 8bit Graphics Library
  
  Copyright (c) 2011, olikraus@gmail.com
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

#include "u8g.h"

#define WIDTH 128
#define HEIGHT 64
#define PAGE_HEIGHT 8

/**
  ******************************************************************************
  * @file    stm32l1xx_glcd.c
  * @author  Coskun ERGAN
  * @version V1.1.0
  * @date    01-Nisan-2014
  * @brief   Bu dosya YMS12864 glcd kütüpanesidir.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
//#include "stm32l1xx_NT7538.h"
//#include "stm32l1xx_lcd_tablo2.h"

#define WIDTH 128
#define HEIGHT 64
#define PAGE_HEIGHT 8

static const uint8_t u8g_dev_nt7538_128x64_init_seq[] PROGMEM = {
  U8G_ESC_DLY(20),         /* delay 20 ms */	
  U8G_ESC_CS(0),             /* enable chip */
  U8G_ESC_RST(0),           /* do reset low pulse with (1*16)+2 milliseconds */	
  U8G_ESC_ADR(0),           /* command mode */	
	0xA0,  // ADC select (A0=normal , A1=reverse) // Ekrani Tersten yazar
	0x40,  // Display start line set (Specifies Ram display line for COM0)
	0xA6,  // Normal/Reverse display (A6=normal , A7=reverse) // renkleri ters çevirir
	0xA4,  // Entire display On/Off (A5=entire display on , A4=normal display mode)
	0xA2,  // Lcd bias set (A2=1/9 , A3= 1/7)
	0xE0,  // increments column adress counter during each write
	0xC8,  // Common output mode select (C0-C7=normal , C8-CF=reverse)
	0x2F,  // Power control set (voltage follower,voltage regulator,voltage booster on)
	0x24,  // V0 voltage regulator internal resistor ratio set(0x20=small , 27=large)
	0x81,  // Elektronik volume mode set
	0x1D,  // (01=small , 3F=large)     
	0xAD,  // Set static indicator On/Off(AC=static indicator Off , AD=static indicator On)
	0x03,  // (00=Off, 01=On(1second interval) , 02=On(0,5second interval) , 03=constantly on)  
	0xE4,  // Oscillation frequency (E4=31,4 kHz , E5=26,3 kHz)
	0x82,  // Partial display mode set (82=normal display , 83=partial display)
	0xE6,  // DC/DC clock set
	0x00,   // division=0 , fosc*/ 
	0xAF,
  U8G_ESC_DLY(20),         /* delay 20 ms */
  U8G_ESC_END                /* end of sequence */
};



uint8_t u8g_dev_nt7538_128x64_fn(u8g_t *u8g, u8g_dev_t *dev, uint8_t msg, void *arg)
{
  switch(msg)
  {
    case U8G_DEV_MSG_SET_8PIXEL:                /* most often used command */
      break;
    case U8G_DEV_MSG_SET_PIXEL:
      break;
    case U8G_DEV_MSG_INIT:
					u8g_WriteEscSeqP(u8g, dev, u8g_dev_nt7538_128x64_init_seq);
      break;
    case U8G_DEV_MSG_STOP:
      break;
    case U8G_DEV_MSG_PAGE_FIRST:
      break;
    case U8G_DEV_MSG_PAGE_NEXT:
		{
			u8g_pb_t *pb = (u8g_pb_t *)(dev->dev_mem);			
		  u8g_SetAddress(u8g, dev, 0);           /* command mode */		
      u8g_WriteByte(u8g, dev, 0x10);		/* set address 0 */
			u8g_WriteByte(u8g, dev, 0xB0 | pb->p.page );		/* set address 0 */			
      u8g_SetAddress(u8g, dev, 1);           /* data mode */
      u8g_WriteSequenceP(u8g, dev,128,(uint8_t*)pb->buf);
      break;
		}

  }
  return u8g_dev_pb8v1_base_fn(u8g, dev, msg, arg);
}

U8G_PB_DEV(u8g_dev_nt7538_128x64, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_nt7538_128x64_fn, U8G_COM_PARALLEL);
U8G_PB_DEV(u8g_dev_nt7538_128x64_fast, WIDTH, HEIGHT, PAGE_HEIGHT, u8g_dev_nt7538_128x64_fn, U8G_COM_FAST_PARALLEL);
