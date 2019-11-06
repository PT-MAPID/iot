#include <SoftwareSerial.h>
//SoftwareSerial mySerial(8, 10);
SoftwareSerial mySerial(7, 8);
String c, latitude, longitude, altitud, timegps, speedknot, state, dir;
int d = 100;
#define trig_pin     2
#define echo_pin     3
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
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CGATT=1");
  Serial.println(mySerial.readString());
  delay(d);

  //commented

  //  mySerial.println("AT+CIPSHUT");
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //  mySerial.println("AT+CIPMUX=0");
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //commented

  mySerial.println("AT+CSTT=\"m2mdev\",\"wap\",\"wap123\"");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CIICR");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CIFSR");
  Serial.println(mySerial.readString());
  delay(d);

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
  Serial.println("");
  delay(d);


  //commented

  //  mySerial.println("AT+CIPSEND");
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //commented

  mySerial.println("AT+CIPSTATUS");           //query current connection status
  Serial.println(mySerial.readString());
  delay(d);

  //commented

  //  mySerial.println("AT+CIPMUX=0");            //start up multi-IP connection
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //  mySerial.println("AT+CSTT=\"internet\"");   //start task and setting the APN,
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //  mySerial.println("AT+CIICR");               //bring up wireless connection
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //commented

  mySerial.println("AT+CIFSR");               //get local IP adress
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+CIPSPRT=0");           //set prompt of '>' when modul sends data
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+SAPBR=3,1,\"APN\",\"\"");//setting the APN,2nd parameter empty works for all networks
  Serial.println(mySerial.readString());
  delay(d);

  //commented

  mySerial.println("AT+SAPBR=1,1");
  Serial.println(mySerial.readString());
  delay(d * 4);

  mySerial.println("AT+HTTPINIT"); //init the HTTP request
  Serial.println(mySerial.readString());
  delay(d * 3);

  String var1 = (String(latitude).length()>1) ? ("&var1=" + latitude) : "";
  String var2 = (String(longitude).length()>1) ? ("&var2=" + longitude) : "";
  String var3 = (String(altitud).length()>1) ? ("&var3=" + altitud) : "";
  String var4 = (String(speedknot).length()>1) ? ("&var4=" + speedknot) : "";
  String var5 = (String(dir).length()>1) ? ("&var5=" + dir) : "";
  
  //commented
  String str = "AT+HTTPPARA=\"URL\",\"api.mapid.io/api/update?key=PASTE_YOUR_WRITE_API_KEY"
               + var1
               + var2
               + var3
               + var4
               + var5
               + "\"";
  mySerial.println(str);// setting the httppara,
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+HTTPSSL=1");
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+HTTPACTION=0");//submit the GET request
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.println("AT+HTTPREAD=0,20");
  Serial.println(mySerial.readString());
  delay(d);

  //commented

  //  mySerial.println("AT+HTTPTERM");// terminate HTTP service
  //  Serial.println(mySerial.readString());
  //  delay(d);

  //commented

  mySerial.println("AT+CIPSHUT");             //close the connection
  Serial.println(mySerial.readString());
  delay(d);

  mySerial.flush();
  delay(d);
  //  mySerial.println("AT+CIPCLOSE");
  //  Serial.println(mySerial.readString());
  //  delay(d);
}
