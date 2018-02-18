# Distance Alarm System

_Captured: 2018-02-15 at 20:11 from [www.instructables.com](http://www.instructables.com/id/Distance-Alarm-System/)_

## Introduction: Distance Alarm System

A simple device that will trigger an alarm when objects come too close to the Ultrasonic sensor.

## Step 1: Hardware Components

![Picture of Hardware Components](https://cdn.instructables.com/FZD/2NJQ/JBWJYJ1Z/FZD2NJQJBWJYJ1Z.LARGE.jpg)[ ](https://cdn.instructables.com/FZD/2NJQ/JBWJYJ1Z/FZD2NJQJBWJYJ1Z.LARGE.jpg)![Picture of Hardware Components](https://cdn.instructables.com/FN5/E0QA/JBWJYJ21/FN5E0QAJBWJYJ21.MEDIUM.jpg)[ ](https://cdn.instructables.com/FN5/E0QA/JBWJYJ21/FN5E0QAJBWJYJ21.LARGE.jpg)![Picture of Hardware Components](https://cdn.instructables.com/F5J/4LAZ/JBWJYJLS/F5J4LAZJBWJYJLS.MEDIUM.jpg)![Picture of Hardware Components](https://cdn.instructables.com/F8Z/I4PP/JBWJYJLU/F8ZI4PPJBWJYJLU.MEDIUM.jpg)[ ](https://cdn.instructables.com/F8Z/I4PP/JBWJYJLU/F8ZI4PPJBWJYJLU.LARGE.jpg)![Picture of Hardware Components](https://cdn.instructables.com/FRM/VA4N/JBWJYJLW/FRMVA4NJBWJYJLW.MEDIUM.jpg)

Arduino UNO https://goo.gl/Z8dDbH

Ultrasonic Sensor 1LED (generic) https://goo.gl/X4NCqa

1 Buzzer https://goo.gl/6kP83v

1 Resistor 220 ohm https://goo.gl/rGQyWL

1 Breadboard (generic) https://goo.gl/aqdBDr

1 Jumper wires (generic) https://goo.gl/6JrpLz

## Step 2: Connections: HC-SR04 Sensor

![Picture of Connections: HC-SR04 Sensor](https://cdn.instructables.com/FCD/WIX5/JBWJYKUB/FCDWIX5JBWJYKUB.LARGE.jpg)[ ](https://cdn.instructables.com/FCD/WIX5/JBWJYKUB/FCDWIX5JBWJYKUB.LARGE.jpg)![Picture of Connections: HC-SR04 Sensor](https://cdn.instructables.com/F1V/UMF0/JBWJYKV2/F1VUMF0JBWJYKV2.LARGE.jpg)[ ](https://cdn.instructables.com/F1V/UMF0/JBWJYKV2/F1VUMF0JBWJYKV2.LARGE.jpg)

The Sensor VCC connect to the Arduino Board +5V

The Sensor GND connect to the Arduino Board GND

The Sensor Trig connect to the Arduino Board Digital I/O 9

The Sensor Echo connect to the Arduino Board Digital I/O 10

## Step 3: Buzzer and LED

![Picture of Buzzer and LED](https://cdn.instructables.com/F7G/O3AC/JBWJYL4E/F7GO3ACJBWJYL4E.LARGE.jpg)[ ](https://cdn.instructables.com/F7G/O3AC/JBWJYL4E/F7GO3ACJBWJYL4E.LARGE.jpg)

The Buzzer attach to the Breadboard

The Buzzer long leg (+) connect to the Arduino Board Digital 11

The Buzzer short leg (-) connect to the Arduino Board GND

The LED attach to the Breadboard

The Resistor connect to the LED long leg (+)

The Resistor other leg (from LED's long leg) connect to the Arduino Board Digital 13The LED short leg (-) connect to the Arduino Board GND

## Step 4: CODES

const int trigPin = 9;
const int echoPin = 10; 
const int buzzer = 11; 
const int ledPin = 13; 
long duration; 
int distance; 
int safetyDistance; 

void setup() { 
	pinMode(trigPin, OUTPUT); 
	pinMode(echoPin, INPUT); 
	pinMode(buzzer, OUTPUT); 
	pinMode(ledPin, OUTPUT); 
	Serial.begin(9600); } 

void loop() { // Clears the trigPin 
digitalWrite(trigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); 
distance= duration*0.034/2; 
safetyDistance = distance; 
	if (safetyDistance <= 5){ 
	digitalWrite(buzzer, HIGH); 
	digitalWrite(ledPin, HIGH);
		else{ 
			digitalWrite(buzzer, LOW); digitalWrite(ledPin, LOW); } Serial.print("Distance: "); Serial.println(distance); }
