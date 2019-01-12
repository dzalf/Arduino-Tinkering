/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define PIN_INPUT 0
#define PIN_OUTPUT 10

//Define Variables we'll be connecting to
double Setpoint, Input, Output, mapped;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  Serial.begin(115200);
  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  Setpoint = 510;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 5000); 
}

void loop()
{
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  mapped = map(Output, 0, 5000, 0, 255);
  analogWrite(PIN_OUTPUT, mapped);
  Serial.print("Input -> ");
  Serial.print(Input);
  Serial.print("; ");
  Serial.print("mapped -> ");
  Serial.print(mapped);
  Serial.print("; ");
  Serial.print("Output-> ");
  Serial.print(Output);
  Serial.print("\n");
}

