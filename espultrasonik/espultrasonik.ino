#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#ifndef STASSID
#define STASSID "Fave"
#define STAPSK  "personalized"
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "api.mapid.io";
const int httpsPort = 443;
//Satu
float latSatu = -0.6680;
float lonSatu = 100.8255;
//int satuLatSementara = 0;
//int satuLonSementara = 0;
//int satuValSementara = 0;
//Dua
float latDua = -0.6785;
float lonDua = 100.8354;
//Tiga
//float latTiga = -0.6684;
//float lonTiga = 100.7984;
float latTiga = -0.6684;
float lonTiga = 100.8052;
//Empat
float latEmpat = -0.6715;
float lonEmpat = 100.8118;
//Lima
float latLima = -0.6826;
float lonLima = 100.7999;
//Enam
float latEnam = -0.6746;
float lonEnam = 100.8205;
//Val
int val = 25;
int randomNumber = 40;
bool ngelewatSatu = false;
bool ngelewatDua = false;
bool ngelewatTiga = false;
bool ngelewatEmpat = false;
bool ngelewatLima = false;
bool ngelewatEnam = false;
const char fingerprint[] PROGMEM = "7E D3 F6 37 E0 6E 7E EF 99 FF 0F 9A 4F 91 CA A5 F1 6F 6D 1E";
WiFiClientSecure client;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
//  //Satu
//  if (ngelewatSatu == false) {
//    lonSatu = lonSatu + 0.0002;
//    latSatu = latSatu - 0.0010;
//  } else {
//    lonSatu = lonSatu - 0.0002;
//    latSatu = latSatu + 0.0010;
//  }
//  //Dua
//  if (ngelewatDua == false) {
//    lonDua = lonDua + 0.0002;
//    latDua = latDua - 0.0010;
//  } else {
//    lonDua = lonDua - 0.0002;
//    latDua = latDua + 0.0010;
//  }
//  //Tiga
//  if (ngelewatTiga == false) {
//    lonTiga = lonTiga + 0.0004;
//  } else {
//    lonTiga = lonTiga - 0.0004;
//  }
//  //Empat
//  if (ngelewatEmpat == false) {
//    lonEmpat = lonEmpat - 0.0004;
//  } else {
//    lonEmpat = lonEmpat + 0.0004;
//  }
//  //Lima
//  if (ngelewatLima == false) {
//    lonLima = lonLima + 0.0007;
//    latLima = latLima + 0.0002;
//  } else {
//    lonLima = lonLima - 0.0007;
//    latLima = latLima - 0.0002;
//  }
//  //Enam
//  if (ngelewatEnam == false) {
//    lonEnam = lonEnam - 0.0007;
//    latEnam = latEnam + 0.0001;
//  } else {
//    lonEnam = lonEnam + 0.0007;
//    latEnam = latEnam - 0.0001;
//  }

  //Tiga
  val=random(20,29);
  if (ngelewatTiga == false) {
    lonTiga = lonTiga - 0.0002;
    latTiga = latTiga + 0.00015;
  } else {
    lonTiga = lonTiga + 0.0002;
    latTiga = latTiga - 0.00015;
  }
  //  satuLatSementara = random(0, 100);
  //  satuLonSementara = random(0, 100);
  //  satuValSementara = random(0, 100);

  Serial.print("connecting to ");
  Serial.println(host);
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  //  String url1 = "/api/update?key=1e072ecad425f6e37d28285f2632ca59&var1=" + String(satuLatSementara, 6) + "&var2=" + String(satuLonSementara, 6) + "&var3=" + String(satuValSementara);
  String url1 = "/api/update?key=1e072ecad425f6e37d28285f2632ca59&var1=" + String(latSatu, 6) + "&var2=" + String(lonSatu, 6) + "&var3=" + String(val);
  String url2 = "/api/update?key=743f6a30834fc7272669677f2414a35f&var1=" + String(latDua, 6) + "&var2=" + String(lonDua, 6) + "&var3=" + String(val);
  String url3 = "/api/geofencing?key=e3efac2a1e8ba4bec77ad5595ecf93b1&var1=" + String(latTiga, 6) + "&var2=" + String(lonTiga, 6) + "&var3=" + String(val);
  String url4 = "/api/update?key=c446dacf358e352a31f4b6069dbf30af&var1=" + String(latEmpat, 6) + "&var2=" + String(lonEmpat, 6) + "&var3=" + String(val);
  String url5 = "/api/update?key=9d4ed4b6ee6a4372c0b9f4428822b487&var1=" + String(latLima, 6) + "&var2=" + String(lonLima, 6) + "&var3=" + String(val);
  String url6 = "/api/update?key=e35ca302e3eb8c79f346c4e672bc6b89&var1=" + String(latEnam, 6) + "&var2=" + String(lonEnam, 6) + "&var3=" + String(val);
//  delay(700);
//  client.print(String("GET ") + url1 + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
//  client.print(String("GET ") + url2 + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
  client.print(String("GET ") + url3 + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
//  client.print(String("GET ") + url4 + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
//  client.print(String("GET ") + url5 + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
//  client.print(String("GET ") + url6 + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "User-Agent: BuildFailureDetectorESP8266\r\n" +
//               "Connection: Keep-Alive\r\n\r\n");
//  delay(700);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  Serial.println("request sent");
//  //Satu
//  if (latSatu < -0.6742 ) {
//    ngelewatSatu = true;
//  } else if (latSatu >= -0.6680 )
//  {
//    ngelewatSatu = false;
//  }
//  //Dua
//  if (latDua < -0.6832 ) {
//    ngelewatDua = true;
//  } else if (latDua >= -0.6785 )
//  {
//    ngelewatDua = false;
//  }
//  //Tiga
//  if (lonTiga > 100.8105 ) {
//    ngelewatTiga = true;
//  } else if (lonTiga <= 100.7984 )
//  {
//    ngelewatTiga = false;
//  }
//  //Empat
//  if (lonEmpat < 100.7998 ) {
//    ngelewatEmpat = true;
//  } else if (lonEmpat >= 100.8118 )
//  {
//    ngelewatEmpat = false;
//  }
//  //Lima
//  if (lonLima > 100.8183 ) {
//    ngelewatLima = true;
//  } else if (lonLima <= 100.7999 )
//  {
//    ngelewatLima = false;
//  }
//  //Enam
//  if (lonEnam < 100.8063 ) {
//    ngelewatEnam = true;
//  } else if (lonEnam >= 100.8205 )
//  {
//    ngelewatEnam = false;
//  }
  if (lonTiga < 100.7987 ) {
    ngelewatTiga = true;
  } else if (lonTiga >= 100.8052 )
  {
    ngelewatTiga = false;
  }
  delay(1000);
}
