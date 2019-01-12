// LED strobe project by Vortecks
// Connect the MOSFET gate to P0 on Digispark

const byte outPin = 0;

void setup() {
  pinMode(outPin, OUTPUT);
  digitalWrite(outPin, LOW);
  delay(2000);
}

void loop() 
{
  for (int i = 0; i < 2; i++)
  {
      digitalWrite(outPin, HIGH);
      delay(10);
      digitalWrite(outPin, LOW);
      delay(100);
  }

  delay(2500);

}
