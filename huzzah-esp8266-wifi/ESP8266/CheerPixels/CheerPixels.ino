/* Cheerlight Christmas Tree
 *  Set an LED strip's color from the internet!
 *
 * brightcolorfulflickers.tumblr.com
 * instagram.com/brightcolorfulflickers
 * github.com/brightcolorfulflickers
 * instructables.com/member/brightcolorfulflickers/
 * 
 * Dec 2016
 * 
 * Original code from:  http://www.instructables.com/id/Cheerlights-Christmas-Tree/
 * Edited by LB for the Adafruit Feather HUZZAH ESP8266 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>


const char* host = "api.thingspeak.com";

long lastUpdateTime = 0;
const long updateWaitTime = 3000; //3 seconds between queries
bool firstUpdate = false;
long lastAnimationTime = 0;
const long animWaitTime = 30000; // if it's been 30 seconds since something happened, do something!

#define NUM_LEDS 8
#define DATA_PIN 12 // LED strip on pin 12

//most recent Cheerlight color in r, g, b
uint8_t currentR;
uint8_t currentG;
uint8_t currentB;

//store recent values from Cheerlights
uint8_t rhistory[NUM_LEDS];
uint8_t ghistory[NUM_LEDS];
uint8_t bhistory[NUM_LEDS];

// Define the array of leds
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ400);   // (LB) had to swap from RGB!

void setup() {

   pinMode(0, OUTPUT);
   pinMode(2, OUTPUT);
   digitalWrite(0, HIGH);
   digitalWrite(2, HIGH);
   
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  strip.begin();
  strip.show();

  //initialize arrays

  for(int i = 0; i < NUM_LEDS; i++ ) {
    rhistory[i] = 0;
    ghistory[i] = 0;
    bhistory[i] = 0;
  }
  // This array could be used for something fun! Right now I only use it to compare against old values.
}

void loop() {
  //Check Cheerlights API every 3 seconds
  if ((unsigned long)(millis() - lastUpdateTime) > updateWaitTime  || firstUpdate == false) 
  {
    digitalWrite(0, LOW);
    getCurrentColor();
    digitalWrite(0, HIGH);
    
    if (isNewColor(currentR,currentG,currentB)) 
    {
      digitalWrite(2, LOW);
      updateRGBArrays(currentR,currentG,currentB);
      Serial.println("New color: " + (String)currentR + "," + (String)currentG + "," + (String)currentB);
      lastAnimationTime == millis();
      fillUpLEDs(currentR,currentG,currentB);
      digitalWrite(2, HIGH);
    }
    if (firstUpdate == false) {
      firstUpdate = true;
    }
  }

  //Let's keep it interesting if the color doesn't change very often.
  //Animations every 30 seconds.
  if ((unsigned long)(millis() - lastAnimationTime) > animWaitTime) {
    //pick one animation randomly - feel free to add more of your own 
    int animSelect = random(2);
    switch (animSelect) {
        case 0:
          dance(currentR,currentG,currentB);
          break;
        case 1:
          twinkle(currentR,currentG,currentB);
          break;
        default: 
          // if nothing else matches, do the default
          // default is optional
        break;
    }
    lastAnimationTime = millis(); 
    SetAllLEDs(currentR,currentG,currentB);
  }

}

//Query the Cheerlights API for the current color
void getCurrentColor() {
  String colorString = "";

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/channels/1417/field/2/last.txt";

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  // Read all the lines of the reply from server and print them to Serial
  String line = "";
  while(client.available()){
    line = client.readStringUntil('\r');
    //If the line has a # it's the HTML hex color
    if (line.indexOf('#') > 0) {
      colorString = line;
      int poundindex = line.indexOf('#');
      String thisColorString = line.substring(poundindex,poundindex+7);
      // Convert HTML hex color code to RGB values
      long colorNumber = (int) strtol( &thisColorString[1], NULL, 16);
      // Split them up into r, g, b values
      currentR = colorNumber >> 16;
      currentG = colorNumber >> 8 & 0xFF;
      currentB = colorNumber & 0xFF;
    }
  }
  lastUpdateTime = millis();
}

//Updates color of LEDs from bottom up
void fillUpLEDs(uint8_t r, uint8_t g, uint8_t b) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, r,g,b);
    delay(50); //delay adds fun animation effect
    strip.show();
  }
}

//Set all LEDs to a given set of r,g,b values
void SetAllLEDs(uint8_t r, uint8_t g, uint8_t b) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, r,g,b);
    strip.show();
  }
}

//Set every other LED to the current color and the rest blank, and alternate
void dance(uint8_t r, uint8_t g, uint8_t b) {
  for(uint16_t j=0; j<6; j++) {
    SetAllLEDs(0,0,0);
    for(uint16_t i=0; i<strip.numPixels(); i++){
      if (j % 2 == i % 2) { 
        strip.setPixelColor(i, r,g,b);
      } else {
        strip.setPixelColor(i, 0,0,0);
      }
    }
    strip.show();
    delay(250);
  }
  delay(500);
}

//Turn on random LEDs
void twinkle(uint8_t r, uint8_t g, uint8_t b) {
  int numToTwinkle = 20;
  SetAllLEDs(0,0,0);
  for(uint16_t i=0; i<numToTwinkle; i++){
    strip.setPixelColor(random(NUM_LEDS), r,g,b);
    strip.show();
    delay(75);
  }
  delay(500);
}

bool isNewColor(int r, int g, int b) {
  if (r == rhistory[0] && g == ghistory[0] && b == bhistory[0]) {
    return false;
  } else {
    return true;
  }
}

void updateRGBArrays(int r, int g, int b) {
  for(int i = NUM_LEDS - 1; i > 0; i--) {
    rhistory[i] = rhistory[i-1];
    ghistory[i] = ghistory[i-1];
    bhistory[i] = bhistory[i-1];
  }
  rhistory[0] = r;
  ghistory[0] = g;
  bhistory[0] = b;
}

