#include <resin.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Buttons on the FeatherWing OLED:
#define BUTTON_A 0
#define BUTTON_B 16
#define BUTTON_C 2

Resin resin;
String applicationUUID = "424605";
String deviceType = "ESP8266";
String split = "_";
String ssid = "resin-hotspot";
String password = "resin-hotspot";

Adafruit_SSD1306 display = Adafruit_SSD1306();

static const unsigned char PROGMEM logosmall[] =
{ B00000000, B00000000,
  B00000011, B11000000,
  B00000111, B11100000,
  B00011110, B11111000,
  B00111100, B01111100,
  B00110000, B00011100,
  B00110000, B00001100,
  B00110110, B00001100,
  B00110111, B00001100,
  B00110111, B00001100,
  B00110011, B00001100,
  B00111100, B00011100,
  B00011110, B01111000,
  B00000111, B11100000,
  B00000011, B11000000,
  B00000000, B00000000 };

static const unsigned char PROGMEM logobig[] =
{ B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000001, B10000000, B00000000,
  B00000000, B00000011, B11000000, B00000000,
  B00000000, B00001111, B11110000, B00000000,
  B00000000, B00111111, B11111100, B00000000,
  B00000000, B11111111, B11111111, B00000000,
  B00000001, B11111111, B11111111, B10000000,
  B00000111, B11111100, B01111111, B11100000,
  B00011111, B11111000, B00011111, B11111000,
  B00011111, B11000000, B00001111, B11111000,
  B00011111, B10000000, B00000011, B11111000,
  B00011111, B00000000, B00000001, B11111000,
  B00011111, B00000000, B00000000, B11111000,
  B00011111, B00110000, B00000000, B11111000,
  B00011111, B00111000, B00000000, B11111000,
  B00011111, B00111110, B00000000, B11111000,
  B00011111, B00111111, B00000000, B11111000,
  B00011111, B00111111, B00000000, B11111000,
  B00011111, B00111111, B00000000, B11111000,
  B00011111, B00111111, B00000000, B11111000,
  B00011111, B00011111, B00000000, B11111000,
  B00011111, B10000111, B00000000, B11111000,
  B00011111, B11000011, B00000011, B11111000,
  B00011111, B11110000, B00001111, B11111000,
  B00000111, B11111100, B00111111, B11100000,
  B00000001, B11111110, B01111111, B10000000,
  B00000000, B11111111, B11111111, B00000000,
  B00000000, B00111111, B11111100, B00000000,
  B00000000, B00001111, B11110000, B00000000,
  B00000000, B00000111, B11100000, B00000000,
  B00000000, B00000001, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000 };

void display_logo();
void display_batt();
long battery_level();
void btn_batt();
void btn_logo();


// true when displaying the battery status
bool show_batt = true;

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display_logo();

  // Set up buttons to change display modes
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // It doesn't appear to be possible to set an interrupt on button B...?
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), btn_batt, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_C), btn_logo, RISING);

  resin.Setup(deviceType, applicationUUID, split, ssid, password, false);

  // Let the splash screen linger for a bit...
  delay(1000);

}

void loop(void) {
  resin.Loop();

  if (show_batt)
    display_batt();

  resin.Loop();

  delay(1000);
}

void btn_logo() {
  show_batt = false;
  display_logo();
}

void btn_batt() {
  show_batt = true;
  display_batt();
}

void display_logo() {
  // Show a resin.io splash screen
  display.clearDisplay();
  display.drawBitmap(-3, 0, logobig, 32, 32, 1);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30, 8);
  display.println("resin.io");
  display.display();
}

void display_batt() {
  long battery = battery_level();
  
  display.clearDisplay();
  display.drawBitmap(30, 0, logosmall, 16, 16, 1);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(45, 4);
  display.print("resin.io");
  display.setCursor(0, 22);
  display.print("Battery: ");
  display.print(battery);
  display.println("%");

  // Double-check before we write to the display, just in case an
  // interrupt came in during processing above
  if (show_batt)
    display.display();
}

long battery_level() {
  // Shamelessly stolen from
  // https://learn.adafruit.com/using-ifttt-with-adafruit-io?view=all#arduino-code-1

  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 1M & 220K voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 580 (3.14V)
  // and the max analog read value should be 774 (4.2V).
  int level = analogRead(A0);
 
  // convert battery level to percent
  return map(level, 580, 774, 0, 100);
 
}
