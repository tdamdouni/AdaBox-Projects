// -------------------------------------------------------------------------
// DMA-driven AM radio-transmit audio library for M0 microcontrollers
// (Circuit Playground Express, Feather M0, Arduino Zero, etc.).
// Gator-clip antenna to pin A0. Tune receiver to lower frequencies in AM
// band (examples use 540 KHz by default).
//
// Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
// Adafruit invests time and resources providing this open source code,
// please support Adafruit and open-source hardware by purchasing
// products from Adafruit!
//
// MIT license, all text above must be included in any redistribution
// -------------------------------------------------------------------------

#ifndef _ADAFRUIT_AMRADIO_H_
#define _ADAFRUIT_AMRADIO_H_

#include <Adafruit_ZeroDMA.h>

class Adafruit_AMRadio {
 public:
  Adafruit_AMRadio();
  boolean begin(uint32_t freq=540000); // 510000+
  void    write(uint16_t n);           // 0-1023
  void    tone(uint16_t freq, uint32_t msec, uint16_t vol=1023);
 private:
  uint16_t         carrier[2];         // Square wave; 2 elements, hi & low
  Adafruit_ZeroDMA dma;
};

#endif // _ADAFRUIT_AMRADIO_H_
