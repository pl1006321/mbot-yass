#include <Arduino.h>
#include <MeMCore.h> 

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
  motor1.run(-100);
  motor2.run(100); 
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

void checkdistance()
{
  spincw(800);
  right = ultrasonic.distanceCm();
  spinccw(1450);
  left = ultrasonic.distanceCm(); 
  spincw(800); 
  motor1.stop();
  motor2.stop();
  delay(100);
}

void frontdistance()
{
  front = ultrasonic.distanceCm();
  Serial.println(front);
}

void deadend()
{
  do 
  {
  movebackward(100);
  checkdistance();
  } while ((abs(right - left)) <= 5)
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  moveforward(400);
  frontdistance(); 
  if (front <= 10)
  {
    checkdistance();
    if ((abs(right - left)) <= 5)
    {
      deadend();
      if (right > left)
      {
       spincw(800);
       return; 
      } 
      else spinccw(800);
      return; 
    }
    else spinccw(800);
    return; 
    }
    if (right > left)
    {
      spincw(800);
      return; 
    }
    else spinccw(800);
    return; 
  }
}
