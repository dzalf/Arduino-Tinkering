#include <LedControlMS.h>

#define NumMatrix 1       // Cuantas matrices vamos a usar

LedControl lc=LedControl(16,15,14,1); // 

// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219

void setup()
   {
      for (int i=0; i< NumMatrix ; i++)
        {
           lc.shutdown(i,false);    // Activar las matrices
           lc.setIntensity(i,8);    // Poner el brillo a un valor intermedio
           lc.clearDisplay(i);      // Y borrar todo
        }
   }

void loop()
   {
        lc.writeString(0," Hola Lety bebe...");
        delay(1000);
   }
