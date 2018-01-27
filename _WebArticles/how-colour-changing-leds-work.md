# How Colour Changing LEDs Work

_Captured: 2017-11-26 at 23:30 from [www.kitronik.co.uk](https://www.kitronik.co.uk/blog/how-colour-changing-leds-work/)_

A [colour changing LED](https://www.kitronik.co.uk/leds-and-lamps/colour-changing-and-rgb-leds.html) isn't one LED in a package but three LEDs along with a small computer to drive them. The LED is made up of red, green and blue LEDs each of which can be controlled by a microcontroller. Since the two legs on the LED that supply the power are connected to the microcontroller and not the LED elements a current limit resistor is not required.

The microcontroller is able to turn each of the colours on or off, so if the red LED is turned on then the output from the colour changing LED is red. When the blue LED is turned on it is blue, if both the blue and red LEDs are turned on then the colour changing LED is a shade of purple (called magenta). Similarly combining red with green gives yellow and blue & green gives cyan.

Although the colour changing LED uses the six colours mentioned above, it slowly changes from one to another. This is still done using the three basic red, green & blue elements. If the red LED is combined with the blue LED, but the blue LED is only driven at 50% of its normal brightness then a colour half way between red and magenta is generated.

Whilst the red LED is left turned on, if the blue LED is slowly taken from 0% brightness to 100% brightness then the colour will gradually change from red to magenta.

If a standard LED is turned on and off very quickly, say 100 times every second then as far as the human eye is concerned it looks like it is constantly on. If the amount of time the LED is on for is the same as the time it is off for then it will be on for 50% of the time and 50% of its full brightness.

This same method can be done with the three LED elements inside the colour changing LED. This means it is possible to combine any amount of the red, green and blue to give the desired colour. Looking once again at the change from red to magenta, if the blue LED starts mainly turned off, goes to being on and off in even amounts and then to mainly being on then the the colour will change as required.

Download a pdf version of this page [here](https://www.kitronik.co.uk/pdf/How_colour_changing_LEDs_work.pdf)

Learn more about the author [read more »](https://www.kitronik.co.uk/about/geoff-hampson/)

(C)Kitronik Ltd - You may print this page & link to it, but must not copy the page or part thereof without Kitronik's prior written consent.

![E-Textiles](https://www.kitronik.co.uk/img/banners/e_textiles.png)

> _<- Previous Post Next Post ->_
