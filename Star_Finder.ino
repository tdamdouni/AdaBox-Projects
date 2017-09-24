// This project is design to monitor the movement of the Sun (during day time) and Moon (during night time) on the celestial sphere, recording the bearing and altitude
// for the calculation of the position of the observer. 
// The project is using a photo resistor which senses the highest light intensity and records the position of the two servo motors.
// The servo motors sweep the photo resistor across the sky and when the maximum light intensity is sensed the position of the servo motors is recorded on the LCD.
// The project is design to be fun, easy, cheap and "help navigators find their way" :P.


#include <Servo.h>
#include <LiquidCrystal.h>

int servoPin1=10;  //Declare pin 10 as servoPin1
int servoPin2=11;  //Declare pin 11 as servoPin2
int pos1=90;       //Default/calibration position for horizontal servo
int pos2=90;       //Default/calibration position for vertical servo
int servoDelay=25;
int pinButton=12;  //Declare pin 12 as pinButton

int rezPin=A0;     //Declare int variable rezPin as pin A0
int analogValue;    //Declare valoareArduino as an int - values read from the A0 pin
int minimValue=1023;   //The minimum analogValue read
int currentValue;   //The current analogValue read
int buttonStatus;   //Variable for the state of the button

Servo horizontal;
Servo vertical;
LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  Serial.begin(9600);           //Start serial communication
  horizontal.attach(servoPin1); 
  vertical.attach(servoPin2);
  lcd.begin(16,2);              //Declare LCD
  lcd.setCursor(0,0);           
  lcd.print("Star finder");     //Print on the LCD
  lcd.setCursor(0,1);
  lcd.print("Hello Sky");     //Print on the LCD
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("                ");
  pinMode(rezPin,INPUT);    //Declare rezPin as an INPUT pin

}
void loop() {

buttonStatus=digitalRead(pinButton);        //Read the state of the button
if(buttonStatus==HIGH){                     // If button is pressed (HIGH)

 for(int i=20; i<=170; i=i+2){              
  pos1=i;
  horizontal.write(pos1);                   //horizontal servo takes positions from 30 to 150 degrees
  delay(servoDelay);
    for (int j=90; j<=170; j=j+2){          //vertical servo takes positions from 90 to 170 degrees
      pos2=j;
      vertical.write(pos2);
      delay(servoDelay);
      analogValue=analogRead(rezPin);       //Assigne analogValue the value read from the A0
currentValue=analogValue;                   //analogValue becomes currentValue
  lcd.setCursor(0,0);
  lcd.print("Pos:BRG=");
  lcd.print(i);
  lcd.print("/H=");
  lcd.print(j-90);
if( currentValue<=minimValue){            // if currentValue smaller than minimValue (first time is 1023) make currentValue=minimumValue
  minimValue=currentValue;

  lcd.setCursor(0,1);
  lcd.print("BRG=");
  lcd.print(i);
  lcd.print(" /// H=");
  lcd.print(j-90);
  Serial.print(minimValue);
  Serial.print("// BRG=");
  Serial.println(i);
  Serial.print(" Altitude=");
  Serial.println(j);
}
    }
    for (int j=170; j>=90; j=j-2){          //vertical servo takes positions from 170 to 90 degrees
      pos2=j;
      vertical.write(pos2);
      delay(servoDelay);
      analogValue=analogRead(rezPin);       // read again the analogValue from the A0 pin
currentValue=analogValue;                   // set currentValue=analogValue
  lcd.setCursor(0,0);
  lcd.print("Pos:BRG=");
  lcd.print(i);
  lcd.print("/H=");
  lcd.print(j-90);
  
if( currentValue<=minimValue){  
  minimValue=currentValue;

  lcd.setCursor(0,1);
  lcd.print("BRG=");
  lcd.print(i);
  lcd.print(" /// H=");
  lcd.print(j-90);
  Serial.print(minimValue);
  Serial.print("// BRG=");
  Serial.println(i);
  Serial.print(" Altitude=");
  Serial.println(j);
}
    }
 }
  minimValue=1023;
  
 for(int i=170; i>=20; i=i-2){          //Horizontal sevo takes position from 150 to 30 degrees
  pos1=i;
  horizontal.write(pos1);
  delay(servoDelay);
      for (int j=90; j<=170; j=j+2){
      pos2=j;
      vertical.write(pos2);
      delay(servoDelay);
      analogValue=analogRead(rezPin);
currentValue=analogValue;
  lcd.setCursor(0,0);
  lcd.print("Pos:BRG=");
  lcd.print(i);
  lcd.print("/H=");
  lcd.print(j-90);
if( currentValue<=minimValue){
  minimValue=currentValue;

  lcd.setCursor(0,1);
  lcd.print("BRG=");
  lcd.print(i);
  lcd.print(" /// H=");
  lcd.print(j-90);
  Serial.print(minimValue);
  Serial.print("// BRG=");
  Serial.println(i);
  Serial.print(" Altitude=");
  Serial.println(j);
  }
    }
    for (int j=170; j>=90; j=j-2){
      pos2=j;
      vertical.write(pos2);
      delay(servoDelay);
      analogValue=analogRead(rezPin);
currentValue=analogValue;
  lcd.setCursor(0,0);
  lcd.print("Pos:BRG=");
  lcd.print(i);
  lcd.print("/H=");
  lcd.print(j-90);
if( currentValue<=minimValue){
  minimValue=currentValue;
  lcd.setCursor(0,1);
  lcd.print("BRG=");
  lcd.print(i);
  lcd.print(" /// H=");
  lcd.print(j-90);
  Serial.print(minimValue);
  Serial.print("// BRG=");
  Serial.println(i);
  Serial.print(" Altitude=");
  Serial.println(j);
}

    }
 }
minimValue=1023;
 }

 else{                            //If button is not pressed both servos take 90 degrees position
  pos1=90;                  
  horizontal.write(pos1);
  pos2=90;
  vertical.write(pos2);
  lcd.setCursor(0,0);             //Print on the LCD message
  lcd.print("Calibrate");
  lcd.setCursor(0,1);
  lcd.print("Press to measure");
 }
}

