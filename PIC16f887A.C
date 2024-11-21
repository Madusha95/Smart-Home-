///////////////////ultrasonic 
int ultara; 
char ultratext[10]; 
////////////////////////ACS712 
unsigned long adcVoltage; 
unsigned long sensitivity=100; 
unsigned long offsetVoltage=0; 
unsigned long currentValue; 
unsigned int i; 
char digit[]="0.000"; 
unsigned long x; 
///////////////////////MQ-2 
int gas_value; 
char gasstext[10]; 
//////////////////////hall effect 
#include <built_in.h> 
unsigned int SomeInt1; 
unsigned int a; 
unsigned int time; 
char halltext[15]; 
/////////////////////BPM 
int RxBMP; 
char btext[10]; 
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
//DHT11 
unsigned char Check; 
unsigned char uniT=0,decT=0,uniHR=0,decHR=0; 
unsigned char  T_byte1, T_byte2,RH_byte1, RH_byte2; 
unsigned Sum; 
sbit DataDHT       
at    PORTA.B5;   //assigning pins for DHT11 
sbit InDataDHT     at    TRISA.B5; 
/////////////////////////////////// 
void StartSignal() 
{
    TRISA.F5 = 0;   //configuration of reciving data 
DataDHT = 0; 
delay_ms(18); 
DataDHT = 1; 
delay_us(30); 
TRISA.F5 = 1; 
} 
////////////////////////////// 
void CheckResponse() 
{ 
} 
Check = 0;                    
delay_us(40); 
if(DataDHT == 0) 
{ 
} 
delay_us(80); 
if (DataDHT == 1) 
Check = 1; 
delay_us(40); 
//checking respond from the DHT11 sensor 
////////////////////////////// 
char ReadData() 
{ 
char i, j; 
for(j = 0; j < 8; j++)    //Reading data Array 
{ 
while(!DataDHT); 
delay_us(30); 
if(DataDHT == 0)
  i&= ~(1<<(7 - j)); 
    else 
    { 
      i|= (1 << (7 - j)); 
      while(DataDHT); 
    } 
  } 
 return i; 
} 
 
