/* 
  WiFiTelnetToSerial - Example Transparent UART to Telnet Server for esp8266
  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the ESP8266WiFi library for Arduino environment.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 1


WiFiServer server(23);
WiFiClient serverClients[MAX_SRV_CLIENTS];

// Neopixel stuff
#define NUM_LEDS 8
#define DATA_PIN 12 // LED strip on pin 12

// Define the array of leds
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ400);   // (LB) had to swap from RGB!

void setup() 
{  
//   pinMode(0, OUTPUT);
//   pinMode(2, OUTPUT);
//   digitalWrite(0, HIGH);
//   digitalWrite(2, HIGH);

   strip.begin();
   strip.show();

  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  
  if(i == 21)
  {
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  //start UART and the server
  // Serial.begin(115200);
  server.begin();
  server.setNoDelay(true);   


  
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 23' to connect");
}

int rx=0;
int tx=0;
int conn=0;

void loop() 
{  
  strip.setPixelColor(5, 0, tx, 0);
  strip.setPixelColor(6, rx, 0, 0);
  strip.setPixelColor(7, conn,conn,0);
  strip.show();

  tx *= 0.99;
  rx *= 0.99;
  
  
  uint8_t i;
  //check if there are any new clients
  if (server.hasClient())
  {
    conn = 50;
     
    for(i = 0; i < MAX_SRV_CLIENTS; i++)
    {
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected())
      {
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        Serial.print("New client: "); Serial.println(i);
        continue;
      }
    }
    
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.write("\n\rSorry, server is busy\n\r\n\r");
    serverClient.stop();
  }
  else
  {
     conn = 1;
  }
  
  //check clients for data
  for(i = 0; i < MAX_SRV_CLIENTS; i++)
  {
    if (serverClients[i] && serverClients[i].connected())
    {
      if(serverClients[i].available())
      {
         rx = 255;
        
        //get data from the telnet client and push it to the UART
        while(serverClients[i].available()) 
        {          
          Serial.write(serverClients[i].read());
        }       
      }
    }
  }
  //check UART for data
  if(Serial.available())
  {
    tx = 255;
    
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //push UART data to all connected telnet clients
    
    for(i = 0; i < MAX_SRV_CLIENTS; i++)
    {
      if (serverClients[i] && serverClients[i].connected())
      {
        serverClients[i].write(sbuf, len);
        delay(1);
      }
    }
  }
}
