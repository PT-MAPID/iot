#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8);
String c, gps_status, longitude, altitud, timegps, speedknot, dir;
String latitude = "0";
String fix_status = "0";
int d = 50;
#define trig_pin     2
#define echo_pin     3
float duration;
float distance;
float jarak;
int voltage;
int panjang1;
String response1 = "OK";
void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop()
{
  Serial.println("Getting distance...");
  jarak = getDistance();
  Serial.println("Getting voltage...");
  Serial.println("");
  voltage = analogRead(A0);
  //  ema = EMA_function(ema_a, voltage, ema);
  if (fix_status == "1"  ) {
    Serial.println("No GPS anymore");
    sendingdata();
  } else {
    Serial.println("Not get position data, starting GPS");
    getGPS();
    sendingdata();
  }
  delay(240000);
  //  delay(10);
}
float  getDistance()
{
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration / 2) / 28.1;
  return distance;
}
//int EMA_function(float alpha, int latest, int stored){
//  return round(alpha*latest) + round((1-alpha)*stored);
//}
void sendingdata()
{

  mySerial.println("AT");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=2,1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=1,1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPProBR=2,1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+HTTPINIT");
  Serial.println(mySerial.readString());
  delay(d);

  String var1 = (latitude.length() < 9) ?  "" : ("&var1=" + latitude);
  String var2 = (longitude.length() < 10) ?  "" : ("&var2=" + longitude);
  String var3 = "&var3="  + String(jarak);
  String var4 = "&var4="  + String(voltage);
  String var5 = (fix_status == "0" || fix_status == "1") ? "&var5="  + String(fix_status) : "";

  //commented
  String str = "AT+HTTPPARA=\"URL\",\"http://api.mapid.io/api/update?key=7f91e6375d97477eb31a8d20d8bc4395"
               + var1
               + var2
               + var3
               + var4
               + var5
               + "\"";

  mySerial.println(str);
  String respo = mySerial.readString();
  panjang1 = respo.length();
  response1 = respo.substring(panjang1 - 4, panjang1 - 2);
  Serial.println(respo);
  delay(d);

  mySerial.println("AT+HTTPPARA=\"CID\",1");
  Serial.println(mySerial.readString());
  delay(d);

  //  mySerial.println("AT+HTTPSSL=1");
  //  Serial.println(mySerial.readString());
  //  delay(d);

  mySerial.println("AT+HTTPACTION=0");
  Serial.println(mySerial.readString());
  delay(d);



  //  mySerial.println("AT");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CGATT=1");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIPMUX=0");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CSTT=\"internet\",\"wap\",\"wap123\"");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIICR");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIFSR");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIPSTATUS");           //query current connection status
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIFSR");               //get local IP adress
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+CIPSPRT=0");           //set prompt of '>' when modul sends data
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+SAPBR=1,1");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+SAPProBR=2,1");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+HTTPINIT"); //init the HTTP request
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+HTTPPARA=\"CID\",1");
  //  delay(d);
  //
  //  String var1 = (latitude.length() < 9) ?  "" : ("&var1=" + latitude);
  //  String var2 = (longitude.length() < 10) ?  "" : ("&var2=" + longitude);
  //  String var3 = "&var3="  + String(distance);
  //  String var4 = "&var4="  + String(voltage);
  //  String var5 = (fix_status == "0" || fix_status == "1") ? "&var5="  + String(fix_status) : "";
  //
  //  //commented
  //  String str = "AT+HTTPPARA=\"URL\",\"api.mapid.io/api/update?key=15641a22924fbf2dfda970d657ba645b"
  //               + var1
  //               + var2
  //               + var3
  //               + var4
  //               + var5
  //               + "\"";
  //  mySerial.println(str);
  //  String respo = mySerial.readString();
  //  panjang1 = respo.length();
  //  response1 = respo.substring(panjang1 - 4, panjang1 - 2);
  //  Serial.println(respo);
  //  delay(d);
  //
  //  mySerial.println("AT+HTTPSSL=1");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  //
  //  mySerial.println("AT+HTTPACTION=0");
  //  Serial.println(mySerial.readString());
  //
  //  //  response2 = mySerial.readString().substring(18, 20);
  //  //  Serial.println("response2=" + response2);
  //  delay(d);
  //
  //  mySerial.println("AT+HTTPREAD=0,20");
  //  Serial.println(mySerial.readString());
  //  delay(d);
  ////
  ////  mySerial.println("AT+CIPSHUT");             //close the connection
  ////  Serial.println(mySerial.readString());
  ////  delay(d);
  ////
  ////  mySerial.flush();
  ////  delay(d);
  //  //  mySerial.println("AT+CIPCLOSE");
  //  //  Serial.println(mySerial.readString());
  //  //  delay(d);

  Serial.println("Cek variabel");
  Serial.println("response1=" + response1);
  Serial.println("");

  while (response1 != "OK") {
    Serial.println("Ada yang gagal kirim");
    sendingdata();
  }
  Serial.println("Pengiriman selesai");
  Serial.println("");
  mySerial.println("AT+HTTPTERM");
  Serial.println(mySerial.readString());
  delay(d);
  Serial.println("");
}
void getGPS ()
{
  mySerial.println("AT+CGPSPWR=1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CGNSPWR=1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CGNSSEQ=RMC");
  Serial.println(mySerial.readString());
  delay(d);

  Serial.println("GPS Initialising...");
  Serial.println("");
  delay(d);

  mySerial.println("AT+CGPSSTATUS?");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CGNSINF");         //get the gps data
  c = mySerial.readString();              //save the paramater returned from AT command
  delay(d);

  int state_1 = c.indexOf(",", 0) + 1;
  int state_2 = c.indexOf(",", state_1 + 1);
  int time_1 = c.indexOf(",", state_2) + 1;
  int time_2 = c.indexOf(",", time_1 + 1);
  int lat_1 = c.indexOf(",", time_2) + 1;
  int lat_2 = c.indexOf(",", lat_1 + 1);
  int lon_1 = c.indexOf(",", lat_2) + 1;
  int lon_2 = c.indexOf(",", lon_1 + 1);
  int alt_1 = c.indexOf(",", lon_2) + 1;
  int alt_2 = c.indexOf(",", alt_1 + 1);
  int speed_1 = c.indexOf(",", alt_2) + 1;
  int speed_2 = c.indexOf(",", speed_1 + 1);
  int dir_1 = c.indexOf(",", speed_2) + 1;
  int dir_2 = c.indexOf(",", dir_1 + 1);
  gps_status = c.substring(state_1 - 2, state_2 - 2);
  fix_status = c.substring(state_1, state_2);
  latitude = c.substring(lat_1, lat_2);
  longitude = c.substring(lon_1, lon_2);
  altitud = c.substring(alt_1, alt_2);
  speedknot = c.substring(speed_1, speed_2);
  dir = c.substring(dir_1, dir_2);

  Serial.println("gps_status    :" + gps_status);
  Serial.println("fix_status    :" + fix_status);
  Serial.println("Latitude    :" + String(latitude.length()));
  Serial.println("Longitude   :" + String(longitude.length()));
  Serial.println("Distance     :" + String(getDistance()));
  Serial.println("");
  delay(d);
}
