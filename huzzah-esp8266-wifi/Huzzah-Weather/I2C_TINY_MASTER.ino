/*
  I2C_TINY_MASTER - Sketch for interfacing with ATTiny85 as a slave I2C device.
  Created by Gaetano, September 27, 2016.
  Released into the public domain.
*/

#include <Wire.h>

const byte I2C_SLAVE_ADDR = 0x05;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {

  Serial.println(getWindDir());
  delay(100);
}

int getWindDir(){
    Wire.requestFrom(I2C_SLAVE_ADDR, 1);    

  while (Wire.available()) { 
    uint8_t c = Wire.read(); 
  if(c==1) return(0);
  if(c==2) return(45);
  if(c==3) return(90);
  if(c==4) return(135);
  if(c==5) return(180);
  if(c==6) return(225);
  if(c==7) return(270);
  if(c==8) return(315);
  if(c==255) return (-1);
    


}
}

