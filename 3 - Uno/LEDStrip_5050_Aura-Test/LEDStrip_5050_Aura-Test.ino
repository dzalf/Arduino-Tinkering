
const int RGB[3] = {10, 9, 11};
long randPWM;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {

    pinMode(RGB[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {

    analogWrite(RGB[i], 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 256; j++) {
      analogWrite(RGB[i], j);
      delay(20);
    }

    delay(100);

    analogWrite(RGB[i], 0);

    delay(100);
  }

  //  randPWM = random(0, 2);
  //  analogWrite(RGB[randPWM], 127);
  //
  //  randPWM = random(0, 2);
  //  analogWrite(RGB[randPWM], 127);
  //
  //  randPWM = random(0, 2);
  //  analogWrite(RGB[randPWM], 127);

  delay(2000);



  for (int j = 0; j < 256; j++) {
    analogWrite(RGB[0], j);
    analogWrite(RGB[1], j);
    analogWrite(RGB[2], j);
    delay(20);
  }

  delay(2000);

  for (int i = 0; i < 3; i++) {

    analogWrite(RGB[i], 0);
  }

  delay(500);

}
