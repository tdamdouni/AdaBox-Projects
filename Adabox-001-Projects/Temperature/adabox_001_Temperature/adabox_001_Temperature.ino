/*
 This project uses code examples learned from Adafruit Tutorials
 https://learn.adafruit.com/tmp36-temperature-sensor
 https://learn.adafruit.com/character-lcds
 
  LCD Wiring
 * LCD RS pin to digital pin 6
 * LCD Enable pin to digital pin 5
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 * TMP36 wiring
 * Left to 3.3V
 * Middle to Anolog 0
 * Right to ground
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(6, 5, 9, 10, 11, 12);

//TMP36 Pin Variables
int sensorPin = 0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures

 
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Display Temperature is
   lcd.print("Temperature is") ;
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  //getting the voltage reading from the temperature sensor
 int reading = analogRead(sensorPin);  

  // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 3.3;
 voltage /= 1024.0; 
 
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

 // Display temperature in F
 lcd.print(temperatureF); lcd.print(" degrees F");

  delay(1000);                                     //waiting a second
}

