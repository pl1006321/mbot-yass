#include <Arduino.h>
#include <MeMCore.h> 

MeLineFollower linefinder(PORT_2);
MeDCMotor motor1(M1);
MeDCMotor motor2(M2); 

int value, sensedbothblack;
int firstturncomplete = 0;
int secondturncomplete = 0; 

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
sensedbothblack = 0;
if (firstturncomplete != 1) {
  moveforward(300); 
  do {
    spincw(35);
    linesensor();
    if (value==1) {
     sensedbothblack = 1;
     firstturncomplete = 1;  
      value = 1;
      return;
    }
  } while (sensedbothblack != 1); 
}

if (secondturncomplete != 1) {
  moveforward(300); 
  do {
    spincw(35);
    linesensor();
    if (value==1) {
     sensedbothblack = 1;
     secondturncomplete = 1;  
    }
  } while (sensedbothblack != 1); 
}


// if (nthturncomplete != 1)
// do spinny thing (just copy and paste from above and change to clockwise or counterclockwise as necessary 
// for the last turn, make sure to include return to case 5
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
