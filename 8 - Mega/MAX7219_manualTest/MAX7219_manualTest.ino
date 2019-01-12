const int MAX_CLK = 15;
const int MAX_CS = 16;
const int MAX_DATA = 14;

void initialise() {
  digitalWrite(MAX_CS, HIGH);
  pinMode(MAX_DATA, OUTPUT);
  pinMode(MAX_CLK, OUTPUT);
  pinMode(MAX_CS, OUTPUT);
}

void output( byte address, byte data) {

  digitalWrite(MAX_CS, LOW);
  shiftOut(MAX_DATA, MAX_CLK, MSBFIRST, address);
  shiftOut(MAX_DATA, MAX_CLK, MSBFIRST, data);
}

void setup() {
  // put your setup code here, to run once:
  initialise();
  output(0x0f, 0x00);
  output(0x0c, 0x01);
  output(0x0b, 0x07);
  output(0x09, 0xff);
  output(0x01, 0x05);
  output(0x02, 0x06);
  output(0x03, 0x07);
  output(0x04, 0x08);
}

void loop() {
  // put your main code here, to run repeatedly:

}
