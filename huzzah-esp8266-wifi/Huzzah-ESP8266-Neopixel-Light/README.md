# Huzzah-ESP8266-Neopixel-Light
Brian Leschke 2017

## **Overview**

The ESP8266 will control a neopixel and change the color based on Weather events, Holidays, and Fire/EMS calls. 

Currently Implemented:
* Fire/EMS Call Alerts
* NOAA Weather Alerts (provided by wunderground)
    * Tornado Warning
    * Tornado Watch
    * Severe Thunderstorm Warning
    * Winter Weather
* Morse Code transmission from 433 Mhz chip
* Lights change color for Holidays

### **Prerequisities**

You will need:

1. Adafruit Huzzah ESP8266 (http://adafru.it/2471)
2. Flora Neopixel (http://adafru.it/1312)
3. Arduino Programming software
4. FTDI cable (https://www.sparkfun.com/products/9717)
5. Radio Transmitter (https://www.sparkfun.com/products/10534)

### **Usage**

In order to use successfully implement this project and its code, you will need to install the Arduino Programming Software.
    
### **Libraries**

The following libraries are required for this project:
    
  * [Arduino Framework (core library)](https://github.com/esp8266/Arduino)
  * ArduinoOTA
  * ArduinoJson
  * Adafruit_Neopixel
  * ESP8266WiFi
  * NTPClient
  * [JSON Streaming Parser](https://github.com/squix78/json-streaming-parser)
        
## **Uploading**

The code can be uploaded to the ESP8266 in two ways, either by OTA (over-the-air) updates or by a serial (FTDI cable) connection.
Users will need to initially upload the code using an FTDI cable.

### **FTDI Upload**

This method must be used in the initial flashing of the ESP8266. An FTDI or UART cable has 6 pins.
Every time the you want to flash the ESP8266, you will need to do the following to enter the bootloader mode:

  1. Press and hold the RESET button.
  2. Press and hold the GPIO0 button.
  3. Release the RESET button and continue to hold the GPIO0 button.
  4. Release the GPIO0 button (you should see a faint red glow from the GPIO0 LED).
  

### **OTA Upload**

Over-the-air updates is a method to update the ESP8266 without physically being with the device. To update the device you will need to
know the IP address and be connected to the same network.

If for some reason, the network ESP8266 network configuration is incorrect, the device will restart.


### **Recognition and Credit**
I would like to recognize [cjntaylor](https://github.com/cjntaylor/) and other users/projects for some inspiration and ideas.
Thanks to Mike Rankin for the example parsing code! (to be implemented in the future)
