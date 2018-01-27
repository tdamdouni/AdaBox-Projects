# RGB Matrix + Spectrum Analyzer

_Captured: 2017-11-25 at 14:49 from [www.instructables.com](http://www.instructables.com/id/RGB-Matrix-Spectrum-Analyzer/)_

![](https://cdn.instructables.com/FWN/K44K/JA8JC7QH/FWNK44KJA8JC7QH.MEDIUM.jpg)

## Step 3: Prototyping.

![](https://cdn.instructables.com/FQL/JNSQ/JA7HT09I/FQLJNSQJA7HT09I.MEDIUM.jpg)

![](https://cdn.instructables.com/FPQ/0PDL/JA7HT0BV/FPQ0PDLJA7HT0BV.SMALL.jpg)

![](https://cdn.instructables.com/F8P/6N43/JA7HT0HB/F8P6N43JA7HT0HB.SMALL.jpg)

![](https://cdn.instructables.com/F0M/23LR/JA7HT0NQ/F0M23LRJA7HT0NQ.SMALL.jpg)

![](https://cdn.instructables.com/F95/UGUP/JA7HT3FI/F95UGUPJA7HT3FI.SMALL.jpg)

![](https://cdn.instructables.com/F1B/AL5S/JA7HT3RY/F1BAL5SJA7HT3RY.SMALL.jpg)

Download and add these Arduino Libraries:  
FastLED - <https://github.com/FastLED/FastLED>  
Aadafruit NeoPixel Library - <https://github.com/adafruit/Adafruit_NeoPixel>

Test the WS2812B LED Strip using the FirstLight sketch from examples of FastLED library. Edit the data pin and number of LEDs and after uploading the LEDs should light up white one after another showing that the LEDs are working fine.

Now build the test circuit using the circuit diagram attached in this step without IR Receiver. Upload the sketch, also attached in this step. You will need 21 LEDs. The MSGEQ7 divided audio spectrum into 7 frequency bands. So, keeping that in mind, the sketch divides 21 LEDs in to 7 sets, each set having 3 LEDs, first LED will be always off and the rest two LEDs will light up according to the intensity of audio in that particular frequency band. Look out for analog values of all the seven bands in the Serial Monitor for debugging and making sure everything looks good. When this is working fine, finalize the prototyping by adding the IR Receiver.

Now add the Infrared receiver and upload the second attached I have attached which will light up 2 sets having 7 LEDs each according to the intensity of audio signal from any two band which you can edit in the sketch. I will suggest you to choose bands 3 and 4.  
Now determine the hex code of any of the button in IR remote you are using.  
To know how to do that, click here: [https://www.instructables.com/id/Control-AC-Applia..  
](https://www.instructables.com/id/Control-AC-Appliances-Sitting-on-Your-Bed/)Edit that hex code in the sketch and upload it. Now when you press the button, the LEDs will show animation and when you press the same button again, it will switch back to spectrum analyzer mode.

And the prototyping is complete.

![](https://cdn.instructables.com/FGB/CRAT/JA7HT15W/FGBCRATJA7HT15W.MEDIUM.jpg)

![](https://cdn.instructables.com/FQO/O4GS/JA7HT0NW/FQOO4GSJA7HT0NW.MEDIUM.jpg)

![](https://cdn.instructables.com/FNS/7Q8M/JA7HT3I6/FNS7Q8MJA7HT3I6.MEDIUM.jpg)

![](https://cdn.instructables.com/FGR/SCXB/JA7HT0TJ/FGRSCXBJA7HT0TJ.MEDIUM.jpg)

![](https://cdn.instructables.com/FPI/JLOC/JA7HT1UX/FPIJLOCJA7HT1UX.MEDIUM.jpg)

![](https://cdn.instructables.com/FO3/PO8S/JA7HT2CB/FO3PO8SJA7HT2CB.SMALL.jpg)

![](https://cdn.instructables.com/FMZ/093N/JA7HT3BZ/FMZ093NJA7HT3BZ.MEDIUM.jpg)
