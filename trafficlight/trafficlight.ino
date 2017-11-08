#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <stdio.h>

#include "config.h"

#define RED 0
#define YELLOW 1
#define GREEN 2
#define RED_PIN    5
#define YELLOW_PIN 4
#define GREEN_PIN   15

int brightness = 512;
uint8_t lamps[] = {0,0,0};

WiFiClient wifiClient;
PubSubClient client(MQTT_HOST, MQTT_PORT);

void callback(const MQTT::Publish& pub) {
  
  Serial.println("Callback: ");
  Serial.print("Topic: ");
  Serial.println(pub.topic());
  Serial.print("Payload: ");
  Serial.println(pub.payload_string());
  
  //String topicStr = String(topic);

  if (pub.topic() == "mumalab/room/trafficlight/red") {
    setLamp(RED, pub.payload_string()[0]);
  } else if (pub.topic() == "mumalab/room/trafficlight/yellow") {
    setLamp(YELLOW, pub.payload_string()[0]);
  } else if (pub.topic() == "mumalab/room/trafficlight/green") {
    setLamp(GREEN, pub.payload_string()[0]);
  } else if (pub.topic() == "mumalab/room/trafficlight/ryg") {
    if (pub.payload_string().length() == 3) {
      setLamp(RED, pub.payload_string()[0]);
      setLamp(YELLOW, pub.payload_string()[1]);
      setLamp(GREEN, pub.payload_string()[2]);
    } else {
      Serial.println(pub.payload_string().length());
    }
  } else if (pub.topic() == "mumalab/room/trafficlight/brightness") {
    brightness = atoi(pub.payload_string().c_str());
    brightness = brightness * 10; // map 0-100 to 0-1000 (instead of 1023)
    Serial.print("Set brightness to ");
    Serial.println(brightness);
    updateLamps();
  } else {
  }
}

void setLamp(uint8_t lamp, char payload) {
  if (payload == '0') {
    lamps[lamp] = 0;
  } else if (payload == '1') {
    lamps[lamp] = 1;
  }
  Serial.print("Set lamp ");
  Serial.print(lamp);
  Serial.print(" to ");
  Serial.println(lamps[lamp]);
  updateLamps();
}

void updateLamps() {
  if (lamps[RED] == 0) {
    analogWrite(RED_PIN, 0);
  } else {
    analogWrite(RED_PIN, brightness);
  }
  
  if (lamps[YELLOW] == 0) {
    analogWrite(YELLOW_PIN, 0);
  } else {
    analogWrite(YELLOW_PIN, brightness);
  }
  
  if (lamps[GREEN] == 0) {
    analogWrite(GREEN_PIN, 0);
  } else {
    analogWrite(GREEN_PIN, brightness);
  }
}

void setup(void)
{
  Serial.begin(9600);

  client.set_callback(callback);

  WiFi.begin(WIFI_SSID, WIFI_PW);
  
  Serial.print("Wifi connecting.");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);

  Serial.flush();
}
 
void loop(void)
{ 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Broker...");
    
    if (client.connect(MQTT::Connect("trafficlight").set_auth(MQTT_USER, MQTT_PASS))) {
      Serial.println("MQTT connection successfull.");
      client.publish("mumalab/room/trafficlight/status","connected");
      client.subscribe("mumalab/room/trafficlight/red");
      client.subscribe("mumalab/room/trafficlight/yellow");
      client.subscribe("mumalab/room/trafficlight/green");
      client.subscribe("mumalab/room/trafficlight/brightness");
      client.subscribe("mumalab/room/trafficlight/ryg");
    } else {
      Serial.println("MQTT connection failed.");
    }
    
    delay(500);
  }
  
  client.loop();
  delay(500);
} 
