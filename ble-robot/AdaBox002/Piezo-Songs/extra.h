//Mario Specific
int melod[] = {tonec, toneG, toneE, toneA, toneB, toneBb, toneA, toneG, tonee, toneg, tonea, tonef, toneg, tonee, tonec, toned, toneB};
int ritmo[] = {18, 18, 18, 12, 12, 6, 12, 8, 8, 8, 12, 6, 12, 12, 6, 6, 6};

//Star Wars Specific
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

//He's a Pirate Specific
const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song

int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};
