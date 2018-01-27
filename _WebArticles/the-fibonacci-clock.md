# The Fibonacci Clock

_Captured: 2017-11-18 at 14:44 from [www.instructables.com](http://www.instructables.com/id/The-Fibonacci-Clock/)_

![](https://cdn.instructables.com/F83/N8FZ/I99R3RE4/F83N8FZI99R3RE4.MEDIUM.jpg)

**UPDATE: This project has been successfully funded on **[Kickstarter](https://www.kickstarter.com/projects/basbrun/fibonacci-clock-an-open-source-clock-for-nerds-wit/description)**and is now available for sale at **[http://store.basbrun.com](http://store.basbrun.com/)**Thank you to all those who supported my campaign!**

I present to you the Fibonacci Clock, a clock for nerds with style. Beautiful and fun at the same time, the clock uses the famous Fibonacci sequence to display time in a brand new way.

## Step 1: How Do I Tell Time?

![](https://cdn.instructables.com/FCY/RL9Y/I99R3REJ/FCYRL9YI99R3REJ.MEDIUM.jpg)

The Fibonacci sequence is a sequence of numbers created by the Italian mathematician Fibonacci in the 13th century. This is a sequence starting with 1 and 1, where each subsequent number is the sum of the previous two. For the clock I used the first 5 terms: 1, 1, 2, 3 and 5.

The screen of the clock is made up of five squares whose side lengths match the first five Fibonacci numbers: 1, 1, 2, 3 and 5. The hours are displayed using red and the minutes using green. When a square is used to display both the hours and minutes it turns blue. White squares are ignored. To tell time on the Fibonacci clock you need to do some math. To read the hour, simply add up the corresponding values of the red and blue squares. To read the minutes, do the same with the green and blue squares. The minutes are displayed in 5 minute increments (0 to 12) so you have to multiply your result by 5 to get the actual number.

Often, there are multiple ways to display a single time. To add to the challenge, the combinations are picked randomly from all the different ways a number can be displayed. There are, for example, 16 different ways to display 6:30 and you never know which one the clock will use!

## Step 2: Circuit

![](https://cdn.instructables.com/FZD/QLZ6/I99R3RE5/FZDQLZ6I99R3RE5.MEDIUM.jpg)

![](https://cdn.instructables.com/F42/2XI1/I99R3RMV/F422XI1I99R3RMV.MEDIUM.jpg)

I built the Fibonacci clock using an Atmega328P micro-controller using Arduino. You could buy an Arduino board and a DS1307 real-time clock break-out board and build a custom shield for your circuit but I preferred to build my own circuit board. That allows me to keep size small and price low.

## Step 3: Buttons

![](https://cdn.instructables.com/FO2/FLNP/I99R3RE9/FO2FLNPI99R3RE9.MEDIUM.jpg)

The three buttons attached to Arduino pins #3,#4 and #6 are used together to change time. Button on pin #3 can be used alone to change the color palette of the LEDs. An extra button is attached to pin #5 to change between different modes of the clock. Two modes are lamp modes and the default mode is the clock. All buttons are connected to the Arduino pins with a 10K pull-down resistor in parallel.

## Step 4: Real-Time Clock

![](https://cdn.instructables.com/F6W/M2IV/I99R3REE/F6WM2IVI99R3REE.MEDIUM.jpg)

The real-time clock chip DS1307 is connected to the Arduino analog pins 4 and 5 with two 22K pull-up resistors. The clock pin 5 (SDA) is connected to the Atmega328P pin 27 (Arduino A4) and the clock pin 6 (SCL) is connected to the Atmega329P pin 29 (Arduino A5). To keep time while unplugged the DS1307 chip needs a 3V battery connected to pint 3 and 4 of the chip. Finally, the real-time clock is driven by a 32KHz crystal connected on pins 1 and 2. A 5V power is applied on pin 8.

## Step 5: LED Pixels Strip

![](https://cdn.instructables.com/FMS/1QZC/I99R3REA/FMS1QZCI99R3REA.MEDIUM.jpg)

I am using LED pixels built on top of the WS2811 drivers. These microcontrollers allows me to set the color of each individual LED with a single output on the Arduino microcontroller. The Arduino pin used to control the LEDs in this project is pin #8 (Atmega328P pin #14).

## Step 6: Microcontroller

You will find all the details on how to connect the Atmega328P to make an Arduino clone on my post "[Build an Arduino Clone](http://basbrun.com/2011/03/04/build-an-arduino-clone/)". I added a new feature in this project, an FTDI port to program your Arduino microcontroller directly on this circuit. You connect pin one to the reset pin of the Arduino trough a 0.1uF capacitor to synchronize your uploader with the chip bootup sequence.

Pin 2 (RX) of the FTDI port connects to pin 3 of the Atmega328P(Arduino 1-TX) and pin 3 (TX) of the FTDI connector connects to pin 2 of the Atmega328P (Arduino 0 - RX). Finally FTDI pin 4 goes to 5V and 5 and 6 to ground.

## Step 7: The Enclosure

![](https://cdn.instructables.com/F26/3798/I99R3RE7/F263798I99R3RE7.MEDIUM.jpg)

![](https://cdn.instructables.com/FKE/2ZKE/I99R3REB/FKE2ZKEI99R3REB.MEDIUM.jpg)

The video presents all the steps for the construction of the Fibonacci clock enclosure. The idea is to create 5 square compartments in the clock, two inches deep, matching the size of the five first terms of the Fibonacci sequence, 1, 1, 2, 3 and 5. The LEDs are distributed in all squares and connected in the back of the clock to the circuit board.

The enclosure is built out of birch plywood. The frame is 1/4″ thick and the back panel is 1/8″ thick. The separators are 1/16″ thick and can be made of any opaque material. The dimensions of the clock are 8″x5″x4″. The front of the clock is a piece of 1/8″ thick semi-transparent plexiglass. The separators are marked using a Sharpie pen.

The wood finish is a water based varnish applied after a good sanding using 220 sand paper.

## Step 8: Make It a Lamp

The Fibonacci clock can also be converted into an ambiant lamp! The code published already support two lamp modes. Simply push the mode button to toggle between the three modes. The code is open for you to hack, feel free to implement your own modes!

## Step 9: You'r Done

![](https://cdn.instructables.com/FPD/R7J2/I99R3REI/FPDR7J2I99R3REI.MEDIUM.jpg)

## Step 10: The Code
