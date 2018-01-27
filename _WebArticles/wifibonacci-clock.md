# WiFibonacci Clock

_Captured: 2017-11-18 at 14:43 from [www.instructables.com](http://www.instructables.com/id/WiFibonacci-Clock/)_

![](https://cdn.instructables.com/F8U/K5GV/J9JFP0HT/F8UK5GVJ9JFP0HT.MEDIUM.jpg)

I have been inspired by the awesome [Fibonacci Clock](https://www.instructables.com/id/The-Fibonacci-Clock/) (designed by [Philippe Chretien](http://basbrun.com/)) and I decided to make it **wireless** using Wifi, hence the name of **WiFibonacci Clock** =D

The main enhancement is the replacement of the Atmega328 with an [ESP8266](http://www.esp8266.com/) providing WiFi capability. This is game-changing as we can now virtualise part of the physical UI having the ESP acting as a [Websocket](https://en.wikipedia.org/wiki/WebSocket) server. Furthermore, the dematerialisation of the UI allows more tuning options.

The list of existing modes that Philippe included in his design are:

  * Current Time 
  * Rainbow Cycle 
  * Rainbow 
  * Error Code Display

I chose to remove the Error Code Display mode and add the following list of new modes:

  * Random 
  * Pulse 
  * Constant Light

For each mode, several settings can be tweaked.

There are only two momentary buttons in my design:

  * Mode button 
  * Brightness button

The brightness is also an enhancement. The time adjustment can be done via the virtual UI.

In this Instructable I won't explain how to make the enclosure as it is covered in [Philippe's instructable](https://www.instructables.com/id/The-Fibonacci-Clock/), **I will only explain how to make it Wireless / Wifi connected.**

**_If you like this instructable please vote here:  
_**<https://www.instructables.com/contest/wireless2017/>

![](https://cdn.instructables.com/F5H/NIXI/J9JFOZGI/F5HNIXIJ9JFOZGI.MEDIUM.jpg)

![](https://cdn.instructables.com/FUG/K27V/J9JFP0GR/FUGK27VJ9JFP0GR.MEDIUM.jpg)

![](https://cdn.instructables.com/FOK/ANE7/J9SVKCKP/FOKANE7J9SVKCKP.MEDIUM.jpg)
