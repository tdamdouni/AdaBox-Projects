#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"
#include "pitches.h"
#include "extra.h"

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);

//Name your RC here
String BROADCAST_NAME = "Adafruit Black Robot Rover";

String BROADCAST_CMD = String("AT+GAPDEVNAME=" + BROADCAST_NAME);

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST); 
 
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

/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
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
  
  L_MOTOR->setSpeed(155); 
  R_MOTOR->setSpeed(155);
}

void loop(void)
{
    // read new packet data
    uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);

  readController();
}

bool readController(){

 // Buttons
  if (packetbuffer[1] == 'B') {

    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    // Serial.println(buttnum);

    if (pressed) {
      //Mario Theme Song
      if(buttnum == 1){
        if (hasplayed == true){ return;}
        MarioTheme();
        hasplayed = true;
      }
      
      //Star Wars
      if(buttnum == 2){
        if (hasplayed == true){ return;}
        DuelOfFates();
        DarthVaderTheme();
        hasplayed = true;
      }
      
      //More Star Wars
      if(buttnum == 3){
        if (hasplayed == true){ return;}
        MayTheForceBeWithYou();
        LoveTheme();
        hasplayed = true;
      } 
      
      //More Star Wars and Pirates of the Caribbean
      if(buttnum == 4){
        if (hasplayed == true){ return;}
        Cantina();
        //HesAPirate(); //Can't seem to get this to work at same time as others. Commenting out Star Wars makes this work though
        hasplayed = true;
      }

      if(buttnum == 5){
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(FORWARD);
      }
      
      if(buttnum == 6){
        L_MOTOR->run(BACKWARD);
        R_MOTOR->run(BACKWARD);        
      }
      
      if(buttnum == 7){
        L_MOTOR->run(RELEASE);
        R_MOTOR->run(FORWARD);
      }
      
      if(buttnum == 8){
        L_MOTOR->run(FORWARD);
        R_MOTOR->run(RELEASE);        
      }     
  }
  else {
      L_MOTOR->run(RELEASE);
      R_MOTOR->run(RELEASE);
      hasplayed = false;
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

void MarioTheme(){
  for (int i=0; i<17; i++) {
    int tom = melod[i];
    int tempo = ritmo[i];
    long tvalue = tempo * vel;
    tocar(tom, tvalue);
    delayMicroseconds(1000);
  }
}

void DuelOfFates(){
  for (int thisNote = 0; thisNote < 59; thisNote++) {  // for the 59 notes being played... this is what happens
    int noteDuration4 = 1000/noteDurations4[thisNote];  // sets up the note duration for Duel of the Fates
    tone(speaker, melody4[thisNote],noteDuration4);  // tells the buzzer to play Duel of the Fates
    int pauseBetweenNotes4 = noteDuration4 * 1.40;  // sets the tempo
    delay(pauseBetweenNotes4);  // pauses the buzzer
    noTone(speaker); // stops the buzzer
  }
}

void DarthVaderTheme() {
  for (int thisNote = 0; thisNote < 70; thisNote++) {  // for 70 notes... this is what happens
    int noteDuration1 = 1000/noteDurations1[thisNote];  // sets up note duration for Darth Vader's Theme
    tone(speaker, melody1[thisNote],noteDuration1);  // tells the buzzer to play Darth Vader's Theme
    int pauseBetweenNotes = noteDuration1 * 1.60;  // sets the tempo for the song
    delay(pauseBetweenNotes);  // pauses the buzzer
    noTone(speaker);  // stops the buzzer playing
  }
}

void MayTheForceBeWithYou() {
  for (int thisNote = 0; thisNote < 36; thisNote++) {  // for 36 notes this is what happens
    int noteDuration5 = 1000/noteDurations5[thisNote];  // defines the note duration for may the force be with you
    tone(speaker, melody5[thisNote],noteDuration5);  // tells the buzzer to play may the force be with you
    int pauseBetweenNotes5 = noteDuration5 * 1.1;  // sets the tempo
    delay(pauseBetweenNotes5);  //pauses the buzzer
    noTone(speaker);  // stops the buzzer
  }
}

void LoveTheme(){
  for (int thisNote = 0; thisNote < 61; thisNote++) {  // for 61 notes this is what happens
    int noteDuration3 = 1000/noteDurations3[thisNote];  // defines note duration for love theme
    tone(speaker, melody3[thisNote],noteDuration3);  // tells the buzzer to play love theme
    int pauseBetweenNotes3 = noteDuration3 * 1.10;  // sets the tempo
    delay(pauseBetweenNotes3);  // pauses the buzzer
    noTone(speaker);  // stops the buzzer
   }
}

void Cantina() {
  for (int thisNote = 0; thisNote < 91; thisNote++) {  // for 91 notes, this is what happens
    int noteDuration2 = 1000/noteDurations2[thisNote];  // defines note duration for cantina band
    tone(speaker, melody2[thisNote],noteDuration2);  // tells the  buzzer to play the cantina band melody
    int pauseBetweenNotes2 = noteDuration2 * 0.80; // sets the tempo
    delay(pauseBetweenNotes2);  //pauses the buzzer
    noTone(speaker);  // stops the buzzer playing
  }
}
     
void HesAPirate(){
  for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
    int wait = duration[i] * songspeed;
    tone(speaker,notes[i],wait);          //tone(pin,frequency,duration)
    delay(wait);
  }
}
