void setup()
{
Serial.begin(115200);
// Instrução para colocar o gpio que iremos utilizar como entrada,
// podemos fazer a leitura nesse pino
pinMode(A0, INPUT); 
// A0 é uma constante que indica o pino que ligamos nosso potenciômetro
// Instrução para colocar o gpio que iremos utilizar como saída,
// podemos alterar seu valor livremente para HIGH ou LOW

// LED_BUILTIN é uma constante que indica o LED do ESP8266
}

void loop()
{


  int val = analogRead(0);
  val = map(val, 0, 1023, 0, 100);
Serial.println(val);

}
