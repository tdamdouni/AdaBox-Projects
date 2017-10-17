
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_)
  #include <SoftwareSerial.h>
#endif

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);


#define toneC    1911
#define toneC1    1804
#define toneD    1703
#define toneEb    1607
#define toneE    1517
#define toneF    1432
#define toneF1    1352
#define toneG    1276
#define toneAb    1204
#define toneA    1136
#define toneBb    1073
#define toneB    1012
#define tonec       955
#define tonec1      902
#define toned       851
#define toneeb      803
#define tonee       758
#define tonef       716
#define tonef1      676
#define toneg       638
#define toneab      602
#define tonea       568
#define tonebb      536
#define toneb       506
 
#define tonep       0 
 
int speaker = A1; 
long vel = 20000;
boolean hasplayed = false;

int upDown=0;
int leftRight=0;

void setup(void)
{
  Serial.begin(9600);

  AFMS.begin();  // create with the default frequency 1.6KHz

  // turn on motors
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);
    
  Serial.begin(9600);
  
  pinMode(speaker, OUTPUT);
  
  L_MOTOR->setSpeed(5); 
  R_MOTOR->setSpeed(5);
} 

int melod[] = {tonec, toneG, toneE, toneA, toneB, toneBb, toneA, toneG, tonee, toneg, tonea, tonef, toneg, tonee, tonec, toned, toneB};
int ritmo[] = {18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6};

void loop(void)
{
  leftRight=analogRead(A4);
  upDown=analogRead(A3);
  setMotors();
  //delay(1000);
}

void setMotors()
{
  Serial.println();
  Serial.println(upDown);
  Serial.println();
  
  upDown-=255;
  
  float upDownFloat=float(upDown);
  upDownFloat/=255;

  leftRight-=255;
  float leftRightFloat=float(leftRight);
  leftRightFloat/=255;
  
  float rightFloat=leftRightFloat;
  float leftFloat=leftRightFloat*-1;

  leftFloat+=upDownFloat;

  rightFloat+=upDownFloat;

  bool leftMotorDirection=1; //1 Forward, 0 backwards.
  if (leftFloat <0)
  {
    leftMotorDirection=0;
    leftFloat*=(-1);
  }
  bool rightMotorDirection=1; //1 Forward, 0 backwards.
    if (rightFloat <0)
  {
    rightMotorDirection=0;
    rightFloat*=(-1);
  }

  if (leftFloat > 1)
  {
    rightFloat/=leftFloat;
    leftFloat/=leftFloat;
  }

   if (rightFloat >1)
  {
    leftFloat/=rightFloat;
    rightFloat/=rightFloat;
  }

  int leftMotorSpeed=0;  //Could be a byte, but int has easier functions.
  leftFloat*=255;
  leftMotorSpeed=int(leftFloat);

  int rightMotorSpeed=0;  //Could be a byte, but int has easier functions.
  rightFloat*=255;
  rightMotorSpeed=int(rightFloat);
  
  L_MOTOR->setSpeed(leftMotorSpeed);
  if (leftMotorDirection==1)
  {
    L_MOTOR->run(FORWARD);
  }
  else
  {
    L_MOTOR->run(BACKWARD);
  }
  
  R_MOTOR->setSpeed(rightMotorSpeed);
  if (rightMotorDirection==1)
  {
    R_MOTOR->run(FORWARD);
  }
  else
  {
    R_MOTOR->run(BACKWARD); 
  }

  Serial.print("Left motor speed: ");
  Serial.println(leftMotorSpeed);
  Serial.print("Left motor direction: ");
  if (leftMotorDirection==1)
  {
    Serial.println("Forward");
  }
  else
  {
    Serial.println("Reverse");
  }
  
  Serial.print("Right motor speed: ");
  Serial.println(rightMotorSpeed);
  Serial.print("Right motor direction: ");
  if (rightMotorDirection==1)
  {
    Serial.println("Forward");
  }
  else
  {
    Serial.println("Reverse");
  }

  Serial.println();
  Serial.println();
}

