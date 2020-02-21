const int LS= A5; //LoudnessSrnsor on analog pin 5
//const int LED = 12;
const int BZ=8; //Buzzer on digital pin 11
const long interval = 15000; //time constant
int val = 0; //variable to hold the analog reading from the LS
int buzz = 0;
int max_sound = 220; //sound when I whistle
int min_sound = 100; //ambient sound in mb519 
int i;//for loop
unsigned long displayStarted =0; //time when display starts

#include "LiquidCrystal.h"
// POWERTIP LCD PC1602 - H
// LiquidCrystal display with:
// rs lcd  pin 4 on arduino pin 12
// rw lcd pin 5 on arduino pin 11
// enable lcd  pin 6 arduino on pin 10
// d4,d5,d6,d7 lcd pins 11, 12, 13, 14 on arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()  
{
  pinMode(LS, INPUT);
  pinMode(BZ, OUTPUT);
  Serial.begin(9600); 
  lcd.begin(16, 2);
}

void loop() 
{ 
  unsigned long Time = millis();
 
int maxWell = 0; // variable to store max values
  for(i=0;i<5000;i++)// 5sec 
  {
    delay(1);
    val = analogRead(LS);
    buzz = val;
   buzz = map(buzz, min_sound, max_sound, 0, 255); //Map the mic reading 
   buzz = constrain(buzz, 0, 255); //Constrain mic value
   analogWrite(BZ, buzz); //Control the buzzer
   //analogWrite(LED, buzz);
   //Serial.println(buzz); //it works, hurray, 255 when I whistl
    //Fire alarm : https://www.youtube.com/watch?v=NE9aI0l2k3g
    //Baby crying : https://www.youtube.com/watch?v=oL2B-AAnsHo
    //Engine running: https://www.youtube.com/watch?v=2Y33bTlAA-E 
   
    if (val > maxWell)
    {
      maxWell = val;
    }
 
   }
    Serial.println(maxWell);
 
  if (Time - displayStarted >= interval) 
  {
    if (110<maxWell and maxWell<120)
    {
    Serial.println("Engine Running!");
    lcd.setCursor(0,0);
    lcd.print("Engine   ");
    lcd.setCursor(0,1);
    lcd.print("Running!   ");
    displayStarted = Time;
    
     }
     else if(130<maxWell and maxWell<140)
     {
    Serial.println("Baby Crying!");
    lcd.setCursor(0,0);
    lcd.print("Baby   ");
    lcd.setCursor(0,1);
    lcd.print("Crying!   ");
    displayStarted = Time;
     }
     else if(140<maxWell and maxWell<150)
     {
    Serial.println("Fire Alarm!");
    lcd.setCursor(0,0);
    lcd.print("Fire   ");
    lcd.setCursor(0,1);
    lcd.print("Alarm!   ");
    displayStarted = Time;
     }
  }
 }
