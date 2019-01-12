

int outputs[4] = {6, 7, 8, 9}; // A,B,C,D inputs
int number = 0;
int cathodes[3] = {5, 4, 3};
byte cathodeOn[3][3] = {{HIGH, LOW, LOW}, {LOW, HIGH, LOW},{LOW, LOW, HIGH} };
int pointer = 2;
int val = 62;
int num[3] = {0,};

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

  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(outputs[i], OUTPUT);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(cathodes[i], OUTPUT);
  }

  for (int anode = 0; anode < 4; anode++) {
    digitalWrite(outputs[anode], BCD[0][anode]);
  }


  for (int index = 0; index < 4; index++) {
    digitalWrite(cathodes[index], LOW);
  }

}

void loop() {

  
  
  num[0] =  val  % 10;
  num[1] = (val / 10) % 10;
  num[2] = (val / 100) % 10;

  if (num[2]==0) digitalWrite(cathodes[2], LOW);

  for (int numIndex = 0; numIndex < 3; numIndex++) {

    //    digitalWrite(cathodes[index], HIGH);

    for (int catIndex = 0; catIndex < 3; catIndex++) {
      digitalWrite(cathodes[catIndex], cathodeOn[numIndex][catIndex]);
    }
    for (int anode = 0; anode < 4; anode++) {
      digitalWrite(outputs[anode], BCD[num[numIndex]][anode]);
    }
    delay(400);
  }

}
