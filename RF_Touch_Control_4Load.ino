#include "RCSwitch.h"
#include <EEPROM.h>

RCSwitch mySwitch = RCSwitch();

#define Relay1 3 // Load1 Pin Out
#define Relay2 4 // Load2 Pin Out
#define Relay3 5 // Load3 Pin Out
#define Relay4 6 // Load4 Pin Out

#define touch1 A0 // Light Button Pin in
#define touch2 A1 // Lamp Button Pin in 
#define touch3 A2 // Socket Button Pin in 
#define touch4 A3 // Fan Button Pin in

int load1, load2, load3, load4;
int flag1, flag2, flag3, flag4;

void setup() {
Serial.begin(9600);

mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2

pinMode(touch1, INPUT);
pinMode(touch2, INPUT);
pinMode(touch3, INPUT);
pinMode(touch4, INPUT);

load1 = EEPROM.read(1);
load2 = EEPROM.read(2);
load3 = EEPROM.read(3);
load4 = EEPROM.read(4);

pinMode(Relay1, OUTPUT); digitalWrite(Relay1, load1); 
pinMode(Relay2, OUTPUT); digitalWrite(Relay2, load2); 
pinMode(Relay3, OUTPUT); digitalWrite(Relay3, load3); 
pinMode(Relay4, OUTPUT); digitalWrite(Relay4, load4); 
delay(100);  
}

void loop() {
  
if(digitalRead(touch1)==1){
if(flag1==0){flag1=1; 
load1 = !load1; 
EEPROM.write(1, load1); 
Relays();
delay(100);
 }
}else{flag1=0;}

if(digitalRead(touch2)==1){ 
if(flag2==0){flag2=1; 
load2 = !load2; 
EEPROM.write(2, load2); 
Relays();
delay(100);
 }
}else{flag2=0;}

if(digitalRead(touch3)==1){ 
if(flag3==0){flag3=1; 
load3 = !load3; 
EEPROM.write(3, load3); 
Relays();
delay(100);
 }
}else{flag3=0;}

if(digitalRead(touch4)==1){ 
if(flag4==0){flag4=1; 
load4 = !load4; 
EEPROM.write(4, load4); 
Relays();
delay(100);
 }
}else{flag4=0;}

  
if (mySwitch.available()>0) {  
unsigned long int RF_data =  mySwitch.getReceivedValue() ;
Serial.println(RF_data);

switch(RF_data){
  case 1393923: mySwitch.disableReceive();
                load1 = !load1;
                EEPROM.write(1, load1);
                break;
                
  case 1393932: mySwitch.disableReceive();
                load2 = !load2;
                EEPROM.write(2, load2);
                break;
                              
  case 1393968: mySwitch.disableReceive();
                load3 = !load3;
                EEPROM.write(3, load3);
                break; 
                
   case 1394112: mySwitch.disableReceive();
                load4 = !load4;
                EEPROM.write(4, load4);
                break;                

}

Relays();

unsigned long time_now = millis();
int ck = 500;
while(millis()<time_now + ck){;}
  mySwitch.resetAvailable();
  mySwitch.enableReceive(0);
  }
}

void Relays(){
digitalWrite(Relay1, load1); 
digitalWrite(Relay2, load2); 
digitalWrite(Relay3, load3); 
digitalWrite(Relay4, load4);
}

