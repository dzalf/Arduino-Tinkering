#define clk 7
#define dt 5
#define sw 6
#define yellow 3
#define green 4

int counter = 0;
int initial_clk = HIGH;
int initial_dt = HIGH;
int dir = 0; //   0 = Clockwise, 1 = Counterclockwise

void setup(){
  
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(sw, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  Serial.begin(9600);
}

void loop(){
  
}


int getDir(void){
  static int new_clk = digitalRead(clk);
  static int new_dt= digitalRead(dt);
}
