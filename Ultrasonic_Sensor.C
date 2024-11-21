//int a=500; 
#include <built_in.h> 
unsigned int SomeInt1; 
//unsigned int SomeInt2; 
void main() { 
UART1_Init(9600); 
delay_ms(10); 
TRISD = 0b00000010; 
T1CON = 0x10;                 
while(1) 
{ 
TMR1H = 0;                  
TMR1L = 0;                  
PORTD.F0 = 1;               
Delay_us(10);               
PORTD.F0 = 0;               
while(!PORTD.F1);           
T1CON.F0 = 1;               
while(PORTD.F1);            
T1CON.F0 = 0;               
//Initialize Timer Module 
//Sets the Initial Value of Timer 
//Sets the Initial Value of Timer 
//TRIGGER HIGH 
//10uS Delay 
//TRIGGER LOW 
//Waiting for Echo 
//Timer Starts 
//Waiting for Echo goes LOW 
//Timer Stops 
a = (TMR1L | (TMR1H<<8));   //Reads Timer Value 
a = a/58.82;                
//Converts Time to Distance 
a = a + 1;                  
UART1_Write(a); 
SomeInt1=a; 
//Distance Calibration 
UART1_Write(Lo(SomeInt1)); 
//UART1_Write(Hi(SomeInt1)); 
delay_ms(100); 
} 
}