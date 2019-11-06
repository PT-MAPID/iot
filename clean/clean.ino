#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8);
float temp = 27.8;
float latitude = -7.0599;
float longitude = 109.4259;
int d = 500;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() {
  sendingdata();
  delay(10);
}
void sendingdata()
{
  mySerial.println("AT");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"\"");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=1,1");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+SAPBR=2,1");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPINIT");
  ShowSerialData();
  delay(d);
  mySerial.println("AT+HTTPPARA=\"CID\",1");
  ShowSerialData();
  delay(d);
  String str = "AT+HTTPPARA=\"URL\",\"api.mapid.io/api/update?key=PASTE_YOUR_WRITE_API_KEY&var1=" + String(latitude)
               + "&var2=" + String(longitude)
               + "&var3=" + String(temp) + "\"";
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
