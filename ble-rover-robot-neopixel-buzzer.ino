/*********************************************************************
 This is an example for our nRF51822 based Bluefruit LE modules

 Modified to drive a 3-wheeled BLE Robot Rover! by http://james.devi.to

 https://forums.adafruit.com/viewtopic.php?f=59&t=115676&p=577872&hilit=adabox+002#p577872

 Pick one up today in the Adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_)
  #include <SoftwareSerial.h>
#endif
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIN 6
#define NUMPIXELS 24
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(NUMPIXELS, NEOPIN);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

//Name your RC here
String BROADCAST_NAME = "AndyBot";

String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

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

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

char buf[60];

// Set your forward, reverse, and turning speeds
#define ForwardSpeed                255
#define ReverseSpeed                255
#define TurningSpeed                100


/**************************************************************************/
/*!
    @brief  Sets up the HW and the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
//NeoPixel setup
#define NEOPIN 6
#define NUMPIXELS 24
//Color
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    uint8_t animationState = 1;

void setup(void)
{
  Serial.begin(9600);

  AFMS.begin();  // create with the default frequency 1.6KHz

  // turn on motors
  L_MOTOR->setSpeed(0);
  L_MOTOR->run(RELEASE);

  R_MOTOR->setSpeed(0);
  R_MOTOR->run(RELEASE);

  Serial.begin(115200);
  Serial.println(F("Adafruit Bluefruit Robot Controller Example"));
  Serial.println(F("-----------------------------------------"));

  /* Initialize the module */
  BLEsetup();

  pinMode(speaker, OUTPUT);

  //setup the neopixel ring
  pixel.begin();
  pixel.setBrightness(128); //medium brightness
  for(uint8_t i=0; i<NUMPIXELS; i++) {
    pixel.setPixelColor(i, pixel.Color(0,0,0)); // off
  }
  colorWipe(pixel.Color(100, 100, 100), 20);
  colorWipe(pixel.Color(0, 0, 0), 20);
  pixel.show();

}

int melod[] = {tonec, toneG, toneE, toneA, toneB, toneBb, toneA, toneG, tonee, toneg, tonea, tonef, toneg, tonee, tonec, toned, toneB};
int ritmo[] = {18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6};

void loop(void)
{

    //Set your motor speed
  int reading  = analogRead(A0);
  L_MOTOR->setSpeed(map(reading, 0, 1023, 0, 255));
  R_MOTOR->setSpeed(map(reading, 0, 1023, 0, 255));

  // read new packet data
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);

  readController();

  //color picker for NeoPixel ring
  if(packetbuffer[1]== 'C') {
    uint8_t red = packetbuffer[2];
    uint8_t green = packetbuffer[3];
    uint8_t blue = packetbuffer[4];
    for(int i=0; i<NUMPIXELS;i++){
      pixel.setPixelColor(i, pixel.Color(red,green,blue));
    }
    pixel.show();
  }

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixel.numPixels(); i++) {
      pixel.setPixelColor(i, c);
      pixel.show();
      delay(wait);
  }
}

// This wheel command is needed for the rainbow button
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
//rainbow
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixel.numPixels(); i++) {
      pixel.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixel.show();
    delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < pixel.numPixels(); i=i+3) {
        pixel.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixel.show();

      delay(wait);

      for (int i=0; i < pixel.numPixels(); i=i+3) {
        pixel.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

bool isMoving = false;
unsigned long lastPress = 0;

bool readController(){
  uint8_t maxspeed;

 // Buttons
  if (packetbuffer[1] == 'B') {

    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    if (pressed) {
      if(buttnum == 1){
        if (hasplayed == true){ return;}
          for (int i=0; i<17; i++) {
            int tom = melod[i];
            int tempo = ritmo[i];

            long tvalue = tempo * vel;

            tocar(tom, tvalue);

            delayMicroseconds(1000);
            }      //delay(1000);


      }

      if(buttnum == 2){

      }

      if(buttnum == 3){
        for(uint16_t i=0; i<pixel.numPixels(); i++) {
      pixel.setPixelColor(i, pixel.Color(0,0,0));
    }
    pixel.setBrightness(50);
    rainbow(10);
    pixel.show(); // This sends the updated pixel color to the hardware.
      }

      if(buttnum == 4){
      for(uint16_t i=0; i<pixel.numPixels(); i++) {
      pixel.setPixelColor(i, pixel.Color(0,0,0));
    }
    pixel.setBrightness(50);
    theaterChaseRainbow(10);
    pixel.show(); // This sends the updated pixel color to the hardware.
      }

      if(buttnum == 5){
        isMoving = true;
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(FORWARD);
        maxspeed = ForwardSpeed;
      }

      if(buttnum == 6){
        isMoving = true;
        L_MOTOR->run(BACKWARD);
        R_MOTOR->run(BACKWARD);
        maxspeed = ReverseSpeed;
      }

      if(buttnum == 7){
        isMoving = true;
        L_MOTOR->run(RELEASE);
        R_MOTOR->run(FORWARD);
        maxspeed = TurningSpeed;
      }

      if(buttnum == 8){
        isMoving = true;
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(RELEASE);
        maxspeed = TurningSpeed;
      }

      lastPress = millis();

      // speed up the motors
      for (int speed=0; speed < maxspeed; speed+=5) {
        L_MOTOR->setSpeed(speed);
        R_MOTOR->setSpeed(speed);
        delay(5); // 250ms total to speed up
      }
  } else {
      isMoving = false;
      // slow down the motors
      for (int speed = maxspeed; speed >= 0; speed-=5) {
        L_MOTOR->setSpeed(speed);
        R_MOTOR->setSpeed(speed);
        delay(5); // 50ms total to slow down
      }
      L_MOTOR->run(RELEASE);
      R_MOTOR->run(RELEASE);
    }
}
}

void BLEsetup(){
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }

  //Convert the name change command to a char array
  BROADCAST_CMD.toCharArray(buf, 60);

  //Change the broadcast device name here!
  if(ble.sendCommandCheckOK(buf)){
    Serial.println("name changed");
  }
  delay(250);

  //reset to take effect
  if(ble.sendCommandCheckOK("ATZ")){
    Serial.println("resetting");
  }
  delay(250);

  //Confirm name change
  ble.sendCommandCheckOK("AT+GAPDEVNAME");

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
  Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("*****************"));

  // Set Bluefruit to DATA mode
  Serial.println( F("Switching to DATA mode!") );
  ble.setMode(BLUEFRUIT_MODE_DATA);

  Serial.println(F("*****************"));
}

void tocar(int tom, long tempo_value) {
  long tempo_gasto = 0;
  while (tempo_gasto < tempo_value) {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(tom / 2);

    digitalWrite(speaker, LOW);
    delayMicroseconds(tom/2);
    tempo_gasto += tom;
  }

}
