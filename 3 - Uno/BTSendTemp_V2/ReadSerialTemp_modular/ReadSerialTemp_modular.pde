import processing.serial.*;

Serial myPort;  // Create object from Serial class
float inVal = 20.0;     // Data received from the serial port
String inString;
String[] PortList;
String[] dataText;
String joinedText = "";

int w = 300;
int h = 150;
int numPort;
int tempSize = 45;
int headerSize = 30;
int responseSize = 15;

int unPressedCol[] = {106,146,178};
int ONCol[] = {47, 245, 61};
int OFFCol[] = {250, 74, 43};
int buttonX = 40;
int buttonY = 145;
int buttonW = 90;
int buttonH = 50;
int shiftX = 130;
boolean pressed = false;

conditionsBox lowTempBox;
conditionsBox mediumTempBox;
conditionsBox highTempBox;
conditionsBox RawTempBox;
conditionsBox headerBox;
conditionsBox footBox;
conditionsBox degreesBox;
conditionsBox serialResponseBox;

buttonBox onButton;
buttonBox offButton;

void setup()
{  
  size(300,200);
  
  dataText = new String[2];
  PortList = new String[5];
  
  int PosData[] = {floor(w*0.20), floor(h*0.60)};
  int colLowTemp[] = {47, 245, 61};
  int colMediumTemp[] = {250, 157, 43};
  int colHighTemp[] = {250, 74, 43};
  int colHeaderandFoot[] = {210, 210, 210};
  
  
  lowTempBox = new conditionsBox(tempSize,PosData[0],PosData[1],colLowTemp);
  mediumTempBox = new conditionsBox(tempSize,PosData[0],PosData[1],colMediumTemp);
  highTempBox = new conditionsBox(tempSize,PosData[0],PosData[1],colHighTemp);
  RawTempBox = new conditionsBox(tempSize,PosData[0],PosData[1],colHeaderandFoot);
  headerBox = new conditionsBox(headerSize,floor(w*0.05),floor(h*.20),colHeaderandFoot);
  footBox = new conditionsBox(headerSize, floor(w*0.1), floor(h*.90), colHeaderandFoot);
  serialResponseBox = new conditionsBox(headerSize, floor(w*0.1), floor(h*.95), colHeaderandFoot);
  
  onButton = new buttonBox(40, 145, 0);
  offButton = new buttonBox(40, 145, shiftX);
    
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
  numPort = PortList.length;
  PortList = Serial.list();
}

void draw()
{
  background(70);
  
  headerBox.display("CPU exhaust temp");
  
  if((inVal >= 20.0) && (inVal <= 40.0)){
    lowTempBox.display(joinedText);
    println("Low: "+joinedText);
  } else if((inVal >= 40.1) && (inVal <= 60.0)){
    mediumTempBox.display(joinedText);
    println("Medium: "+joinedText);
  } else if((inVal >=60.1) && (inVal<=80.0) ){
    highTempBox.display(joinedText);
    println("High"+joinedText);
  } else{
    RawTempBox.display(joinedText);
    println("Raw "+joinedText);
  }
  
  footBox.display("Bluetooth COM6");
 
  //fill(#6A92B2);
  //noStroke();
  //rect(40, 145, 90,50, 10);
  //fill(220);
  //textSize(30);
  //text("ON", 63,180);
  
  onButton.display("ON", unPressedCol);
  
  //fill(#6A92B2);
  //noStroke();
  //rect(40+110, 145, 90,50, 10);
  //fill(220);
  //textSize(30);
  //text("OFF", 63+100,180);
  
  offButton.display("OFF", unPressedCol);
  
}

void serialEvent (Serial myPort) {
  inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    String[] chain = split(inString, " ");
    inVal = float(chain[2]);
    dataText[0] = nf(inVal, 2,1);
    dataText[1] = "°C";
    joinedText = join(dataText, " ");
    printArray(chain);
  }
}

void mouseClicked(){

  //if((mouseX>40)&&(mouseX<130)&&(mouseY>145)&&(mouseY<195)){
  if((mouseX>buttonX)&&(mouseX<buttonX+buttonW)&&(mouseY>buttonY)&&(mouseY<buttonY+buttonH)){
    myPort.write("ON\n");
    onButton.display("ON", ONCol);
    //onButton.display("OFF", OFFCol);
    println("ON!");
  
  }
  
   //if((mouseX>140)&&(mouseX<230)&&(mouseY>145)&&(mouseY<195)){
   if((mouseX>buttonX+shiftX)&&(mouseX<buttonX+shiftX+buttonW)&&(mouseY>buttonY)&&(mouseY<buttonY+buttonH)){ 
    myPort.write("OFF\n");
    offButton.display("OFF", OFFCol);
    println("OFF!");
  }




}