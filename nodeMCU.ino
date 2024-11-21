#include <ESP8266WiFi.h>      
#include "ThingSpeak.h" 
#include <SoftwareSerial.h> 
const char* ssid="Madusha"; 
//thingspeak 
const char* password="madusha12345"; 
unsigned long myChannelNumber =1001400; 
const char* myWriteAPIkey="6Q72P02Q5GEMHBF0";// thingspeak 
const char* myReadAPIkey="EMNYDVST5A5I70FU"; //thingspeak 
unsigned long myChannelNumber1 =1091314; 
const char* myWriteAPIkey1="WLJOQ05IKWD5OYQN";// thingspeak 
const char* myReadAPIkey1="JDGBVK55N9MRYTGG"; //thingspeak 
//////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////// 
WiFiClient client; 
SoftwareSerial s(4,5); 
SoftwareSerial sim(7,8); 
///////////////////////////////////////////////////////////////// 
#include <Wire.h> 
//Heart rate sensor initiation  
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math. 
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0 
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore. 
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default 
setting. 
                               // Otherwise leave the default "550" value.  
 
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called 
"pulseSensor" 
///////////////////////////////////////////////////////////////////////// 
////////////Blynk app 
#define BLYNK_PRINT Serial // Enables Serial Monitor 
#include <SPI.h> 
#include <Ethernet.h> 
#include <BlynkSimpleEthernet.h> 
char auth[] = "JnpEiz2ouz30e74NB0ZbQvxZgYhcs598"; 
 
 
float MQ;  // Assigning variables 
float ACS; 
float wlevel; 
float DHT11; 
float tem; 
float humidity; 
float power; 
float Device1; 
float Device2; 
float Device3; 
float Device4; 
float rpm; 
 
 
void setup() { 
Serial.begin(115200);
s.begin(115200); 
WiFi.begin(ssid,password); 
Blynk.begin(auth);  
while(!Serial) continue; 
while( WiFi.status() != WL_CONNECTED) 
{ 
delay(500); 
Serial.println("connecting......"); 
} 
Serial.println("WiFi is connected"); 
ThingSpeak.begin(client);  //thingspeak 
} 
void loop() { 
if (Serial.available()){ 
MQ =Serial.read(); 
Serial.print("MQ:"); 
Serial.println(MQ); 
} 
if (Serial.available()){ 
Serial.print("ACS:"); 
ACS =Serial.read(); 
Serial.println(ACS); 
} 
if (Serial.available()){ 
wlevel =Serial.read(); 
Serial.print("wlevel:"); 
Serial.println(wlevel); 
}
if (Serial.available()){ 
Serial.print("DHT11:"); 
DHT11 =Serial.read(); 
Serial.println(DHT11); 
} 
if (Serial.available()){ 
humidity =Serial.read(); 
Serial.print("humidity:"); 
Serial.println(humidity); 
} 
if (Serial.available()){ 
power =Serial.read(); 
Serial.print("power:"); 
Serial.println(power); 
} 
if (Serial.available()){ 
rpm =Serial.read(); 
Serial.print("rpm:"); 
Serial.println(rpm); 
} 
BPM(); 
blyk(); 
tothingspeak(); 
tothingspeak1(); 
SendMessage(); 
} 
void tothingspeak(){  //For channel1 
ThingSpeak.setField(1,MQ);
ThingSpeak.setField(2,ACS); 
ThingSpeak.setField(3,PulseWire); 
ThingSpeak.setField(4,humidity); 
ThingSpeak.setField(5,power); 
ThingSpeak.setField(6,Device1); 
ThingSpeak.setField(7,Device2); 
ThingSpeak.setField(8,Device3); 
ThingSpeak.writeFields(myChannelNumber,myWriteAPIkey);  
} 
/////////////////////////////////////////////////////////// 
void tothingspeak1(){ //For channel2 
ThingSpeak.setField(1,Device4); 
ThingSpeak.setField(2,PulseWire); 
ThingSpeak.setField(3,rpm); 
ThingSpeak.writeFields(myChannelNumber1,myWriteAPIkey1);  
} 
void BPM() {    
Serial.begin(9600);          
// For Serial Monitor
// Configure the PulseSensor object, by assigning our variables to it.  
pulseSensor.analogInput(PulseWire);   
pulseSensor.setThreshold(Threshold);    
// Double-check the "pulseSensor" object was created and "began" seeing a signal.  
if (pulseSensor.begin()) { 
Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or 
on Arduino reset.   
s.print(PulseWire); 
} 
} 
void blyk() 
{ 
// All the Blynk process happens here... 
Blynk.run(); 
if (D0 == 1){ 
Device1 = 1; 
if (D1 == 1){ 
Device2 = 1; 
if (D2 == 1){ 
Device3 = 1; 
if (D3 == 1){ 
Device4 = 1; 
} 
} 
} 
} 
else{ 
Device1 = 0; 
Device2 = 0; 
Device3 = 0; 
Device4 = 0; 
}  
} 
void SendMessage() 
{ 
String dataMessage = ("Temperature: " + String(temp) + "*C " + " Humidity: " + String(himudity) + 
"BPM: " + String(bpm)  + " windspeed: " + String(rpm) + "Water Level:" + String(wlevel)"%"); 
//if (Serial.available()>0){ 
//char a = Serial.read(); 
if (D6 == 1){  // if GSM Switch is on 
Serial.println("AT+CMGF=1"); 
sim.println("AT+CMGF=1"); 
delay(1000); 
Serial.println("AT+CMGS=\"+94779408269\"\r"); 
sim.println("AT+CMGS=\"+94779408269\"\r"); 
delay(1000);  
sim.println(dataMessage); 
delay(1000);  
Serial.println((char)26); 
sim.println((char)26); 
delay(1000);   
} 
}