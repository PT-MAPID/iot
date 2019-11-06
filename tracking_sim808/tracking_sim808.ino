#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 8);
String c, latitude, longitude, altitud, timegps, speedknot, state, dir;
int d = 100;
#define trig_pin     2   // pin TRIG to D1
#define echo_pin     3   // pin ECHO to D2
float duration;
float distance;
void setup()
{
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
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
void loop() {
  getDistance();
  sendingdata();
  delay(10);
}
void sendingdata()
{
  mySerial.println("AT");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CGATT=1");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPSHUT");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPMUX=0");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CSTT=\"m2mdev\",\"wap\",\"wap123\"");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIICR");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIFSR");
  delay(1000);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CGPSPWR=1");
  delay(d * 3);

  mySerial.println("AT+CGNSPWR=1");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CGNSSEQ=RMC");
  delay(d);

  Serial.println(mySerial.readString());
  Serial.println("GPS Initialising...");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CGPSSTATUS?");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CGNSINF");         //get the gps data
  c = mySerial.readString();              //save the paramater returned from AT command
  delay(d);

  //  Serial.println("State      :" + state);
  //  Serial.println("Time       :" + timegps);
  //  Serial.println("c      :" + c );

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

  //  Serial.println("state_1:" + String(state_1));
  //  Serial.println("state_2:" + String(state_2));
  //  Serial.println("time_1:" + String(time_1));
  //  Serial.println("time_2:" + String(time_2));
  //  Serial.println("lat_1:" + String(lat_1));
  //  Serial.println("lat_2:" + String(lat_2));
  //  Serial.println("lon_1:" + String(lon_1));
  //  Serial.println("lon_2:" + String(lon_2));
  //  Serial.println("alt_1:" + String(alt_1));
  //  Serial.println("alt_2:" + String(alt_2));
  //  Serial.println("speed_1:" + String(speed_1));
  //  Serial.println("speed_2:" + String(speed_2));
  //  Serial.println("dir_1:" + String(dir_1));
  //  Serial.println("dir_2:" + String(dir_2));

  state = c.substring(state_1, state_2);
  latitude = c.substring(lat_1, lat_2);
  longitude = c.substring(lon_1, lon_2);
  altitud = c.substring(alt_1, alt_2);
  speedknot = c.substring(speed_1, speed_2);
  dir = c.substring(dir_1, dir_2);

  Serial.println("Latitude    :" + latitude);
  Serial.println("Longitude   :" + longitude);
  Serial.println("altitud     :" + altitud);
  Serial.println("Speed       :" + speedknot + " km/hour");
  Serial.println("Direction   :" + dir + " degree");
  delay(d);


  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPSEND");
  delay(d);

  mySerial.println("AT+CIPSTATUS");           //query current connection status
  delay(d);

  mySerial.println("AT+CIPMUX=0");            //start up multi-IP connection
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CSTT=\"internet\"");   //start task and setting the APN,
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIICR");               //bring up wireless connection
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIFSR");               //get local IP adress
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPSPRT=0");           //set prompt of '>' when modul sends data
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"\"");//setting the APN,2nd parameter empty works for all networks
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println();
  mySerial.println("AT+SAPBR=1,1");
  delay(d * 4);

  Serial.println(mySerial.readString());
  mySerial.println("AT+HTTPINIT"); //init the HTTP request
  delay(d * 3);
  Serial.println(mySerial.readString());

  String str = "AT+HTTPPARA=\"URL\",\"api.mapid.io/api/update?key=ed10ba7f4b54ab98360592bff55a6fb3&var1=" + latitude
               + "&var2=" + longitude
               + "&var3=" + altitud
               + "&var4=" + speedknot
               + "&var5=" + dir
               + "\"";

  mySerial.println(str);// setting the httppara,
  //the second parameter is the website from where you want to access data
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+HTTPSSL=1");
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println();
  mySerial.println("AT+HTTPACTION=0");//submit the GET request
  delay(d);//the delay is important if the return datas are very large, the time required longer.

  Serial.println(mySerial.readString());
  mySerial.println("AT+HTTPREAD=0,20");// read the data from the website you access
  delay(d * 2);

  Serial.println(mySerial.readString());
  mySerial.println("");
  delay(d);

  mySerial.println("AT+HTTPTERM");// terminate HTTP service
  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPSHUT");             //close the connection
  delay(d);

  Serial.println(mySerial.readString());
  mySerial.println("AT+CIPCLOSE");
  delay(d);

  Serial.println(mySerial.readString());
  delay(d * 10);

  mySerial.flush();
  mySerial.println("AT+CIPCLOSE");
  delay(d);


}
