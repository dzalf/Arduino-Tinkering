/*
  
 */
 
// 
int led = 3;

void setup()
{
  // no setup needed
}
// the loop routine runs over and over again forever:
void loop() {
  for (int n = 0; n <= 255 ; n += 6){
    analogWrite(led, n);   // turn the LED on (HIGH is the voltage level)
    delay(30);               // wait for a second
   }
  for ( int n = 255; n >= 0 ;n -= 6){
     analogWrite(led, n);   // turn the LED on (HIGH is the voltage level)
      delay(30);               // wait for a second
    }
  // wait for a second
  
}
