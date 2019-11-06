void setup() {
  Serial.begin(9600);
}
void loop() {
  int val = analogRead(A0);
  float temp_celsius = val * 330.0 / 1023.0;
  Serial.println(val);
  delay(1);
}
