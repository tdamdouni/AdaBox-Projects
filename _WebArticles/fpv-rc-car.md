# FPV RC Car

_Captured: 2017-11-19 at 15:22 from [www.instructables.com](http://www.instructables.com/id/FPV-RC-Car/)_

![](https://cdn.instructables.com/F12/2Y59/J9OJ5G3L/F122Y59J9OJ5G3L.MEDIUM.jpg)

This project is in in my drawer for some time and I since Maker Fair is coming to town, this was a good time to make it.

A long time ago, there was a game called "Micro Machines" for Sega Mega Drive (Genesis) that I spend hours playing. Basically this was a racing game with small cars where the race track was parts of daily life objects. I found that there is a new version of this old classic.

On the original version, the game had top view of the track and cars, but I wanted to had the first person view in a head display. The camera would move according to the movement of the head of the player.

The controller should be a racing wheel.

Unfortunately, this was not possible, and in the end this was what I got.

Due to several factors I did not implemented the head display and servo controlled camera but the car is controller by the racing wheel, I have a wireless camera and everything works. The problem is the range. I can only control and see camera feed if every transmitter and receiver units are in line of sight.

In any case there are very interesting aspect of this project worth sharing.

## Step 1: Components

![](https://cdn.instructables.com/FFU/363K/J9OJ5G89/FFU363KJ9OJ5G89.MEDIUM.jpg)

![](https://cdn.instructables.com/FFI/PXWS/J9OJ5GA6/FFIPXWSJ9OJ5GA6.SMALL.jpg)

![](https://cdn.instructables.com/FWH/8VND/J9OJ5GJ6/FWH8VNDJ9OJ5GJ6.MEDIUM.jpg)

![](https://cdn.instructables.com/FM6/H7C7/J9OJ5GL0/FM6H7C7J9OJ5GL0.SMALL.jpg)

![](https://cdn.instructables.com/F1J/5L1O/J9OJ5GMA/F1J5L1OJ9OJ5GMA.SMALL.jpg)

![](https://cdn.instructables.com/FSI/24L6/J9OJ5GQD/FSI24L6J9OJ5GQD.SMALL.jpg)

**RC Car**

I just selected the most cheap that I could find in a 1:20 scale.

**Wireless Camera**

I had several chooses where, but probably when for the worst. If you are planning on doing something like this DO NOT use these type of cameras.

**Microcontroller**  
[DFRobot Dreamer Nano V4.1](https://goo.gl/wbCVJv), the 2.54mm pinout is essencial for this project. Check DFRobot wiki page for more info regarding this microcontroller

**Computador Racing Wheel**

Today is very easy to find old racing controllers almost for free. This one I got for free in the local internet market.

It comes with the old 15 pins game port, that was connected in the sound card of the computer.

**Motor Controller **

The choice was the L298N with a capability of 2A and with a max of 46V in the input serves perfectly or this project.

**RF transceiver**

For the wireless communication between the racing wheel and car, I went with the nRF24L01+ RF transceiver.

I had some where, and they are easy to use.

**Battery**

A 7.4V 800mA LiPo battery provides the power to the RC car, microcontroller, RF transceiver, and wireless camera

**Miscellaneous**

4x - 10K Resistor

4x - 100K Resistor

Perfboard (a usual in my projects), 9V battery plug, and some wires

## Step 2: Connect the Components

![](https://cdn.instructables.com/FCN/BS71/J9JFWQXR/FCNBS71J9JFWQXR.MEDIUM.jpg)

![](https://cdn.instructables.com/FR9/EWPN/J9JFWXUR/FR9EWPNJ9JFWXUR.SMALL.jpg)

![](https://cdn.instructables.com/F6E/N4WC/J9OJ5I8W/F6EN4WCJ9OJ5I8W.SMALL.jpg)

![](https://cdn.instructables.com/FBJ/6MZJ/J9SVUZDB/FBJ6MZJJ9SVUZDB.SMALL.jpg)

**Computar Racing Wheel T****ransmitter**

The game port pin out can be find where

I also found a very nice site with a schematic for the a connection to the arduino

The circuit is build in the prefboard according to the schematic that I've added.

For the NRF24L01+ connection I'm using the base adapter that bring a 3.3V voltage regulator plus additional capacitors for increasing the line stabilization.

If you want just to use the NRF24L01+, the power line need to come from the +3.3V from the Arduino.

**RC Car Receiver**

For the car I also user the NRF24L01+ base adapter, again this is an optional.

The L298n connect to pins D2 to D7.

The power for wireless camera comes also from the battery pack

After some tests, I used the rule of thumb for the heat sink, and decided to use a fan.

![](https://cdn.instructables.com/FII/YDL3/J9OJ5HOD/FIIYDL3J9OJ5HOD.MEDIUM.jpg)

![](https://cdn.instructables.com/F3M/LN5W/J9OJ5HSJ/F3MLN5WJ9OJ5HSJ.MEDIUM.jpg)

![](https://cdn.instructables.com/FRL/8KN9/J9OJ5H4U/FRL8KN9J9OJ5H4U.MEDIUM.jpg)
