#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

const char* ssid = "******";
const char* password = "*******";
const char* host = "AdyLightHue";
const int relay = 0;
const int LED = 2;

int hue = 0;
float brightness = 0.0;
float saturation = 0.0;

// Update these with values suitable for your network.
IPAddress MQTTserver(192, 168, 1, 155);

#define BUFFER_SIZE 100

WiFiClient wclient;
PubSubClient client(wclient, MQTTserver);


void callback(const MQTT::Publish& pub) {

  uint16_t i, j;

  String myMessage = String(pub.payload_string());
  // handle message arrived
  Serial.print(pub.topic());
  Serial.print(" => ");
  String myTpoic = String(pub.topic());

  if(myTpoic == "AdyLight")
  {

    Serial.println(pub.payload_string());

    if(pub.payload_string() == "on")
    {
      hue = 0;
      brightness = 1.0;
      saturation = 0.0;
      
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.HSVColor(hue,saturation,brightness));
    }
    strip.show();
      
    }
    else
    {
      hue = 0;
      brightness = 0.0;
      saturation = 0.0;
      
      for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.HSVColor(hue,saturation,brightness));
    }
    strip.show();
    }

  }
  
  else if(myTpoic == "AdyLightBrightness")
  {
    Serial.println(pub.payload_string());
    brightness = (myMessage.toFloat())/100;
      for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.HSVColor(hue,saturation,brightness));
    }
    strip.show();
    
  }
  else if(myTpoic == "AdyLightHue")
  {
    Serial.println(pub.payload_string());
    hue = myMessage.toInt();
      for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.HSVColor(hue,saturation,brightness));
    }
    strip.show();
    
  }
  else if(myTpoic == "AdyLightSaturation")
  {
    Serial.println(pub.payload_string());
    saturation = (myMessage.toFloat())/100;
      for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.HSVColor(hue,saturation,brightness));
    }
    strip.show();
  }
}

void setup() {
  pinMode(relay, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(host);

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // MQTT callback
  client.set_callback(callback);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}

void loop() {
  ArduinoOTA.handle();
  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("ESP8266: AdyLight")) {
  client.publish("outTopic","hello world");
  client.subscribe("AdyLight");
  client.subscribe("AdyLightHue");
  client.subscribe("AdyLightSaturation");  
  client.subscribe("AdyLightBrightness");
      }
    }

    if (client.connected())
      client.loop();
  }
  
//  Serial.println("*");
}
