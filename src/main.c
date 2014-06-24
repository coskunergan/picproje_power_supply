
#include "main.h"
#include <stdio.h>
//-Use Nano C lib- Seçilmeli. eðer seçilmezse sprintf den dolayý ekranda birþey görünmyor..

#define TRUE 1
#define FALSE 0


char intValue=0;
float AyarGerilim=0.0;
float AyarAkim=0.0;
float OlcumGerilim=24.40;
float OlcumAkim=3.10;



char Button1Now=0;
char Button2Now=0;
char Button3Now=0;
char Button3Pass=0;

char SetOutputValue=FALSE;

short AkimTam=0;
short AkimOnda=0;
short GerilimTam=0;
short GerilimOnda=0;


						char GerilimStr[5];
						char AkimStr[5];
/******************************************************************************/
u8g_t u8g;
/*******************************************************************************/
void UserButtonGpioConfig(){

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIO Pin Configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7; // GLCD port out yapiliyor
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}



void UserButtonControl(){
	if (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)) {//Geri
		        if (Button1Now==TRUE) {
		        	if (intValue==0) {
						intValue=5;//maximum adým boyutudur
					}
		            intValue--;
		            Button1Now=FALSE;
		        }
		    }

		    else {
		        Button1Now=TRUE;
		    }

		if (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)) { //Ýleri
		        if (Button2Now==TRUE) {

		            intValue++;
		            if (intValue==5) {
						intValue=0;//maximum adým boyutudur
					}
		            Button2Now=FALSE;
		        }
		    }

		    else {
		        Button2Now=TRUE;
		    }

		 if (!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)) {
		        if (Button3Now==TRUE) {
		            Button3Pass++;
		            if (Button3Pass>30) {// rotary buton basmak için zaman  ayarý

		            	SetOutputValue=TRUE;

		                Button3Pass=FALSE;
		                Button3Now=FALSE;
		            }

		        }
		    }
		 else{
             Button3Pass=0;
             //SetOutputValue=FALSE; birkez set olduðunda devamlý öyle kalmalý
             Button3Now=TRUE;
		 }




		switch (intValue) {
				case 1:
					UB_ENCODER_TIM2_Init(ENC_T2_MODE_2A, ENC_T2_TYP_NORMAL, 30); //SON PARAMETRE ENCODERIN MAX DEGER BELÝRLER..
					TIM2->CNT=GerilimTam; //imlecin bulunduðu yerdeki deðerden Rotary enkoderin devam etmesi için
					break;
				case 2:
					UB_ENCODER_TIM2_Init(ENC_T2_MODE_2A, ENC_T2_TYP_NORMAL, 99); //SON PARAMETRE ENCODERIN MAX DEGER BELÝRLER..
					TIM2->CNT=GerilimOnda;//imlecin bulunduðu yerdeki deðerden Rotary enkoderin devam etmesi için
					break;
				case 3:
					UB_ENCODER_TIM2_Init(ENC_T2_MODE_2A, ENC_T2_TYP_NORMAL, 5); //SON PARAMETRE ENCODERIN MAX DEGER BELÝRLER..
					TIM2->CNT=AkimTam;//imlecin bulunduðu yerdeki deðerden Rotary enkoderin devam etmesi için
					break;
				case 4:
					UB_ENCODER_TIM2_Init(ENC_T2_MODE_2A, ENC_T2_TYP_NORMAL, 9); //SON PARAMETRE ENCODERIN MAX DEGER BELÝRLER..
					TIM2->CNT=AkimOnda;//imlecin bulunduðu yerdeki deðerden Rotary enkoderin devam etmesi için
					break;
				default:
					break;
			}




}




void SysTick_Handler(void){
	UserButtonControl();
}


