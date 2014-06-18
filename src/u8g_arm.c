/*

  u8g_arm.c

	StdLibrary kullan1larak pin haberlesmesi kuran STM32F1, STM32L1, STM32F4 destekleyen u8gLib ARM kütüpanesidir.

	Coskun ERGAN

	13.04.2014

	V-1.0.2

*/

#include "u8g_arm.h"

GPIO_InitTypeDef GPIO_InitStructure;

//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin kapali dongu bekleme fonksiyonu (Hem 72 hem 168 Mhz e göre)
//////////////////////////////////////////////////////////////////////////////////////////////
void delay_micro_seconds(uint32_t us)
{
#ifdef STM32F4  // 168 Mhz
    us *= 7;
#endif
    while(us--)
    {
        __NOP();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen deger kadar Ms bekleyen fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_Delay(uint16_t val)
{
    delay_micro_seconds(1000UL * (uint32_t)val);
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
// ARM Cortex-M3 islemciler icin girilen pin için initalize yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_Pin_Initalize(uint8_t temp)
{
    if(temp == 0xA)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
#endif
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    else if(temp == 0xB)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
#endif
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
    else if(temp == 0xC)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
#endif
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
    else if(temp == 0xD)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
#endif
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }
    else if(temp == 0xE)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
#endif
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    }
    else if(temp == 0xF)
    {
#ifdef STM32F1
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
#elif STM32L1
        RCC_AHBPeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
#else // STM32F4
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
#endif
        GPIO_Init(GPIOF, &GPIO_InitStructure);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini OUTPUT yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinOutput(uint8_t internal_pin_number)
{
    uint8_t temp = (internal_pin_number >> 4);
    GPIO_InitStructure.GPIO_Pin = 1 << (internal_pin_number & 15);
#ifdef STM32F1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#elif STM32L1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
#else // STM32F4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
#endif
    u8g_Pin_Initalize(temp);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini INPUT ve PULL-x yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinInput(uint8_t internal_pin_number,uint8_t pull)
{
    uint8_t temp = (internal_pin_number >> 4);
    GPIO_InitStructure.GPIO_Pin = 1 << (internal_pin_number & 15);
#ifdef STM32F1
   if(pull==PullUp)
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	else if(pull==PullDown)
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	else
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#else // STM32L1, STM32F4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  if(pull==PullUp)
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	else if(pull==PullDown)
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	else
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
#endif
    u8g_Pin_Initalize(temp);
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini HIGH yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
void u8g_SetPinLevel(uint8_t internal_pin_number, uint8_t level)
{
    uint16_t temp_pin = (1 << (internal_pin_number & 15));
    uint8_t temp_port = (internal_pin_number >> 4);

    if(level)
    {
        if(temp_port == 0xA) // set
        {
            GPIOA->SetBitReg = temp_pin;
        }
        else if(temp_port == 0xB)
        {
            GPIOB->SetBitReg = temp_pin;
        }
        else if(temp_port == 0xC)
        {
            GPIOC->SetBitReg = temp_pin;
        }
        else if(temp_port == 0xD)
        {
            GPIOD->SetBitReg = temp_pin;
        }
        else if(temp_port == 0xE)
        {
            GPIOE->SetBitReg = temp_pin;
        }
        else if(temp_port == 0xF)
        {
            GPIOF->SetBitReg = temp_pin;
        }
    }
    else
    {
        if(temp_port == 0xA) // Reset
        {
            GPIOA->ResetBitReg = temp_pin;
        }
        else if(temp_port == 0xB)
        {
            GPIOB->ResetBitReg = temp_pin;
        }
        else if(temp_port == 0xC)
        {
            GPIOC->ResetBitReg = temp_pin;
        }
        else if(temp_port == 0xD)
        {
            GPIOD->ResetBitReg = temp_pin;
        }
        else if(temp_port == 0xE)
        {
            GPIOE->ResetBitReg = temp_pin;
        }
        else if(temp_port == 0xF)
        {
            GPIOF->ResetBitReg = temp_pin;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
// ARM Cortex-M3 islemciler icin girilen pini LOW yapan fonksiyon
//////////////////////////////////////////////////////////////////////////////////////////////
uint16_t u8g_GetPinLevel(uint8_t internal_pin_number)
{
    uint16_t temp_pin = (1 << (internal_pin_number & 15));
    uint8_t temp_port = (internal_pin_number >> 4);

    if(temp_port == 0xA)
    {
        return (GPIOA->ReadInBitReg & temp_pin);
    }
    else if(temp_port == 0xB)
    {
        return (GPIOB->ReadInBitReg & temp_pin);
    }
    else if(temp_port == 0xC)
    {
        return (GPIOC->ReadInBitReg & temp_pin);
    }
    else if(temp_port == 0xD)
    {
        return (GPIOD->ReadInBitReg & temp_pin);
    }
    else if(temp_port == 0xE)
    {
        return (GPIOE->ReadInBitReg & temp_pin);
    }
    else if(temp_port == 0xF)
    {
        return (GPIOF->ReadInBitReg & temp_pin);
    }
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
            /* setup the RW pin as output and force it to low */
            u8g_SetPIOutput(u8g, U8G_PI_D0);
            u8g_SetPIOutput(u8g, U8G_PI_D1);
            u8g_SetPIOutput(u8g, U8G_PI_D2);
            u8g_SetPIOutput(u8g, U8G_PI_D3);
            u8g_SetPIOutput(u8g, U8G_PI_D4);
            u8g_SetPIOutput(u8g, U8G_PI_D5);
            u8g_SetPIOutput(u8g, U8G_PI_D6);
            u8g_SetPIOutput(u8g, U8G_PI_D7);
            u8g_SetPIOutput(u8g, U8G_PI_EN);
            u8g_SetPIOutput(u8g, U8G_PI_CS1);
            u8g_SetPIOutput(u8g, U8G_PI_CS2);
            u8g_SetPIOutput(u8g, U8G_PI_A0);
            u8g_SetPIOutput(u8g, U8G_PI_RW);
            u8g_SetPIOutput(u8g, U8G_PI_RESET);
            break;

        case U8G_COM_MSG_ADDRESS:   /* define cmd (arg_val = 0) or data mode (arg_val = 1) */
        {
            u8g_SetPILevel(u8g, U8G_PI_A0, arg_val);
            //u8g_MicroDelay();
            break;
        }
        case U8G_COM_MSG_CHIP_SELECT:
        {
            if(arg_val == 1)
            {
                u8g_SetPILevel(u8g, U8G_PI_CS1, 1);
                u8g_SetPILevel(u8g, U8G_PI_CS2, 0);
            }
            else if(arg_val == 2)
            {
                u8g_SetPILevel(u8g, U8G_PI_CS1, 0);
                u8g_SetPILevel(u8g, U8G_PI_CS2, 1);
            }
            else
            {
                u8g_SetPILevel(u8g, U8G_PI_CS1, 0);
                u8g_SetPILevel(u8g, U8G_PI_CS2, 0);
            }
            // u8g_MicroDelay();
            break;
        }
        case U8G_COM_MSG_RESET:
        {
            u8g_SetPILevel(u8g, U8G_PI_RESET, arg_val);
            u8g_10MicroDelay();
            break;
        }
        case U8G_COM_MSG_WRITE_BYTE:
        {
            delay_micro_seconds(25);
            u8g_SetPILevel(u8g, U8G_PI_D0, arg_val & 0x1);
            u8g_SetPILevel(u8g, U8G_PI_D1, arg_val & 0x2);
            u8g_SetPILevel(u8g, U8G_PI_D2, arg_val & 0x4);
            u8g_SetPILevel(u8g, U8G_PI_D3, arg_val & 0x8);
            u8g_SetPILevel(u8g, U8G_PI_D4, arg_val & 0x10);
            u8g_SetPILevel(u8g, U8G_PI_D5, arg_val & 0x20);
            u8g_SetPILevel(u8g, U8G_PI_D6, arg_val & 0x40);
            u8g_SetPILevel(u8g, U8G_PI_D7, arg_val & 0x80);
            u8g_SetPILevel(u8g, U8G_PI_EN, 1);
            u8g_MicroDelay();
            u8g_SetPILevel(u8g, U8G_PI_EN, 0);
            break;
        }
        case U8G_COM_MSG_WRITE_SEQ:
        {
            register uint8_t *ptr = arg_ptr;
            while(arg_val > 0)
            {
                delay_micro_seconds(25);
                u8g_SetPILevel(u8g, U8G_PI_D0, *ptr & 0x1);
                u8g_SetPILevel(u8g, U8G_PI_D1, *ptr & 0x2);
                u8g_SetPILevel(u8g, U8G_PI_D2, *ptr & 0x4);
                u8g_SetPILevel(u8g, U8G_PI_D3, *ptr & 0x8);
                u8g_SetPILevel(u8g, U8G_PI_D4, *ptr & 0x10);
                u8g_SetPILevel(u8g, U8G_PI_D5, *ptr & 0x20);
                u8g_SetPILevel(u8g, U8G_PI_D6, *ptr & 0x40);
                u8g_SetPILevel(u8g, U8G_PI_D7, *ptr & 0x80);
                u8g_SetPILevel(u8g, U8G_PI_EN, 1);
                u8g_MicroDelay();
                u8g_SetPILevel(u8g, U8G_PI_EN, 0);
                ptr++;
                arg_val--;
            }
            break;
        }
        case U8G_COM_MSG_WRITE_SEQ_P:
        {
            register uint8_t *ptr = arg_ptr;
            while(arg_val > 0)
            {
                delay_micro_seconds(25);
                u8g_SetPILevel(u8g, U8G_PI_D0, *ptr & 0x1);
                u8g_SetPILevel(u8g, U8G_PI_D1, *ptr & 0x2);
                u8g_SetPILevel(u8g, U8G_PI_D2, *ptr & 0x4);
                u8g_SetPILevel(u8g, U8G_PI_D3, *ptr & 0x8);
                u8g_SetPILevel(u8g, U8G_PI_D4, *ptr & 0x10);
                u8g_SetPILevel(u8g, U8G_PI_D5, *ptr & 0x20);
                u8g_SetPILevel(u8g, U8G_PI_D6, *ptr & 0x40);
                u8g_SetPILevel(u8g, U8G_PI_D7, *ptr & 0x80);
                u8g_SetPILevel(u8g, U8G_PI_EN, 1);
                u8g_MicroDelay();
                u8g_SetPILevel(u8g, U8G_PI_EN, 0);
                ptr++;
                arg_val--;
            }
            break;
        }
    }
    return 1;
}


