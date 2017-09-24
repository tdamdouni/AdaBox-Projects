#include <Servo.h>
int servoPin=5;
int pos=0;
int servoDelay=25;

Servo microServo;

void setup() {
  Serial.begin(9600);
  microServo.attach(servoPin);
}

void loop() {
 Serial.println("Unde vrei sa pozitionezi servo?"); //prompt user for input
 while(Serial.available()==0){  //wait for user input
 }
 pos=Serial.parseInt();   // read the input and puting it in the variable pos
 microServo.write(pos);   // command servo to go to the user input
}
