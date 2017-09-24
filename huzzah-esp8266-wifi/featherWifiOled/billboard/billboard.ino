#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(0);

/*
 * TODO
 * look at Adafruit_SSD1306 and see how to reset the line
 * look into threading code to do the lookup in the background
 * use an array of ints to fill in the bitmap
 */
#include "wifi.h"
/*
const char* ssid     = "timeburglar";
const char* password = "";
*/

const char* host  = "192.168.0.119";
int httpPort = 5002;
const char* url = "/loadData";

int pointer=0;
//unsigned char logo16_glcd_bmp[8292];
unsigned int bmp[512];

int haveData=0;

int loopCounter=0;
WiFiClient client;

/*
static const unsigned char PROGMEM logo16_glcd_bmp[] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,255,255,128,0,0,0,0,0,0,0,0,0,0,0,0,248,0,0,126,0,0,0,0,0,0,0,0,0,0,0,1,128,0,0,3,240,0,0,0,0,0,0,0,0,0,0,3,31,128,0,0,31,0,0,0,0,0,0,0,0,0,0,6,240,0,0,0,1,192,0,0,0,0,0,0,0,0,0,15,128,0,0,0,0,96,0,0,0,0,0,0,0,0,0,28,0,0,0,0,0,48,0,0,0,0,0,0,0,0,0,56,0,0,0,0,0,24,0,0,0,0,0,0,0,0,0,96,0,0,0,0,0,12,0,0,0,0,0,0,0,0,0,192,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,128,0,0,0,7,254,1,192,0,0,0,0,0,0,0,1,128,15,240,0,248,1,192,96,0,0,0,0,0,0,0,3,0,120,0,0,0,0,96,32,0,0,0,0,0,0,0,2,3,192,0,0,0,0,0,32,0,0,0,0,0,0,0,6,14,63,224,0,7,192,0,16,0,0,0,0,0,0,0,4,24,192,56,0,28,60,0,16,0,0,0,0,0,0,0,4,1,128,12,0,112,7,0,16,0,0,0,0,0,0,0,4,3,0,6,0,192,1,128,16,0,0,0,0,0,0,0,12,6,0,2,0,128,0,192,8,0,0,0,0,0,0,0,8,4,14,3,1,3,240,64,8,0,0,0,0,0,0,0,8,12,31,193,1,15,252,64,8,0,0,0,0,0,0,0,24,8,56,97,3,15,134,32,8,0,0,0,0,0,0,0,16,8,125,225,2,31,142,32,8,0,0,0,0,0,0,0,16,8,127,225,2,31,254,96,8,0,0,0,0,0,0,0,16,8,127,227,2,31,254,64,8,0,0,0,0,0,0,0,16,12,127,194,2,15,254,64,8,0,0,0,0,0,0,0,16,4,31,130,3,15,252,64,8,0,0,0,0,0,0,0,16,6,0,6,1,3,252,192,8,0,0,0,0,0,0,0,16,3,0,4,1,192,0,128,8,0,0,0,0,0,0,0,16,1,143,248,0,127,249,0,8,0,0,0,0,0,0,0,16,0,248,8,0,96,15,0,8,0,0,0,0,0,0,0,16,0,64,8,0,0,3,0,8,0,0,0,0,0,0,0,16,0,64,0,0,0,0,0,24,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,16,0,0,0,0,0,0,0,16,0,0,0,0,3,192,0,16,0,0,0,0,0,0,0,24,0,63,224,0,7,120,0,16,0,0,0,0,0,0,0,8,0,96,48,0,12,12,0,48,0,0,0,0,0,0,0,8,0,64,28,0,24,4,0,32,0,0,0,0,0,0,0,8,0,224,135,143,240,4,0,32,0,0,0,0,0,0,0,8,0,241,128,250,0,28,0,32,0,0,0,0,0,0,0,4,0,249,0,2,0,52,0,96,0,0,0,0,0,0,0,4,0,255,0,2,0,104,0,64,0,0,0,0,0,0,0,6,0,255,128,0,0,200,0,192,0,0,0,0,0,0,0,2,0,127,240,0,3,152,0,128,0,0,0,0,0,0,0,3,0,63,255,128,14,48,1,128,0,0,0,0,0,0,0,1,0,31,0,127,240,32,1,0,0,0,0,0,0,0,0,0,128,12,0,0,0,96,2,0,0,0,0,0,0,0,0,0,64,3,0,0,0,192,6,0,0,0,0,0,0,0,0,0,48,1,224,0,3,128,12,0,0,0,0,0,0,0,0,0,24,0,62,0,14,0,24,0,0,0,0,0,0,0,0,0,14,0,3,255,248,0,48,0,0,0,0,0,0,0,0,0,3,128,0,0,0,96,96,0,0,0,0,0,0,0,0,0,0,224,0,0,127,193,192,0,0,0,0,0,0,0,0,0,0,60,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,7,128,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,124,0,1,224,0,0,0,0,0,0,0,0,0,0,0,0,7,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
*/
 
