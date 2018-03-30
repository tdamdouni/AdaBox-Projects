// Minimalist IoT Clock code
// Commands are collected in a feed
// Multiple NeoPixels visualize the command
//
// Modified by Igor Fonseca Albuquerque 2018
// based on Instructables IoT Class by Becky Stern 2017
// based on the Adafruit IO Subscription Example
// based on torntrousers approach for getting time from Google (http://www.esp8266.com/viewtopic.php?f=29&t=6007&start=5)

// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************ Adafruit IO Configuration *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "XXXXXXXXXX"
#define IO_KEY         "YYYYYYYYY"

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "WWWWWWWWWW"
#define WIFI_PASS       "ZZZZZZZZZZ"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>
#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 12   // Pin connected to the NeoPixel data input
#define NUM_LEDS   16   // Number of NeoPixels
#define BRIGHTNESS 30   // Brightness of the LEDs
#define PIXEL_TYPE NEO_GRB + NEO_KHZ800   // Type of the NeoPixels (see strandtest example).
Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUM_LEDS, PIXELS_PIN, PIXEL_TYPE);// + NEO_KHZ800);

AdafruitIO_Feed *command = io.feed("iot-air-freshner-command"); // Set up the 'command' feed

String TimeDate = ""; // Variable used to store the data received from the server
int hours;    // Current hour
int minutes;  // Current minute
int seconds;  // Current second
int seconds0; // Last time when the LEDs were updated
String weather = "Clear"; // Current weather condition
#define OFFSET  2 // LED offset. It's used to compensate for misalignment between the LED ring and the 12 o'clock position
#define TIMEZONE  3 // Current time zone. Used for correction of server time


void setup() {
  
  // Initialize all pixels to 'off'
  ring.setBrightness(BRIGHTNESS);
  ring.begin();
  ring.show(); 

  // Start the serial connection
  Serial.begin(115200);

  // Enable wathchdog timer. The ESP8266 after 5 seconds if something goes wrong
  ESP.wdtEnable(5000);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);  

  // wait for a connection
  int i = NUM_LEDS - 1;
  int color = 255;
  // animate LEDs while waiting for connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    ring.setPixelColor(i, 0, 0, color);
    ring.show();
    i = i - 1;
    if (i < 0) {
      if (color == 255) {
        color = 0;
      }
      else {
        color = 255;
      }
      i = NUM_LEDS - 1;
    }
    delay(50);
  }
  lightPixels(ring.Color(0, 0, 0, 0)); // reset all pixels to off when connected

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  // get current time from server
  getTime();

  seconds0 = millis();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  // update LED ring every 3 seconds
  if ((millis() - seconds0) > 3000) {
    seconds = seconds + 3;

    // synchronize with the server every minute
    if (seconds > 59) {
      getTime();
    }

    // display clock
    showTime();
    seconds0 = millis();
  }
}

// this function is called whenever a message
// is received from Adafruit IO. it was attached to
// the feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {
  
  lightPixels(ring.Color(0, 0, 0, 0)); // reset all pixels to off when new info is received

  String commandStr = data->toString(); // store the incoming commands in a string
  
  Serial.print("received <- ");
  Serial.println(commandStr);
  
  // These if statements compare the incoming weather variable to the stored conditions, and control the NeoPixels accordingly.
  
  // if weather has changed
  if (commandStr.equalsIgnoreCase("Rain")){
    Serial.println("It's raining!");
    weather = "Rain";
  }
  if (commandStr.equalsIgnoreCase("Clear")){
    Serial.println("It's clear!");
    weather = "Clear";
  }
  if (commandStr.equalsIgnoreCase("Cloudy")){
    Serial.println("It's cloudy!");
    weather = "Cloudy";
  }
  if (commandStr.equalsIgnoreCase("Snow")){
    Serial.println("Snow!");
    weather = "Snow";
  }  
} 


// Function to set all the NeoPixels to the specified color.
void lightPixels(uint32_t color) {
  for (int i=0; i<NUM_LEDS; ++i) {
    ring.setPixelColor(i, color);
  }
  ring.show();
}


