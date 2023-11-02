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

void leftturn(int d)
{
  motor1.run(110);
  motor2.run(0);  
  delay(d); 
  motor1.stop();
  motor2.stop(); 
}

void rightturn(int d)
{
  motor1.run(-100); 
  motor2.run(0);
  delay(d);
  motor1.stop();
  motor2.stop(); 
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A7, INPUT);

  while (analogRead(A7) !=0);
  moveforward(2000); 
  rightturn(1250); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
