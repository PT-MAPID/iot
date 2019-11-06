#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); //tx rx
#define trig_pin     2
#define echo_pin     3
// defines variables
float duration;
float distance;
float value;
float latitude = -7.0599;
float longitude = 109.4259;
float voltage;
int d = 500;
void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop()
{
  voltage = analogRead(A0);
  value = getDistance();
  sendingdata();
  delay(1000);
  Serial.println(voltage);
}
float  getDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration / 2) / 28.1;
  return distance;
}
void sendingdata()
{
  mySerial.println("AT");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"Telkomsel\"");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=1,1");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPProBR=2,1");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPINIT");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPPARA=\"CID\",1");
  ShowSerialData();
  delay(d);
  ShowSerialData();
  String str = "AT+HTTPPARA=\"URL\",\"api.mapid.io/api/update?key=fa6565c7243a3550e9f06026d9ced813&var1=" + String(latitude)
               + "&var2=" + String(longitude) 
               + "&var3=" + String(value)
//               + "&var4=" + String(voltage)
               + "\"";
  mySerial.println(str);
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPSSL=1");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPACTION=0");
  ShowSerialData();
  delay(d);
}
void ShowSerialData()
{
  while (mySerial.available() != 0)
    Serial.write(mySerial.read());
}