//Funcion NeoPixels full rotation
void rotatingPixels(uint32_t color) {
  for (int j = 0; j < 3; j++) {
    for (int i=NUM_LEDS-1; i>=0; i--) {
      ring.setPixelColor(i, color);
      ring.show();
      delay(50);
      ring.setPixelColor(i, 0, 0, 0);//ring.Color(0, 0, 0, 255));
      ring.show();
    }
  }
}

//Get current time Google server
void getTime() {

  WiFiClient client;
  while (!!!client.connect("google.com", 80)) {
    Serial.println("connection failed, retrying...");
  }

  client.print("HEAD / HTTP/1.1\r\n\r\n");

  delay(500); //wait a few milisseconds for incoming message

  //if there is an incoming message
  if(client.available()){
    while(client.available()){
      if (client.read() == '\n') {    
        if (client.read() == 'D') {    
          if (client.read() == 'a') {    
            if (client.read() == 't') {    
              if (client.read() == 'e') {    
                if (client.read() == ':') {    
                  client.read();
                  String theDate = client.readStringUntil('\r');
                  client.stop();

                 TimeDate = theDate.substring(7);
                  Serial.println(TimeDate);
                  // time starts at pos 14
                  String strCurrentHour = theDate.substring(17,19);
                  String strCurrentMinute = theDate.substring(20,22);
                  String strCurrentSecond = theDate.substring(23,25);
                  Serial.println(strCurrentHour);
                  Serial.println(strCurrentMinute);
                  Serial.println(strCurrentSecond);
                  hours = strCurrentHour.toInt();
                  minutes = strCurrentMinute.toInt();
                  seconds = strCurrentSecond.toInt();
                }
              }
            }
          }
        }
      }
    }
  }
  //if no message was received (an issue with the Wi-Fi connection, for instance)
  else{
    seconds = 0;
    minutes += 1;
    if (minutes > 59) {
      minutes = 0;
      hours += 1;
      if (hours > 11) {
        hours = 0;
      }
    }
  }
}

//Update LED rings clock
void showTime(){
  
  // reset all pixels to off when connected
  lightPixels(ring.Color(0, 0, 0, 0)); 
  int pixelR = 0;
  int pixelG = 0;
  int pixelB = 0;

  // choose color according to current weather condition
  // hours, minutes, and seconds LEDs will have the same colors
  // hours will be brighter, while seconds will be more faint
  if (weather == "Rain") {
    pixelR = 1;
  }
  if (weather == "Clear") {
    pixelG = 1;
  }
  if (weather == "Cloudy") {
    pixelR = 1;
    pixelG = 1;
  }                
  if (weather == "Snow") {
    pixelB = 1;
  }

  // map the seconds to the LED ring
  int secondsdisplay = map(seconds, 0, 60, NUM_LEDS, 0);
  secondsdisplay = secondsdisplay - OFFSET;
  if (secondsdisplay < 0) {
    secondsdisplay = secondsdisplay + NUM_LEDS;
  }
  ring.setPixelColor(secondsdisplay, 10*pixelR, 10*pixelG, 10*pixelB);
  
  // map the minutes to the LED ring
  int minutesdisplay = map(minutes, 0, 60, NUM_LEDS, 0);
  minutesdisplay = minutesdisplay - OFFSET;
  if (minutesdisplay < 0) {
    minutesdisplay = minutesdisplay + NUM_LEDS;
  }
  ring.setPixelColor(minutesdisplay, 64*pixelR, 64*pixelG, 64*pixelB);
  
  // map the hours to the LED ring
  int hoursdisplay;
  hoursdisplay = hours - TIMEZONE;
  if (hoursdisplay < 0) {
    hoursdisplay += 12;
  }
  if (hoursdisplay > 12) {
    hoursdisplay = hoursdisplay - 12;
  }
  
  hoursdisplay = map(hoursdisplay, 0, 12, NUM_LEDS, 0);
  hoursdisplay = hoursdisplay - OFFSET;
  if (hoursdisplay < 0) {
      hoursdisplay = hoursdisplay + NUM_LEDS;
  }              
  ring.setPixelColor(hoursdisplay, 255*pixelR, 255*pixelG, 255*pixelB);
  
  // update LEDs
  ring.show();
}
