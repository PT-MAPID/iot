#include <ESP8266WiFi.h>                                //Memuat library untuk menggunakan chip ESP
#include <WiFiClientSecure.h>                           //Memuat library untuk menggunakan WiFi dengan koneksi secure

#ifndef STASSID
#define STASSID "ISI_SSID_WIFI_DI_SINI"                 //<-- Masukkan SSID WiFi kamu di sini
#define STAPSK  "ISI_PASSWORD_WIFI_DI_SINI"             //<-- Masukkan Password WiFi kamu di sini
#endif
String apiKey = "PASTE_API_KEY_DI_SINI";                //<-- Paste POST API KEY kamu di sini!, Inget ya, yang POST yaaa

const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "api.mapid.io";
const int httpsPort = 443;
const char fingerprint[] PROGMEM = "7E D3 F6 37 E0 6E 7E EF 99 FF 0F 9A 4F 91 CA A5 F1 6F 6D 1E";
WiFiClientSecure client;

double lat = -6.886914;                                 //Data dummy untuk latitude
double lon = 107.615298;                                //Data dummy untuk longitude
int sensor_pin = A0;                                    //Deklarasi pin input tempat masuk sensor temperatur
int EMA_function(float alpha, int latest, int stored);  //Fungsi filter Exponential Moving Average
float konstanta_ema = 0.7;                              //Konstanta EMA, coba di angka 0.5 atau 0.25
float celciusFiltered = 20;                             //Asumsi temperatur awal (Celcius)

void setup() {
  Serial.begin(9600);
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
  //Tahap 1; Pembacaan sensor
  int sensor_value = analogRead(sensor_pin);                                      //Pembacaan ADC dari sensor
  float mVraw = sensor_value * 3300 / 1023;                                       //Konversi dari ADC ke miliVolt
  float celciusRaw = (mVraw / 10) * 0.75;                                                //Konversi dari miliVolt ke Celcius
  celciusFiltered = EMA_function(konstanta_ema, celciusRaw, celciusFiltered);     //Pemanggilan fungsi Exponential Moving Average
  Serial.print("raw:");
  Serial.print("\t");
  Serial.println("filtered:");
  Serial.print(celciusRaw);
  Serial.print("\t");
  Serial.println(celciusFiltered);

  //Tahap 2; Pengiriman data
  Serial.print("connecting to ");
  Serial.println(host);
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  client.setFingerprint(fingerprint);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  String url = "/api/update?key=" + apiKey + "&var1=" + String(lat, 6) + "&var2=" + String(lon, 6) + "&var3=" + String(celciusFiltered, 2);
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
int EMA_function(float alpha, int latest, int stored) {
  return round(alpha * latest) + round((1 - alpha) * stored);
}
