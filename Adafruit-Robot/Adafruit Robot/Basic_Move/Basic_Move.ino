
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *LeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(4);

int moveSpeed = 50;   // Set the speed to start, from 0 (off) to 255 (max speed)

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  
  LeftMotor->setSpeed(moveSpeed);
  RightMotor->setSpeed(moveSpeed);

  // Enter code that you only want done once here.
  MoveF(moveSpeed, 4000);
  TurnL(moveSpeed, 2000);
  TurnR(moveSpeed, 2000);
  MoveStop(2000);
  MoveB(moveSpeed, 2000);
}

void loop()
{  
  // Enter code that you only want done once here.
  
}

/* The Hack-E-Bot can now be programmed to move by giving it instructions like:
MoveStop(stopTime); -- to stop moving
MoveF(moveSpeed, moveTime); -- to drive forward
MoveB(moveSpeed, moveTime); -- to drive backward
TurnR(moveSpeed, moveTime); -- to turn right
TurnL(moveSpeed, moveTime); -- to turn left
stopTime and moveTime are mesured in miliseconds.
moveSpeed is a number between 0 to 90 with 0 being no movment and 90 being full speed.
*/

void MoveStop(int T){ // Stop moving, T = stopTime.
  RightMotor->run(RELEASE);
  LeftMotor->run(RELEASE);
  delay(T);
}

void MoveF(int S, int T){ // Move forward, S = moveSpeed, T = moveTime.
  RightMotor->run(FORWARD);
  LeftMotor->run(BACKWARD);
  delay(T);
}

void MoveB(int S, int T){ // Move backward, S = moveSpeed, T = moveTime.
  RightMotor->run(BACKWARD);
  LeftMotor->run(FORWARD);
  delay(T);
}

void TurnL(int S, int T){ // Turn Left, S = moveSpeed, T = moveTime.
  RightMotor->run(BACKWARD);
  LeftMotor->run(BACKWARD);
  delay(T);
}

void TurnR(int S, int T){ // Turn Right, S = moveSpeed, T = moveTime.
  RightMotor->run(FORWARD);
  LeftMotor->run(FORWARD);
  delay(T);
}
