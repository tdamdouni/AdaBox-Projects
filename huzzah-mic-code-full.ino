// https://forums.adafruit.com/viewtopic.php?f=57&t=125480
/***************************************************
Code to run neoPixel wall

 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "config.h"

///////Light define//////
#include <Adafruit_NeoPixel.h>
//final code for 2016 =)


#define MPIN 6// check middle
#define MNEOCount 37
#define LLpixelBrightness 50

#define RPIN 14 //SCLcheck Right
#define RNEOCount 61
#define RLpixelBrightness 50

#define LPIN 2 //check Left
#define LNEOCount 37
#define RApixelBrightness 50

#define LongestCount 61

/////////////////////mic////////////////////
#define MIC_PIN   13  // Microphone is attached to Trinket GPIO #2/Gemma D2 (A1)
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     50  // Noise/hum/interference in mic signal
#define SAMPLES   60  // Length of buffer for dynamic level adjustment
#define TOP       (LongestCount +1) // Allow dot to go slightly off scale
//////////////for mic////////////////
byte
  peak      = 0,      // Used for falling dot
  dotCount  = 0,      // Frame counter for delaying dot-falling speed
  volCount  = 0;      // Frame counter for storing past volume data

int
  vol[SAMPLES],       // Collection of prior volume samples
  lvl       = 5,     // Current "dampened" audio level
  minLvlAvg = 0,      // For dynamic adjustment of graph low & high
  maxLvlAvg = 512;
////////////////////////////////////////////

Adafruit_NeoPixel stripM = Adafruit_NeoPixel(MNEOCount, MPIN, NEO_RGBW + NEO_KHZ800); //Note NEO_RGBW for RGBW (but acts like GRBW) and NEO_GRB for GRB
Adafruit_NeoPixel stripR = Adafruit_NeoPixel(RNEOCount, RPIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel stripL = Adafruit_NeoPixel(LNEOCount, LPIN, NEO_RGBW + NEO_KHZ800);


/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
//WiFiClient client;
// or... use WiFiFlientSecure for SSL
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/test");


// io.adafruit.com SHA1 fingerprint
const char* fingerprint = "AD 4B 64 B3 67 40 B5 FC 0E 51 9B BD 25 E9 7F 88 B6 2A A3 5B";

/*************************** Error Reporting *********************************/

Adafruit_MQTT_Subscribe errors = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/errors");
Adafruit_MQTT_Subscribe throttle = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/throttle");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();



//********* Setup Some Global Variables  ***************
//********* Setup Some Global Variables  ***************
uint32_t x=0;
char * lastVal;
unsigned long Interval = 1010;   // milliseconds between updates
unsigned long lastUpdate; // last update of position
char * feed_read = "16";
uint16_t responseWait_Long = 5000;
uint16_t responseWait_Short = 50;


/*************************** setup ************************************/
/*************************** setup ************************************/
void setup() {
  Serial.begin(115200);
  delay(10);


  //stripL.begin();
  //stripL.setBrightness(LLpixelBrightness); //adjust brightness here 0 - 255
  //stripL.show(); // Initialize all pixels to 'off'
  //stripM.begin();
  //stripM.setBrightness(LLpixelBrightness); //adjust brightness here 0 - 255
  //stripM.show(); // Initialize all pixels to 'off'
  stripR.begin();
  stripR.setBrightness(LLpixelBrightness); //adjust brightness here 0 - 255
  stripR.show(); // Initialize all pixels to 'off'
  memset(vol, 0, sizeof(vol)); //used by vol_m



//********** Connect to WiFi access point. **********
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // check the fingerprint of io.adafruit.com's SSL cert
  Serial.println("check the fingerprint of io.adafruit.com's SSL cert");
  verifyFingerprint();

//********** Setup MQTT subscription for onoff feed **********
  mqtt.subscribe(&onoffbutton);

  // Setup MQTT subscriptions for throttle & error messages
  mqtt.subscribe(&throttle);
  mqtt.subscribe(&errors);


//Set lastUpdate so that it will check first time it runs
lastUpdate = millis()+ lastUpdate +1;

MQTT_connect();

}


