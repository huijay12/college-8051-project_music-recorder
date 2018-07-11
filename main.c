#include "reg51.h"

//************************************************************************** LCD
void Delay_100ms(void);
void delay_time(unsigned int k);

void LCD_INIT(void);
void LCD_Data_In(char  LCD_WORD);																			   
void  LCD_COMMAND(char temp);																
void check_BF(void);																		   
void  LCD_Clear(void); 														  
void  LCD_Home(void); 																 				  
void  LCD_ADDRESS(char row, char column);											  
void LCD_Display_String(char  *s1);

// LCD 模組I/O的定義
sbit     RW  = P3^5;  // 直接接地
sbit     RS  = P3^7; 
sbit     E  = P3^6;  
#define  LCD_DATA   P2     // DB0-DB7  

extern int xdata delaytime;				
//************************************************************************** LCD

//**************************************************************************鍵盤
#define Key_Port P0 // Port 0 接到 	4x4 鍵盤

// 定義4x4 鍵盤與數字的關係
#define Key_0 0
#define Key_1 1
#define Key_2 2
#define Key_3 3
#define Key_4 4
#define Key_5 5
#define Key_6 6
#define Key_7 7
#define Key_8 8
#define Key_9 9
#define Key_A 10
#define Key_B 11
#define Key_C 12
#define Key_D 13
#define Key_E 14
#define Key_F 15

unsigned char key_current=0x0F; // 按鍵現在的狀態, 1: 正常 0:被按
unsigned char key_previous=0x0F; // 按鍵前10ms 的狀態, 1: 正常 0:被按		   
unsigned int key_value=16;
unsigned char showBtn;


//**************************************************************************鍵盤

//**************************************************************************聲音
sbit P1_7 = P1^7;

#define	 DO  65536 - 460800/523    //中音DO
#define	 RE  65536 - 460800/587    //中音RE
#define	 MI  65536 - 460800/659    //中音MI
#define	 FA  65536 - 460800/698    //中音FA
#define	 SO  65536 - 460800/785    //中音SO
#define	 LA  65536 - 460800/880    //中音LA
#define	 SI  65536 - 460800/998    //中音SI
#define	 HDO  65536 - 460800/1048   //高音DO
#define	 HRE  65536 - 460800/1176   //高音RE
#define  NON


//定義音階表
code unsigned int Table[] = {DO, RE, MI, FA, SO, LA, SI, HDO, HRE, NON};
unsigned int temp;



//**************************************************************************聲音

/**********************************************************************///功能函式
void mainMenu(void);
void record(void);	  
void playAllRecord(void);
void playPart(void);
void delete(void);
/**********************************************************************///功能函式

void delay_1ms(void);


xdata unsigned int i;
xdata unsigned int j;
xdata unsigned int k;
unsigned int func;

xdata unsigned int recordSet[4][10];
xdata unsigned int recordQuan = 0;	    //已記錄數目
xdata unsigned int recordLength[4] = {0, 0, 0, 0};	    //各記錄的長度

xdata int a = 0;				 //第幾個記錄
xdata int b = 0;				 //第幾個位置



void main(void){                  /*********************************************************///main

//************鍵盤
Key_Port = 0xFF; // Port1 接到4x4 鍵盤
TMOD = 0x11; // Timer0(鍵盤) Timer1(聲音)    Mode1 設定
TH0 = (65536-10000)/256; // 10ms 設定
TL0 = (65536-10000)%256; // 10ms 設定

EA = 1; // 致能所有中斷
ET0 = 1; // 致能Timer0 中斷
ET1 = 1;
IP = 0x02;          //Timer0 高優先權
//TR0 = 1; // 啟動Timer 0 計時

//*************鍵盤


  while(1)
  {


   TH0 = (65536-10000)/256; // 10ms 設定
   TL0 = (65536-10000)%256; // 10ms 設定

   mainMenu();

   
   switch(key_value)
   {
   
   		 case 10: 

		      record();
			  break;
   
   		 case 11:

			  playAllRecord();
			  break;								  
   
   		 case 12:

			  playPart();
		      break;												   		  
        
		
		case 13:

			 delete();
  		     break;												 
		
		
		  

   }  /*****************************************///end switch

   key_value = 16;
   
 }  /***********************************************///end outer while
   
   }                             /*********************************************************///end main


void T1_int(void) interrupt 3		   // Timer1 計時中斷
{

   	TR1 = 0;
	TL1 = temp % 256;
	TH1 = temp / 256;
	TR1 = 1;
	P1_7 = !P1_7;
//    P1_1 = 0;

}


void delay_1ms(void)
{
		unsigned char temp;
        unsigned int i;

		for(i=0; i<60; i++)
		temp=0;
		

}
