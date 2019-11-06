#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() // run over and over
{
 Serial.println("Coba");
 delay(1000);
}
