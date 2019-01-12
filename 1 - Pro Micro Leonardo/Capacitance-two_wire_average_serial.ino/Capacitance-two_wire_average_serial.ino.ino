#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 4, 6, 7, 8, 9);

const int OUT_PIN = A2;
const int IN_PIN = A0;

//Capacitance between IN_PIN and Ground
//Stray capacitance is always present. Extra capacitance can be added to
//allow higher capacitance to be measured.
const float IN_STRAY_CAP_TO_GND = 27.107; //initially this was 27.107
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;
float capacitance;
float acum;
float finalVal;
int i;
int val;
const int samples = 200;


void setup()
{
  pinMode(OUT_PIN, OUTPUT);
  //digitalWrite(OUT_PIN, LOW);  //This is the default state for outputs
  pinMode(IN_PIN, OUTPUT);
  //digitalWrite(IN_PIN, LOW);
  Serial.begin(9600);      // open the serial port at 9600 bps:  
  lcd.begin(16, 2);
}

void loop()
{
  //Capacitor under test between OUT_PIN and IN_PIN
  //Rising high edge on OUT_PIN
  i = 0;
  acum = 0;
  do{
      pinMode(IN_PIN, INPUT);
      digitalWrite(OUT_PIN, HIGH);
      val = analogRead(IN_PIN);
    
      //Clear everything for next measurement
      digitalWrite(OUT_PIN, LOW);
      pinMode(IN_PIN, OUTPUT);
    
      //Calculate and print result
      
      capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
      acum = acum + capacitance;
      i = i+1;
    } while (i<samples);
    
  finalVal = acum/samples;

  Serial.print(F("Cap = "));  // print as an ASCII-encoded decimal
  Serial.print("\t");  
  Serial.print(finalVal, 2); 
  Serial.print(F("pF")); 
  Serial.println("");
  
  
  Serial.print("ADC = ");  // print as an ASCII-encoded decimal
  Serial.print("\t");  
  Serial.print(val); 
  Serial.println("");

  
lcd.setCursor(0,0);
lcd.print(F("Cap = "));
lcd.setCursor(6,0);
lcd.print(finalVal, 1);
lcd.setCursor(12,0);
lcd.print(F("pF"));
lcd.setCursor(0,1);
lcd.print("ADC = ");
lcd.setCursor(6,1);
lcd.print(val);
delay(500);

    if (finalVal < 0.15){
      val = 0;
      capacitance = 0;
      lcd.clear();
    }
}
