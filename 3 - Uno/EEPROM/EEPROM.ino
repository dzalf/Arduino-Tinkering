#include <EEPROM.h>
int zz;
int EEsize = 1024; // size in bytes of your board's EEPROM
 
void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
}
void loop()
{
  Serial.println("Writing random numbers...");
  for (int i = 0; i < EEsize; i++)
  {
    zz=random(255);
    EEPROM.write(i, zz);
  }
  Serial.println();
  for (int a=0; a<EEsize; a++)
  {
    zz = EEPROM.read(a);
    Serial.print("EEPROM position: ");
    Serial.print(a);
    Serial.print(" contains ");
    Serial.println(zz);
    delay(25);
  }
}
