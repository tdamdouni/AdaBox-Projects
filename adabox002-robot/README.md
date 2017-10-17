# adabox002-robot
Customized robot built with [AdaBox002](https://www.adafruit.com/products/3235).

## Changes
 * No need to hold buttons in the Bluefruit app to keep the robot moving.
 * Buttons 1-4 set the speed to 25-50-75-100%
 * Turning + forward/reverse can be combined.
 * Added a backup beeping buzzer.
 * Added blinker LEDs.
 * Added stop/go LEDs. The stop LED will blink when going in reverse.
 * Improved the stepping when increasing/decreasing speed so the robot doesn't pop a wheelie or tip over.
 
## Setup
First you'll want to follow [Adafruit's guide for assembling the robot](https://learn.adafruit.com/adabox002/assembling-your-robot) and then also follow their code examples in the guide, which will walk you through setting up some of the required libraries needed for this custom version.

Next you can add the necessary wires, LEDs, resistors, and buzzer by following the [Fritzing](./adabox002-robot.fzz) I've provided. Note I've only included the motor driver Feather Wing it the Fritzing to simplify. Here is also a screenshot...
 
![adabox002-robot Fritzing](./adabox002-robot.png?raw=true "adabox002-robot Fritzing")

## Demo
View a poor unedited [video on my blog](https://nick.blog/2017/03/12/adabox002-make-robot-friend/).
