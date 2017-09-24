/*
 * This is an example sketch on using aREST with an Adafruit Feather Huzzah board
 * The sketch starts a web server and handles requests as REST calls via aREST
 * The board uses two relays on pins 12 and 13 that can be toggled via the REST API
 * Examples:
 * HuzzahIP/digital/12 -> returns the state of relay 1
 * HuzzahIP/digital/13 -> returns the state of relay 2
 * HuzzahIP/digital/12/0 -> turns relay 1 off
 * HuzzahIP/digital/12/1 -> turns relay 1 on
 * HuzzahIP/digital/13/0 -> turns relay 2 off
 * HuzzahIP/digital/13/1 -> turns relay 2 on
 */
#include <ESP8266WiFi.h>
#include <aREST.h>
#include "WiFi_parameters.h"  // Your personal WiFi ssid and password

aREST rest = aREST();

#define LISTEN_PORT           80

WiFiServer server(LISTEN_PORT);

#define RELAY1_PIN 12
#define RELAY2_PIN 13

void setup(void)
{
  Serial.begin(115200);

  pinMode(RELAY1_PIN,OUTPUT);
  pinMode(RELAY2_PIN,OUTPUT);
  
  rest.set_id("42");
  rest.set_name("Lars' Feather Huzzah");

  // Connect to WiFi
  WiFi.begin(SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() 
{
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
  
  while(!client.available())
  {
    delay(10);
  }
  
  rest.handle(client);
}

