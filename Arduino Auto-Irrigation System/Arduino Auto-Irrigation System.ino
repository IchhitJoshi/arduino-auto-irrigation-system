#include <LiquidCrystal.h> 
#include <DS3231.h>

#define NOTE_C4 262 
#define NOTE_D4 294 
#define NOTE_E4 330 
#define NOTE_F4 349 
#define NOTE_G4 392 
#define NOTE_A4 440 
#define NOTE_B4 494                                               
#define NOTE_C5 523 

int Triggerpin=7;
int Echopin=6;
int M_Sensor = A0;
int W_Sensor= A1;
int Pump = 13;
int Buzzer = 9; 

String DOW;
String Date;
String OnTime;
String OffTime;
String answer = ""; 

int SurfaceArea = 121;
float height1;
float height2;
float duration1;
float duration2;
float distance1;
float distance2;
float initvolume;
float finalvolume;
float VolumeUsed;

double startTime = 0;  
double stopTime = 0;  
double runTime = 0;  
double totTime = 0;

int pumpCommand = 8; 

boolean pumpLastState = false;
boolean pumpRunning = false; 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DS3231 rtc(SDA, SCL);

void setup()
 {

    Serial.begin(9600);
    
    lcd.begin(16, 2);
    lcd.clear();
    
    rtc.begin();
    
    pinMode(Pump,OUTPUT);
    pinMode(Buzzer,OUTPUT);
    pinMode(pumpCommand, INPUT);  
    digitalWrite(pumpCommand, HIGH);
    
    lcd.setCursor(0,0);
    lcd.print("Auto-Irrigation");
    lcd.setCursor(4,1);
    lcd.print("System");
    delay(2000);
    lcd.clear(); 
   
    lcd.clear(); 
    lcd.setCursor(0,0);
    lcd.print("Project By :");
    lcd.setCursor(0,1);
    lcd.print("Thought Squad");
    delay(2000);
    lcd.clear ();
}

