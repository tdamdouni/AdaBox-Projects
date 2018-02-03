# NERD ALERT! // Smart Doorbell with Arduino

_Captured: 2018-02-02 at 12:52 from [www.hackster.io](https://www.hackster.io/glowascii/nerd-alert-smart-doorbell-with-arduino-e31fc2?utm_source=Hackster.io+newsletter&utm_campaign=994f82f734-EMAIL_CAMPAIGN_2017_07_26&utm_medium=email&utm_term=0_6ff81e3e5b-994f82f734-141949901&mc_cid=994f82f734&mc_eid=1c68da4188)_

![NERD ALERT! // Smart Doorbell with Arduino](https://hackster.imgix.net/uploads/attachments/412261/screen_shot_2018-01-26_at_6_06_14_pm_Qlz93cDpaq.png?auto=compress%2Cformat&w=900&h=675&fit=min)

We needed a doorbell for our freight elevator. I'm pretty much the only one who uses the freight elevator. So, a NERD ALERT seemed in order...

This one uses a red-backlit LCD display, showing "NERD ALERT!", as well as a typical siren noise, to indicate that somebody needs to come rescue me when I push the button in the elevator.

I wanted something quick and dirty to shove in a cardboard box; it didn't need to be small or pretty, and so I used an Arduino 101 with a Seeed Grove kit. (An Uno would do just fine, and work the same way.)

After plugging the Grove base shield into my Arduino, I plugged the buzzer module into pin **D3**, and the RGB backlit LCD module into an **I2C** port. I wanted the button to be simple, since I have to run cable all the way from the door to the inside wall-mounted module, so I used a regular button with two wires attached to pin **D2** (on the Arduino's standard female headers) and **GND**. Condensed version:

  * Buzzer module > D3 port
  * LCD module > I2C port
  * Button > Arduino pins D2, GND

Make sure you have the Grove LCD shield set to 5V! If it's on 3V3, the text doesn't show up - just the backlight.

I'm powering the whole thing with a 12V wall plug that feeds into the Arduino's barrel jack. I don't want to use a perfectly good USB cable for something that's just gonna stay plugged into the wall. ¯\\_(ツ)_/¯

I cobbled together something fairly disgusting from the [Seeed Grove Kit examples on GitHub](https://github.com/Seeed-Studio/Sketchbook_Starter_Kit_V2.0); you can download my code below. I did have to [download and install the Arduino library](http://wiki.seeed.cc/Grove-LCD_RGB_Backlight/#step1-download-arduino-library) for the LCD. (To do this, unzip the file and place it in your _/Arduino/libraries_ folder.)

I figured that an alternating minor third (A-C-A-C-A-C...) would do for a siren noise, and I didn't really care what pitch or octave it ended up being, so it's probably a little inaccurate. Being fairly low-pitched, this is actually not that annoying. I may have to do better.

I used the **INPUT_PULLUP** mode for the button, because that means I don't have to stick a pullup or pulldown resistor in my circuit; it's all handled onboard by the Arduino.

When the button is pushed, the LCD scrolls "NERD ALERT!" on both lines, and it lights up with a red backlight.

Altogether, this build took me about an hour to debug. Then, I just stuffed the main bits into a cardboard box, ran the button wire to the elevator, and mounted both to their respective walls.
