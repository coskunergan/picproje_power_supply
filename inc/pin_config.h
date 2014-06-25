// Pin listeyi kullanacak kisi kendi tanimini aktif eder

//#define Coskun_ERGAN
#define Muhittin_KAPLAN

/////////////////////////////////////////////////////////////
///////////////// Coskun ERGAN Pin list /////////////////////
/////////////////////////////////////////////////////////////
#ifdef Coskun_ERGAN
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
#endif	
/////////////////////////////////////////////////////////////
///////////////// Muhittin KAPLAN Pin list///////////////////
/////////////////////////////////////////////////////////////
#ifdef Muhittin_KAPLAN
	#define U8g_Pin_D0  	PN(0xE, 0)  			  /* D0 		(PE0)*/
	#define U8g_Pin_D1  	PN(0xE, 1)  			  /* D1 		(PE1)*/
	#define U8g_Pin_D2  	PN(0xE, 2)  			  /* D2 		(PE2)*/
	#define U8g_Pin_D3  	PN(0xE, 3)  			  /* D3 		(PE3)*/
	#define U8g_Pin_D4  	PN(0xE, 4)  			  /* D4 		(PE4)*/
	#define U8g_Pin_D5  	PN(0xE, 5)  			  /* D5 		(PE5)*/
	#define U8g_Pin_D6  	PN(0xE, 6)	 			  /* D6 		(PE6)*/
	#define U8g_Pin_D7  	PN(0xE, 7)  			  /* D7 		(PE7)*/
	#define U8g_Pin_En  	PN(0xD, 9)  			  /* Enable (PD9)*/
	#define U8g_Pin_Cs1  	PN(0xD, 12)  			  /* CS1 		(PD12)*/
	#define U8g_Pin_Cs2  	PN(0xD, 11)  			  /* CS2 		(PD11)*/
	#define U8g_Pin_A0  	PN(0xD, 8)  			  /* A0  		(PD8)*/
	#define U8g_Pin_Rw  	PN(0xD, 9)  			  /* RW  		(PD9)*/
	#define U8g_Pin_Reset PN(0xD, 13)  			  /* Reset 	(PD13)*/
#endif
/////////////////////////////////////////////////////////////
////////////////////////      x x       /////////////////////
/////////////////////////////////////////////////////////////
#ifdef FALSE
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
#endif
