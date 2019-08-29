#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* wifiname = "WiFi SSID"       //Ganti "WiFi SSID" dengan nama SSID WiFi kamu
const char* wifipass = "WiFi Password"   //Ganti "WiFi Password" dengan password WiFi kamu

const char* host = "https://api.mapid.io/api/request?key=PASTE_YOUR_API_KEY_HERE";

int ledpin1 = 4;
int ledpin2 = 5;
void setup() {
  pinMode(ledpin1, OUTPUT);    // LED pin as output.
  pinMode(ledpin2, OUTPUT);    // LED pin as output.
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifiname);
  WiFi.begin(wifiname,wifipass);

  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  HTTPClient http;
  String fp = "7E:D3:F6:37:E0:6E:7E:EF:99:FF:0F:9A:4F:91:CA:A5:F1:6F:6D:1E";
  http.begin(host,fp);
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.print("Returned data from server: ");
  Serial.println(payload);
  delay(10);

  if(httpCode == 200)
  {
    StaticJsonDocument<512> doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err){
      Serial.print("Error : ");
      Serial.println(err.c_str());
      delay(10);
      return;
    }
    Serial.println("====================");
    Serial.println("Get data from server");
    Serial.println("====================");
    Serial.println("RESPONSE");
    Serial.print("_id    : ");
    Serial.println(doc["_id"].as<char*>());
    Serial.print("Nama   : ");
    Serial.println(doc["name"].as<String>());
    Serial.print("Data_1 : ");
    Serial.println(doc["last_data"]["var1"]["values"][0].as<float>());
    float data1 = doc ["last_data"]["var1"]["values"][0];
    if (data1 == 1){
      digitalWrite(ledpin2, HIGH);
      delay(10);
      digitalWrite(ledpin1, LOW);
      delay(10);
      Serial.println("LED Menyala");
    }
    if (data1 == 0) {
        digitalWrite(ledpin2, LOW); // turn the LED on.
        delay(10); // wait for 1 second.
        digitalWrite(ledpin1, HIGH); // turn the LED on.
        delay(10); // wait for 1 second.
        Serial.println("LED Padam");
      }
  }
  Serial.println();
  http.end();
  delay(10);
}
