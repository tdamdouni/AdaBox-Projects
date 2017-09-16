#include <string.h>
#include <Arduino.h>
#include <SPI.h>

#include "pitches.h"
#include "extra.h"

int speaker = A1; 

void setup(void)
{
  pinMode(speaker, OUTPUT);
}

void loop(void)
{
    HesAPirate();
}
     
void HesAPirate(){
  for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
    int wait = duration[i] * songspeed;
    tone(speaker,notes[i],wait);          //tone(pin,frequency,duration)
    delay(wait);
  }
}
