int motorIn1 = 5;
int motorIn2 = 4;
int motorIn3 = 6;
int motorIn4 = 7;
int motorEn = 1;
int encoder1 = 2;
int encoder2 = 3;

const int pinIR0 = A0;
const int pinIR1 = A1;
const int pinIR2 = A2;
const int pinIR3 = A3;
const int pinIR4 = A4;
const int pinIR5 = A5;
const int pinIR6 = A6;

int IRvalue[7];

float counter1;
float count1;
float pre_count1;
float counter2;
float count2;
float pre_count2;

float rpm1;
float rpm2;

float left_rpm = 180;
float right_rpm = 180;
float left_rpm_max = 320;
float right_rpm_max = 320;

float Kp_left = 0.8;
float Kp_right = 0.833;

float left_pwm = Kp_left*left_rpm - 7.7;
float right_pwm = Kp_right*right_rpm - 13;
float P_pwm = 0;
float I_pwm;
float D_pwm;

unsigned int Ts; // Sampling time
static uint32_t pre_mil;

unsigned int count = 0;
void Motor_PID_Left(float Va_rel, unsigned long Va_pur  )
{
  float pre_Err;
  
  float Ki = 0.01 ;
  float Kp = 1.4067;
  float Kd = 0;
  float Err = Va_pur - Va_rel; //tinh error
  float pPart = Kp*Err;
  float dPart = Kd*(Err - pre_Err);
  float iPart = iPart + Ki*(Err + pre_Err);
  float PID_val = pPart + dPart + iPart;
  pre_Err = Err; //luu lai gia tri error
  left_pwm = left_pwm + PID_val;
}
void Motor_PID_Right(float Va_rel, unsigned long Va_pur  )
{
  float pre_Err;
  
  float Ki = 0.01 ;
  float Kp = 1.21;
  float Kd = 0;
  float Err = Va_pur - Va_rel; //tinh error
  float pPart = Kp*Err;
  float dPart = Kd*(Err - pre_Err);
  float iPart = iPart + Ki*(Err + pre_Err);
  float PID_val = pPart + dPart + iPart;
  pre_Err = Err; //luu lai gia tri error
  right_pwm = right_pwm + PID_val;
}

void setup() {
  Serial.begin(9600);
  
  //cam bien line
  pinMode(pinIR0,INPUT);
  pinMode(pinIR1,INPUT);
  pinMode(pinIR2,INPUT);
  pinMode(pinIR3,INPUT);
  pinMode(pinIR4,INPUT);
  pinMode(pinIR5,INPUT);
  pinMode(pinIR6,INPUT);
  
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

  randomSeed(analogRead(A0));
}

void adc(){
  IRvalue[0] = analogRead(pinIR0);
  IRvalue[1] = analogRead(pinIR1);
  IRvalue[2] = analogRead(pinIR2);
  IRvalue[3] = analogRead(pinIR3);
  IRvalue[4] = analogRead(pinIR4);
  IRvalue[5] = analogRead(pinIR5);
  IRvalue[6] = analogRead(pinIR6);
   
  for (int i =0; i < 7; i++){
    if(IRvalue[i] < 40){IRvalue[i] = 0;}
    else if (IRvalue[i] >= 40) {IRvalue[i] = 1;}
    Serial.print(IRvalue[i]);
  }
  Serial.println();
  delay(100);
}

void countpulse1(){
        counter1++;
}

void countpulse2(){
        counter2++;
}

void get_rpm(){
  Ts =  millis() - pre_mil;
    
  count1 = counter1 - pre_count1;
  count2 = counter2 - pre_count2;
  pre_count1 = counter1;
  pre_count2 = counter2;
    
  
  rpm1 = (count1/374)/(Ts * 0.001 * 1/60);
  rpm2 = (count2/374)/(Ts * 0.001 * 1/60);  

  pre_mil += Ts;
    
//  Serial.print(rpm2, 2);
//  Serial.print("_");
//  Serial.println(rpm1, 2);
//  Serial.println(Ts);
}

void loop() { 
  if(count == 15000) {
    get_rpm();
    adc();
//    Motor_PID_Left(rpm2, left_rpm);
//    Motor_PID_Right(rpm1, right_rpm);
    count = 0;    
  }
//  analogWrite(motorIn1, 150); // Send PWM signal to L298N In1 pin
//  analogWrite(motorIn3, 150); // Send PWM signal to L298N In3 pin
  count ++;

}
