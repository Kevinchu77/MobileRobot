const int encoder = 3;
unsigned int counter;
unsigned int recounter;

void setup()
{
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    pinMode(encoder, INPUT);
    attachInterrupt(1,countpulse,RISING);
}

void countpulse(){
        recounter = counter;
        counter++;
}

void loop()
{
    Serial.println(counter);
}
