#include <Arduino.h>
#include <MeMCore.h> 
#include <Math.h>

MeUltrasonicSensor ultrasonic(PORT_3);
MeDCMotor motor1(M1); 
MeDCMotor motor2(M2); 

int front, left, right;

void movebackward(int d)
{
  motor1.run(100);
  motor2.run(-100);
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void moveforward(int d) 
{ 
  motor1.run(-150);
  motor2.run(150); 
  delay(d); 
  motor1.stop();
  motor2.stop();  
}

void spincw(int d) 
{
  motor1.run(-100);
  motor2.run(-100); 
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void spinccw(int d) 
{
  motor1.run(100);
  motor2.run(115); 
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void moveleft(int d)
{
  motor1.run(100);
  motor2.run(100);  
  delay(100); 
  motor1.stop();
  motor2.stop(); 
  moveforward(100); 
}

void moveright(int d) // d = 1250 was optimal for this 
{
  motor1.run(-100); 
  motor2.run(-100);
  delay(100);
  motor1.stop(); 
  motor2.stop(); 
  moveforward(100); 
}

void spinnything()
{
  spinccw(800);
  motor1.stop();
  motor2.stop();
  right = ultrasonic.distanceCm();
  spincw(1450);
  motor1.stop();
  motor2.stop();
  left = ultrasonic.distanceCm();
  spinccw(800); 
  motor1.stop();
  motor2.stop();
}

void deadend()
{
  do
  {
    spinnything();
  } while ((abs(right-left)) <= 7);
  return;
}

void navigate()
{
  spinccw(800);
  right = ultrasonic.distanceCm();
  if (right >= 7)
  {
    return;
  }
  spincw(1350);
  left = ultrasonic.distanceCm(); 
  if (left >= 7)
  {
    return;
  }
  spincw(750); 
  motor1.stop();
  motor2.stop();
  delay(100);
  deadend();
}

void frontdistance()
{
  front = ultrasonic.distanceCm();
  Serial.println(front);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  moveforward(50);
  frontdistance(); 
  if (front <= 6)
  {
    navigate();
    return;
  }
}
