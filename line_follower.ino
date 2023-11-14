#include <Arduino.h>
#include <MeMCore.h> 

MeLineFollower linefinder(PORT_2);
MeDCMotor motor1(M1);
MeDCMotor motor2(M2); 

int value, turned; 
int count = 0; 

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
  motor2.run(-115); 
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

void turn180() 
{
  motor1.run(100);
  motor2.run(115); 
  delay(750); 
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

void linesensor() 
// black = blue light off = 0
// white = blue light on = 1
{
if (linefinder.readSensor1()==0 && linefinder.readSensor2()==0)
  {
    Serial.println("Sensor 1 on black and Sensor 2 on black"); 
    value = 1; 
  }

  else if (linefinder.readSensor1()==1 && linefinder.readSensor2()==0)
  {
    Serial.println("Sensor 1 on white and Sensor 2 on black"); 
    value = 2;
  }

  else if (linefinder.readSensor1()==0 && linefinder.readSensor2()==1)
  {
    Serial.println("Sensor 1 on black and Sensor 2 on white"); 
    value = 3; 
  }

  else // (linefinder.readSensor1()==1 && linefinder.readSensor2()==1)
  {
    Serial.println("Sensor 1 on white and Sensor 2 on white"); 
    value = 4;
  }
}

void checkforstop()
{
moveforward(100); 
spincw(560); 
  if (linefinder.readSensor1()==0 && linefinder.readSensor2()==0)
  {
    value=1;
  }
spinccw(1110);
  if (linefinder.readSensor1()==0 && linefinder.readSensor2()==0)
  {
    value=1;
  }
spincw(375);
if (linefinder.readSensor1()==0 && linefinder.readSensor2()==0)
  {
    value=1;
  }
  else
  {
    value=5;
  }
}

void setup()
{
  Serial.begin(9600); 
}

void loop()
{

while (value!=5)
{
linesensor();

  movement:

  switch (value) 
  {
    case 1:
      moveforward(100);
      break;
  
    case 2: 
      right(100); 
      break;
  
    case 3:
      left(100); 
      break;
  
    case 4:
      checkforstop(); 
      if (value==5)
      {
        motor1.stop();
        motor2.stop();
      }
      break;
}
}
}
