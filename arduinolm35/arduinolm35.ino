void setup() {
  Serial.begin(9600);
}
void loop() {
  int val = analogRead(A0);
  float temp = val * 0.48828125;
  Serial.println(val);
  delay(1);
}
