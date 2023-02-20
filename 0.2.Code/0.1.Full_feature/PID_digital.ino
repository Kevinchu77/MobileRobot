int motorIn1 = 5;
int motorIn2 = 4;
int motorIn3 = 6;
int motorIn4 = 7;
int motorEn = 1;
int encoder1 = 2;
int encoder2 = 3;

const int trig = 9;     // chân trig của HC-SR04
const int echo = 8;     // chân echo của HC-SR04

const int pinIR0 = A0;
const int pinIR1 = A1;
const int pinIR2 = A2;
const int pinIR3 = A3;
const int pinIR4 = A4;
const int pinIR5 = A5;
const int pinIR6 = A6;
int IRvalue[7];
float Kp = 20;
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
float Kp_left = 0.1;
float Ki_left = 0;
float Kd_left = 0;

float right_pre_Err;
float Kp_right = 0.1;
float Ki_right = 0;
float Kd_right = 0;

unsigned int Ts; // Sampling time
static uint32_t pre_mil;

bool pass = false;

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

  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu

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
  IRvalue[0] = digitalRead(pinIR0);
  IRvalue[1] = digitalRead(pinIR1);
  IRvalue[2] = digitalRead(pinIR2);
  IRvalue[3] = digitalRead(pinIR3);
  IRvalue[4] = digitalRead(pinIR4);
  IRvalue[5] = digitalRead(pinIR5);
  IRvalue[6] = digitalRead(pinIR6);
}

float calc_line(){
  float sum = IRvalue[1] + IRvalue[2] + IRvalue[3] + IRvalue[4] + IRvalue[5];
  Serial.println(sum);
  if (sum != 0) {
    return (-2*IRvalue[1] + -1*IRvalue[2] + 0*IRvalue[3] + 1*IRvalue[4] + 2*IRvalue[5])/sum;
  }
}

void Line_PID(float Err)
{
  float pPart = Kp*Err;
  float dPart = Kd*(Err - pre_Err);
  float iPart = Ki*(Err + pre_Err);
  float PID_val = pPart + dPart + iPart;
  pre_Err = Err; 
  left_rpm = set_rpm + PID_val;
  right_rpm = set_rpm - PID_val;
}

int sonar(){
    unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    return distance;
}

void avoiding(){
  analogWrite(motorIn1, 200); 
  analogWrite(motorIn3, 120);
  delay(550);
  analogWrite(motorIn1, 120); 
  analogWrite(motorIn3, 200);
  delay(1000);
  analogWrite(motorIn1, 200); 
  analogWrite(motorIn3, 120);
  delay(600);
//  analogWrite(motorIn1, 150); 
//  analogWrite(motorIn3, 150);
//  delay(1500);
//  analogWrite(motorIn1, 150); 
//  analogWrite(motorIn3, 180);
//  delay(800);
  pass = true;
}

void loop() { 
  read_sensor();
  if (pass == false){
    if (sonar() < 35){
      avoiding();
    }
  }
  float x = calc_line();
  if (x == 0){
    if (IRvalue[2] == 1 && IRvalue[4] == 1){
      Line_PID(-3);
    }
  }
  else{
    Line_PID(x);
  }
  get_rpm();
  Motor_PID_Left(rpm2, left_rpm);
  Motor_PID_Right(rpm1, right_rpm);

 
  if (IRvalue[1] == 0 && IRvalue[2] == 0 && IRvalue[3] == 0 && IRvalue[4] == 0 && IRvalue[5] == 0){
     left_pwm = 0;
     right_pwm = 0;
  }
  analogWrite(motorIn1, left_pwm); 
  analogWrite(motorIn3, right_pwm); 
}
