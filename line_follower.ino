#include <Arduino.h>
#include <MeMCore.h> 

MeLineFollower linefinder(PORT_2);
MeDCMotor motor1(M1);
MeDCMotor motor2(M2); 

int value;

void moveforward(int d) 
{ 
  motor1.run(-100);
  motor2.run(100); 
  delay(d); 
  motor1.stop();
  motor2.stop();  
}

void movebackward(int d)
{
  motor1.run(100);
  motor2.run(-100);
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void spin() // d = 1000 is optimal depending on surface
{
  motor1.run(115);
  motor2.run(100); 
  delay(500); 
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

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // black = blue light off = 0
  // white = blue light on = 1

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

  if (value == 1)
  {
    moveforward(100); 
  }

  else if (value == 2)
  {
    right(100); 
  }

  else if (value == 3)
  {
    left(100); 
  }

  else // (if value == 4)
  {
  spin();
  }

}
