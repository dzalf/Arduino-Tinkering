void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(100);
  // put your main code here, to run repeatedly:
  Serial.print("Hola esto es una prueba");
  Serial.print("\n");
  
  digitalWrite(13, LOW);
  delay(250);
}
