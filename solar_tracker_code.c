#include <Servo.h>

int sensorPin = A0;
int servoPin  = 9;

int sensorValue = 0;
int servoGrad = 90;
int tollerance = 40;

Servo myservo;

void setup() {
  pinMode( sensorPin, INPUT);
  myservo.attach( servoPin );
  myservo.write( servoGrad );
}

void loop() {
  sensorValue = analogRead(sensorPin);
  if ( sensorValue < (512-tollerance) )
  {
    if (servoGrad < 180) servoGrad++;
  }

  if ( sensorValue > (512+tolleranza) )
  {
    if (servoGrad > 0) servoGrad--;
  }

  myservo.write( servoGrad ); 

  delay(100);
}