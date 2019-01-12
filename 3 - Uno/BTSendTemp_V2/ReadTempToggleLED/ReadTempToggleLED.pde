import controlP5.*;
import processing.serial.*;

// Display a simulation of a water tank filling and emptying



//Canvas variables
float w = 400.0;
float h = 200.0;

// Serial Port variables
Serial myPort;        
float inByte = 0.0;
float seed = 0;
String[] PortList;
int numPort;
int portSelected = 0;

// Tank simulation variables
float tall = 1.0;
float percent = 0.0;

//Wave generation

float[] statesArray;
float lastVal = 0.0;;
float newState = 0.0;
int index = 0;
int state;
int lastState;
int count = 0;

//Proprietary variables for displaying messages

percentBox perBox;
conditionsBox emptyBox;
conditionsBox fullBox;
conditionsBox fillingBox;
conditionsBox emptyingBox;
conditionsBox idleBox;

void setup () {
  size(400, 200);
  
  frameRate(60);
  state = 0;
  
  PortList = new String[5];
  
  // Define Tank status messages
  int colEmpty[] = {255, 186, 0};
  int colFull[] = {138, 255, 124};
 
  perBox = new percentBox();
  emptyBox = new conditionsBox("Empty tank :(", 40, 200, 660, colEmpty);
  fullBox = new conditionsBox("Full tank! :)", 40, 210, 660, colFull );
  fillingBox = new conditionsBox("Filling tank...", 40, 200, 660, colFilling );
  
  //Serial Port definition
  myPort = new Serial(this, Serial.list()[portSelected], 115200);
  PortList = Serial.list();
  numPort = PortList.length;
  myPort.bufferUntil('\n'); // don't generate a serialEvent() unless you get a newline character:
 
}
void draw () {
  
  background(#C4D0FF); //light grey #5751B2
  
  // Count number of frames and define 
  rect(50,50,);
  
  
  
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    
    //considering one value coming from the buffer
    float[] pot = float(split(inString, ","));
    if (pot.length >=3) {
      //println(pot[0]);
      inByte = pot[0];
      seed = map(pot[1], 0, 1023, 0, w);
    }
  }
}

void displayRawInputs() {
  //float posX = tempPosX;
  fill(#4CF5FA);
  textSize(12);
  String dataText = nf(int(inByte), 1);
  String tallText = nf(int(tall), 1);
  text("data  = " +dataText, 480, h+45);
  text("tall = " +tallText, 480, h+60);
  text("index = " +index, 480, h+75);
  text("lastVal = " +lastVal, 480, h+90);
}

// TO REPLACE SERIAL WITH KEYBOARD

void keyPressed(){
  if (key == CODED) {
    if(keyCode == UP){
      inByte = inByte + 1;
    }
    
    if(keyCode == DOWN){
      inByte = inByte - 1;
    }
  }
  inByte = constrain(inByte, 0, 1023);
  seed = int(seed);
  seed = constrain(seed, 0, w);
}