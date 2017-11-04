/*
  Main part of the « GY6050 » library 
  for the MPU6050
  
  Coded and debugged by Frédéric Druppel.
*/


#include "Arduino.h"
#include "GY6050.h"
#include "Wire.h"

//const int MPU = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


GY6050::GY6050(int address1)
{
  address = address1;
}


void GY6050::initialisation()
{
  
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

int GY6050::refresh(char device, char axis)
{
  Wire.beginTransmission(address);
  Wire.write(0x3B);                // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(address, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  if (device == 'A' && axis == 'X')
  {
    return (map(AcX, -16000, 17000, -90, 90));
  }
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  if (device == 'A' && axis == 'Y')
  {
    return (map(AcY, -16600, 16400, -90, 90));
  }
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  if (device == 'A' && axis == 'Z')
  {
    return (map(AcZ, -17700, 16000, -90, 90));
  }
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  if (device == 'T' && axis == 'C')
  {
    return (Tmp / 340.00 + 36.53);
  }
  if (device == 'T' && axis == 'F')
  {
    return ((Tmp / 340.00 + 36.53) * 9 / 5 + 32);
  }
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  if (device == 'G' && axis == 'X')
  {
    return (map(GyX, -30101, 29900, -100, 101));
  }
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  if (device == 'G' && axis == 'Y')
  {
    return (map(GyY, -30010, 29990, -100, 100));
  }
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  if (device == 'G' && axis == 'Z')
  {
    return (map(GyZ, -30055, 29945, -100, 101));
  }
}
