/*
 * Ref: https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/using-arduino-ide
 * to get Arduino IDE set up, use http://arduino.esp8266.com/stable/package_esp8266com_index.json
 * Ref: info on the ESP8266 support lib, see https://github.com/probonopd/Arduino
 * Ref: https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/using-the-arduino-addon
 * Ref: http://playground.arduino.cc/Learning/OneWire
 * Ref: http://www.pjrc.com/teensy/td_libs_OneWire.html
 * Ref: example code  https://github.com/openhomeautomation/adafruit-io-esp8266/blob/master/esp8266_sensor_module/esp8266_sensor_module.ino
 * Ref: MQTT library from https://github.com/adafruit/Adafruit_MQTT_Library
 * Ref: DallasTemperature library from https://github.com/milesburton/Arduino-Temperature-Control-Library
 * 
 * 2016/1/1 - Works! Upload working on Mac, but not Chromebook/Ubuntu. Using Sparkfun FTDI, plugged direct into back of Mac.
 * Interesting things to try: set high, low alarms; get alarms, send to AdafruitIO and/or start beeping
 */

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "OneWire.h"
#include <DallasTemperature.h>

ADC_MODE(ADC_VCC); // I'm going to read the internal voltage, so the ADC has to be disabled, per https://github.com/esp8266/Arduino/issues/756 and https://github.com/adafruit/ESP8266-Arduino

// Sensor connection
#define ONE_WIRE_BUS 12

// WiFi parameters
#define WLAN_SSID       "-------------"
#define WLAN_PASS       "-------------"
 
// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "-------------"
#define AIO_KEY         "-------------"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, client ID, username, and password in flash memory.
const char MQTT_SERVER[] PROGMEM    = AIO_SERVER;

// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM  = AIO_KEY __DATE__ __TIME__;
const char MQTT_USERNAME[] PROGMEM  = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM  = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);

// function prototype - so the compiler doesn't complain that the fn doesn't exist when I make a call to it, 
// before the complete function definition that comes later in the code!
void connect (void);

/****************************** Feeds ***************************************/

// Setup feeds for temperature & humidity
const char TEMPERATURE_FEED[] PROGMEM = AIO_USERNAME "/feeds/temperature";
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, TEMPERATURE_FEED);

// const char HUMIDITY_FEED[] PROGMEM = AIO_USERNAME "/feeds/humidity";
// Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, HUMIDITY_FEED);

const char VOLTAGE_FEED[] PROGMEM = AIO_USERNAME "/feeds/vcc";
Adafruit_MQTT_Publish vcc = Adafruit_MQTT_Publish(&mqtt, VOLTAGE_FEED);

OneWire ds(ONE_WIRE_BUS);
DallasTemperature sensors(&ds);

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  Serial.println("Temp sensor testing");

  pinMode(0, OUTPUT); // for blinking the LED
  digitalWrite(0, HIGH); // turn LED off
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  delay(10);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());

  // connect to adafruit io
  connect();

  sensors.begin();
//  scanSensors(); // Only one sensor on the line

}

void loop() {

  // ping adafruit io a few times to make sure we remain connected
  if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }
  
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  float temperature_data = sensors.getTempFByIndex(0);
  Serial.println(" DONE - got temps.");
  Serial.print("Temperature for Device 1 is: ");
  Serial.print(temperature_data);
  Serial.print("F");

  if (! temperature.publish(temperature_data))
    Serial.println(F("  Failed to publish temperature"));
  else {
    Serial.println(F("  Temperature published!"));
    // blink the LED for success
    digitalWrite(0, LOW); // note LOW turns ON the LED...
    delay(250);
    digitalWrite(0, HIGH);
  }

  delay(250);

  int vcc_data = ESP.getVcc();
  Serial.print("Vcc is: ");
  Serial.print(vcc_data);
  Serial.print(" V");
  
  if (! vcc.publish(vcc_data))
    Serial.println(F("  Failed to publish vcc"));
  else {
    Serial.println(F("  Vcc published!"));
    // blink the LED for success
    digitalWrite(0, LOW); // note LOW turns ON the LED...
    delay(250);
    digitalWrite(0, HIGH);
  }

  delay(60L*1000L); // sleep 1 min
 }

 // connect to adafruit io via MQTT
void connect() {

  Serial.print(F("Connecting to Adafruit IO... "));

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(5000);

  }

  Serial.println(F("Adafruit IO Connected!"));

}
