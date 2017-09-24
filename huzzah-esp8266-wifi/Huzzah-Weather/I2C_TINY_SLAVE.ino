/*
  I2C_TINY_SLAVE - Sketch for intercaing with I2C master from ATTiny85 as a I2C slave device.
  Created by Gaetano, September 27, 2016.
  Released into the public domain.
*/



#include <TinyWireS.h>


const byte I2C_SLAVE_ADDR = 0x05;//I2C slave addresse

const byte ADC_PIN = PB3; //PB3

uint8_t i2c_value = 0;
int adc_value = 0;


void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDR);                //als slave mit adresse 0x05 starten
  TinyWireS.onRequest(requestEvent); // register event
  pinMode(ADC_PIN,INPUT);
}

void loop() {
  //loop bleibt leer, wartet nur auf den i2c interrupt
}

void requestEvent() {   //i2c event
  TinyWireS.send(getAdcValue(ADC_PIN)); 
}

uint8_t getAdcValue(const byte PIN){  //funktion um windfane auszulesen
    adc_value = analogRead(PIN);
  i2c_value = map(adc_value, 0, 1023, 0, 255);
  if (i2c_value <= 31) return (1); //Norden
  if (i2c_value <= 63 && i2c_value >31) return (2); //Nordosten
  if (i2c_value <= 96 && i2c_value > 63) return (3); //Osten
  if (i2c_value <= 127 && i2c_value > 96) return (4);//Südosten
  if (i2c_value <= 159 && i2c_value > 127) return (5);//Süden
  if (i2c_value <= 191 && i2c_value > 159) return (6);//Südwesten
  if (i2c_value <= 223 && i2c_value > 191) return (7);//Westen
  if (i2c_value <= 255 && i2c_value > 223) return (8);//Nordwesten
  else 
  return(255);//nicht verbunden?
}
