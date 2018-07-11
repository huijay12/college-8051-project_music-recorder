#include "reg51.h"

//*********************************************************** LCD�ܼƫŧi
// LCD �Ҳ�I/O���w�q
sbit     RW  = P3^5;  // �������a
sbit     RS  = P3^7; 
sbit     E  = P3^6;  
#define  LCD_DATA   P2     // DB0-DB7  

//int xdata delaytime=100;									  
//************************************************************LCD�ܼƫŧi

//************************************************************LCD�禡�ŧi
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
//************************************************************LCD�禡�ŧi						 

#define Key_Port P0 // Port 3 ���� 	4x4 ��L


void LCD_INIT (void){
  int i;

 LCD_Clear();                 //�M��LCD���RAM
 LCD_Home();                  //LCD����k��

// LCD Initialization
     LCD_COMMAND(0x30);     // ���m LCD
     LCD_COMMAND(0X01);     // �M��LCD���RAM

      E=0;
      delay_time(100);

     for(i=0;i<10;i++)      //  �]�w����ɶ�
        delay_time(100);
         
    LCD_COMMAND(0x3f);    // �]�wLCD����C ,��Ƭ�8bits, 5*7�r�� 
     
    //  LCD_COMMAND(0x0f);        // ����� �|�{�{
    LCD_COMMAND(0x0c);            // �L��� ���|�{�{
    // LCD_COMMAND(0x0e);         // �����  ���|�{�{
     
    LCD_COMMAND(0x06);            // �]�wLCD�۰ʼW�[�Ҧ�
////////////////////////////////////////////////////////////////////////
  
    LCD_Clear(); 
    LCD_Home(); 

}


void Delay_100ms(void){
unsigned short kk;

  for (kk=0;kk<20000;kk++){
  }

} 
  
void delay_time(unsigned int k)
{
    while(k>0) k--;
}


//-------------------------------------------------------
//   �]�w LCD Module ����R�O
//------------------------------------------------------- 
void  LCD_COMMAND(char temp)
{
    RW=0;  
    RS=0;                   // �]�w�s���R�O�Ȧs��
    LCD_DATA=temp;          //  �e�XLCD�R�O�r�� 
 
    E=1;
	     check_BF(); 
	E = 0;

}


//---------------------------------------------------
//     �bLCD�W��ܤ@�Ӧr��
//---------------------------------------------------
void LCD_Data_In(char  temp)
{
    RW=0;  
    RS=1;                   // �]�w�s���R�O�Ȧs��
    LCD_DATA=temp;          //  �e�XLCD�R�O�r�� 
     
    E=1;
	   check_BF();   
	E = 0;
}

void check_BF(void) {
    Delay_100ms();
	Delay_100ms();
}

//----------------------------------------------------
//    �M��LCD���RAM
//----------------------------------------------------
void LCD_Clear(void)
{
    LCD_COMMAND(0x01);             
}
//----------------------------------------------------
//     LCD����k��
//----------------------------------------------------
void LCD_Home(void)
{
    LCD_COMMAND(0x02);        
}

//----------------------------------------------------
//         �]�wLCD��Ц�}
//         �C(row)    : 1,2
//         ��(column) : 1,16
//----------------------------------------------------
void  LCD_ADDRESS(char row, char column)
{
     unsigned char  tmp1;

//       16*2 LCD Module Address
//  row_1=> 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
//  row_2=> c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf

       tmp1=(row-1)*0x40+(column-1)+0x80;
        //�p��XLCD�Ҳդ���Ь۹�������}
      
       LCD_COMMAND(tmp1);       // �]�w LCD ��Ц�}
       
 
}

//---------------------------------------------------
//     �bLCD�W��ܤ@�Ӧr��
//     Example: s1="LCD TEST\0";  
//     �r��פ�Ÿ���'\0'
//---------------------------------------------------
void LCD_Display_String(char  *s1)
{
   unsigned char  	  i;

    for (i=0;i<50;i++){
         if (*(s1+i)=='\0') 
         	break;  //�P�_�r��O�_�w�g�ǰe����
         	
         LCD_Data_In(*(s1+i)); 
    }
}
