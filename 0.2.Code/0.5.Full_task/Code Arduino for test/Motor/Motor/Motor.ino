int motorIn1 = 5;
int motorIn2 = 4;
int motorIn3 = 6;
int motorIn4 = 7;
int motorEn = 1;
int encoder1 = 2;
int encoder2 = 3;

float counter1;
float counter2;
int rpm1;
int rpm2;
int i = random(255);
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  pinMode(motorEn, OUTPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn4, LOW);
  digitalWrite(motorEn, HIGH);

  attachInterrupt(0,countpulse1,RISING);
  attachInterrupt(1,countpulse2,RISING);
}

void countpulse1(){
        counter1++;
}

void countpulse2(){
        counter2++;
}

void loop() {
  analogWrite(motorIn1, i); // Send PWM signal to L298N In1 pin
  analogWrite(motorIn3, i); // Send PWM signal to L298N In3 pin
  
  static uint32_t previousMillis;
    
  if (millis() - previousMillis >= 1000) {
            rpm1 = (counter1/374)*60;
            rpm2 = (counter2/374)*60;  
                    
            counter1 = 0;
            counter2 = 0;

            previousMillis += 1000;
  }

  Serial.print(" i = ");
  Serial.print(i);
  Serial.print(", RPM1 = ");
  Serial.print(rpm1);
  Serial.print(", RPM2 = ");
  Serial.println(rpm2);
  count += 1;
  if (count == 400){
    count = 0;
    i = random(25);
    }

}
