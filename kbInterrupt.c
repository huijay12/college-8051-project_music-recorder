#include "reg51.h"

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

extern unsigned char key_current; // 按鍵現在的狀態, 1: 正常 0:被按
extern unsigned char key_previous; // 按鍵前10ms 的狀態, 1: 正常 0:被按		   
extern unsigned int key_value;
extern unsigned char showBtn;



////////////////////////////////////////////////////////////////鍵盤中斷

void T0_int(void) interrupt 1
{
unsigned char i=0;
TH0 = (65536-10000)/256; // 10ms 再設定
TL0 = (65536-10000)%256; // 10ms 再設定



Key_Port = 0x7f; // P2.7 = 0, 掃描第ㄧ列
key_current = Key_Port & 0x0f;
if (key_current != key_previous) { // 有按鍵被按

if (key_current == 0x0E){
key_value =Key_0;
showBtn = '0';
i++;
}
if (key_current == 0x0D){
key_value =Key_7;
showBtn = '7';
i++;
}
if (key_current == 0x0B){
key_value =Key_4;
showBtn = '4';
i++;
}
if (key_current == 0x07){
key_value =Key_1;
showBtn = '1';
i++;
}
}
Key_Port = 0xbf; // P2.6 = 0, 掃描第二列
key_current = Key_Port & 0x0f;
if (key_current != key_previous) { // 有按鍵被按

if (key_current == 0x0E){
key_value =Key_F;
showBtn = 'F';
i++;
}
if (key_current == 0x0D){
key_value =Key_8;
showBtn = '8';
i++;
}
if (key_current == 0x0B){
key_value =Key_5;
showBtn = '5';
i++;
}
if (key_current == 0x07){
key_value =Key_2;
showBtn = '2';
i++;
}
}
Key_Port = 0xdf; // P2.5 = 0, 掃描第三列
key_current = Key_Port & 0x0f;
if (key_current != key_previous) { // 有按鍵被按
if (key_current == 0x0E){
key_value =Key_E;
showBtn = 'E';

i++;
}
if (key_current == 0x0D){
key_value =Key_9;
showBtn = '9';
i++;
}
if (key_current == 0x0B){
key_value =Key_6;
showBtn = '6';
i++;
}
if (key_current == 0x07){
key_value =Key_3;
showBtn = '3';
i++;
}
}
Key_Port = 0xef; // P2.4 = 0, 掃描第四列
key_current = Key_Port & 0x0f;

if (key_current != key_previous) { // 有按鍵被按
   if (key_current == 0x0E){
     key_value =Key_D;
	 showBtn = 'D';
     i++;
      }

if (key_current == 0x0D){
    key_value =Key_C;
	showBtn = 'C';
    i++;
    }

if (key_current == 0x0B){
key_value =Key_B;
showBtn = 'B';
i++;
}

if (key_current == 0x07){
key_value =Key_A;
showBtn = 'A';
i++;
}

}

if (i >= 2) //若是有兩個以上按鍵被按
key_value = 16; // 七段顯示器全暗

key_previous = key_current; // 更新上ㄧ次10ms 的值


 } ////////////////// end of T0_int
