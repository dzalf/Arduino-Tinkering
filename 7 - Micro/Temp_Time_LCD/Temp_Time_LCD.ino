
/*-----( Import needed libraries )-----*/
// Get 1-wire Library here: http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <OneWire.h>

//Get DallasTemperature Library here:  http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library
#include <DallasTemperature.h>
// Wire (I2C) Library
#include <Wire.h>
// LCD Library
//#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library
//Download: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move original LiquidCrystal library elsewhere, copy this in it's place
//RTC Library
#include <DS3231.h>
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
/*-----( Declare Constants and Pin Numbers )-----*/
// Data wire is plugged into port 10 on the Arduino (can be changed)
#define ONE_WIRE_BUS 12    // NOTE: No ";" on #define  
#define TEMPERATURE_PRECISION 9 // Lower resolution
#define BACKLIGHT_PIN  7
#define  LED_OFF  0
#define  LED_ON  1

byte customChar[8] = {
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};



LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //0x27

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
int numberOfDevices; // Number of temperature devices found
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address
// Pass address of our oneWire instance to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Start the LCD display library
//LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://arduino-info.wikispaces.com/Brick-Temperature-DS18B20#Read%20individual

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

/*-----( Declare User-written Functions )-----*/
void displayTemperature(DeviceAddress deviceAddress)
{

  float tempC = sensors.getTempC(deviceAddress);

  if (tempC == -127.00) // Measurement failed or no device found
  {
    lcd.print("Temperature Error");
  }
  else
  {
    lcd.setCursor(3, 1);
    lcd.print("Temp = ");
    lcd.print(tempC);
    lcd.print("");
    //lcd.print((char)223);
    lcd.write((uint8_t)0);
    lcd.print("C");
    //lcd.setCursor(3, 1);
    //lcd.print("F = ");
    //lcd.print(DallasTemperature::toFahrenheit(tempC)); // Convert to F
  }
}// End printTemperature

void displayTime(){
  
  String day = rtc.getDOWStr();
  String date = rtc.getDateStr();
  String timeStr = rtc.getTimeStr();
  // Send Day-of-Week

  lcd.setCursor(6, 2);
  lcd.print(day);
  lcd.setCursor(0, 3);
  lcd.print(date);
  lcd.print(" ");
  lcd.print(timeStr);
  }
void setup()   /****** SETUP: RUNS ONCE ******/
{
  
  //---------------- Initialize the lcd ------------------
  lcd.begin (20, 4); // 20 characters, 4 lines
  // Switch on the backlight
  //lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  //lcd.setBacklight(LED_ON);

  // create a new custom character
  lcd.createChar(0, customChar);
  //------- Initialize the Temperature measurement library--------------
  sensors.begin();
   // Initialize the rtc object
  rtc.begin();
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(THURSDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(15, 41, 50);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(8, 6, 2017);   // Set the date to January 1st, 2014
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  Serial.begin(115200);
  // locate devices on the bus
  Serial.print("Locating devices...");

  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // Loop through each device, print out address
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      Serial.print("Found device ");
      Serial.print(i, DEC);
      Serial.print(" with address: ");
      printAddress(tempDeviceAddress);
      Serial.println();

      Serial.print("Setting resolution to ");
      Serial.println(TEMPERATURE_PRECISION, DEC);

      // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
      sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

      Serial.print("Resolution actually set to: ");
      Serial.print(sensors.getResolution(tempDeviceAddress), DEC);
      Serial.println();
    } else {
      Serial.print("Found ghost device at ");
      Serial.print(i, DEC);
      Serial.print(" but could not detect address. Check power and cabling");
    }
  }

  

}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");

  //lcd.clear();  // Reset the display
  //lcd.home();
  //lcd.backlight();  //Backlight ON if under program control

  // Print our characters on the LCD
  // NOTE: Line number and character number start at 0 not 1
  // Loop through each device, print out temperature data
  for (int i = 0; i < numberOfDevices; i++)
  {
    // Search the wire for address
    if (sensors.getAddress(tempDeviceAddress, i))
    {
      // Output the device ID
      Serial.print("Temperature for device: ");
      Serial.println(i, DEC);
      lcd.setCursor(0, 0); //Start at character 0 on line 0
      lcd.print("Dan's clock machine ");
      displayTemperature(tempDeviceAddress);
      // It responds almost immediately. Let's print out the data
      //printTemperature(tempDeviceAddress); // Use a simple function to print out the data
    }
    displayTime();
    delayMicroseconds(10);

  }//--(end main loop )---
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
}


//*********( THE END )***********
