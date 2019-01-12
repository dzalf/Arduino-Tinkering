#define clk 3
#define dt 6
#define sw 7
#define yellow 4
#define green 5
#define red 2

byte counter;

void setup(){
  
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(sw, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  Serial.begin(9600);
  counter = 127;
  attachInterrupt(0,handleEncoder,FALLING);
}

void loop(){
  digitalWrite(red,LOW);
  while(digitalRead(sw) == LOW){
    digitalWrite(red,HIGH);
    counter = 127;
  }
  
  Serial.println(counter);
  delay(500);
 
}

void handleEncoder(){

  if(digitalRead(clk) == digitalRead(dt)){
    digitalWrite(yellow, HIGH);
    delay(100);
    digitalWrite(yellow,LOW); 
    counter--;
  }
  else
  { 
    digitalWrite(green, HIGH);
    delay(100);
    digitalWrite(green,LOW);
    counter++;
  }

}


