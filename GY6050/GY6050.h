/*
  Header file of the « GY6050 » library
  for the MPU6050.
  
  Coded and debugged by Frédéric Druppel.
*/

#ifndef GY6050_h
#define GY6050_h

#include "Arduino.h"

class GY6050
{
  public:
    GY6050(int address1);
    void initialisation();
    int refresh(char device, char axis);
  private:
    int address;
    int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
};

#endif
