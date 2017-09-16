// Example for Adafruit_AMRadio library -- transmits Godzilla sounds on
// AM 540. Connect antenna to pin A0 (a gator-clip jumper wire works OK). 
// RANGE IS LIMITED TO A FEW INCHES, so don't take this too seriously,
// simply a fun science project kind of thing!

#include <Adafruit_AMRadio.h>
#include "zilla.h" // Audio data is in a table in this file

Adafruit_AMRadio radio;

void setup() {
  radio.begin(540000);
}

// Plays back audio stored in PROGMEM array
void play(const uint8_t *data, uint32_t len, uint16_t sampleRate,
  boolean tenBit) {

  uint32_t i;
  uint32_t r2 = sampleRate / 2;
  uint32_t startTime = micros();

  if(tenBit) { // 10-bit audio samples?
    uint8_t loIdx = 4;
    uint32_t idx = 0;
    uint16_t hiBits;
    for(i=0; i<len; i++) {
      if(++loIdx >= 4) {
        hiBits = (uint16_t)pgm_read_byte(&data[idx++]);
        loIdx  = 0;
      }
      hiBits <<= 2; // Do this before write, because of masking op below
      radio.write((hiBits & 0x300) | pgm_read_byte(&data[idx++]));
      while(((micros()-startTime+50)/100) < ((i*10000UL+r2)/sampleRate));
    }
  } else { // 8-bit audio samples
    for(i=0; i<len; i++) {
      radio.write((pgm_read_byte(&data[i]) * 257) >> 6);
      while(((micros()-startTime+50)/100) < ((i*10000UL+r2)/sampleRate));
    }
  }
  radio.write(512);
}

void loop() {
  play(zillaAudioData, zillaSamples, zillaSampleRate, false);
  delay(250);
}
