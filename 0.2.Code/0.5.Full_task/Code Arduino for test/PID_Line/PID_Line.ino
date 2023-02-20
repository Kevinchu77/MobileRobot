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
float a0 = 2.61;
float b0 = 33;
float a1 = 1.18;
float b1 = 33;
float a2 = 0.91;
float b2 = 33;
float a3 = 1.63;
float b3 = 33;
float a4 = 1.5;
float b4 = 33;
float a5 = 2.2;
float b5 = 33;
float a6 = 1.3;
float b6 = 33;
float Kp = 0;
float Ki = 0;
float Kd = 0;
float pre_Err;

float counter1;
float count1;
float pre_count1;
float counter2;
float count2;
float pre_count2;
float rpm1;
float rpm2;

float set_rpm  = 150;
float left_rpm;
float right_rpm;

float left_pwm;
float right_pwm;

float left_pre_Err; 
float Kp_left = 0.1 ;
float Ki_left = 0;
float Kd_left = 0;

float right_pre_Err;
float Kp_right = 0.1 ;
float Ki_right = 0;
float Kd_right = 0;

unsigned int Ts; // Sampling time
static uint32_t pre_mil;

unsigned int count = 0;
void Motor_PID_Left(float Va_rel, unsigned long Va_pur  )
{
  float Err = Va_pur - Va_rel; //tinh error
  float pPart = Kp_left*Err;
  float dPart = Kd_left*(Err - left_pre_Err);
  float iPart = Ki_left*(Err + left_pre_Err);
  float PID_val = pPart + dPart + iPart;
  left_pre_Err = Err; //luu lai gia tri error
  left_pwm = (0.8*left_rpm - 7.7) + PID_val;
}
void Motor_PID_Right(float Va_rel, unsigned long Va_pur  )
{
  float Err = Va_pur - Va_rel; //tinh error
  float pPart = Kp_right*Err;
  float dPart = Kd_right*(Err - right_pre_Err);
  float iPart = Ki_right*(Err + right_pre_Err);
  float PID_val = pPart + dPart + iPart;
  right_pre_Err = Err; //luu lai gia tri error
  right_pwm = (0.833*right_rpm - 13) + PID_val;
}

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

  pinMode(pinIR0,INPUT);
  pinMode(pinIR1,INPUT);
  pinMode(pinIR2,INPUT);
  pinMode(pinIR3,INPUT);
  pinMode(pinIR4,INPUT);
  pinMode(pinIR5,INPUT);
  pinMode(pinIR6,INPUT);

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

void read_sensor(){
  IRvalue[0] = analogRead(pinIR0);
  IRvalue[1] = analogRead(pinIR1);
  IRvalue[2] = analogRead(pinIR2);
  IRvalue[3] = analogRead(pinIR3);
  IRvalue[4] = analogRead(pinIR4);
  IRvalue[5] = analogRead(pinIR5);
  IRvalue[6] = analogRead(pinIR6);
}

float calc_line(){
  float y0 = a0*IRvalue[0] + b0;
  float y1 = a1*IRvalue[1] + b1;
  float y2 = a2*IRvalue[2] + b2;
  float y3 = a3*IRvalue[3] + b3;
  float y4 = a4*IRvalue[4] + b4;
  float y5 = a5*IRvalue[5] + b5;
  float y6 = a6*IRvalue[6] + b6;
  float sum = y0 + y1 + y2 + y3 + y4 + y5 + y6;
  float center = (-6*y0 + -4*y1 + -2*y2 + 0*y3 + 2*y4 + 4*y5 + 6*y6)/sum;
  Serial.println(center);
  return center;
}

void Line_PID(float Va_rel, unsigned long Va_pur  )
{
  float Err = Va_pur - Va_rel; //tinh error
  float pPart = Kp*Err;
  float dPart = Kd*(Err - pre_Err);
  float iPart = Ki*(Err + pre_Err);
  float PID_val = pPart + dPart + iPart;
  pre_Err = Err; //luu lai gia tri error
  left_rpm = set_rpm + PID_val;
  right_rpm = set_rpm - PID_val;
}

void loop() { 
  if(count == 10) {
    read_sensor();
    Line_PID(calc_line(),0);
    get_rpm();
    Motor_PID_Left(rpm2, left_rpm);
    Motor_PID_Right(rpm1, right_rpm);
    count = 0;    
  }
  analogWrite(motorIn1, left_pwm); // Send PWM signal to L298N In1 pin
  analogWrite(motorIn3, right_pwm); // Send PWM signal to L298N In3 pin
  count ++;

}
