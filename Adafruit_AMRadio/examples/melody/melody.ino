// Example for Adafruit_AMRadio library -- plays the Jeoparty theme on AM 540.
// Connect antenna to pin A0 (a gator-clip jumper wire works OK).
// RANGE IS LIMITED TO A FEW INCHES, so don't take this too seriously,
// simply a fun science project kind of thing!  Adapted from by PyroPeter's
// "Jeopardy" sketch, in turn from Tom Igoe's "toneMelody" example.

#include <Adafruit_AMRadio.h>
#include "pitches.h" // Lets us refer to notes by name

Adafruit_AMRadio radio;

void setup() {
  radio.begin(540000);
}

// Notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3,
  NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_CS4,
  NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F3,
  NOTE_C4, NOTE_F4, NOTE_C4,
  NOTE_F4, 0, NOTE_D4, NOTE_C4, NOTE_AS3,
  NOTE_A3, NOTE_G3, NOTE_F3 };

// Note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4,    4,    4,    4,
  4,    4,          2,
  4,    4,    4,    4,
  3,    8, 8, 8, 8, 8,
  4,    4,    4,    4,
  4,    4,          2,
  4, 8, 8,    4,    4,
  4,    4,    2,
  0 };

void loop() {
  for(uint8_t n=0; noteDurations[n]; n++) {

    // Note duration is 1 second divided by the note type,
    // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[n];
    radio.tone(melody[n], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    // Half the note's duration seems to work well:
    delay(noteDuration / 2);
  }
  delay(500);
}
