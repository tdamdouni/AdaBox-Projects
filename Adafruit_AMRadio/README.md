# Adafruit_AMRadio
AM radio-transmit from M0 microcontrollers: Circuit Playground Express (not 'classic'), Feather M0, Arduino Zero, etc. Requires latest Adafruit_ZeroDMA library.

Connect antenna to pin A0 (a gator-clip jumper wire works fine). Tune receiver to lower frequencies in AM band (examples use 540 KHz by default). **RANGE IS LIMITED TO A FEW INCHES**, so don't take this too seriously, simply a fun science project kind of thing. A proper antenna for this frequency would be impractically long, *hundreds* of feet, and transmit power from the microcontroller pin is extremely limited anyway.

Tutorial is located here:
https://learn.adafruit.com/circuit-playground-express-dac-hacks

Uses Timer/Counter 5 and DAC. Speaker output will be disabled. DMA driven; interrupts, delay() and millis(), NeoPixels, etc. are all available.
