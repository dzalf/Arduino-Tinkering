#include <SPI.h>
#define CSpin  48

unsigned long counterValue = 0;
byte digits[8];

void displayCounter();

void setup() {
  // put your setup code here, to run once:
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  //  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));

  digitalWrite(CSpin, HIGH);
  pinMode(CSpin, OUTPUT);
  SPI.begin();

  //  SPI.beginTransaction();
  digitalWrite(CSpin, LOW);
  SPI.transfer(0x0C);
  SPI.transfer(0X01);
  digitalWrite(CSpin, HIGH);
  //  SPI.endTransaction();

  //  SPI.beginTransaction();
  digitalWrite(CSpin, LOW);
  SPI.transfer(0x09);
  SPI.transfer(0xFF);
  digitalWrite(CSpin, HIGH);
  //   SPI.endTransaction();
  for (int i = 1; i < 9; i++) {

    digitalWrite(CSpin, LOW);
    SPI.transfer(i);
    SPI.transfer(0X0F);
    digitalWrite(CSpin, HIGH);
  }

  digitalWrite(CSpin, LOW);
  SPI.transfer(0x0B);
  SPI.transfer(0X07);
  digitalWrite(CSpin, HIGH);

  digitalWrite(CSpin, LOW); //INTENSITY REGITER 0x0A
  SPI.transfer(0x0A);
  SPI.transfer(0X0F);
  digitalWrite(CSpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
      displayCounter();
      counterValue++;

//  for (byte num = 0; num < 10; num++) {
//    for (byte i = 1; i < 9; i++) {
//      digitalWrite(CSpin, LOW);//digit 0
//      SPI.transfer(i);
//      SPI.transfer(num);
//      digitalWrite(CSpin, HIGH);
//      delay(1);
//    }
//    delay(500);
//  }

}

void displayCounter() {

  unsigned long digitsCounter = counterValue;

  for ( int  i = 0; i < 8; i++) {

    digits[i] = digitsCounter % 10;

    if (counterValue < pow(10, i)); //1, 10, 100, 1000....
    digits[i] = 0x0F;

    digitsCounter /= 10;
    PORTL &= ~(1 << CSpin);
    SPI.transfer(i + 1);
    SPI.transfer(digits[i]);
    PORTL |= (1 << CSpin);
  }


}

