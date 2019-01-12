

int outputs[4] = {6, 7, 8, 9}; // A,B,C,D inputs
int number = 0;
int cathodes[3] = {3, 4, 5};
int pointer = 2;

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

  for (int number = 0; number < 10; number++) {
    for (int anode = 0; anode < 4; anode++) {

      digitalWrite(cathodes[pointer], HIGH);
      digitalWrite(outputs[anode], BCD[number][anode]);
    }
    delay(300);
    
  }
  digitalWrite(cathodes[pointer], LOW);
    pointer--;

    if(pointer<0) pointer = 2;

}
