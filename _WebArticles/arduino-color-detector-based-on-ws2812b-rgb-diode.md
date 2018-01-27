# Arduino Color Detector Based on Ws2812b RGB Diode

_Captured: 2017-11-12 at 22:17 from [www.instructables.com](http://www.instructables.com/id/Arduino-Color-Detector-Based-on-Ws2812b-RGB-Diode/)_

Today, in industry machines can recognize shape. dimensions, position of products on line and many other parametes. One is the color of them. At example in factory of chips it's using in order to check the quality of potatoes. One method is to use cameras and dedicated software, second simplier three colour light (based on RGB) and photocell. If You have Arduino and abut 20 minutes you Can build something similar to recognize colours of M&M's, papers or you'r Cat. It can be adapt in robot or candy's sorting machine or builded just for that.

## Step 1: HOW IT WORKS?

Easly.

Our detector will check 3 basics colors - **r**ed, **g**reen, **b**lue, which is making the RGB pallet. Combination of all of them takes us white color and eg. when we combine Red and Blue we will have pink.you'r display is using this principle.

So we need to check if the tested material red, blue or green. We'll base on rule that material color will reflect the most the color of that. So if eg. we have light sensor and under them blue object and then we will illuminate it one by one by red, blue and green light, the biggest amount of light will come to sensor after blue illumination.

For the 3 color light we will use RGB digital diode. For the sensor photoresistor and 10kOhm Resistor (in order to make voltage divider). We will checking the voltage between reisostors on analog Pin in Arduino. In this configuration more light = lover voltage.

At the end everything is putted on serial monitor.

Our RGB diode is a popular WS2812B.

Exactly WS212B is a RGB diode driver. In small cover there is a driver and 3 diode's. Combinations of this 3 light can take you every color you want. The driver is addressable, so practicly it means that if You want use 1 RGB diode You need one digital pin in Microcontroller, but if You want to use 100 diodes You need.... still one pin. For easy implement it we'll use NanoPixel librbary.

## Step 2: Components

![](https://cdn.instructables.com/FJ2/V5NX/J9JFMUQH/FJ2V5NXJ9JFMUQH.MEDIUM.jpg)

1\. 1x Arudino (I used UNO but You can take any other or "naked" Atmega)

2\. 1x WS2812B RGB digital diode (on the picture)

3\. 1x1cm part of pcb board and some pins

4.1x Photoresistor

5\. 1x 10 kOhm resistor

6\. small piece of thermo-shrink tubing or insulation tube

7\. breadboard, wires

## Step 3: CIRCUIT DESIGN

![](https://cdn.instructables.com/FQI/4GF8/J9JFMUEU/FQI4GF8J9JFMUEU.MEDIUM.jpg)

## Step 4: Soldering RGB Diode on PCB

![](https://cdn.instructables.com/FEZ/9V2Z/J9JFMU01/FEZ9V2ZJ9JFMU01.MEDIUM.jpg)

![](https://cdn.instructables.com/F1W/DMLI/J9JFMU8F/F1WDMLIJ9JFMU8F.MEDIUM.jpg)

Because WS2812B is SMD and I want to have small module with pins I decided to put it on PCB.

It has 4 connectors but for better stabilization i Used 2 3 pin bars and solder to connectors. In this project we we'll use only 3 connectors (VDD, DIN and Input), 4th is useful if You want to plug more diodes

On the picture You have circuit taken from documentation and my photo in order to simplify proper soldering.

## Step 5: Insolation the Sensor and Placing Diode With It

![](https://cdn.instructables.com/FU2/IR5E/J9JFMUGH/FU2IR5EJ9JFMUGH.MEDIUM.jpg)

![](https://cdn.instructables.com/FJV/L3UD/J9JFMUUK/FJVL3UDJ9JFMUUK.MEDIUM.jpg)

So now you need to isolate the top of the our sensor (photo resistor) in order to isolate it from flank reflections (it should see only the material on opposite). Thermo-shrink tube or insulation tape should be higher than surface of sensor only for about 2-3 millimetres.

Now please put sensor and light on about 1-2 cm under tested materials. Light should illuminate exactly the surface under sensor.

## Step 6: Coding

Code assumptions have already been discussed.

For controlling the RGB we used the **Neopixel library** (to find newest version please visit GitHub).

There is a loop where Microcontroller is changing the colors from RED to GREEN, and then to BLUE. Between this there is some stops whene diode is switched off.

Here

_pixels.setPixelColor(i, 255, 0, 0); _

you can define combination of each color. Variable i is a chosen diode (It' s important when you use more than one).

Then we can chose the level of R, G and B. 255 is maximum.

This_ pixels.show(); _willturn diode with chosen mix of colors

Variable_ COLOR_TIME _in next delay establish time of lighting. From my tests I checked that when you use photoresistor it's better not to pur timings shorten than 3 ms. If you want to see the effect of changing colours please put the time longer that 200 ms. In short timings our eyes will not register the changings and we see only white light (but exactly its changing and microcontroller see this).

Variable WAITING is for time of waiting before each colour. Variables are defined on the beginning of code.

After every colour code is saving reading from analog pin to color variable, and after 3 color changes it's comparing colours in order to check dominating colour (it means the colour with lover reading- lover voltage on divider).

Result is sending via Serial.println into serial monitor

When it will not recognize colour (so it means that one colour = second) it will inform You.

After loop there is a delay. It determines sampling frquency of detector. Lower = higher frequency. But if you want read it on serial monitor You must know that as frequency is higher You need also higher rate of serial monitor baud.

On the begening when You turned up circuit there is diode test. It schow every color and white in one second.

## Step 8: VIDEO
