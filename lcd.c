#include "reg51.h"

//*********************************************************** LCD變數宣告
// LCD 模組I/O的定義
sbit     RW  = P3^5;  // 直接接地
sbit     RS  = P3^7; 
sbit     E  = P3^6;  
#define  LCD_DATA   P2     // DB0-DB7  

//int xdata delaytime=100;									  
//************************************************************LCD變數宣告

//************************************************************LCD函式宣告
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
//************************************************************LCD函式宣告						 

#define Key_Port P0 // Port 3 接到 	4x4 鍵盤


void LCD_INIT (void){
  int i;

 LCD_Clear();                 //清除LCD顯示RAM
 LCD_Home();                  //LCD游標歸位

// LCD Initialization
     LCD_COMMAND(0x30);     // 重置 LCD
     LCD_COMMAND(0X01);     // 清除LCD顯示RAM

      E=0;
      delay_time(100);

     for(i=0;i<10;i++)      //  設定延遲時間
        delay_time(100);
         
    LCD_COMMAND(0x3f);    // 設定LCD為兩列 ,資料為8bits, 5*7字型 
     
    //  LCD_COMMAND(0x0f);        // 有游標 會閃爍
    LCD_COMMAND(0x0c);            // 無游標 不會閃爍
    // LCD_COMMAND(0x0e);         // 有游標  不會閃爍
     
    LCD_COMMAND(0x06);            // 設定LCD自動增加模式
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
//   設定 LCD Module 控制命令
//------------------------------------------------------- 
void  LCD_COMMAND(char temp)
{
    RW=0;  
    RS=0;                   // 設定存取命令暫存器
    LCD_DATA=temp;          //  送出LCD命令字元 
 
    E=1;
	     check_BF(); 
	E = 0;

}


//---------------------------------------------------
//     在LCD上顯示一個字元
//---------------------------------------------------
void LCD_Data_In(char  temp)
{
    RW=0;  
    RS=1;                   // 設定存取命令暫存器
    LCD_DATA=temp;          //  送出LCD命令字元 
     
    E=1;
	   check_BF();   
	E = 0;
}

void check_BF(void) {
    Delay_100ms();
	Delay_100ms();
}

//----------------------------------------------------
//    清除LCD顯示RAM
//----------------------------------------------------
void LCD_Clear(void)
{
    LCD_COMMAND(0x01);             
}
//----------------------------------------------------
//     LCD游標歸位
//----------------------------------------------------
void LCD_Home(void)
{
    LCD_COMMAND(0x02);        
}

//----------------------------------------------------
//         設定LCD游標位址
//         列(row)    : 1,2
//         行(column) : 1,16
//----------------------------------------------------
void  LCD_ADDRESS(char row, char column)
{
     unsigned char  tmp1;

//       16*2 LCD Module Address
//  row_1=> 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
//  row_2=> c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf

       tmp1=(row-1)*0x40+(column-1)+0x80;
        //計算出LCD模組之游標相對應的位址
      
       LCD_COMMAND(tmp1);       // 設定 LCD 游標位址
       
 
}

//---------------------------------------------------
//     在LCD上顯示一個字串
//     Example: s1="LCD TEST\0";  
//     字串終止符號為'\0'
//---------------------------------------------------
void LCD_Display_String(char  *s1)
{
   unsigned char  	  i;

    for (i=0;i<50;i++){
         if (*(s1+i)=='\0') 
         	break;  //判斷字串是否已經傳送完畢
         	
         LCD_Data_In(*(s1+i)); 
    }
}
