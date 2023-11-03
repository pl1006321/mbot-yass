#include <Arduino.h> 
#include <MeMCore.h> 

MeDCMotor motor1(M1);
MeDCMotor motor2(M2); 
MeRGBLed led(0,30); 

void greenled(int d) 
{
  led.setpin(13); 
  led.setColor(0,255,0); 
  led.show(); 
  delay(d); 
}

void redled(int d) 
{
  led.setpin(13);
  led.setColor(255,0,0);
  led.show();
  delay(d); 
}

void moveforward(int d) 
{ 
  motor1.run(-100);
  motor2.run(100); 
  greenled(d);
  delay(d); 
  motor1.stop();
  motor2.stop(); 
  redled(d); 
}

void movebackward(int d)
{
  motor1.run(100);
  motor2.run(-100);
  greenled(d);
  delay(d); 
  motor1.stop();
  motor2.stop();
  redled(d); 
}

void turn180(int d) // d = 1000 is optimal depending on surface
{
  motor1.run(100);
  motor2.run(115); 
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void leftturn(int d)
{
  motor1.run(110);
  motor2.run(0);  
  delay(d); 
  motor1.stop();
  motor2.stop(); 
}

void rightturn(int d) // d = 1250 was optimal for this 
{
  motor1.run(-100); 
  motor2.run(0);
  delay(d);
  motor1.stop();
  motor2.stop(); 
}

void setup() {
  pinMode(A7, INPUT);

  while (analogRead(A7) !=0);
  // put code here 
}

void loop() {}
