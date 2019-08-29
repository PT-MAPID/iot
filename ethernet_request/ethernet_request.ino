#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize Ethernet library
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to configure Ethernet"));
    return;
  }
  delay(1000);

  Serial.println(F("Connecting..."));
}
void loop() {
  // Connect to HTTP server
  EthernetClient client;
  client.setTimeout(10000);
  if (!client.connect("api.mapid.io", 80)) {
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(F("Connected!"));
  // Send HTTP request
  client.println("GET /api/request?key=PASTE_YOUR_API_KEY_HERE HTTP/1.0");
  client.println("Host: api.mapid.io");
  client.println(F("Connection: close"));
  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    return;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  // Allocate the JSON document
  // Use arduinojson.org/v6/assistant to compute the capacity.
  const size_t capacity = 3*JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(9);
  DynamicJsonDocument doc(capacity);

  // Parse JSON object
  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  // Extract values
    Serial.println("====================");
    Serial.println("GET DATA FROM SERVER !");
    Serial.println("====================");
    //Serial.println(F("RESPONSE : "));
    Serial.print("ID       : ");
    Serial.println(doc["_id"].as<char*>());
    Serial.print("NAMA     : ");
    Serial.println(doc["name"].as<String>());
    Serial.print("USERNAME : ");
    Serial.println(doc["username"].as<String>());
    //Serial.println(doc["last_data"]["var1"]["name"].as<String>());
  // Disconnect
  client.stop();
}
