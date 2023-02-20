const int pinIR0 = A0;
const int pinIR1 = A1;
const int pinIR2 = A2;
const int pinIR3 = A3;
const int pinIR4 = A4;
const int pinIR5 = A5;
const int pinIR6 = A6;

int IRvalue[7];
int max_value=0;
int min_value=1000;


int i = 0;

void setup()
{
  Serial.begin(9600);
//  pinMode(pinIRb,INPUT);
  pinMode(pinIR0,INPUT);
  pinMode(pinIR1,INPUT);
  pinMode(pinIR2,INPUT);
  pinMode(pinIR3,INPUT);
  pinMode(pinIR4,INPUT);
  pinMode(pinIR5,INPUT);
  pinMode(pinIR6,INPUT);
}

void loop()
{
  IRvalue[0] = analogRead(pinIR0);
  IRvalue[1] = analogRead(pinIR1);
  IRvalue[2] = analogRead(pinIR2);
  IRvalue[3] = analogRead(pinIR3);
  IRvalue[4] = analogRead(pinIR4);
  IRvalue[5] = analogRead(pinIR5);
  IRvalue[6] = analogRead(pinIR6);
  
  int x = (IRvalue[6]);
  delay(100);
  if(x > max_value){
    max_value = x;
  }
  if(x < min_value){
    min_value = x;
  }
  Serial.println(max_value);
  Serial.println(min_value);
//  
//  if (i == 5000){
//    Serial.print("Max Value = ");
//    Serial.println(max_value);
// 
//    Serial.print("Min Value = ");
//    Serial.println(min_value);
//  
//    max_value = 0;
//    min_value = 1000;
//    i = 0;
//  }
//  i++;
}
