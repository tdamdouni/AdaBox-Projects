# ESP32 Photo Clock

_Captured: 2017-12-17 at 12:50 from [www.instructables.com](http://www.instructables.com/id/ESP32-Photo-Clock/)_

![](https://cdn.instructables.com/FY2/ULCL/JB3ZS2F1/FY2ULCLJB3ZS2F1.MEDIUM.jpg)

![](https://cdn.instructables.com/FCN/R4VF/JB3ZS2EJ/FCNR4VFJB3ZS2EJ.MEDIUM.jpg)

![](https://cdn.instructables.com/FFM/MD2O/JB3ZS2EV/FFMMD2OJB3ZS2EV.MEDIUM.jpg)

![](https://cdn.instructables.com/FEM/RDTS/JB3ZS2BZ/FEMRDTSJB3ZS2BZ.MEDIUM.jpg)

![](https://cdn.instructables.com/FA3/P4Q0/JB3ZS2BV/FA3P4Q0JB3ZS2BV.SMALL.jpg)

![](https://cdn.instructables.com/FMM/ETZ0/JB3ZS2E1/FMMETZ0JB3ZS2E1.SMALL.jpg)

## Step 4: Design

![](https://cdn.instructables.com/FU5/MKT6/JB3ZSLOT/FU5MKT6JB3ZSLOT.MEDIUM.jpg)

A photo clock require the ability to display photo. The photo at [ www.bijint.com ](http://www.bijint.com) is in JPG format so I need a JPG decode and display library. I am looking for the related library a long times ago, until ESP32 become popular.

ESP32 is the first hobby chip that have complete solution for displaying JPG image (thanks [loboris's effort](https://www.esp32.com/viewtopic.php?f=17&t=1937)). Before that, I can found some video in Youtube claimed can show JPG with ESP8266, but lack of source code.

So this project start from Loboris's [ESP32_TFT_library](https://github.com/loboris/ESP32_TFT_library).

Here is the program flow:

  1. Connect WiFi 
  2. Get current time with NTP protocol 
  3. Concat the hour and minute string to form the current time picture URL and then retrieve it from [ www.bijint.com](http://www.bijint.com) every minute
  4. Save the picture jpg file to SPIFFS
  5. Display jpg file

Design concerning details:

  1. WiFi is not 100% reliable and I don't want the clock freezes at a wrong time, so once encounter any error (e.g. DNS lookup fail, NTP fail, download fail) the program trigger restart and do it again. 
  2. Every minute have a single time picture means 1440 pictures a day, ESP32 built-in flash cannot fit hundreds MB pictures. So the clock cannot prefetch all pictures, but it can retrieve the picture every time, display it and then clean it up.
  3. Flash worn out easy from subsequent overwrite, so the program rotate the cache files to avoid write to the same place every minute.
  4. The picture size is bigger than the LCD resolution, so it is required to shrink the picture to half size to display. 
  5. The ESP-IDF built-in timezone adjustment not work as expected, so require adjust with custom code.
  6. Download file time require 10-50 seconds (depends on file size and network), so I have advanced 20 seconds (configurable) from the real time to overcome this delay.
![](https://cdn.instructables.com/FPR/33T2/JB3ZSGBR/FPR33T2JB3ZSGBR.MEDIUM.jpg)

![](https://cdn.instructables.com/FMY/BCD8/JB3ZS2C5/FMYBCD8JB3ZS2C5.MEDIUM.jpg)

![](https://cdn.instructables.com/FNB/A486/JB3ZS981/FNBA486JB3ZS981.MEDIUM.jpg)

![](https://cdn.instructables.com/F2T/ZLR4/JB3ZS2D0/F2TZLR4JB3ZS2D0.MEDIUM.jpg)

![](https://cdn.instructables.com/FE7/N5RP/JB3ZS2DS/FE7N5RPJB3ZS2DS.MEDIUM.jpg)

![](https://cdn.instructables.com/F47/83NP/JB3ZS2E7/F4783NPJB3ZS2E7.MEDIUM.jpg)

![](https://cdn.instructables.com/FNY/DDVQ/JB3ZS2EK/FNYDDVQJB3ZS2EK.MEDIUM.jpg)