/*************************** loop ************************************/
/*************************** loop ************************************/
void loop() {
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  Adafruit_MQTT_Subscribe *subscription;


  //Looping Through
  //Do a feed_reed per loop

   if((millis() - lastUpdate) > Interval) {
        feed_read = sub_onoffbutton(responseWait_Long);
        Serial.print("In void Loop sub_onoffbutton returned ");
        Serial.println(feed_read);
   }

  //Functions will do feed_read and if value has changed end, return to void loop the new feed_read value
  if(strcmp(feed_read, "16") == 0) {
    chase_call();
  } else if(strcmp(feed_read, "17") == 0) {
     rainbow(20);
     } else if(strcmp(feed_read, "18") == 0) {
     vol_m();
  } else if(strcmp(feed_read, "OFF") == 0) {
    all_off();
  }

}


/*************************** sub_onoffbutton************************************/
char * sub_onoffbutton(uint16_t responseWait) {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  Adafruit_MQTT_Subscribe *subscription;

    subscription = mqtt.readSubscription(responseWait) ;
    if (subscription == &onoffbutton) {
      Serial.print(F("Sub Got onoff: "));
      Serial.println((char *)onoffbutton.lastread);
    } else if(subscription == &errors) {
      Serial.print(F("ERROR: "));
      Serial.println((char *)errors.lastread);
    } else if(subscription == &throttle) {
      Serial.println((char *)throttle.lastread);
    }
    //Reset the lastUpdate time to now
    lastUpdate = millis();
    Serial.print("lastUpdate = ");
    Serial.println(lastUpdate);
    return((char *)onoffbutton.lastread);
}


char * all_off() {
  while(strcmp(feed_read, "OFF") == 0) {
    if((millis() - lastUpdate) > Interval) {
          feed_read = sub_onoffbutton(responseWait_Short);
    }
    //Add code here to set all pixels off
    Serial.println("looping OFF ");
    delay(50);
    for(uint16_t pix=0; pix<LongestCount+1; pix++) {
      stripM.setPixelColor(pix, 0);
      stripM.show();
      stripR.setPixelColor(pix, 0);
      stripR.show();
      stripL.setPixelColor(pix, 0);
      stripL.show();
    }
    //Check if a button was pushed
    //feed_read = sub_onoffbutton();
    if(strcmp(feed_read, "OFF") != 0) {
        return feed_read;
    }
  }
}

char * sixteen() {


      //Do a feed_read on a set interval so as not to fload the server and be throttled
      if((millis() - lastUpdate) > Interval) {
        feed_read = sub_onoffbutton(responseWait_Short);
      }

}
void chase(uint32_t c, uint8_t wait,uint8_t litLen) {
  for(uint16_t pix=0; pix<LongestCount+litLen; pix++) {
//      stripB.setPixelColor(pix, c);
//      stripB.setPixelColor(pix-litLen, 0);
//      stripB.show();
//
      Serial.println("Chase");
      Serial.println(pix);


      stripM.setPixelColor(pix, c);
      stripM.setPixelColor(pix-litLen, 0);
      stripM.show();
      stripR.setPixelColor(pix, c);
      stripR.setPixelColor(pix-litLen, 0);
      stripR.show();
      stripL.setPixelColor(pix, c);
      stripL.setPixelColor(pix-litLen, 0);
      stripL.show();

      delay(wait);

  }
}

char * chase_call() {

  while(strcmp(feed_read, "16") == 0) {
        chase(stripM.Color(0, 0, 255), 7, 5); // Blue
        delay(20);

        //Do a feed_read on a set interval so as not to fload the server and be throttled
        if((millis() - lastUpdate) > Interval) {
          feed_read = sub_onoffbutton(responseWait_Short);
        }

        chase(stripR.Color(0, 0, 255), 7, 5); // Blue
        delay(20);

        //Do a feed_read on a set interval so as not to fload the server and be throttled
        if((millis() - lastUpdate) > Interval) {
          feed_read = sub_onoffbutton(responseWait_Short);
        }

        chase(stripL.Color(0, 0, 255), 7, 5); // Blue
        delay(20);

         //Do a feed_read on a set interval so as not to fload the server and be throttled
        if((millis() - lastUpdate) > Interval) {
          feed_read = sub_onoffbutton(responseWait_Short);
        }
        if(strcmp(feed_read, "16") != 0) {
        return feed_read;
        }
    }
}





char * rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<LongestCount ; i++) {
      stripM.setPixelColor(i, Wheel((i+j) & 255));
      stripR.setPixelColor(i, Wheel((i+j) & 255));
      stripL.setPixelColor(i, Wheel((i+j) & 255));
    }
    stripM.show();
    stripR.show();
    stripL.show();
    delay(wait);
    if((millis() - lastUpdate) > Interval) {
      feed_read = sub_onoffbutton(responseWait_Short);
    }
    if(strcmp(feed_read, "17") != 0) {
      return feed_read;
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return stripM.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return stripM.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  } else {
   WheelPos -= 170;
   return stripM.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
////////////////////////////////////////////mic vol_m//////////////////////////////////////
char * vol_m() {
  int ii = 0;
  while(strcmp(feed_read, "18") == 0) {
    uint8_t  i;
    uint16_t minLvl, maxLvl;
    int      n, height;

    n   = analogRead(MIC_PIN);                 // Raw reading from mic
    n   = abs(n - 512 - DC_OFFSET);            // Center on zero
    n   = (n <= NOISE) ? 0 : (n - NOISE);      // Remove noise/hum
    lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)

    // Calculate bar height based on dynamic min/max levels (fixed point):
    height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);

    if(height < 0L)       height = 0;      // Clip output
    else if(height > TOP) height = TOP;
    if(height > peak)     peak   = height; // Keep 'peak' dot at top

    // Color pixels based on rainbow gradient
    for(i=0; i<LongestCount; i++) {
      if(i >= height) {
         stripM.setPixelColor(i,   0,   0, 0, 0); // RGBW
         stripR.setPixelColor(i,   0,   0, 0, 0); // RGBW
         stripL.setPixelColor(i,   0,   0, 0, 0); // RGBW
      } else {
         stripM.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
         stripR.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
         stripL.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
           }
         //stripM.setPixelColor(i,Wheel(map(i,0,stripM.numPixels()-1,30,150)));//worked with rgb
      }

     stripM.show(); // Update strip
     stripR.show(); // Update strip
     stripL.show(); // Update strip

    vol[volCount] = n;                      // Save sample for dynamic leveling
    if(++volCount >= SAMPLES) volCount = 0; // Advance/rollover sample counter

    // Get volume range of prior frames
    minLvl = maxLvl = vol[0];
    for(i=1; i<SAMPLES; i++) {
      if(vol[i] < minLvl)      minLvl = vol[i];
      else if(vol[i] > maxLvl) maxLvl = vol[i];
    }

    // minLvl and maxLvl indicate the volume range over prior frames, used
    // for vertically scaling the output graph (so it looks interesting
    // regardless of volume level).  If they're too close together though
    // (e.g. at very low volume levels) the graph becomes super coarse
    // and 'jumpy'...so keep some minimum distance between them (this
    // also lets the graph go to zero when no sound is playing):
    if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
    minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
    maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)
    ii++;
    Serial.println(maxLvl);
    Serial.println(maxLvlAvg);
    Serial.println("end");

    if((millis() - lastUpdate) > Interval) {
      feed_read = sub_onoffbutton(responseWait_Short);
    }
    if(strcmp(feed_read, "18") != 0) {
      return feed_read;
    }
  }
      if((millis() - lastUpdate) > Interval) {
      feed_read = sub_onoffbutton(responseWait_Short);
    }
    if(strcmp(feed_read, "18") != 0) {
      return feed_read;
    }
}





// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    //Serial.println("MQTT already connected");
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

//Used to verify that there is a secure connection
void verifyFingerprint() {

  const char* host = AIO_SERVER;

  Serial.print("Connecting to ");
  Serial.println(host);

  if (! client.connect(host, AIO_SERVERPORT)) {
    Serial.println("Connection failed. Halting execution.");
    while(1);
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("Connection secure.");
  } else {
    Serial.println("Connection insecure! Halting execution.");
    while(1);
  }

}
