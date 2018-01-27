# AdaBox002: Make Robot Friend

_Captured: 2017-10-29 at 13:42 from [nick.blog](https://nick.blog/2017/03/12/adabox002-make-robot-friend/)_

[Adafruit's 2nd AdaBox](https://www.adafruit.com/products/3235) is everything needed to build a full functioning robot, controlled over Bluetooth via their [Bluefruit app](https://itunes.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=830125974&mt=8).

When I got it a couple of months ago, I put it together and wrote a bunch of notes for improvements I wanted to make. I finally got around to spending some time on it. [Adafruit's learn guide](https://learn.adafruit.com/adabox002) and the [associated code](https://github.com/adafruit/BLE-Black-Robot-Rover/) were a great start and I referenced some ideas from their [Multi-tasking the Arduino](https://learn.adafruit.com/multi-tasking-the-arduino-part-1) series. Some of the things I customized with my robot:

  * No need to hold buttons in the Bluefruit app to keep the robot moving.
  * Increase/decrease speed by pressing buttons 1-4.
  * Allowed turning left/right to be combined with forward/reverse.
  * Added a backup beeper.
  * Added blinkers.
  * Added stop/go LEDs. The stop LED will blink when going in reverse.
  * Improved the increasing/decreasing speed so the robot doesn't pop a wheelie or tip over.

I put all of [the code and wiring info on GitHub](https://github.com/nickmomrik/adabox002-robot). Here's a very poor and unedited video of the robot in action. I did a terrible job of keeping the iPhone in frame.

AdaBox002 Robot

Share

Play Video

At some point in the future I should update this to work with the iPhone's gyroscope instead of having to press buttons. Getting my ideas for AdaBox002 wrapped up came just in time since I now have an [AdaBox subscription](https://www.adafruit.com/adabox) and AdaBox003 ships out tomorrow. I'm excited to see what it is!
