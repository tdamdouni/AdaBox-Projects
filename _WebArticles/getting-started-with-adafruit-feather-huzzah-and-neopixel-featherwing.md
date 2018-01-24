# Getting started with Adafruit Feather Huzzah and Neopixel FeatherWing

_Captured: 2017-10-07 at 18:06 from [richardhayler.blogspot.de](https://richardhayler.blogspot.de/2016/04/getting-started-with-adafruit-feather.html?m=1)_

The Adafruit Feather boards are a great size and the growing ecosystems of add-ons and compatible boards is really impressive.

This blog describes a quick-start project for the ESP8266 Huzzah Feather board with a Neopixel featherwing to provide a simple status indicator.

We're going to use the ESP8266 to scan for available WiFi networks and alert us if any insecure (open, with no encryption and requiring no password) networks are found. This might be a useful sensor for the corporate environment where sysadmins want to ensure nobody is introducing un-protected access routes into their network. Red LEDs indicate that a possible rogue AP has been found, all green means everything is ok.

![](https://4.bp.blogspot.com/-YcU1oxmlASM/VyEgR1h33II/AAAAAAAAGVM/WGEHTLmBrHQ3bh2ctoD0AgC_ImFSKxP7ACLcB/s280/green3.jpg)

###  **Hardware Setup**

Depending on where you purchased you boards from, you may need to solder header pins. I added female headers to the Huzzah and males to the NeoPixel FeatherWing so that the two simply connect together like a couple of mating beetles!

![](https://1.bp.blogspot.com/-teWtiD772kw/Vx_KEAdqY0I/AAAAAAAAGT8/wGkehZDOlZ84ejHD3V44WedJ0s-QKiGvgCLcB/s280/IMG_1741.JPG)

The Neopixel_FeatherWing needs to have a jumper set to work with the EXP8266 Huzzah Feather. Using a sharp knife, break the preset jumper on pin 16 and then solder across the jumper on pin 15.

![](https://1.bp.blogspot.com/-MKCRY5YrtCQ/VyEFmqenKAI/AAAAAAAAGUk/8gdldWqUFYktDNqyw8P47Qv5eROcJR_sACLcB/s280/feather.png)

###  Software Setup

1\. Ensure your Arduino Sketch editor is the latest version

2\. Install the [CP210x USB to UART Bridge Virtual COM Port (VCP) drivers](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx)

3\. Download the [Adafruit Neopixel library for Arduino](https://github.com/adafruit/Adafruit_NeoPixel). Download the zip file from the Github page and unzip it. Then rename the extracted folder to Adafruit_Neopixel and copy it to your Arduino libraries folder (on a Mac that's in /home/<user>/Documents/Arduino/libraries).

4\. Add the ESP8266 board package as an additional board into the editor's preferences.

![](https://1.bp.blogspot.com/-4jkHykU6sF4/Vx5pKdFm7fI/AAAAAAAAGTU/M-1e8kSwY0YSzPzOCt-19TUcpnYnmm8iACLcB/s280/Snip20160425_1.png)

5\. Now go to Tools -> Board: -> Boards Manager

Scroll down to the bottom and click the ESP8266 entry, then click the Install button

![](https://1.bp.blogspot.com/-XidN2WdF5Bk/Vx5pvZMMoZI/AAAAAAAAGTY/8__HI39ne2wNksijDUdHQjNJ3TRwIdbPACLcB/s280/Snip20160425_2.png)

6\. Once that's finished, go back to Tools-> and select the Adafruit Huzzah ESP8266 board. All the default values should be set, but make sure the Port setting corresponds to how you have connected your Feather (on a Mac it is normally /dev/cu.SLAB_USBtoUART).

![](https://2.bp.blogspot.com/-gXxLm2O1ft4/VyEetVxqKWI/AAAAAAAAGU8/nQpvmYMQYkMffcAWyJakArBdY_fcve6ngCLcB/s320/Snip20160427_3.png)

7\. Now for some test code. Copy this into your Ardunio Sketch editor and then click the Upload button.

```
#include "ESP8266WiFi.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(32, 15, NEO_GRB + NEO_KHZ800);
int OPEN = 0;
void allOn(char* col);
void setup() {
  pixels.begin();
  Serial.begin(115200);
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Setup done");
}
void allOn(char* col) {
    //Pulsing
        if (col == "red"){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
            for (int p=0;p<200;p++){
                for(int i=0;i<32;i++){
                 // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                    pixels.setPixelColor(i, pixels.Color(p,0,0)); // Moderately bright red color.
                    pixels.show();
                }
            delay(1);
            }
            for (int p=200;p>0;p--){
                for(int i=0;i<32;i++){
  
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                    pixels.setPixelColor(i, pixels.Color(p,0,0)); // Moderately bright red color.
                    pixels.show();
                }
            delay(1);
            }
        } else {
           for (int p=0;p<200;p++){
               for(int i=0;i<32;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                   pixels.setPixelColor(i, pixels.Color(0,p,0)); // Moderately bright green color.
                   pixels.show(); 
               }
           delay(1);
           }
           for (int p=200;p>0;p--){
               for(int i=0;i<32;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
                   pixels.setPixelColor(i, pixels.Color(0,p,0)); // Moderately bright green color.
                   pixels.show();
               }
          delay(1);
          }
       }
    //}
}
void loop() {
  Serial.println("Starting Scan");
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete");
  if (n == 0)
    Serial.println("No networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found:");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
    
      byte enc = WiFi.encryptionType(i);
      Serial.print(" Encryption: ");
      Serial.println(enc,HEX);
      // No encryption - open network
      if (enc == 7){
        OPEN++; 
      }
    
      delay(10);
    }
  }
  if (OPEN  > 0){
    Serial.println("Alert");
    allOn("red");
  } else {
    Serial.println("All good");
    allOn("green");
  }
  pixels.show();
  Serial.println("");
  OPEN = 0;
}
```

If you open up the Serial Monitor (Tools ->) you will be able to see the SSIDs and signal strengths of the networks that the ESP8266 finds.
