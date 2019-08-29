#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

#ifndef STASSID
#define STASSID "HOME SWEET HOME"
#define STAPSK  "rairaka123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

#define DHTPIN D8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* host = "api.mapid.io";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char fingerprint[] PROGMEM = "7E D3 F6 37 E0 6E 7E EF 99 FF 0F 9A 4F 91 CA A5 F1 6F 6D 1E";
// Use WiFiClientSecure class to create TLS connection
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
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

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/update?key=4f1467da62d42d0446bc890a7b79e88b&var1=" + String(t, 6) + "&var2=" + String(h, 6);
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
  delay(100000);
}
