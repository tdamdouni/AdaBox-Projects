/**
 * NeoClock
 * 
 * Clock using 60 WS2812B/Neopixel LEDs and DS3231 RTC
 * 
 * Libraries needed:
 *   * Adafruit NeoPixel (Library Manager) - Phil Burgess / Paint Your Dragon for Adafruit Industries - LGPL3
 *   * Rtc by Makuna (Library Manager) - Michael C. Miller
 *   * Arduino Timezone Library (https://github.com/JChristensen/Timezone) - Jack Christensen - CC-BY-SA
 *   * Time Library (https://github.com/PaulStoffregen/Time) - Paul Stoffregen, Michael Margolis - LGPL2.1
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif

#include <SoftwareWire.h>  // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

#include <Time.h>        //http://www.arduino.cc/playground/Code/Time
#include <Timezone.h>    //https://github.com/JChristensen/Timezone

#include <EEPROM.h>

//Central European Time (Frankfurt, Paris)
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     //Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       //Central European Standard Time
Timezone CE(CEST, CET);

TimeChangeRule *tcr;        //pointer to the time change rule, use to get the TZ abbrev
time_t utc;

SoftwareWire myWire(8, 9);
RtcDS3231<SoftwareWire> Rtc(myWire);

#define PIN 6

unsigned long lastMillis = millis();
byte dimmer = 0x88;
byte hmark = 0;

byte ohour=0;
byte ominute=0;
byte osecond=0;

boolean fader=true;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(115200);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  Rtc.Begin();

  Rtc.Enable32kHzPin(false);
  Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 

  if (!Rtc.GetIsRunning())
  {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
  }

  if (!Rtc.IsDateTimeValid()) 
  {
      // Common Cuases:
      //    1) the battery on the device is low or even missing and the power line was disconnected
      Serial.println("RTC lost confidence in the DateTime!");
  }

  byte eechk = EEPROM.read(0);
  if(eechk == 0xAA) { //Assume this is our config and not a fresh chip
    dimmer = EEPROM.read(1);
    hmark = EEPROM.read(2);
    fader = EEPROM.read(3);
  }

  timeSync();
}

void calcTime(void) {
  utc = now();
  CE.toLocal(utc, &tcr);
  ohour = hour(utc);
  ominute = minute(utc);
  if(osecond != second(utc)) {
    osecond = second(utc);
    lastMillis = millis();

    if(ominute == 0 && osecond == 0) {
      //Every hour
      timeSync();
    }
  }
}

void addPixelColor(byte pixel, byte color, byte brightness) {
  color *= 8;
  uint32_t acolor = brightness;
  acolor <<= color;
  uint32_t ocolor = strip.getPixelColor(pixel);
  ocolor |= acolor;
  strip.setPixelColor(pixel, ocolor);
}

void drawClock(byte h, byte m, byte s) {  
  strip.clear();
  
  addPixelColor(m, 1, dimmer);

  if(hmark > 0) {
    for(byte i = 0; i<12; i++) {
      addPixelColor((5*i), 2, hmark);
    }
  }

  h %= 12;
  h *= 5;
  h += (m/12);
  addPixelColor(h, 2, dimmer);
  // 0x RR GG BB

  if(fader) {
    byte dim_s1 = dimmer;
    byte dim_s2 = 0;
    byte px_s2 = s+1;
    if(px_s2 >= 60) px_s2 = 0;
    unsigned long curMillis = millis()-lastMillis;
    if(curMillis < 250) {
      dim_s2 = 0;
      dim_s1 = dimmer;
    }else{
      dim_s2 = map(curMillis, 250, 1000, 0, dimmer);
      dim_s1 = dimmer - map(curMillis, 250, 1000, 0, dimmer);
    }
    
    addPixelColor(s, 0, dim_s1);
    addPixelColor(px_s2, 0, dim_s2);
  }else{
    addPixelColor(s, 0, dimmer);
  }
  
  strip.show();
}

byte rounds = 0;

void loop() {
  calcTime();

  if(rounds++ > 100) {
    Serial.print(ohour);
    Serial.print(":");
    Serial.print(ominute);
    Serial.print(":");
    Serial.println(osecond);
    rounds = 0;
  }
  
  drawClock(ohour,ominute,osecond);

  delay(10);
  
  chkSer();
}

void timeSync(void) {
  RtcDateTime dt = Rtc.GetDateTime();
  setTime(dt.Hour(),dt.Minute(),dt.Second(),dt.Day(),dt.Month(),dt.Year());
    
  Serial.print("Synced to: ");
  Serial.print(dt.Year());
  Serial.print("-");
  Serial.print(dt.Month());
  Serial.print("-");
  Serial.print(dt.Day());
  Serial.print("-");
  Serial.print(dt.Hour());
  Serial.print("-");
  Serial.print(dt.Minute());
  Serial.print("-");
  Serial.println(dt.Second());
}

void timeSave(void) {
  utc = now();
  
  RtcDateTime store = RtcDateTime(year(utc), month(utc), day(utc), hour(utc), minute(utc), second(utc));
  Rtc.SetDateTime(store);

  Serial.print("Synced to: ");
  Serial.print(year(utc));
  Serial.print("-");
  Serial.print(month(utc));
  Serial.print("-");
  Serial.print(day(utc));
  Serial.print("-");
  Serial.print(hour(utc));
  Serial.print("-");
  Serial.print(minute(utc));
  Serial.print("-");
  Serial.println(second(utc));
  
}

void setBrightness(byte brightness) {
  dimmer = brightness;
}

void chkSer(void) {
  unsigned int iy;
  byte im,id,iH,iM,iS;
  
  if(!Serial.available()) return;

  switch(Serial.read()) {
    case 'b':
      setBrightness(Serial.parseInt());
      Serial.print(F("Brightness changed to: "));
      Serial.println(dimmer);
      EEPROM.put(0, 0xAA);
      EEPROM.put(1, dimmer);
      break;
    case 't':
      iy = Serial.parseInt();
      im = Serial.parseInt();
      id = Serial.parseInt();
      iH = Serial.parseInt();
      iM = Serial.parseInt();
      iS = Serial.parseInt();
      setTime(iH,iM,iS,id,im,iy);
      Serial.println(F("System time changed"));
      break;
    case 'f':
      fader = false;
      EEPROM.put(0, 0xAA);
      EEPROM.put(3, 0);
      Serial.println(F("Fader off"));
      break;
    case 'F':
      fader = true;
      EEPROM.put(0, 0xAA);
      EEPROM.put(3, 1);
      Serial.println(F("Fader on"));
      break;
    case 'm':
      hmark = Serial.parseInt();
      EEPROM.put(0, 0xAA);
      EEPROM.put(2, hmark);
      Serial.println(F("HMark changed"));
      break;
    case 's':
      timeSync();
      Serial.println(F("Synced RTC to System"));
      break;
    case 'S':
      timeSave();
      Serial.println(F("Synced System to RTC"));
      break;
    default:
      Serial.println('?');
  }
}
