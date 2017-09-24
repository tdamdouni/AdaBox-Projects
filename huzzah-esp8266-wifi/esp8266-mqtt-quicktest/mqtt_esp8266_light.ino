/***************************************************
  Adafruit MQTT Library ESP8266 Example
  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
extern "C" {
#include "user_interface.h"
}


/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "...your_SSID..."
#define WLAN_PASS       "...your_password..."


/***************************** Your Setup ************************************/

#define YOUR_SERVER      "...your_mqtt_broker_host..."
#define YOUR_SERVERPORT  1883
#define YOUR_USERNAME    "...your_username..."
#define YOUR_PASSWORD    "...your_password..."

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, client ID, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
const char MQTT_SERVER[] PROGMEM    = YOUR_SERVER;
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ "_light_client_id";
const char MQTT_USERNAME[] PROGMEM  = YOUR_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = YOUR_PASSWORD;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, YOUR_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

/****************************** Topic ***************************************/

// Setup a pubulisher & subscriber.
const char LIGHT_TOPIC[] PROGMEM = "light";
Adafruit_MQTT_Publish lightPublisher = Adafruit_MQTT_Publish(&mqtt, LIGHT_TOPIC);
Adafruit_MQTT_Subscribe lightSubscriber = Adafruit_MQTT_Subscribe(&mqtt, LIGHT_TOPIC);

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("MQTT demo"));

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

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription.
  mqtt.subscribe(&lightSubscriber);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
 Adafruit_MQTT_Subscribe *subscription;
 while ((subscription = mqtt.readSubscription(1000))) {
   if (subscription == &lightSubscriber) {
     Serial.print(F("Got: "));
     Serial.println((char *)lightSubscriber.lastread);
   }
 }

  //unsigned int 型の入れ物を用意
  uint ADC_Value = 0;

  //AD変換実行
  ADC_Value = system_adc_read();
  // publish
  lightPublisher.publish(ADC_Value);

  delay(50000);
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

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(ret);
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}