/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution


  Watch tutorial video on my YouTube channel
  search for techiesms on YouTube.

  Visit my Website for more such projects on IoT
  http://www.techiesms.com
 ****************************************************/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define l1 D0
#define l2 D1
#define l3 D2
#define l4 D3
#define l5 D4
#define l6 D5
#define l7 D6
#define l8 D7
#define l9 D8

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "SSID"
#define WLAN_PASS       "Password"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USername"
#define AIO_KEY         "AIO KEY"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
//Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/test");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/test");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 pinMode(l1,OUTPUT);
 pinMode(l2,OUTPUT);
 pinMode(l3,OUTPUT);
 pinMode(l4,OUTPUT);
 pinMode(l5,OUTPUT);
 pinMode(l6,OUTPUT);
 pinMode(l7,OUTPUT);
 pinMode(l8,OUTPUT);
 pinMode(l9,OUTPUT);
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription())) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      String RAW = (char *)onoffbutton.lastread;
      int i=0;
      while(RAW.charAt(i) != '_')
      i++;
      String pin = RAW.substring(0,i);
      //Serial.println(pin);
      int pin_number = pin.toInt();
      Serial.println(pin_number);

      int j=i+1;
      while(RAW.charAt(j) != '_')
      j++;
     // Serial.println(i);
     //Serial.println(j);
      String state = RAW.substring(i+1,j);
      //Serial.println(state);
      int state_number = state.toInt();
      Serial.println(state_number);

      if(pin_number == 1)
      {
        digitalWrite(l1,state_number);
      }
      else if(pin_number == 2)
      {
        digitalWrite(l2,state_number);
      }
      else if(pin_number == 3)
      {
        digitalWrite(l3,state_number);
      }
      else if(pin_number == 4)
      {
        digitalWrite(l4,state_number);
      }
      else if(pin_number == 5)
      {
        digitalWrite(l5,state_number);
      }
      else if(pin_number == 6)
      {
        digitalWrite(l6,state_number);
      }
      else if(pin_number == 7)
      {
        digitalWrite(l7,state_number);
      }
      else if(pin_number == 8)
      {
        digitalWrite(l8,state_number);
      }
      else if(pin_number == 9)
      {
        digitalWrite(l9,state_number);
      }
      
      
      
    }
  }

 

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
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
