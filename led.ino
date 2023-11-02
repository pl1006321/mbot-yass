#include <Arduino.h> 
#include <MeMCore.h>

// data type for led lights are MeRGBLed

MeRGBLed led(0,30);

void setup() {
  // put your setup code here, to run once:
  led.setpin(13); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // led.setColor(255,255,255); // sets both leds to white
  // led.show(); // must include this for the led to physically show 
  // delay(1000); // must have delay for it to show, measurement is millseconds
  led.setColorAt(0,255,0,0); // first number (0) represents the right led, other 3 numbers are the rgb values
  led.setColorAt(1,0,255,0); // first number (1) represents the left led 
  led.show();
  delay(200); 
  led.setColorAt(0,0,255,0);
  led.setColorAt(1,255,0,0); 
  led.show();
  delay(200);
}