void dht11(){ 
 
UART1_Init(9600); 
ADCON1=0x06; 
 
Lcd_Init(); 
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
 
 
//while(1) 
//{ 
  StartSignal(); 
  CheckResponse(); 
  if(Check == 1) 
  { 
    RH_byte1 = ReadData(); 
    RH_byte2 = ReadData(); 
    T_byte1 = ReadData(); 
 T_byte2 = ReadData(); 
    Sum = ReadData(); 
 
    if(Sum == ((RH_byte1+RH_byte2+T_byte1+T_byte2) & 0XFF)) 
    { 
     decHR=RH_byte1/10; 
     uniHR=RH_byte1%10; 
     decT=T_byte1/10; 
     uniT=T_byte1%10; 
 
     decHR=decHR+0x30; 
     uniHR=uniHR+0x30; 
     decT=decT+0x30; 
     uniT=uniT+0x30; 
 
     Lcd_Out(1,1, "TEMP= "); 
     Lcd_Chr(1,7, decT); 
     Lcd_Chr(1,8, uniT); 
     Lcd_Out_Cp(" oC"); 
 
     Lcd_Out(2,1, "HR= "); 
     Lcd_Chr(2,7, decHR); 
     Lcd_Chr(2,8, uniHR); 
     Lcd_Out_Cp(" %"); 
 
    } 
  } 
  else 
  {
    Lcd_Cmd(_LCD_CLEAR); 
Lcd_Out(1, 1, "error"); 
} 
UART1_Write(RH_byte1); 
UART1_Write(T_byte1); 
Delay_ms(500); 
delay_ms(1000); 
//} 
} 
/////////////////////////////// 
//////////////////////////////rain drop sensor 
void rain() { 
TRISD = 0b00001000; 
UART1_Init(9600); 
Lcd_Init(); // Initialize LCD 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off 
Lcd_Out(1,1,"Rain sensor" ); // Write text in first 
delay_ms(2000); 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
//while(1){ 
if(PORTD.F3 == 1) 
{ 
Lcd_Out(1,1,"Not Raining"); 
delay_ms(2000);
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
} 
else 
{ 
Lcd_Out(1,1,"Raining"); 
delay_ms(2000); 
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
} 
//} 
} 
///////////////////////////////////// 
////////////////////////////////////ultrasonic 
void ultrasonic() { 
UART1_Init(9600); 
delay_ms(10); 
Lcd_Init(); // Initialize LCD 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off 
delay_ms(2000); 
TRISD = 0b10000000; 
T1CON = 0x10;                 
TMR1H = 0;                  
TMR1L = 0;                  
//Initialize Timer Module 
//Sets the Initial Value of Timer 
//Sets the Initial Value of Timer
PORTD.F6 = 1;               
Delay_us(10);               
PORTD.F6 = 0;               
while(!PORTD.F7);           
T1CON.F0 = 1;               
while(PORTD.F7);            
T1CON.F0 = 0;               
//TRIGGER HIGH 
//10uS Delay 
//TRIGGER LOW 
//Waiting for Echo 
//Timer Starts 
//Waiting for Echo goes LOW 
//Timer Stops 
ultara = (TMR1L | (TMR1H<<8));   //Reads Timer Value 
ultara = ultara/58.82;                
ultara = ultara/2;                  
UART1_Write(ultara); 
//SomeInt1=ultara; 
//Converts Time to Distance 
//Distance Calibration 
//UART1_Write(Lo(SomeInt1)); 
//UART1_Write(Hi(SomeInt1)); 
delay_ms(100); 
Lcd_Out(1,1, "Distance(cm)" ); 
intToStr(ultara,ultratext); 
Lcd_Out(2,1,ultratext); 
delay_ms(1000); 
} 
/////////////////////////////////ACS712 
void ACS712() {
    //TRISA=0xFF; 
ADCON0=0x01; 
ADCON1=0x0E; 
UART1_Init(9600); 
Lcd_Init();                        
// Initialize LCD 
Lcd_Cmd(_LCD_CLEAR);               
Lcd_Cmd(_LCD_CURSOR_OFF);          
LCD_Out(1,1,"Current Sensor"); 
Delay_ms(1000); 
// Clear display 
// Cursor off 
adcVoltage = ADC_Read(0);   // Get 10-bit results of AD conversion 
adcVoltage=adcVoltage*5000/1023;   //Convert ADC value to mV 
currentValue = ((adcVoltage - offsetVoltage) / sensitivity); 
digit[0]=(currentValue/1000)+48; 
digit[2]=((currentValue%1000)/100)+48; 
digit[3]=(((currentValue%1000)%100)/10)+48; 
digit[4]=(((currentValue%1000)%100)%10)+48; 
//LongToStr(currentValue,digit); 
LCD_Cmd(_LCD_CLEAR); 
LCD_Out(1,1,"Current(mA)"); 
LCD_Out(2,1,digit); 
// x = xtoi(currentValue)*10000; 
UART1_Write(currentValue); 
Delay_ms(500);
} 
////////////////////////////////////////////// MQ-2 
void gas() 
{ 
ADC_Init(); // 
Lcd_Init(); // Initialize LCD 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off 
Lcd_Out(1,1,"MQ-2 sensor" ); 
delay_ms(2000); 
Lcd_Cmd(_LCD_CLEAR); // Clear display 
//while(1) 
//{ 
gas_value = ADC_Read(0); // It will read the gas value of sensor 
if( gas_value > 400 ) 
Lcd_Out(1,1, "Gas detected" ); 
else 
Lcd_Out(1,4, "No Gas " ); 
intToStr(gas_value, Ltrim(gasstext)); 
Lcd_Out(2,1,gasstext); 
UART1_Write(gas_value); 
delay_ms(1000); 
}
///////////////////////////////////////////hall effect sensor 
void hall() { 
UART1_Init(9600); 
Lcd_Init(); 
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
TRISD = 0b0000011; 
T1CON = 0x10;                 
//while(1) 
//{ 
if (PORTD.F1==1){ 
TMR1H = 0;                  
TMR1L = 0; 
while(!PORTD.F0);           
T1CON.F0 = 1;               
while(PORTD.F0);            
T1CON.F0 = 0;               
//Initialize Timer Module 
//Sets the Initial Value of Timer 
//Waiting for Edge a toggle 
//Timer Starts 
//Waiting for Edge a togle again 
//Timer Stops 
a = (TMR1L | (TMR1H<<8));   //Reads Timer Value 
time= (200*a)/1000; 
SomeInt1=time; 
UART1_Write(Lo(SomeInt1)); 
IntToStr(time,halltext); 
//UART1_Write(Hi(SomeInt1)); 
Lcd_Out(1,1, "Speed:"); 
Lcd_Out(1,7,halltext);
delay_ms(100); 
// } 
} 
} 
////////////////////////////////////////Heart rate Sensor 
void BPM(){ 
UART1_Init(9600); 
Lcd_Init(); 
Lcd_Cmd(_LCD_CLEAR); 
Lcd_Cmd(_LCD_CURSOR_OFF); 
//while(1){ 
if (UART1_Data_Ready() ==1) {    // Serial read(BPM value) from nodeMCU 
RxBMP = UART1_Read(); 
} 
//SomeInt1= receive; 
intToStr(RxBMP,btext); 
Lcd_Out(1,1, "Heart Rate:"); 
Lcd_Out(2,1,btext); 
//} 
} 
void main() { 
while(1){ 
dht11(); 
rain(); 
ultrasonic(); 
ACS712();
gas(); 
hall(); 
BPM(); 
} 
} 
