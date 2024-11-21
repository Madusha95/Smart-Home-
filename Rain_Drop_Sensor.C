#include <built_in.h> 
unsigned int  SomeInt1; 
int moisture_value; 
float rain_value; 
char text[10]; 
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
void main() { 
UART1_Init(9600); 
ADC_Init(); // it will initialize the adc module of pic16f877a microcontroller 
Lcd_Init(); // Initialize LCD 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off 
Lcd_Out(1,1,"Rain sensor" ); // Write text in first 
delay_ms(2000); 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
while(1) 
{ // Endless loop 
moisture_value = ADC_Read(1); // It will read the moisture value of sensor 
moisture_value = (moisture_value * 100)/(1023); // it converts the moisture value on percentage 
FloatToStr(moisture_value,text); 
Lcd_Out(2,1,text ); 
Lcd_Out_cp("%"); 
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
SomeInt1= moisture_value; 
UART1_Write(Lo(SomeInt1)); 
} 
}