# ESP8266 Mini Sniff

_Captured: 2017-11-11 at 01:53 from [www.hackster.io](https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a)_

![ESP8266 Mini Sniff](https://hackster.imgix.net/uploads/attachments/209598/giphy.gif?auto=compress%2Cformat&w=900&h=675&fit=min)

I am constantly amazed at what the inexpensive ESP8266 can perform using only some creative software. In this article, I provide the Arduino sketch code to morph the WiFi device into a promiscuous WiFi scanner that will display both client and AP MAC addresses, broadcasts, signal strength and channel. It is a great project that listens silently to the WiFi 2.4G band looking for activity and then displaying it over the serial port. Since the signal strength is shown, you can even use this project to move your Access Point (WiFi router) around to find the best placement location in your home.

I have been working with the ESP8266 for over a year now; one project, the Tardis Time, has been running continuously since September 2015. Lately however, I have been using the NodeMCU (I am using the LoLin flavor from AliExpress) and I simply love the larger-sized breakout board but there is no reason you cannot use other sized and vendor breakouts: This project should run on any ESP8266 with 1M of flash storage.

As this is an all-software project, you should have it up and running in minutes. Just download the ZIP and put all of the files into your sketch folder. Please note that this is a multi-tab Arduino project, so there are more than one "program" file. Part of the difficulty in the software architecture of this project was to flatten the rather complex mess of code so that it "made sense" and allowed an interested programmer to follow what was going on. The use of function callback in the promiscuous functionality can easily obscure what is happening. By separating the code into "straight Arduino setup() and loop() and then putting all of the data structures into their own tab and putting all of the API functions into their own tabs, I hope that I have accomplished some simplification in what is going on in the sketch. However, I still consider this a complex project.

To give you an idea of what I am talking about in the above paragraph, allow me to show you the main "INO" sketch tab:
    
    
    // by Ray Burnette 20161013 compiled on Linux 16.3 using Arduino 1.6.12 
    #include <ESP8266WiFi.h> 
    #include "./functions.h" 
    #define disable 0 
    #define enable  1 
    // uint8_t channel = 1; 
    unsigned int channel = 1; 
    void setup() { 
     Serial.begin(57600); 
     Serial.printf("\n\nSDK version:%s\n\r", system_get_sdk_version()); 
     Serial.println(F("ESP8266 mini-sniff by Ray Burnette http://www.hackster.io/rayburne/projects")); 
     Serial.println(F("Type:   /-------MAC------/-----WiFi Access Point SSID-----/  /----MAC---/  Chnl  RSSI")); 
     wifi_set_opmode(STATION_MODE);            // Promiscuous station mode 
     wifi_set_channel(channel); 
     wifi_promiscuous_enable(disable); 
     wifi_set_promiscuous_rx_cb(promisc_cb);   // Set up promiscuous callback 
     wifi_promiscuous_enable(enable); 
    } 
    void loop() { 
     channel = 1; 
     wifi_set_channel(channel); 
     while (true) { 
       nothing_new++;                          // Check bounds 
       if (nothing_new > 200) { 
         nothing_new = 0; 
         channel++; 
         if (channel == 15) break;             // Only scan channels 1 to 14 
         wifi_set_channel(channel); 
       } 
       delay(1);                              // critical processing timeslice 
     } 
    } 
    

The critical set-up is in the line** wifi_set_promiscuous_rx_cb(promisc_cb)** and the real work-horse of this sketch is essentially managed in the function **promisc_cb()**.

This line **#include "./functions.h"** in the main sketch tells the ArduinoIDE to includes all of the code in the tab "functions.h" and within the function.h code is **#include "./structures.h" **and therefore all three tabs are linked.

There is really little more that can be said about this project other than to provide some sample output. The first screen below is what the user may expect to see after the device is programmed for the 1st time (or powered on from the off state.)
    
    
    1.5.3(aec24ac9) 
    ESP8266 mini-sniff  
    by Ray Burnette http://www.hackster.io/rayburne/projects 
    Type:   /-------MAC------/---- SSID----/  /----MAC---/  Chnl  RSSI 
    BEACON: <=============== [HOME-01FC-2.4]  84002da251d8    6    -93 
    BEACON: <=============== [   TardisTime]  1afe34a08bc9    8    -80 
    BEACON: <=============== [  xfinitywifi]  84002da251da    6    -92 
    DEVICE: 18fe34f977a0 ==> [   TardisTime]  1afe34a08bc9    8    -91 
    BEACON: <=============== [             ]  fa8fca34e26c   11    -86 
    BEACON: <===============      HOME-30C2]  5c571a0730c0   11    -85 
    DEVICE: 6002b4484f2d ==>    Unknown/Malformed packet  
    BEACON: <=============== [             ]  52571a0730c0   11    -82 
    BEACON: <=============== [  xfinitywifi]  56571a0730c0   11    -88 
    BEACON: <=============== [   ATT8Q4z656]  b077acc4dfd0   11    -92 
    BEACON: <=============== [   ATTGH6Gs22]  1005b1d6ff90   11    -88 
    BEACON: <=============== [             ]  fa8fca95bad3   11    -94 
    BEACON: <=============== [             ]  92877c55b1c0   11    -93 
    DEVICE: 18fe34fdc2b8 ==> [   TardisTime]  1afe34a08bc9    8    -78 
    DEVICE: 6c71d970d1b7 ==> [   ATT8Q4z656]  01005e7ffffa   11    -94 
    BEACON: <=============== [             ]  84002da251d9    6    -90 
    BEACON: <=============== [    HOME-B1C2]  94877c55b1c0   11    -97 
    BEACON: <=============== [   ATT4P3G9f8]  1c1448777420   11    -94 
    DEVICE: 28b2bd6b9d29 ==> [   ATT8Q4z656]  ffffffffffff   11    -91 
    DEVICE: e0f847252fbc ==> [   ATT8Q4z656]  ffffffffffff   11    -91 
    DEVICE: a4773369c4d8 ==> [    HOME-30C2]  88cb8787697a   11    -91 
    BEACON: <=============== [  xfinitywifi]  96877c55b1c0   11    -92 
    

A little explanation to assist in understanding the printout:

An Access Point, AP, will occasionally "beacon" so that WiFi devices and other APs will know of its existence. It does this for the center frequency on which the AP is configured. The RSSI is a signal indicator of the received power: generally speaking, the higher the numeric number the weaker the signal (due to the minus sign.) A MAC address of all "ffffffffffff" is called a **broadcast** which has special network significance.

On the client (device) side, a MAC will be printed followed by "**==>**" to indicate communication (typically) with an AP. Again, the MAC of the receiving device is shown as well as the channel and the signal level.

Pretty simple stuff! Nothing to do now but download and have fun. I'll close with one caveat: "You are working on an API that is below what Arduino would normally access and you are working with complex data structures." Please do not muck with the code if you do not understand what your are doing: I consider this an advanced project as as such, I will not be answering questions on anything other than the Arduino IDE (1st tab) of the sketch. [The manufacturer of the ESP8266 has volumes of PDF references if you wish to educate yourself.](https://espressif.com/en/products/hardware/esp8266ex/overview)

Ray
