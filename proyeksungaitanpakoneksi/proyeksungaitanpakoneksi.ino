//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(7, 8);
//float latitude = -7.0599;
//float longitude = 109.4259;
//int d = 500;

//#define trig_pin     3   // pin TRIG to D1
//#define echo_pin     2   // pin ECHO to D2

#define trig_pin     5   // pin TRIG to D1
#define echo_pin     4   // pin ECHO to D2

// defines variables
float duration;
float distance;
float next;
float value;
float ema = 0.2;

void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
//  mySerial.begin(9600);
}

float  getDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  //  distance = (duration / 2) / 29.1;
  distance = (duration / 2) / 28.1;
  return distance;
}

void loop() {
  next = getDistance();
//  value = (ema * next) + ((1 - ema) * value);
  Serial.print("Distance: ");
  Serial.print(next, 0);
  Serial.println(" cm");
//  sendingdata();
  delay(1000);
}
