

int outputs[4] = {6, 7, 8, 9}; // A,B,C,D inputs
int number = 0;
byte BCD[10][4] = {
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {1, 1, 0, 0},
  {0, 0, 1, 0},
  {1, 0, 1, 0},
  {0, 1, 1, 0},
  {1, 1, 1, 0},
  {0, 0, 0, 1},
  {1, 0, 0, 1},
}; //BCD code


void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(outputs[i], OUTPUT);
  } 

  for (int anode = 0; anode < 4; anode++) {
      digitalWrite(outputs[anode], BCD[0][anode]);
    }
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0){
    
    number = Serial.read();
    Serial.println(number-48);
//  for (int number = 0; number < 10; number++) {
    for (int anode = 0; anode < 4; anode++) {
      digitalWrite(outputs[anode], BCD[number-48][anode]);
    }
//    delay(300);
  }



}


