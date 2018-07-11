#include "reg51.h"

void delay_1ms(void);
void EEI2C_START(void);
void EEI2C_STOP(void);
void EEI2C_ACK(void);

// For 24c04以上版本
//void eewrite(unsigned char rom_addressHigh,unsigned char rom_addressLow,	unsigned char write_data);
//unsigned char eeread(unsigned char rom_addressHigh,unsigned char rom_addressLow);

// For 24C00, 24C01, 24C02 版本
void eewrite(unsigned char rom_address,	unsigned char write_data);
unsigned char eeread(unsigned char read_address);


void write_8bit(wData);
unsigned char read_8bit(void);


sbit  EESDA  = P3^3;
sbit  EESCL  = P3^2;

void delay_1ms(void)
{
		unsigned char temp;
        unsigned int i;

		for(i=0; i<60; i++)
		temp=0;
		

}

void EEI2C_START(void)
{
	EESDA=1;
	delay_1ms();
	EESCL=1;
	delay_1ms();
	EESDA=0;
	delay_1ms();
	EESCL=0;
	delay_1ms();
}

void EEI2C_STOP(void)
{
	EESCL=0;
	delay_1ms();
	EESDA=0;
	delay_1ms();
	EESCL=1;
	delay_1ms();
	EESDA=1;
	delay_1ms();
}

void EEI2C_ACK(void)
{ 	
	unsigned char z=0;
	while((EESDA==1)&&(z<50))	z++;   // Z 保護用，避免程式進入無窮回圈
	EESCL=0;
	delay_1ms();
} 

// For 24c04以上版本
//void eewrite(unsigned char rom_addressHigh,unsigned char rom_addressLow,	unsigned char write_data)
void eewrite(unsigned char rom_address,	unsigned char write_data)
{
	unsigned int ii;

	
	    EEI2C_START();
    
      write_8bit(0xA0);
      EEI2C_ACK();
      
//      write_8bit(rom_addressHigh);
//      EEI2C_ACK();
//      write_8bit(rom_addressLow);
//      EEI2C_ACK();
      write_8bit(rom_address);
      EEI2C_ACK();
      
      write_8bit(write_data);
      EEI2C_ACK();
      
    	EEI2C_STOP();
	
	// Delay only
	for(ii=0;ii<500;ii++){
			delay_1ms();
	}
	
}


void write_8bit(wData){

unsigned char i;

				EESCL=0;
				delay_1ms();	
				
			for(i=0;i<8;i++)
			{
							
				if((wData & 0x80 ) == 0x80)			
					EESDA=1; 
				else
					EESDA=0;				
				
				delay_1ms();
				
				EESCL=1;
				delay_1ms();
				EESCL=0;
				delay_1ms();
				
				wData=wData<<1;
							
			}
			
		EESDA=1;         // 還原到初始
		delay_1ms();
		EESCL=1;         //  還原到初始
		delay_1ms();  
}		

// For 24c04以上版本
//unsigned char eeread(unsigned char rom_addressHigh,unsigned char rom_addressLow)
unsigned char eeread(unsigned char read_address){
	
	unsigned char read_data;

			EEI2C_START();
	
      write_8bit(0xA0);
      EEI2C_ACK();

//      write_8bit(rom_addressHigh);
//      EEI2C_ACK();
//      write_8bit(fLow);
//      EEI2C_ACK();     
      write_8bit(read_address);
      EEI2C_ACK();
	    
	    EEI2C_START();
      write_8bit(0xA1);
      EEI2C_ACK();
      
	    read_data = read_8bit();
			EEI2C_ACK();
			
			EEI2C_STOP();
	
	  return (read_data);
}


unsigned char read_8bit(void){

unsigned char rdata,i;	

	rdata = 0x00;
	
	
	for(i=0;i<8;i++){
		rdata = rdata<<1;
		EESDA = 1;
		delay_1ms();
		EESCL = 0;
		delay_1ms();
		EESCL = 1;
		delay_1ms();
		
		if(EESDA==1)		
			rdata|=0x01;
			
	}
	
	return (rdata);
}