void setup() {  
  Serial.begin(115200);
 
  Serial.println("Booting");
  
  
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  WiFi.begin(ssid, password);
  
  Serial.println("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) {
    yield();
    delay(50);
    Serial.print(".");
  }

  /*
  //WiFiClient client;
  client.connect(host, httpPort);
  
  
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  
  delay(1000);
  
  // Read all the lines of the reply from server and print them to Serial
  pointer=0;
  while(client.available()){
    String line = client.readStringUntil(',');
    //logo16_glcd_bmp[pointer] = line.toInt();
    bmp[pointer] = line.toInt();
    pointer++;
    //Serial.println(line.toInt() );
  }

  Serial.println("Ready to display");
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3C (for the 128x32)

  Serial.println("----Width and Height---");
  Serial.println( display.width() );
  Serial.println( display.height() );
  Serial.println("-----");
  */
  
}
 
 
void loop() {
   yield();
  int x =0;
  int y =0;
  int counter=0;

  // Serial.println(loopCounter);
  
  display.clearDisplay();
  //display.drawBitmap(0, 0,  logo16_glcd_bmp, 128, 64, 1);

  /*
  for (int x=0; x < 128; x++) {
    for (int y=0; y < 64; y++) {
      if (logo16_glcd_bmp[ x + (y*128)] == 1) {
        display.drawPixel(x,y,1);
      }
    }
  }
  */

  if (haveData) {
    // 64 rows
    for (int k=0; k < 64; k++) {
      
      // each row has 8 16bit numbers
      for (int j=0; j < 8;j++) {
        // move x to the end of the 16bit run
        x = 16*j;
  
        // get the next 16bit number
        int a = bmp[counter];
        
          // for each bit in the number, 
          for (int i=0; i < 16; i++) {
  
            // if the pixel is on(1) then display it
            if ( a & 1 ? 1:0 == 1) {
              display.drawPixel(x-i,k,1);
            } 
  
            // shift all the bits over
            a >>=1;
          }
  
          // increase the counter by 1 to get the next number
          counter++;
      }
    }
  }
  
 /*
  for (int j=0; j < 513; j++) {
    int a = bmp[j];

    x += 15;
    if (x >= 121) { x=15; y++ ; }
    
    if (a == 0) { continue; }
    
    for (int i=0; i < 16; i++) {
       if ( a & 1 ? 1:0 == 1) {
        display.drawPixel(x-i,y,1);
      }   
      a >>=1;
    }
     
  }
*/
  display.setCursor(0,0);
  display.display(); // actually display all of the above
  //delay(10);
  loopCounter++;
  
  
  if (loopCounter==1) {
    //Serial.println("Connect...");
    client.connect(host, httpPort);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n"); 
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D); 
  }

  if (loopCounter==30) {
    //Serial.println("Getting data...");
    pointer=0;
    while(client.available()){
      String line = client.readStringUntil(',');
      //logo16_glcd_bmp[pointer] = line.toInt();
      bmp[pointer] = line.toInt();
      pointer++;
      //Serial.println(line.toInt() );
    }
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D); 
    haveData=1;
  }

  if (loopCounter > 90) {
    loopCounter=0;
  }
 
   
}
