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

extern unsigned char key_current; // ����{�b�����A, 1: ���` 0:�Q��
extern unsigned char key_previous; // ����e10ms �����A, 1: ���` 0:�Q��		   
extern unsigned int key_value;
extern unsigned char showBtn;


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
extern code unsigned int Table[];
extern unsigned int temp;



//**************************************************************************�n��

void delay_1ms(void);
void mainMenu(void);
void record(void);
void playAllRecord(void);
void playPart(void);
void delete(void);


extern xdata unsigned int i;
extern xdata unsigned int j;
extern xdata unsigned int k;
extern unsigned int func;

extern xdata unsigned int recordSet[4][10];
extern xdata unsigned int recordQuan;	    //�w�O���ƥ�
extern xdata unsigned int recordLength[4];	    //�U�O��������

extern xdata int a;				 //�ĴX�ӰO��
extern xdata int b;				 //�ĴX�Ӧ�m



void mainMenu(void)
{

  LCD_INIT();
  LCD_Display_String("Select function\0");			//"Select function"
  //LCD_Display_String(str1);

  TR0 = 1;

  while(1){
  
  if(key_value>9 && key_value<14)
  {
    TR0 = 0;
    break;
     }

  else continue;
  }				  


 TH0 = (65536-10000)/256; // 10ms �]�w
 TL0 = (65536-10000)%256; // 10ms �]�w

}






void record(void)
{

       LCD_INIT();
       LCD_Display_String("Recording...   \0");	 //"Recording...  "


 	  key_value = 16;


  	   while(1){

	      TR0 = 1;

		  while(1)
		  {
		  
		  	 if(key_value>0 && key_value<10)
			 {
			 	func = 1;
				TR0 = 0;
			 	break;
			    }
		    
             if(key_value == 15)								// F��, �O������
			 {
			    func = 2;
			 	break;
			   }

		    }                   //inner while
	   
            for(i=0; i<200; i++)
		    delay_1ms();



	       if(func == 1)
		   {
		   	 
                if(b == 10)
				{
				   LCD_ADDRESS(2,1);
				   LCD_Display_String("full!!        \0");

				   for (i=0;i<1000;i++){
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
                       }

                   func = 2;

				  }//song �w��	  

               else
			   {
			   	   recordSet[a][b] = key_value;
				   

			   	   LCD_ADDRESS(2,b+1);
				   LCD_Data_In(showBtn);

				   b++;       
			   
			       key_value = 16;

				   for (i=0;i<100;i++){
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
                       }
			      }
		   
		       }  
	     
		    if(func == 2)
			{

                LCD_INIT();
				LCD_Display_String("Record saved   \0");

				for (i=0;i<1000;i++){
                    delay_1ms();
                    delay_1ms();
                    delay_1ms();
                     }


			   key_value = 16;
			   recordQuan++;
			   recordLength[a]= b-1;
			   b = 0;
			   a++;
			   break;
			   }
	   
	   	 TR0 = 0;



     }   /*************************************///end outer while

}		 /*******************************/// end record




void playAllRecord(void)
{

	    LCD_INIT();
                

                if(recordQuan==0)		  
				{
				  LCD_Display_String("No record!!");

                   for (i=0;i<1000;i++){
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
                       }
                 }

				else
				{
				LCD_Display_String("Playing records\0");	    // play all records

			    for(i=0; i<recordQuan; i++)		         	
				{
				   for(j=0; j<=recordLength[i]; j++)			
				   {

                     temp = Table[recordSet[i][j]-1];

		              TR1 = 1;

		              for(k=0; k<4000; k++)
		              {delay_1ms();}

		              TR1 = 0; 
				   
				     }               //end of inner for
				
				   }				  //end of outer for				  
				  
				}							


}	    /*******************************///end playAllRecord


void playPart(void)
{

              LCD_INIT();

              if(recordQuan==0)		  
				{
				  LCD_Display_String("No record!!");

                   for (i=0;i<1000;i++){
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
                       }
                 }
	           
			  else
			  {

               LCD_Display_String("Select record  \0");

			   TR0 = 1;

               
			   while(1)
		       {
		  
		  	       if(key_value>0 && key_value<=recordQuan)
						break;
			   }

				LCD_ADDRESS(1,1);
			   	LCD_Display_String("Playing record \0");

			    
				 for(j=0; j<=recordLength[key_value-1]; j++)			
				   {

                     temp = Table[recordSet[key_value-1][j]-1];

		              TR1 = 1;

		              for(k=0; k<4000; k++)
		              {delay_1ms();}

		              TR1 = 0; 
				   
				     }               //end of inner for
				}             // end of else
}


void delete(void)
{

	           LCD_INIT();

               if(recordQuan==0)		  
				{
				  LCD_Display_String("No record!!");

                   for (i=0;i<1000;i++){
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
                       }
                 } 


			   else
			   {
               LCD_Display_String("Select record  \0");

			   TR0 = 1;

               
			   while(1)
		       {
		  
		  	       if(key_value>0 && key_value<=4)
						break;
			   }


               if(recordLength[key_value-1] == 0)
			   {
			   
			   	 LCD_ADDRESS(1,1);
			     LCD_Display_String("No record!     \0");
			   
			   
			     }

			   else
			   {


                  for(j=0; j<recordLength[key_value-1]; j++)
			      {	recordSet[key_value-1][j] = 0;  }

                  recordLength[key_value-1] = 0; 	


			      LCD_ADDRESS(1,1);
			      LCD_Display_String("record deleted \0");
			      for (i=0;i<1000;i++)
			      {
                      delay_1ms();
                      delay_1ms();
                      delay_1ms();
				    }

			     }	   // end of else

          }  //end of else


}


