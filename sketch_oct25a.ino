#include <Arduino.h>
#include <MeMCore.h> 

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

void moving(int d) {
  motor1.run(100); // can be any int from -255 to 255
  motor2.run(-100);
  delay(d); 
  motor1.stop();
  motor2.stop();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A7, INPUT);

  while (analogRead(A7) !=0);
  moving(2000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