int main(void)
{

		//int counterwert; //ileri ve geri iþleminde eðer bu deger 0 olursa, 0-255 olmasýndan dolayý yanlýþ hareket edebiliyor..
		//uint16_t OldValue;// menü için gezintilerde kullanýlýyor..

		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_ClocksTypeDef RCC_Clocks;

		SystemInit();//168mhz
		//UB_ENCODER_TIM2_Init(ENC_T2_MODE_2A, ENC_T2_TYP_NORMAL, 99); //SON PARAMETRE ENCODERIN MAX DEGER BELÝRLER..

		UserButtonGpioConfig();


		/* Enable the PWR APB1 Clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

		RCC_GetClocksFreq(&RCC_Clocks);

		if (SysTick_Config(168000000/50)) //10MS stabil deðer
		{
			for (;;) // Capture error
			{
			}
		}


		/*
		 * GEREKLÝ KALDIRIRSAN ÇALIÞMAZ..
		 */
		/* GPIO clock Configuration */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE, ENABLE);

		/* GPIO Pin Configuration */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; // GLCD port out yapiliyor
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOD, &GPIO_InitStructure);
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		u8g_InitComFn(&u8g, &u8g_dev_ks0108_128x64, u8g_com_sw_spi_fn);


				u8g_FirstPage(&u8g);
					do
					{
						u8g_DrawFrame(&u8g,0,0,128,64);
						u8g_SetFont(&u8g, u8g_font_helvB12r);
						u8g_DrawStr(&u8g,50,14,"PIC");
						u8g_DrawStr(&u8g,34,27,"PROJE");

						u8g_SetFont(&u8g, u8g_font_helvB10r);
						u8g_DrawStr(&u8g, 23,50,"community");

					} while ( u8g_NextPage(&u8g) );

					u8g_Delay(50000);

				for(;;){
					u8g_FirstPage(&u8g);
					do
					{
						switch (intValue) {

						case 0:

							u8g_DrawRBox(&u8g,21,40,24,15,2);
							u8g_SetColorIndex(&u8g,0);
							u8g_DrawStr(&u8g,25,52,"OK");
							u8g_SetColorIndex(&u8g,1);

							if (SetOutputValue==TRUE) {
								u8g_DrawStr(&u8g,60,50,"1");
								//SetOutputValue=FALSE;
							}


							break;
						case 1:

							u8g_DrawHLine(&u8g,8,17, 12);     // draw cursor bar
							u8g_DrawHLine(&u8g,8,18, 12);     // draw cursor bar

							GerilimTam=UB_ENCODER_TIM2_ReadPos();

							SetOutputValue=FALSE;

							break;
						case 2:

							u8g_DrawHLine(&u8g,23,17, 12);     // draw cursor bar
							u8g_DrawHLine(&u8g,23,18, 12);     // draw cursor bar

							GerilimOnda=UB_ENCODER_TIM2_ReadPos();
							if (GerilimTam==30) {
								GerilimOnda=0;
							}
							SetOutputValue=FALSE;

							break;

						case 3:

							u8g_DrawHLine(&u8g,8,29, 12);     // draw cursor bar
							u8g_DrawHLine(&u8g,8,30, 12);     // draw cursor bar

							AkimTam=UB_ENCODER_TIM2_ReadPos();


							//maximum 5A lik deðer
							if (AkimTam>5) {
								AkimTam=5;
								TIM2->CNT=5;
							}

							SetOutputValue=FALSE;

							break;
						case 4:
							u8g_DrawHLine(&u8g,23,29, 12);     // draw cursor bar
							u8g_DrawHLine(&u8g,23,30, 12);     // draw cursor bar
							AkimOnda=UB_ENCODER_TIM2_ReadPos();

							if (AkimTam==5) {
									AkimOnda=0;
									TIM2->CNT=0;
							}

							SetOutputValue=FALSE;

							break;
						default:


							break;
					}

						u8g_DrawRFrame(&u8g,2,2,52,60,3);
						u8g_DrawRFrame(&u8g,56,2,70,60,3);





						AyarGerilim=GerilimTam+(GerilimOnda*0.01);
						AyarAkim=AkimTam+(AkimOnda*0.1);

						sprintf(GerilimStr,"%05.2f V",AyarGerilim);
						sprintf(AkimStr,"%05.2f A",AyarAkim);

						u8g_SetFont(&u8g,u8g_font_helvB08);
						u8g_DrawStr(&u8g,8,16,GerilimStr);
						u8g_DrawStr(&u8g,8,28,AkimStr);


						if (!intValue==0) {
							u8g_DrawRFrame(&u8g,21,40,24,15,2);
							u8g_DrawStr(&u8g,25,52,"OK");
						}


						u8g_DrawHLine(&u8g,8,34, 38);     // draw line
						u8g_DrawHLine(&u8g,9,35, 37);     // draw line


						u8g_SetFont(&u8g,u8g_font_timB14);
						u8g_DrawStr(&u8g, 60,20,"30.47 V");
						u8g_DrawStr(&u8g, 60,36,"04.47 A");

						u8g_DrawHLine(&u8g,60,38,60);

						u8g_SetFont(&u8g,u8g_font_helvB08);
						u8g_DrawStr(&u8g, 82,50,"04.47W");



					} while ( u8g_NextPage(&u8g) );
					u8g_Delay(100);

				}



}
