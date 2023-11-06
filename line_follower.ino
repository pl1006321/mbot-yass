#include <Arduino.h>
#include <MeMCore.h> 

MeLineFollower linefinder(PORT_2);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // black = blue light off = 0
  // white = blue light on = 1

  if (linefinder.readSensor1()==0 && linefinder.readSebsir2()==0)
  {
    Serial.println("Sensor 1 on black and Sensor 2 on black"); 
  }

  else if (linefinder.readSensor1()==1 && linefinder.readSensor2()==0)
  {
    Serial.println("Sensor 1 on white and Sensor 2 on black"); 
  }

  else if (linefinder.readSensor1()==0 && linefinder.readSensor2()=1)
  {
    Serial.println("Sensor 1 on black and Sensor 2 on white"); 
  }

  else // (linefinder.readSensor1()==1 && linefinder.readSensor2()==1)
  {
    Serial.println("Sensor 1 on white and Sensor 2 on white"); 
  }
}
