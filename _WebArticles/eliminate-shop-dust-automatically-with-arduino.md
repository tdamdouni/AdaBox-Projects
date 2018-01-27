# Eliminate shop dust automatically with Arduino

_Captured: 2017-12-04 at 21:53 from [blog.arduino.cc](https://blog.arduino.cc/2017/12/04/eliminate-shop-dust-automatically-with-arduino/)_

![](https://blog.arduino.cc/wp-content/uploads/2017/12/Make-Stuff.png)

What's the best way to dispose of the dust that is produced when cutting with power tools? YouTuber Bob Claggett's answer is to [automate the process entirely](https://www.iliketomakestuff.com/how-to-automate-a-dust-collection-system-arduino/), using a series of PVC sewer pipes to transport air to a central vacuum system, along with an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) for control.

Airflow is regulated via a blast gate for each power tool, which is opened and shut using a hobby-style servo and custom linkage system. The powerful dust collector is controlled with the help of a relay.

Cleverly, a voltage sensor is employed for each power tool needing dust collection, allowing the Arduino to turn on the system and decide which gate to open without any human interaction.

Want a similar system for your workshop? Be sure to check out [Claggett's entire build in his write-up here](https://www.iliketomakestuff.com/how-to-automate-a-dust-collection-system-arduino/) and in the video below!

This entry was posted by Arduino Team on Monday, December 4th, 2017 and is filed under [Arduino](https://blog.arduino.cc/category/arduino/), [Featured](https://blog.arduino.cc/category/featured/), [Uno](https://blog.arduino.cc/category/arduino/uno-arduino/). You can follow any responses to this entry through the [RSS 2.0](https://blog.arduino.cc/2017/12/04/eliminate-shop-dust-automatically-with-arduino/feed/) feed. You can [leave a response](https://blog.arduino.cc/2017/12/04/eliminate-shop-dust-automatically-with-arduino/), or [trackback](https://blog.arduino.cc/2017/12/04/eliminate-shop-dust-automatically-with-arduino/trackback/) from your own site.
