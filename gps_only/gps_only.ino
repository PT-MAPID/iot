#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8); //tx rx
String data[7], latitude, longitude, altitud, timegps, speedknot, c, state, com;
int d = 1700;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop()
{
  getPosition();
  delay(1000);
}
void getPosition()
{
  Serial.println("GPS Initialising...");
  mySerial.println("AT");
  ShowSerialData();
  delay(d);

  mySerial.println(" AT+CGPSPWR=1");
  ShowSerialData();
  delay(d * 3);

  mySerial.println("AT+CGNSPWR=1");
  ShowSerialData();
  delay(d);

  mySerial.println("AT+CGNSSEQ=RMC");
  ShowSerialData();
  delay(d);

  mySerial.println("AT+CGPSSTATUS?");
  ShowSerialData();
  delay(d);

  mySerial.println("AT+CGNSINF");
  ShowSerialData();
  delay(d);

  if (mySerial.available() > 0)
  {
    while (mySerial.available() > 0)
    {
      c = (mySerial.readString());
      delay(d * 3);
      c.remove(100);
    }
  }
  Serial.println(c);
  delay(d);

  state = c.substring(25, 26);
  timegps = c.substring(27, 41);
  latitude = c.substring(46, 55);
  longitude = c.substring(56, 66);
  altitud = c.substring(67, 74);
  speedknot = c.substring(75, 79);

  Serial.println("State      :" + state);
  Serial.println("Time       :" + timegps);
  Serial.println("Latitude   :" + latitude);
  Serial.println("Longitude  :" + longitude);
  Serial.println("altitud   :" + altitud);
  Serial.println("Speed      :" + speedknot + " knot");
  Serial.println(" ");
  delay(d);
}

void ShowSerialData()
{
  while (mySerial.available() != 0)
    Serial.write(mySerial.read());
}
