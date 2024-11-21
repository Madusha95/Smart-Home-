/*#include <built_in.h> 
unsigned int SomeInt1;*/
// LCD module connections 
sbit LCD_RS at RB0_bit; 
sbit LCD_EN at RB1_bit; 
sbit LCD_D4 at RB4_bit; 
sbit LCD_D5 at RB5_bit; 
sbit LCD_D6 at RB6_bit; 
sbit LCD_D7 at RB7_bit; 
sbit LCD_RS_Direction at TRISB0_bit; 
sbit LCD_EN_Direction at TRISB1_bit; 
sbit LCD_D4_Direction at TRISB4_bit; 
sbit LCD_D5_Direction at TRISB5_bit; 
sbit LCD_D6_Direction at TRISB6_bit; 
sbit LCD_D7_Direction at TRISB7_bit; 
// End LCD module connections 
float receive; 
char text[10]; 
int s1=100; 
int s2=200; 
int s3=11; 
int s4=55; 
void main() { 
UART1_Init(9600); 
Lcd_Init();                  
Lcd_Cmd(_LCD_CLEAR);         
Lcd_Cmd(_LCD_CURSOR_OFF);    
while(1){ 
if (UART1_Data_Ready() ==1) { 
receive = UART1_Read(); 
} 
//SomeInt1= receive; 
intToStr(receive,text);
Lcd_Out(2,1,text); 
UART1_write(s1); 
UART1_write(s2); 
UART1_write(s3); 
UART1_write(s4); 
} 
}