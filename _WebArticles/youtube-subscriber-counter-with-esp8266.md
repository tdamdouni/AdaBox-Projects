# YouTube Subscriber Counter With ESP8266

_Captured: 2017-09-14 at 09:39 from [www.instructables.com](http://www.instructables.com/id/YouTube-Subscriber-Counter-With-ESP8266/)_

![YouTube Subscriber Counter With ESP8266](https://cdn.instructables.com/FZF/MSM1/IZ6D9U8C/FZFMSM1IZ6D9U8C.MEDIUM.jpg)

I was inspired by the Play Button awards YouTube sends out for subscriber milestones and whipped up a simple circuit using an ESP8266 wifi board and seven segment display to show off my realtime subscriber count. This is a great IoT beginner project, with just a little soldering and a code personalization required to make it work for your own account.

Before attempting this project, you should be generally familiar with uploading new programs to your Arduino board and installing code libraries, both of which you can learn for free in my [Arduino Class](https://www.instructables.com/class/Arduino-Class/), though you really don't have to understand any of the actual Arduino code to get this project running.

For this project, you will need the following materials:

  * Printer and paper
  * Scissors
  * [Cutting mat](http://www.amazon.com/dp/B0025189VE/?tag=instructabl09-20) or scrap cardboard
  * Illustration board or more scrap cardboard
  * [Metal ruler](http://www.amazon.com/dp/B005XUHIBG/?tag=instructabl09-20) (optional)
  * Tape
  * Glue stick
  * [Micro USB cable](https://www.adafruit.com/products/592) (charge + sync, not charge-only)
  * [USB power adapter](https://www.adafruit.com/products/501) (optional)

and the following tools:

Required software libraries:

Unique data required:

_As an alternative to the Feather Huzzah, you can also use your favorite ESP8266 microcontroller board, some of which require [an FTDI cable](https://www.adafruit.com/products/70) to upload new programs. Use the [standard 7-segment backpack](https://www.adafruit.com/categories?q=Adafruit%200.56%22%204-Digit%207-Segment%20Display%20w%2FI2C%20Backpack&) rather than the FeatherWing version._

## Step 1: Assemble Circuit

![Assemble Circuit](https://cdn.instructables.com/FMX/JS4B/IZ6DA2YG/FMXJS4BIZ6DA2YG.MEDIUM.jpg)

![iot-weather-display-05.jpg](https://cdn.instructables.com/FHS/KHEF/IZ6C9OR1/FHSKHEFIZ6C9OR1.SMALL.jpg)

![iot-weather-display-06.jpg](https://cdn.instructables.com/F4C/0BML/IZ6C9OR6/F4C0BMLIZ6C9OR6.SMALL.jpg)

![iot-weather-display-10.jpg](https://cdn.instructables.com/FRI/EB9L/IZ6C9P0C/FRIEB9LIZ6C9P0C.SMALL.jpg)

Follow the official [assembly instructions for the Feather Huzzah](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide) using female headers (or stacking headers, though you'd have to cut the long legs off) Likewise follow the assembly instructions for your [seven-segment FeatherWing display](https://learn.adafruit.com/adafruit-7-segment-led-featherwings/?view=all).

Before you dive into the code for this project, you should first make sure you've got your Arduino software set up properly to program the board you are using, which in my case involves installing the [SiLabs USB driver](https://www.silabs.com/products/mcu/Pages/USBtoUARTBridgeVCPDrivers.aspx) and installing ESP8266 board support (explained in more detail in the [Feather Huzzah tutorial](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)):

  * Go to Arduino-> Preferences...
  * Look for a text field labeled "Additional Boards Manager URLs:" and paste the following URL into the field (separate multiple URLs with commas if applicable): 
    
        <a href="http://arduino.esp8266.com/stable/package_esp8266com_index.json">http://arduino.esp8266.com/stable/package_esp8266c...</a>

  * Click OK
  * Go to Tools->Board-> Boards Manager...
  * Search for ESP8266 and click the Install button in the box "esp8266 by ESP8266 Community" when it shows up

Huzzah ESP8266 boards have an LED connected to pin 0, and you can find a sample blink sketch by navigating to File->Examples->ESP8266->Blink, or copy it from here:
    
    
    void setup() {
      pinMode(0, OUTPUT);
    }
    void loop() {
      digitalWrite(0, HIGH);
      delay(500);
      digitalWrite(0, LOW);
      delay(500);
    }
    

Plug in your USB cable to the board and configure your settings under the Tools menu as follows:

  * Board: Adafruit Huzzah ESP8266
  * CPU Frequency: 80MHz
  * Flash Size: 4M (3M SPIFFS)
  * Upload Speed: 115200
  * Port: whichever one ends in SLAB_USBtoUART (Mac) or COMx (Windows)

Click the Upload button to send the program to your board. This will take several seconds (longer than you are used to with Arduino Uno). After complete, the onboard LED should start blinking.

_While the Feather Huzzah auto-detects when it's being sent a new program, other ESP8266 boards may require a _[sequence of button presses](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout#using-arduino-ide)_ to get into bootloader mode._

Do not proceed until you've successfully uploaded a blink test program to your board.

![Customize Code & Program Board](https://cdn.instructables.com/FSU/9P8M/IZ6D4VDA/FSU9P8MIZ6D4VDA.MEDIUM.jpg)

![Print Paper Template](https://cdn.instructables.com/FRI/LV2P/IZ6D9Q6Y/FRILV2PIZ6D9Q6Y.MEDIUM.jpg)

![Screen Shot 2017-02-26 at 9.19.11 AM.png](https://cdn.instructables.com/FXT/1YY0/IZ6D4VE0/FXT1YY0IZ6D4VE0.MEDIUM.jpg)

![Put It All Together](https://cdn.instructables.com/FAI/ZU9E/IZ6DAFDM/FAIZU9EIZ6DAFDM.MEDIUM.jpg)

![Enjoy!](https://cdn.instructables.com/FGE/ZCD5/IZ6D4VDH/FGEZCD5IZ6D4VDH.MEDIUM.jpg)

![subscriber counter 00.jpg](https://cdn.instructables.com/F1T/5B55/IZ6D4VD1/F1T5B55IZ6D4VD1.MEDIUM.jpg)
