
/* 	
		Picproje.org
		Power Supply Project
		STM32F4 Discovery Board
		08.06.2014 
	  U8gLib Graphics Demo
*/

// define processor ===== >>>>>  USE_STDPERIPH_DRIVER,  U8G_WITH_PINLIST

#include "system.h"
#include "u8g.h"
#include "u8g_arm.h"

/* select, which color background to use  */
#define COLOR_BOX draw_color_box2

#define U8g_Pin_D0  	PN(0xD, 0)  			  /* D0 		(PD0)*/  
#define U8g_Pin_D1  	PN(0xD, 1)  			  /* D1 		(PD1)*/
#define U8g_Pin_D2  	PN(0xD, 2)  			  /* D2 		(PD2)*/
#define U8g_Pin_D3  	PN(0xD, 3)  			  /* D3 		(PD3)*/
#define U8g_Pin_D4  	PN(0xD, 4)  			  /* D4 		(PD4)*/
#define U8g_Pin_D5  	PN(0xD, 5)  			  /* D5 		(PD5)*/
#define U8g_Pin_D6  	PN(0xD, 6)	 			  /* D6 		(PD6)*/
#define U8g_Pin_D7  	PN(0xD, 7)  			  /* D7 		(PD7)*/
#define U8g_Pin_En  	PN(0xE, 1)  			  /* Enable (PE1)*/
#define U8g_Pin_Cs1  	PN(0xB, 5)  			  /* CS1 		(PB5)*/
#define U8g_Pin_Cs2  	PN(0xB, 4)  			  /* CS2 		(PB4)*/
#define U8g_Pin_A0  	PN(0xB, 7)  			  /* A0  		(PB7)*/
#define U8g_Pin_Rw  	PN(0xE, 0)  			  /* RW  		(PE0)*/
#define U8g_Pin_Reset PN(0xB, 6)  			  /* Reset 	(PB6)*/

u8g_t u8g;

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_prepare(void)
{
    u8g_SetFont(&u8g, u8g_font_6x10);
    u8g_SetFontRefHeightExtendedText(&u8g);
    u8g_SetDefaultForegroundColor(&u8g);
    u8g_SetFontPosTop(&u8g);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_box_frame(uint8_t a)
{
    u8g_DrawStr(&u8g, 0, 0, "drawBox");
    u8g_DrawBox(&u8g, 5, 10, 20, 10);
    u8g_DrawBox(&u8g, 10 + a, 15, 30, 7);
    u8g_DrawStr(&u8g, 0, 30, "drawFrame");
    u8g_DrawFrame(&u8g, 5, 10 + 30, 20, 10);
    u8g_DrawFrame(&u8g, 10 + a, 15 + 30, 30, 7);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_string(uint8_t a)
{
    u8g_DrawStr(&u8g, 30 + a, 31, " 0");
    u8g_DrawStr90(&u8g, 30, 31 + a, " 90");
    u8g_DrawStr180(&u8g, 30 - a, 31, " 180");
    u8g_DrawStr270(&u8g, 30, 31 - a, " 270");
}
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_line(uint8_t a)
{
    u8g_DrawStr(&u8g, 0, 0, "drawLine");
    u8g_DrawLine(&u8g, 7 + a, 10, 40, 55);
    u8g_DrawLine(&u8g, 7 + a * 2, 10, 60, 55);
    u8g_DrawLine(&u8g, 7 + a * 3, 10, 80, 55);
    u8g_DrawLine(&u8g, 7 + a * 4, 10, 100, 55);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_ascii_1(void)
{
    char s[2] = " ";
    uint8_t x, y;
    u8g_DrawStr(&u8g, 0, 0, "ASCII page 1");
    for(y = 0; y < 6; y++)
    {
        for(x = 0; x < 16; x++)
        {
            s[0] = y * 16 + x + 32;
            u8g_DrawStr(&u8g, x * 7, y * 10 + 10, s);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void u8g_ascii_2(void)
{
    char s[2] = " ";
    uint8_t x, y;
    u8g_DrawStr(&u8g, 0, 0, "ASCII page 2");
    for(y = 0; y < 6; y++)
    {
        for(x = 0; x < 16; x++)
        {
            s[0] = y * 16 + x + 160;
            u8g_DrawStr(&u8g, x * 7, y * 10 + 10, s);
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
uint8_t draw_state = 0;

void draw(void)
{
    u8g_prepare();
    switch(draw_state >> 3)
    {
        case 0:
            u8g_box_frame(draw_state & 7);
            break;
        case 1:
            u8g_string(draw_state & 7);
            break;
        case 2:
            u8g_line(draw_state & 7);
            break;
        case 3:
            u8g_ascii_1();
            break;
        case 4:
            u8g_ascii_2();
            break;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    u8g_InitComFn(&u8g, &u8g_dev_ks0108_128x64, u8g_com_sw_spi_fn);

    u8g_Init8Bit(&u8g,
                 &u8g_dev_ks0108_128x64,
                 U8g_Pin_D0,
                 U8g_Pin_D1,
                 U8g_Pin_D2,
                 U8g_Pin_D3,
                 U8g_Pin_D4,
                 U8g_Pin_D5,
                 U8g_Pin_D6,
                 U8g_Pin_D7,
                 U8g_Pin_En,
                 U8g_Pin_Cs1,
                 U8g_Pin_Cs2,
                 U8g_Pin_A0,
                 U8g_Pin_Rw,
                 U8g_Pin_Reset);

    for(;;)
    {
        /* picture loop */
        u8g_FirstPage(&u8g);
        do
        {
            draw();
        }
        while(u8g_NextPage(&u8g));

        draw_state++;
        if(draw_state >= 5 * 8)
        {
            draw_state = 0;
        }
        /* refresh screen after some delay */
        u8g_Delay(1000);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
