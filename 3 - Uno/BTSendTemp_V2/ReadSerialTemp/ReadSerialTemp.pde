import processing.serial.*;

Serial myPort;  // Create object from Serial class
float inVal;     // Data received from the serial port
String inString;
String dataText;
String[] PortList;
int numPort;


void setup()
{
  PortList = new String[5];
  size(300,150);
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 115200);
  numPort = PortList.length;
  
  PortList = Serial.list();
  printArray(PortList);
  dataText = " ";
}

void draw()
{
  background(70);
  fill(210);
  textSize(30);
  text("CPU exhaust temp", width*0.05,height*.20); 
  textSize(40);
  text(dataText, width*.25, height*.55); //print it out in the console
  text("°C", 200,height*.55);
  textSize(30);
  text("Bluetooth COM5", width*0.1, height*.90);
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  inString = myPort.readStringUntil('\n');
  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    //inByte = float(inString); //previous code line 
    //considering one value coming from the buffer
    float[] chain = float(split(inString, " "));
    if (chain.length >=3) {
      inVal = chain[2];
      dataText = nf(int(inVal), 2,2);
    }
  }
}