void loop()
{
 
  lcd.clear();
  int Moisture = analogRead(M_Sensor); 
  int Water = analogRead(W_Sensor);
  
  if (Moisture> 750){  // if soil is dry
    lcd.setCursor(11,0);
    lcd.print("DRY");
    lcd.setCursor(11,1);
    lcd.print("SOIL");
    
    if (Water> 450){ // if water pump has water
      
      pumpLastState = digitalRead(pumpCommand);
      
      if (pumpRunning == false && pumpLastState == HIGH){ // if water pump was previously running and currently isn't running
         
        digitalWrite(Pump, HIGH);
        lcd.setCursor(0,1);
        lcd.print("PUMP:ON");

        pinMode(Triggerpin, OUTPUT);
        digitalWrite(Triggerpin, LOW);
        delayMicroseconds(2);
        digitalWrite(Triggerpin,HIGH);
        delayMicroseconds(10);
        digitalWrite(Triggerpin,LOW);
        pinMode(Echopin, INPUT);

        duration1=pulseIn(Echopin,HIGH);
        distance1=(duration1 /2)*0.034364;
        initvolume=(distance1 * SurfaceArea)*0.001;
  
        pumpRunning = true;  
        runTime = 0; 
        startTime = millis();  
        
        DOW = rtc.getDOWStr();
        Date = rtc.getDateStr();
        OnTime = rtc.getTimeStr(); 
      }      
         
      else if (pumpRunning==true && pumpLastState==HIGH){ // if water pump was previously running and is currently running
         
        digitalWrite(Pump, HIGH);
        lcd.setCursor(0,1);
        lcd.print("PUMP:ON");
           
      }
         
      else if (pumpRunning ==false && pumpLastState==LOW){ // if water pump is not currently running and was not running
         
        digitalWrite(Pump, HIGH);
        lcd.setCursor(0,1);
        lcd.print("PUMP:ON");

        pinMode(Triggerpin, OUTPUT);
        digitalWrite(Triggerpin, LOW);
        delayMicroseconds(2);
        digitalWrite(Triggerpin,HIGH);
        delayMicroseconds(10);
        digitalWrite(Triggerpin,LOW);
        pinMode(Echopin, INPUT);
        duration1=pulseIn(Echopin,HIGH);
        distance1=(duration1 /2)*0.034364;
        initvolume=(distance1 * SurfaceArea)*0.001;

        pumpRunning = true;  
        runTime = 0; 
        startTime = millis();  

        OnTime = rtc.getTimeStr(); 
      
        digitalWrite(pumpCommand, HIGH);
     
      }

    }
           
    else{ // if water pump has no water
       
      digitalWrite(Pump, LOW);
      lcd.setCursor(0,1);
      lcd.print("PUMP:OFF");
           
      tone(Buzzer, NOTE_C4, 500); 
      delay(500); 
      tone(Buzzer, NOTE_D4, 500);
      delay(500); 
      tone(Buzzer, NOTE_E4, 500); 
      delay(500); 
      tone(Buzzer, NOTE_F4, 500); 
      delay(500); 
      tone(Buzzer, NOTE_G4, 500); 
      delay(500);
    }
  }
  
  if (Moisture>= 450 & Moisture<=750){ // if soil is moist 


    if (pumpLastState == HIGH && pumpRunning == true){ // if water pump is currently running
      digitalWrite(Pump, LOW); 
      lcd.setCursor(11,0);
      lcd.print("MOIST");
      lcd.setCursor(11,1);
      lcd.print("SOIL");
      lcd.setCursor(0,1);
      lcd.print("PUMP:OFF"); 

      pinMode(Triggerpin, OUTPUT);
      digitalWrite(Triggerpin, LOW);
      delayMicroseconds(2);
      digitalWrite(Triggerpin,HIGH);
      delayMicroseconds(10);
      digitalWrite(Triggerpin,LOW);
      pinMode(Echopin, INPUT);
      
      duration2=pulseIn(Echopin,HIGH);
      distance2=(duration2/2)*0.034364; 
      finalvolume=(distance2*SurfaceArea)*0.001; 
                
      pumpRunning = false;  
      stopTime = millis();  
      runTime +=(stopTime - startTime)/1000;
      totTime += runTime; // 
      
      OffTime = rtc.getTimeStr(); 
      
      VolumeUsed=finalvolume-initvolume;
    
      answer = DOW + " " + Date + " " +  OnTime + " " + OffTime + " "  + String(runTime) + " " + String(totTime) + " " + String(VolumeUsed);

      Serial.write(answer.c_str()); //send info to Ethernet i.e the localhost website
      
      digitalWrite(pumpCommand, LOW);
     
    }
   
    else{ // if water pump is not running
      lcd.setCursor(11,0);
      lcd.print("MOIST");
      lcd.setCursor(11,1);
      lcd.print("SOIL");
      digitalWrite(Pump,LOW);
      digitalWrite(pumpCommand, LOW);
      pumpRunning=false;
      lcd.setCursor(0,1);
      lcd.print("PUMP:OFF");    
    }
  }
 
  if (Moisture < 450){ // if soil is soggy 

    if (pumpLastState == HIGH && pumpRunning == true){ // if water pump is currently running
      
      digitalWrite(Pump, LOW); 
      lcd.setCursor(11,0);
      lcd.print("SOGGY");
      lcd.setCursor(11,1);
      lcd.print("SOIL");
      lcd.setCursor(0,1);
      lcd.print("PUMP:OFF"); 

      pinMode(Triggerpin, OUTPUT);
      digitalWrite(Triggerpin, LOW);
      delayMicroseconds(2);
      digitalWrite(Triggerpin,HIGH);
      delayMicroseconds(10);
      digitalWrite(Triggerpin,LOW);
      pinMode(Echopin, INPUT);
      
      duration2=pulseIn(Echopin,HIGH);
      distance2=(duration2/2)*0.034364; 
      finalvolume=(distance2*SurfaceArea)*0.001; 
              
      pumpRunning = false;  
      stopTime = millis();  
      runTime +=(stopTime - startTime)/1000;
      totTime += runTime; // 
      
      OffTime = rtc.getTimeStr(); 
      
      VolumeUsed=finalvolume-initvolume;

      answer = DOW + " " + Date + " " +  OnTime + " " + OffTime + " "  + String(runTime) + " " + String(totTime) + " " + String(VolumeUsed) ;

      Serial.write(answer.c_str()); //send info to Ethernet i.e the localhost website
      digitalWrite(pumpCommand, LOW);
     
    }

    else{ // if pump is not running

      lcd.setCursor(11,0);
      lcd.print("SOGGY");
      lcd.setCursor(11,1);
      lcd.print("SOIL");
      digitalWrite(Pump,LOW);
      digitalWrite(pumpCommand, LOW);
      pumpRunning=false;
      lcd.setCursor(0,1);
      lcd.print("PUMP:OFF");    
  
    }
  }
  delay(1000);    
}  
