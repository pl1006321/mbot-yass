#include <Arduino.h>
#include <MeMCore.h> 

MeUltrasonicSensor ultrasonic(PORT_3);
MeLineFollower linefinder(PORT_2);
MeDCMotor motor1(M1);
MeDCMotor motor2(M2); 

int value, i; 
float howfar; 

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

void linesensor() 
// black = blue light off = 0
// white = blue light on = 1
{
if (linefinder.readSensor1()==0 && linefinder.readSensor2()==0)
  {
    // Serial.println("Sensor 1 on black and Sensor 2 on black"); 
    value = 1; 
  }

  else if (linefinder.readSensor1()==1 && linefinder.readSensor2()==0)
  {
    // Serial.println("Sensor 1 on white and Sensor 2 on black"); 
    value = 2;
  }

  else if (linefinder.readSensor1()==0 && linefinder.readSensor2()==1)
  {
    // Serial.println("Sensor 1 on black and Sensor 2 on white"); 
    value = 3; 
  }

  else // (linefinder.readSensor1()==1 && linefinder.readSensor2()==1)
  {
    // Serial.println("Sensor 1 on white and Sensor 2 on white"); 
    value = 4;
  }
}

void checkforstop()
{
moveforward(300); 
  for (i=0;i<20;i++) {
    spincw(35);
    linesensor();
    if (value==1) {
     return;
     } 
}
  for (i=0;i<40;i++) {
    spinccw(35); 
    linesensor();
    if (value==1) {
      return; }
}
}

void setup() {
  Serial.begin(9600);
}

void loop() {
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

//you should make movement in a do while / for loop or wtv torture device and make it run the sensors between increments. if an object is sensed, theyll first talk to someone about it, but sooner or later people are going to find out
