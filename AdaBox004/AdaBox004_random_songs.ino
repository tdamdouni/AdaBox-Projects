// Specifically for use with the Adafruit Feather, the pins are pre-set here!
// modified feather_player example for AdaBox 004 project
// standalone player that plays random songs from playlist
// stripped out unused code
// had trouble getting file name string to work converting String type
// since function call for playing uses char array
// after trying different approaches this is the kludge I came up with
// tracks are named TRACK##.mp3
// I have 60 songs on SD card I"m using (000 - 059)
// would have been smarter to count # of files or find some other way to get file name randomly
// Oh well next time

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// These are the pins used
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)
// Feather ESP8266 -- using HUZZAH featther
#define VS1053_CS      16     // VS1053 chip select pin (output)
#define VS1053_DCS     15     // VS1053 Data/command select pin (output)
#define CARDCS          2     // Card chip select pin
#define VS1053_DREQ     0     // VS1053 Data request, ideally an Interrupt pin
#define VOLUME_KNOB    A0

int lastvol = 10;
int loopcounter = 0;
long trackNumber;
String trackString;
char song[13] = {'T','R', 'A', 'C', 'K', '0', '2', '0', '.', 'm', 'p', '3','\0'};

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

void setup() {
//  Serial.begin(115200); // only needed for trouble shooting
//  while (!Serial) { delay(1); } // Wait for serial port to be opened,
//  Serial.println("\n\nAdafruit VS1053 Feather Test");
  
  randomSeed(ESP.getCycleCount()); // HUZZAH has only 1 analog pin which is already used
                                   // needed different random seed
                                   // this idea from https://github.com/esp8266/Arduino/issues/728
  musicPlayer.begin();
  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
  SD.begin(CARDCS);

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(lastvol,lastvol);
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void loop() {

  // check periodically to adjust volume!
  loopcounter++;
  if (loopcounter >= 1000) {
        loopcounter = 0;
        int vol = 0;
        vol = analogRead(VOLUME_KNOB);
        vol /= 10;
        if (abs(vol - lastvol) > 3) {
//          Serial.println(vol);
          lastvol = vol;
          musicPlayer.setVolume(lastvol, lastvol);
        }
      }  

  // Play a file in the background, REQUIRES interrupts!
  if (! musicPlayer.playingMusic) { 
    trackNumber = random(6); // have to do this one digit at a time; first digit 0-5
    char c = char(trackNumber + 48);  // ASCII 48 is '0'; need to shift value to get right character
    song[6] = c; // replace the tens value in the char array
    trackNumber = random(10); // second digit 0-9
    c= char(trackNumber + 48);
    song[7] = c;   
//    Serial.println(song);
    musicPlayer.startPlayingFile(song);
    delay(10);
  }
}




