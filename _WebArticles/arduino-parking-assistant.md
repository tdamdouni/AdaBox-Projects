# Arduino Parking Assistant

_Captured: 2017-11-22 at 09:18 from [www.instructables.com](http://www.instructables.com/id/Arduino-Parking-Assistant/)_

![](https://cdn.instructables.com/F0Q/OHZ1/J0COVN2Y/F0QOHZ1J0COVN2Y.MEDIUM.jpg)

![](https://cdn.instructables.com/FTP/UWZO/J0COVN2H/FTPUWZOJ0COVN2H.SMALL.jpg)

![](https://cdn.instructables.com/FGZ/DNIQ/J0COW677/FGZDNIQJ0COW677.ANIMATED.MEDIUM.gif)

Those of us who have small garages know the frustration of parking a little bit too far in or a little too far out and not being able to walk around the vehicle. We recently bought a larger vehicle, and it has to be parked perfectly in the garage to walk around the front and back.

To appease my frustration I decided to design a device that would allow me to park in the exact spot every time. I love working with arduinos, leds, sensors, and nearly anything else electronic, so I knew from the start that it would probably end up as a contraption with an Arduino inside and a bunch of LEDs on the front!

I tried my best to document every step of this project well, but please note that it has some complicated, tight soldering; it probably shouldn't be your first project.

## Step 1: You Will Need...

![](https://cdn.instructables.com/FT8/47DK/J0COVN5U/FT847DKJ0COVN5U.MEDIUM.jpg)

![](https://cdn.instructables.com/F27/N3TK/J0COVN5R/F27N3TKJ0COVN5R.SMALL.jpg)

![](https://cdn.instructables.com/FE1/NXUC/J0COVN7P/FE1NXUCJ0COVN7P.SMALL.jpg)

All of these materials are cheap and easily available. I'm not affiliated with any of these suppliers, they're simply where I bought the supplies.

**Materials:**

  * 1x 2x4 - at least 8" long 
  * 8x Philips Screws - Preferably 1" Long 
  * 1x Power Supply - 5 volt, 850mA [Here](https://www.walmart.com/ip/Motorola-Original-Travel-Wall-Charger-Adapter-to-Micro-USB-Data-Cable-6ft/822221868?wmlspartner=wlpa&selectedSellerId=1056&adid=22222222227068707795&wmlspartner=wmtlabs&wl0=&wl1=g&wl2=c&wl3=174510555055&wl4=pla-283793518492&wl5=1019250&wl6=&wl7=&wl8=&wl9=pla&wl10=112354288&wl11=online&wl12=822221868&wl13=&veh=sem)
  * 1x Arduino Pro Mini - 5 volt, 16MHz [Here](http://www.ebay.com/itm/3Pcs-Atmega328P-Arduino-Mini-Pro-Mini-Board-Compatible-Nano-Module-5V-16MHZ-USA-/222405448415?hash=item33c865d2df:g:AZoAAOSwzhVWqn~U)
  * 1x HC-SR04 Ultrasonic Distance Sensor [Here](http://www.ebay.com/itm/HC-SR04-Ultrasonic-Distance-Measuring-Sonar-Transducer-Module-for-Arduino-/172078422183?hash=item2810ac58a7:g:CoAAAOSw44BYiXHF)
  * 12x Through-Hole Resistors - 220 ohm, 1/4 watt [Here](https://www.adafruit.com/products/2780)
  * 8x Green LEDs - 5mm [Here](https://www.superbrightleds.com/moreinfo/through-hole/5mm-green-led-32-degree-viewing-angle-7500-mcd/272/1199/)
  * 4x Red LEDs - 5mm [Here](https://www.superbrightleds.com/moreinfo/through-hole/5mm-red-led-30-degree-viewing-angle-8000-mcd/281/1208/)
  * 1x Tactile Pushbutton - 6mm [Here](https://www.adafruit.com/product/367)
  * 3x Four Conductor Wire Sold by the Foot - 22 gauge [Here](https://www.superbrightleds.com/moreinfo/power-wires/rgb-4wire-four-conductor-rgb-wire/45/288/)
  * 1x Stranded Wire - 28 gauge [Here](http://www.ebay.com/itm/5-Foot-50-Conductor-ALPHA-WIRE-Rainbow-Ribbon-Cable-050-300V-Flat-Stranded-/121609437173?hash=item1c507cbff5:g:-1EAAOxyGwNTEMnn)

**Tools:**

  * Wire Stripper 
  * Bandsaw 
  * Soldering Iron 
  * Solder - I use 60/40 Rosin Core 
  * Hot Glue Gun 
  * Speed Square 
  * Stick Glue 
  * Philips Screwdriver 
  * Pencil 
  * Drill 
  * 7/64" Drill Bit - this depends on the size of your screws 
  * 3/16" Drill Bit 
  * 1/4" Drill Bit 
  * 1" Forstner Bit 

## Step 2: Print and Cut!

![](https://cdn.instructables.com/F65/2SA1/J0COVN6R/F652SA1J0COVN6R.MEDIUM.jpg)

![](https://cdn.instructables.com/FT6/R3TG/J0COVN14/FT6R3TGJ0COVN14.MEDIUM.jpg)

The first step in this project is to make the enclosure. We're using a technique I wrote about in an earlier Instructable, Easy 2x4 Enclosures.

Print the PDF Pattern included below. Be sure you're set to print at 100% scale.

Now cut out the pattern and glue it to the 2x4. Be careful to line it up with the edges. It's only temporary, so only glue it lightly.

![](https://cdn.instructables.com/FS4/AACP/J0COVN05/FS4AACPJ0COVN05.MEDIUM.jpg)

![](https://cdn.instructables.com/FUT/GKAR/J0COVN09/FUTGKARJ0COVN09.MEDIUM.jpg)

![](https://cdn.instructables.com/FV5/NXNI/J0COVN0L/FV5NXNIJ0COVN0L.MEDIUM.jpg)

![](https://cdn.instructables.com/FMT/N88P/J0COVN0W/FMTN88PJ0COVN0W.SMALL.jpg)

![](https://cdn.instructables.com/FQ3/SOEV/J0COVMZP/FQ3SOEVJ0COVMZP.MEDIUM.jpg)

![](https://cdn.instructables.com/F8E/I1VO/J0COVMZC/F8EI1VOJ0COVMZC.SMALL.jpg)

![](https://cdn.instructables.com/FUL/Z20N/J0COVN17/FULZ20NJ0COVN17.MEDIUM.jpg)

![](https://cdn.instructables.com/F8Y/R3O0/J0COVN6T/F8YR3O0J0COVN6T.MEDIUM.jpg)

![](https://cdn.instructables.com/FLS/J0ET/J0COVN46/FLSJ0ETJ0COVN46.MEDIUM.jpg)

![](https://cdn.instructables.com/F4D/VMA3/J0COVN72/F4DVMA3J0COVN72.MEDIUM.jpg)

![](https://cdn.instructables.com/FOP/KIYH/J0COVN4M/FOPKIYHJ0COVN4M.MEDIUM.jpg)

![](https://cdn.instructables.com/FOT/2IAK/J0COVN4U/FOT2IAKJ0COVN4U.MEDIUM.jpg)

![](https://cdn.instructables.com/FL2/BXZX/J0COVN4V/FL2BXZXJ0COVN4V.MEDIUM.jpg)

![](https://cdn.instructables.com/F1Z/R1I5/J0COVN02/F1ZR1I5J0COVN02.MEDIUM.jpg)

![](https://cdn.instructables.com/F27/B63L/J0COVPFF/F27B63LJ0COVPFF.MEDIUM.jpg)

![](https://cdn.instructables.com/F5H/ULDD/J0COVN1P/F5HULDDJ0COVN1P.MEDIUM.jpg)

![](https://cdn.instructables.com/FTS/MZ8Y/J0COVN8A/FTSMZ8YJ0COVN8A.MEDIUM.jpg)

![](https://cdn.instructables.com/FH6/DJVN/J0CP4EM8/FH6DJVNJ0CP4EM8.MEDIUM.jpg)
