#include <LiquidCrystal.h>
 
int motorIn1 = 2;
int motorIn2 = 3;
int motorEnA = 10;
 
int encoder = 6;
 
volatile unsigned int counter;
int rpm;
 
//const int rs = 8, en = 3, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
 
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorEnA, OUTPUT);
  pinMode(encoder, INPUT);
 
  digitalWrite(encoder, HIGH);
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  analogWrite(motorEnA, 60);

  Serial.begin(9600);  
  attachInterrupt(0,countpulse,RISING);
//  lcd.begin(16, 2);
}
 
void countpulse(){
        counter++;
}
 
void loop() {
  static uint32_t previousMillis;
  if (millis() - previousMillis >= 1000) {
            rpm = (counter/20)*60;          
            counter = 0;
            previousMillis += 1000;
  }
 
   Serial.println(rpm);
  delay(1);
}
