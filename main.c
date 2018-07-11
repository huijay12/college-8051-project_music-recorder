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

// LCD �Ҳ�I/O���w�q
sbit     RW  = P3^5;  // �������a
sbit     RS  = P3^7; 
sbit     E  = P3^6;  
#define  LCD_DATA   P2     // DB0-DB7  

extern int xdata delaytime;				
//************************************************************************** LCD

//**************************************************************************��L
#define Key_Port P0 // Port 0 ���� 	4x4 ��L

// �w�q4x4 ��L�P�Ʀr�����Y
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

unsigned char key_current=0x0F; // ����{�b�����A, 1: ���` 0:�Q��
unsigned char key_previous=0x0F; // ����e10ms �����A, 1: ���` 0:�Q��		   
unsigned int key_value=16;
unsigned char showBtn;


//**************************************************************************��L

//**************************************************************************�n��
sbit P1_7 = P1^7;

#define	 DO  65536 - 460800/523    //����DO
#define	 RE  65536 - 460800/587    //����RE
#define	 MI  65536 - 460800/659    //����MI
#define	 FA  65536 - 460800/698    //����FA
#define	 SO  65536 - 460800/785    //����SO
#define	 LA  65536 - 460800/880    //����LA
#define	 SI  65536 - 460800/998    //����SI
#define	 HDO  65536 - 460800/1048   //����DO
#define	 HRE  65536 - 460800/1176   //����RE
#define  NON


//�w�q������
code unsigned int Table[] = {DO, RE, MI, FA, SO, LA, SI, HDO, HRE, NON};
unsigned int temp;



//**************************************************************************�n��

/**********************************************************************///�\��禡
void mainMenu(void);
void record(void);	  
void playAllRecord(void);
void playPart(void);
void delete(void);
/**********************************************************************///�\��禡

void delay_1ms(void);


xdata unsigned int i;
xdata unsigned int j;
xdata unsigned int k;
unsigned int func;

xdata unsigned int recordSet[4][10];
xdata unsigned int recordQuan = 0;	    //�w�O���ƥ�
xdata unsigned int recordLength[4] = {0, 0, 0, 0};	    //�U�O��������

xdata int a = 0;				 //�ĴX�ӰO��
xdata int b = 0;				 //�ĴX�Ӧ�m



void main(void){                  /*********************************************************///main

//************��L
Key_Port = 0xFF; // Port1 ����4x4 ��L
TMOD = 0x11; // Timer0(��L) Timer1(�n��)    Mode1 �]�w
TH0 = (65536-10000)/256; // 10ms �]�w
TL0 = (65536-10000)%256; // 10ms �]�w

EA = 1; // �P��Ҧ����_
ET0 = 1; // �P��Timer0 ���_
ET1 = 1;
IP = 0x02;          //Timer0 ���u���v
//TR0 = 1; // �Ұ�Timer 0 �p��

//*************��L


  while(1)
  {


   TH0 = (65536-10000)/256; // 10ms �]�w
   TL0 = (65536-10000)%256; // 10ms �]�w

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


void T1_int(void) interrupt 3		   // Timer1 �p�ɤ��_
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
