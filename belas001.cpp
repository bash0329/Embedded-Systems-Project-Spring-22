#include <LiquidCrystal.h>
#include <IRremote.h>

IRrecv IR(3);

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
const int pin9 = 9;
const int pin10 = 10;


//lCD\ULTRASONIC 
int sensor = 3;              
int state = LOW;             
int value  = 0; 

//for pIR
int led = 12;                
int PIR_sen = 13;              
int PIR_state = LOW;            
int PIR_value  = 0;                

int distance;



typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_Ultrasonic {SM1_INIT, SM1_S0};
int SM1_Tick(int state){
    switch(state){ // State transitions
      case SM1_INIT:
            digitalWrite(pin9, LOW);
            delayMicroseconds(2);
            digitalWrite(pin9, HIGH);
            delayMicroseconds(10);
            digitalWrite(pin9, LOW);
            period  = pulseIn(pin10, HIGH);
            break;
      case SM1_S0:
         distance  = period  * 0.0133 / 2;
            lcd.setCursor(0,0); 
            lcd.print("Distance: ");
            lcd.print(distance );
            lcd.print(" inch");
            delay(10);
            break;
    switch(state)
    { // State Action
      case SM1_INIT:
            break;
      case SM1_S0:
            value = digitalRead(sensor);   
            if (value == HIGH) 
            {           
              delay(500);               
              
              if (state == LOW) 
              {
                state = HIGH;       
              }
            } 
            else 
            {
              delay(500);               
              if (state == HIGH)
              {
                state = LOW;  
              }
            }
    }

    return state;
}

enum SM2_Remote {SM2_INIT, SM2_S0,};
int SM2_Tick(int state)
{
    switch(state){ // State transitions
      case SM2_INIT:
            state = SM2_S0;
        break;
      case SM2_S0:
            state = SM2_INIT;
        break;
    }
    switch(state)
    { // State Action
      case SM2_INIT:
        value = digitalRead(sensor);   
        if (value == HIGH) 
        {           
          delay(500);               
          
          if (state == LOW) 
          {
            state = HIGH;       
          }
        } 
        break;
      case SM2_S0: 
            if 
            {
              delay(500);
              
              if (state == HIGH)
              {
                state = LOW;  
              }
            }
        break;
 
    }

    return state;
}


enum SM3_PIR {SM3_INIT, SM3_S0,};
int SM2_Tick(int state)
{
    switch(state){ // State transitions
      case SM3_INIT:
            state = SM3_S0;
        break;
      case SM3_S0:
            state = SM3_INIT;
        break;
    }
    switch(state)
    { // State Action
      PIR_value = digitalRead(PIR_sen);   
      if (PIR_value == HIGH) {           
        digitalWrite(led, HIGH);  
        delay(500);                
        
        else (PIR_state == LOW) {
          i  = millis();
          PIR_state = HIGH;       
        }
      } 
      break;
      case SM3_S0:
      if 
      {
        digitalWrite(led, LOW); 
        delay(500);
      }     
      else (PIR_state == HIGH)
      {
        Serial.print("Lasted: ");Serial.print((millis() - i )/1000);
        PIR_state = LOW;       
      }
  }
 
    }

    return state;
}





void setup() {
   
  //lCD\ULTRASONIC

  IR.enableIRIn();
  Serial.begin(9600);

  lcd.begin(16, 2); 
  pinMode(pin9, OUTPUT);
  pinMode(pin10, INPUT);

  
  pinMode(sensor, INPUT);    
  Serial.begin(9600); 


  //PIR
  pinMode(led, OUTPUT);      
  pinMode(PIR_sen, INPUT);    
  Serial.begin(9600);        
  delay(15000);
}

  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_S0;
  i++;
  
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_S0;
  i++

  tasks[i].state = SM3_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_S0;
  i++

}


void loop() {
 //lCD\ULTRASONIC
  digitalWrite(pin9, LOW);
  delayMicroseconds(2);
  digitalWrite(pin9, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin9, LOW);
  period  = pulseIn(pin10, HIGH);
  distance  = period  * 0.0133 / 2;
  lcd.setCursor(0,0); 
  lcd.print("Distance: ");
  lcd.print(distance );
  lcd.print(" inch");
  delay(10);
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); 
     }
   }
}
