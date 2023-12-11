#include <Arduino.h>
#include <MeMCore.h> 

MeUltrasonicSensor ultrasonic(PORT_3);
MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

int leftdistance, rightdistance, howfar, frontdistance;

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

void left(int d)
{
  motor1.run(100);
  motor2.run(100);  
  delay(100); 
  motor1.stop();
  motor2.stop(); 
  moveforward(100); 
}

void right(int d) // d = 1250 was optimal for this 
{
  motor1.run(-100); 
  motor2.run(-100);
  delay(100);
  motor1.stop(); 
  motor2.stop(); 
  moveforward(100); 
}

void leftdistancechecker()
{
  leftdistance = ultrasonic.distanceCm(); 
  Serial.println(leftdistance);
  return;
}

void rightdistancechecker()
{
  rightdistance = ultrasonic.distanceCm(); 
  Serial.println(rightdistance);
  return;
}

void frontwallchecker()
{
  frontdistance = ultrasonic.distanceCm(); 
  Serial.println(frontdistance); 
  return; 
}

void checkdistance() // this is vetted and works!!
{
  spincw(800); 
  rightdistancechecker();
  spinccw(1450);
  leftdistancechecker();
  spincw(800);
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{ 
  moveforward(500); 
  frontwallchecker();
  if (frontdistance <= 5); 
  {
    checkdistance();
    if (rightdistance > leftdistance)
    {
      spincw(800);
    }

    else 
    spinccw(800);
  }
}
