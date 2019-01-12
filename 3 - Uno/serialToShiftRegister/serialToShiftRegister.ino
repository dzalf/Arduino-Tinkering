

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
byte  MUX[11] = {B11111111,
                 B00000001,
                 B00000010,
                 B00000011,
                 B00000100,
                 B00000101,
                 B00000110,
                 B00000111,
                 B00001000,
                 B00001001,
                 B00001011,
                };
char serialIn;
byte data;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(57600);
  while (!Serial) {
    ;
  }
  writeData(MUX[0]);
}

void loop() {
  if (Serial.available() > 0) {

    serialIn = Serial.read();

    switch (serialIn) {

      case '1':
        data = MUX[1];
        break;
      case '2':
        data = MUX[2];
        break;
      case '3':
        data = MUX[3];
        break;
      case '4':
        data = MUX[4];
        break;
      case '5':
        data = MUX[5];
        break;
      case '6':
        data = MUX[6];
        break;
      case '7':
        data = MUX[7];
        break;
      case '8':
        data = MUX[8];
        break;
      case '9':
        data = MUX[9];
        break;
//      case "10":
//        data = MUX[10];
//        break;
      default:
        data = MUX[0];
    }
    writeData(data);

    // pause before next value:
    Serial.print(data);

  }
}

void writeData(byte datum) {

  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST,  datum);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
//  delayMicroseconds(1);
}
