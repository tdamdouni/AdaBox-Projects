#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Credentials.h"




// Store the MQTT server, username, and password in flash memory.
// This is required for using the Adafruit MQTT library.
const char Mqtt_Server[] PROGMEM    = MQTT_SERVER;
const char Mqtt_Username[] PROGMEM  = MQTT_USERNAME;
const char Mqtt_Password[] PROGMEM  = MQTT_KEY;

const char Doorbell_Topic[] PROGMEM = "DoorBell";

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, Mqtt_Server, MQTT_SERVERPORT, Mqtt_Username, Mqtt_Password);
Adafruit_MQTT_Subscribe DoorBell = Adafruit_MQTT_Subscribe(&mqtt, Doorbell_Topic);



void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println("ESPDoorBell");

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("WiFi is connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  pinMode(0, OUTPUT);

  mqtt.subscribe(&DoorBell);
  
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



void loop() {
  static unsigned long last_ping = 0;
  unsigned long current_time = millis();
  
  MQTT_connect();

  if (current_time < last_ping || current_time - last_ping > 30000)
  {
    mqtt.ping();
    last_ping = current_time;
  }

  Adafruit_MQTT_Subscribe *subscription;

  while (subscription = mqtt.readSubscription(1000)) {

    // we only care about the lamp events
    if (subscription == &DoorBell) {

      // convert mqtt ascii payload to int
      char *msg = (char *)DoorBell.lastread;
      if (msg[0])
      {
        if (msg[1] == 'i')
          digitalWrite(0, HIGH);
        else
          digitalWrite(0, LOW);
      }
    }
  }
}


