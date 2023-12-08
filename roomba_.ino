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

void checkforstop()
{
moveforward(300); 
  for (i=0;i<20;i++) {
    spincw(35);
    if (value==1) {
     return;
     } 
}
  for (i=0;i<40;i++) {
    spinccw(35); 
    if (value==1) {
      return; }
}
}

void 

void distancechecker()
{
  howfar = ultrasonic.distanceCm(); 
  Serial.println(howfar);
  return;
}

void avoiding()
{
  if (howfar <= 7)
  {
    motor1.stop();
    motor2.stop();
    spincw(450);
    moveforward(1300);
    spinccw(700);
    moveforward(1400);
    checkforstop();
    return;
  }
 return;
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
     obstaclechecker();
     avoiding();
     break;
 
   case 2: 
     right(100); 
     obstaclechecker();
     avoiding();
     break;
 
   case 3:
     left(100); 
     obstaclechecker();
     avoiding();
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
