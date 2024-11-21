#include <built_in.h> 
unsigned int  SomeInt1; 
int gas_value; 
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
void main(void) 
{ 
ADC_Init(); // it will initialize the adc module of pic16f877a microcontroller 
Lcd_Init(); // Initialize LCD 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off 
Lcd_Out(1,1,"MQ-2 sensor" ); // Write text in first 
delay_ms(2000); 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
while(1) 
{ // Endless loop 
gas_value = ADC_Read(0); // It will read the gas value of sensor 
if( gas_value > 400 ) 
Lcd_Out(1,1, "Gas detected" ); 
else 
Lcd_Out(1,4, "No Gas " ); 
intToStr(gas_value, Ltrim(text)); 
Lcd_Out(2,1, text ); 
delay_ms(1000); 
} 
}