#include <Wire.h>
#include <GY6050.h>

// Left motor pins
#define enableL 6
#define LPin1 7
#define LPin2 8

// Right motor pins
#define enableR 11
#define RPin1 9
#define RPin2 10

GY6050 gyro(0x68);

int rightspeed = 200;
int leftspeed = 200;
int response = 1;
int ledPin = 13;
int state = 0;
int flag = 0;
boolean condit = true;
int trigPin = 4;
int echoPin = 5;
long duration;
int distance;
int currentServoPos1 = 0;

void setup() {
  Serial.begin (9600);
  // motors
  pinMode(enableR, OUTPUT);
  pinMode(enableL, OUTPUT);
  pinMode(RPin1, OUTPUT);
  pinMode(RPin2, OUTPUT);
  pinMode(LPin1, OUTPUT);
  pinMode(LPin2, OUTPUT);

  gyro.initialisation();
  //  Serial.begin(9600);
  Serial.println("MPU6050 Test");
  delay(2500);

}

void loop() {
  accel();

}

void accel()

{
  Serial.print("AcX = ");
  Serial.print(gyro.refresh('A', 'X'));           // Ask for the X axis of the Accelerometer and print it


  Serial.print(" | AcY = ");
  Serial.print(gyro.refresh('A', 'Y'));           // Ask for the Y axis of the Accelerometer and print it


  if (gyro.refresh('A', 'Y') > 0)
  {
    //digitalWrite(ledPin, HIGH);
    forward(gyro.refresh('A', 'Y'), (gyro.refresh('A', 'Z') - 30) );
    
    if ((gyro.refresh('A', 'Z') - 30) > 50)
    {
      rightTurn((gyro.refresh('A', 'Z') - 30));
    }
    else if ((gyro.refresh('A', 'Z') - 30) < -50)
    {
      leftTurn((gyro.refresh('A', 'Z') - 30));
    }
  }
  else
  {
    //digitalWrite(ledPin, LOW);
    reverse(gyro.refresh('A', 'Y'), (gyro.refresh('A', 'Z') - 30));
    if ((gyro.refresh('A', 'Z') - 30) > 50)
    {
      rightTurn((gyro.refresh('A', 'Z') - 30));
    }
    else if ((gyro.refresh('A', 'Z') - 30) < -50)
    {
      leftTurn((gyro.refresh('A', 'Z') - 30));
    }
  }

  Serial.print(" | AcZ = ");
  Serial.println(gyro.refresh('A', 'Z') - 30);           // Ask for the Z axis of the Accelerometer and print it

  delay(25);

}

void reverse(int l, int m)
{
  digitalWrite(RPin1, HIGH);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, HIGH);
  digitalWrite(LPin2, LOW);
  analogWrite(enableR, 50 - l*2);
  analogWrite(enableL, 50 - l*2);
}

void forward(int i, int j)
{
  digitalWrite(RPin1, LOW);
  digitalWrite(RPin2, HIGH);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, HIGH);
  analogWrite(enableR, 50 + i*2);
  analogWrite(enableL, 50 + i*2);
}

void rightTurn(int p)  
{
  digitalWrite(RPin1, LOW);
  digitalWrite(RPin2, HIGH);
  digitalWrite(LPin1, HIGH);
  digitalWrite(LPin2, LOW);
  analogWrite(enableR, p*2);
  analogWrite(enableL, p*2);
}

void leftTurn(int r)  
{
  digitalWrite(RPin1, HIGH);
  digitalWrite(RPin2, LOW);
  digitalWrite(LPin1, LOW);
  digitalWrite(LPin2, HIGH);
  analogWrite(enableR, -r*2);
  analogWrite(enableL, -r*2);
}
