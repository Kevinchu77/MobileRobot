const int pinIR0 = A0;
const int pinIR1 = A1;
const int pinIR2 = A2;
const int pinIR3 = A3;
const int pinIR4 = A4;
const int pinIR5 = A5;
const int pinIR6 = A6;

int IRvalue[7];
int max_value[7] = {139,272,341,202,457,220,553};
int min_value[7] = {32,35,36,31,32,32,36};
int sum_max = 0;
float avg_max = 0;
int sum_min = 0;
float avg_min = 0;
float slope[7];
float inter[7];

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
  


    for (int v=0; v<=6; v++){
      sum_max += max_value[v];
    }
    avg_max = sum_max/7;

    for (int u=0; u<=6; u++){
      sum_min += min_value[u];
    }
    avg_min = sum_min/7;

    Serial.print(avg_max);
    Serial.print("_");
    Serial.println(avg_min);
    
    for (int k=0; k <=6; k++){
      slope[k]=(avg_max-avg_min)/(max_value[k]-min_value[k]);
      Serial.print("y= ");
      Serial.print(slope[k]);
      Serial.print("*(x - ");
      Serial.print(min_value[k]);
      Serial.print(") + ");
      Serial.println(avg_min);
    }
    Serial.println(" ");

    sum_max = 0;
    sum_min = 0;
  
//  Serial.print(IRvalue[0]);
//  Serial.print("-");
//  Serial.print(IRvalue[1]);
//  Serial.print("-");
//  Serial.print(IRvalue[2]);
//  Serial.print("-");
//  Serial.print(IRvalue[3]);
//  Serial.print("-");
//  Serial.print(IRvalue[4]);
//  Serial.print("-");
//  Serial.print(IRvalue[5]);
//  Serial.print("-");
//  Serial.println(IRvalue[6]);
  delay(1000);
}

//  Serial.print("Analog Reading=");
//  Serial.println(IRvalue[6]);
//  Serial.print(", ");
//  Serial.println(IRvalueB);
