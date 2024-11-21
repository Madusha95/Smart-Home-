#include <built_in.h> 
unsigned int SomeInt1; 
unsigned int a; 
unsigned int time; 
char text[15]; 
//unsigned int SomeInt2; 
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
UART1_Init(9600); 
Lcd_Init();                  
Lcd_Cmd(_LCD_CLEAR);        
Lcd_Cmd(_LCD_CURSOR_OFF);   
TRISD = 0b0000001; 
T1CON = 0x10;              
while(1) 
{ 
TMR1H = 0;                   
TMR1L = 0; 
while(!PORTD.F0);            
T1CON.F0 = 1;                
while(PORTD.F0);             
T1CON.F0 = 0;                
a = (TMR1L | (TMR1H<<8));    
time= (200*a)/1000; 
SomeInt1=time; 
UART1_Write(Lo(SomeInt1)); 
IntToStr(time,text); 
//UART1_Write(Hi(SomeInt1)); 
Lcd_Out(1,1, "Time:"); 
Lcd_Out(1,7,text); 
delay_ms(100); 
} 
