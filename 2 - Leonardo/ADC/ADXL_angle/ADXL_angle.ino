/*
CODE: Calibrate and display measurements for an accelerometer ADXL335.

Show angle in degrees

analog 1: x-axis
analog 2: y-axis
analog 3: z-axis
*/

const int xpin = 1;             // x-axis of the accelerometer
const int ypin = 2;             // y-axis
const int zpin = 3;             // z-axis (only on 3-axis models)
const int ledPin = 9;           // pin that the LED is attached to

// variables:
int x = 0;                     // the sensor value
int y = 0;
int z = 0;

double angle_x;
double angle_y;
double angle_z;

int x_sense_min = 1023;        // minimum sensor value
int y_sense_min = 1023;        // minimum sensor value
int z_sense_min = 1023;        // minimum sensor value

int x_sense_max = 0;           // maximum sensor value
int y_sense_max = 0;           // maximum sensor value
int z_sense_max = 0;           // maximum sensor value

void setup() {
  // turn on LED to signal the start of the calibration period:
  pinMode(ledPin, OUTPUT); 
  // initialize the serial communications:
  Serial.begin(9600);
  analogReference(EXTERNAL);
  
  // calibrate during the first five seconds
 
  digitalWrite(ledPin, HIGH);
  while (millis() < 10000) {
    x = analogRead(xpin);
    y = analogRead(ypin);
    z = analogRead(zpin);

    // record the maximum sensor value for x
    if (x > x_sense_max) {
      x_sense_max = x;
    }

    // record the minimum sensor value for x
    if (x < x_sense_min) {
      x_sense_min = x;
    }
    
     // record the maximum sensor value for y
    if (y > y_sense_max) {
      y_sense_max = y;
    }

    // record the minimum sensor value for y
    if (y < y_sense_min) {
      y_sense_min = y;
    }
    
     // record the maximum sensor value for z
    if (z > z_sense_max) {
      z_sense_max = z;
    }

    // record the minimum sensor value for z
    if (z < z_sense_min) {
      z_sense_min = z;
    }
  }

  // signal the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop()
{
 x = analogRead(xpin);  //read from xpin
 delay(1); //
 y = analogRead(ypin);  //read from ypin
 delay(1);  
 z = analogRead(zpin);  //read from zpin
 
//convert read values to degrees -90 to 90 - Needed for atan2
int xAng = map(x, x_sense_min, x_sense_max, -90, 90);
int yAng = map(y, y_sense_min, y_sense_max, -90, 90);
int zAng = map(z, z_sense_min, z_sense_max, -90, 90);

//Caculate 360deg values like so: atan2(-yAng, -zAng)
//atan2 outputs the value of -π to π (radians)
//We are then converting the radians to degrees
angle_x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
angle_y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
angle_z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  
Serial.print(angle_x); 
Serial.print("\t");
Serial.print(angle_y);
Serial.print("\t");
Serial.print(angle_z);  
Serial.print("\n");


delay(500);  //wait for 1 second 
}
