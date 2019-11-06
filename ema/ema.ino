int sensor_pin = A0;
int EMA_function(float alpha, int latest, int stored);                           //Fungsi filter Exponential Moving Average
float konstanta_ema = 0.5;                                                         //Konstanta EMA
float celciusFiltered = 27.8;                                                    //Asumsi temperatur awal
void setup() {
  Serial.begin(9600);
}
void loop() {
  int sensor_value = analogRead(sensor_pin);                                     //Pembacaan ADC dari sensor
  float mVraw = sensor_value * 3300 / 1023;                                      //Konversi dari ADC ke miliVolt
  float celciusRaw = mVraw / 10;                                                 //Konversi dari miliVolt ke Celcius
  celciusFiltered = EMA_function(konstanta_ema, celciusRaw, celciusFiltered);    //Pemanggilan fungsi Exponential Moving Average

  Serial.print("raw:");
  Serial.print("\t");
  Serial.println("filtered:");
  delay(1);                                                                       //Delay waktu untuk kestabilan pembacaan

  Serial.print(celciusRaw);
  Serial.print("\t");
  Serial.println(celciusFiltered);
  delay(2000);                                                                       //Delay waktu untuk kestabilan pembacaan
}
int EMA_function(float alpha, int latest, int stored) {
  return round(alpha * latest) + round((1 - alpha) * stored);
}
