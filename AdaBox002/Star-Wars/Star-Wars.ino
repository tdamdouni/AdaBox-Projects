#include "pitches.h"  //sets up program to recognize the pitches.h tab

// notes in the melody Darth Vader's Theme Song
 int melody1[] = {
   NOTE_G4, NOTE_G4,NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_AS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, 0, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_FS4, NOTE_AS4, NOTE_G4, NOTE_AS4, NOTE_D5, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, 0, NOTE_GS4, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, 0, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4 };
// note durations for Darth Vader's Theme Song: 4 = quarter note, 8 = eighth note, etc.:
 int noteDurations1[] = {
   4, 4, 4, 6, 16, 4, 6, 16, 2, 4, 4, 4, 6, 16, 4, 6, 16, 2, 4, 6, 16, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 4, 6, 16, 2, 4, 6, 16, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 16, 16, 8, 8, 8, 4, 6, 16, 4, 6, 16, 2,};
 // Notes in the melody Cantina Band
 int melody2[] = {
 NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4, NOTE_A4, 0, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_G4, 0, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_F4, NOTE_D4, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4, NOTE_A4, 0, NOTE_G4, 0, NOTE_G4, NOTE_FS4, NOTE_G4, 0, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, 0, NOTE_D5, 0, NOTE_A4, NOTE_D5, 0, NOTE_A4, 0, 0, NOTE_GS4, NOTE_A4, 0, NOTE_C5,0, 0, NOTE_C5, NOTE_A4, NOTE_G4, 0, NOTE_F4, NOTE_D4, NOTE_D4, NOTE_F4, NOTE_A4, NOTE_C5, NOTE_DS5, NOTE_D5, NOTE_GS4, NOTE_A4, 0, NOTE_F4, 0};
 // note duration for Cantina Band
 int noteDurations2[] = {
 4, 64, 4, 64, 4, 64, 4, 64, 8, 4, 64, 8, 64, 8, 8, 4, 64, 8, 8, 8, 8, 8, 8, 8, 8, 2.666, 1.99, 4, 64, 4, 64, 4, 64, 4, 64, 8, 4, 64, 8, 64, 8, 8, 4, 64, 8, 8, 2.666, 8, 4, 64, 8, 4, 4, 2.666, 4, 64, 4, 64, 4, 64, 4, 64, 8, 4, 64, 8, 64, 8, 8, 4, 64, 8, 64, 8, 2.666, 8, 4, 64, 2.666, 1.99, 2, 2, 2, 2, 4, 4, 8, 4, 64, 4, 2};
// Notes in the melody Love Theme: Anakin and Padme
int melody3[] = {
  NOTE_A4, NOTE_F5, NOTE_D5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_F5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_A5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_AS5, NOTE_AS5, NOTE_G5, NOTE_C6, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_A5, NOTE_D6, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_G4 };
// note duration for Love Theme
int noteDurations3[] = {
  2, 1.3, 2, 3, 3, 3, 2, 2, 3, 3, 3, 2, 2, 1, 2, 1, 2, 1, 2, 3, 3, 3, 2, 2, 2, 1, 1, 2, 1.6, 4, 4, 4, 3, 3, 3, 2, 2, 1.6, 4, 4, 4, 4, 4, 2, 2, 1.6, 4, 4, 4, 3, 3, 3, 2, 2, 1.6, 4, 4, 4, 4, 4, 1};
// notes in the melody Duel of the Fates
int melody4[] = {
  NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3, NOTE_F3, NOTE_G3, NOTE_F3, NOTE_DS3, NOTE_D3, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B3, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B3, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, 0, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, 0, NOTE_DS4, NOTE_E4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4 };
// note duration for Duel of the Fates
int noteDurations4[] = {
  8, 8, 16, 16, 8, 8, 8, 16, 16, 8, 8, 8, 16, 16, 8, 8, 8, 16, 16, 8, 8, 8, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4, 4, 8, 8, 1};
// notes in melody May the Force be with You
int melody5[] = {
 NOTE_G3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_DS4, NOTE_G3, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_G3, NOTE_DS4, NOTE_C4, NOTE_G4, NOTE_F4, 0, NOTE_G3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_G3, NOTE_G4, NOTE_DS4, NOTE_C5, NOTE_C4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_DS4, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_G3, NOTE_C4, 0 };
// Note duration for May the Force Be with You
int noteDurations5[] = {
  2, 1, 1.333, 8, 8, 1, 1.333, 4, 1.333, 4, 4, 4, 3, 3, 3, 1, 2, 2, 1.333, 4, 1.333, 8, 1.333, 8, 1, 2, 3, 3, 3, 1.2, 3, 3, 2, 1.333, 8, 1, 2 };

int buzzer = A1;  // hooks up the buzzer to pin 8

void setup() {
Serial.begin(9600); 
pinMode(buzzer, OUTPUT);  // sets the buzzer as an output
}

void loop()  {
  for (int thisNote = 0; thisNote < 59; thisNote++) {  // for the 59 notes being played... this is what happens
    int noteDuration4 = 1000/noteDurations4[thisNote];  // sets up the note duration for Duel of the Fates
    tone(buzzer, melody4[thisNote],noteDuration4);  // tells the buzzer to play Duel of the Fates
    int pauseBetweenNotes4 = noteDuration4 * 1.40;  // sets the tempo
    delay(pauseBetweenNotes4);  // pauses the buzzer
    noTone(buzzer); // stops the buzzer
  }
  for (int thisNote = 0; thisNote < 70; thisNote++) {  // for 70 notes... this is what happens
    int noteDuration1 = 1000/noteDurations1[thisNote];  // sets up note duration for Darth Vader's Theme
    tone(buzzer, melody1[thisNote],noteDuration1);  // tells the buzzer to play Darth Vader's Theme
    int pauseBetweenNotes = noteDuration1 * 1.60;  // sets the tempo for the song
    delay(pauseBetweenNotes);  // pauses the buzzer
    noTone(buzzer);  // stops the buzzer playing
  }
  for (int thisNote = 0; thisNote < 36; thisNote++) {  // for 36 notes this is what happens
    int noteDuration5 = 1000/noteDurations5[thisNote];  // defines the note duration for may the force be with you
    tone(buzzer, melody5[thisNote],noteDuration5);  // tells the buzzer to play may the force be with you
    int pauseBetweenNotes5 = noteDuration5 * 1.1;  // sets the tempo
    delay(pauseBetweenNotes5);  //pauses the buzzer
    noTone(buzzer);  // stops the buzzer
  }
  for (int thisNote = 0; thisNote < 91; thisNote++) {  // for 91 notes, this is what happens
    int noteDuration2 = 1000/noteDurations2[thisNote];  // defines note duration for cantina band
    tone(buzzer, melody2[thisNote],noteDuration2);  // tells the  buzzer to play the cantina band melody
    int pauseBetweenNotes2 = noteDuration2 * 0.80; // sets the tempo
    delay(pauseBetweenNotes2);  //pauses the buzzer
    noTone(buzzer);  // stops the buzzer playing
  }
  for (int thisNote = 0; thisNote < 61; thisNote++) {  // for 61 notes this is what happens
    int noteDuration3 = 1000/noteDurations3[thisNote];  // defines note duration for love theme
    tone(buzzer, melody3[thisNote],noteDuration3);  // tells the buzzer to play love theme
    int pauseBetweenNotes3 = noteDuration3 * 1.10;  // sets the tempo
    delay(pauseBetweenNotes3);  // pauses the buzzer
    noTone(buzzer);  // stops the buzzer
   }                                                                                                                                                                                   
}
