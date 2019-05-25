#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#ifndef STASSID
#define STASSID "PT. MAPID"
#define STAPSK  "mapid.io"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "api.mapid.io";
const int httpsPort = 443;

double lat = -7;
double lon = 169.88;

float duration;
float distance;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "7E D3 F6 37 E0 6E 7E EF 99 FF 0F 9A 4F 91 CA A5 F1 6F 6D 1E";
// Use WiFiClientSecure class to create TLS connection
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
  pinMode(A0, INPUT);
}


void loop() {

  int val = analogRead(0);
  val = map(val, 0, 1023, 0, 100);
  Serial.println(val);


  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/update?key=1d7dea814daf44f1736def63e35a4741&var1=" + String(lat, 6) + "&var2=" + String(lon, 6) + "&var3=" + String(val);
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  delay(2000);
}
