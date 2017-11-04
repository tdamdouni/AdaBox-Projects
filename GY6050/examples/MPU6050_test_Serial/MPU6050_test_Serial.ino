/*
  This sketch allows you to read raw data
  from your MPU6050 multifunctionnal
  accelerometer, compute it and write
  them to the Serial monitor.

  Connect "SDA" from your accelerometer to
  analog pin 4 of the Arduino (other than Mega),
  or where it's marked as "SDA" (Rev.3 of Arduino boards).
  Connect "SDCL" from your accelerometer to
  analog pin 5 of the Arduino (other than Mega),
  or where it's marked as "SCL" (Rev.3 of Arduino boards).

  Sketch & Library written
  by Frederic Druppel
*/



#include <Wire.h>
#include <GY6050.h>


GY6050 gyro(0x68);                            // Create Gyro object with "0x68" as I2C addres (most likely the address of your MPU6050)


void setup()                                  // Main setup
{
  gyro.initialisation();
  Serial.begin(9600);
  Serial.println("MPU6050 Test");
  delay(2500);
}
void loop()                                  // Main loop
{
  Serial.print("AcX = ");
  Serial.print(gyro.refresh('A', 'X'));           // Ask for the X axis of the Accelerometer and print it
  Serial.print(" | AcY = ");
  Serial.print(gyro.refresh('A', 'Y'));           // Ask for the Y axis of the Accelerometer and print it
  Serial.print(" | AcZ = ");
  Serial.print(gyro.refresh('A', 'Z'));           // Ask for the Z axis of the Accelerometer and print it
  Serial.print(" | Tmp = ");
  Serial.print(gyro.refresh('T', 'C'));           // Ask for the Temperature in Celsius and print it
  Serial.print(" C | ");
  Serial.print(gyro.refresh('T', 'F'));           // Ask for the Temperature in Farenheit and print it
  Serial.print(" F");
  Serial.print(" | GyX = ");
  Serial.print(gyro.refresh('G', 'X'));           // Ask for the X axis of the Gyroscope and print it
  Serial.print(" | GyY = ");
  Serial.print(gyro.refresh('G', 'Y'));           // Ask for the Y axis of the Gyroscope and print it
  Serial.print(" | GyZ = ");
  Serial.println(gyro.refresh('G', 'Z'));         // Ask for the Z axis of the Gyroscope and print it, then carriage return
  delay(25);
}
