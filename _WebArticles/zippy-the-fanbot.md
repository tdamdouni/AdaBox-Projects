# Zippy the Fanbot

_Captured: 2017-12-05 at 09:26 from [www.instructables.com](http://www.instructables.com/id/Zippy-the-Fanbot/)_

![](https://cdn.instructables.com/FZE/25B0/JAMU1QTH/FZE25B0JAMU1QTH.MEDIUM.jpg)

This instructable was created in fulfillment of the project requirement of the MAKEcourse at the University of South Florida (www.makecourse.com).

Zippy the Fanbot is an Arduino based project which utilizes thrust produced by propellers mounted on brushless motors in order to propel or rotate the bot in desired directions. The user controls the bot with an infrared remote control. The name Zippy was coined from the fact that the majority of the assembly is held together with zip ties.

## Step 1: 3-D Print the Parts

![](https://cdn.instructables.com/FDB/88MO/JAMU1VW4/FDB88MOJAMU1VW4.MEDIUM.jpg)

The frame of this assembly as well as the Arduino case and electronics box were 3-D printed. Each part was printed at 30% infill with 3-5 shells. I have uploaded the STL part files to make it easy for you. Just download them and bring them to a good 3-D printer!

## Step 2: Purchase the Necessary Electronics and Parts

A number of electronics and parts will be needed in order to build and use Zippy the Fanbot. Here is a list of all the parts that I used in the making of this project:

**1x** Arduino Uno R3

**1x** VS/HX1838B Infrared Sensor

**1x** Pack of Male to Male Header Pins (Enough for Arduino Pins)

**1x **Pack of 8" Female to Female Jumper Wires

**1x** 3S 11.1V Lithium Polymer Battery

**1x** Power Distribution Harness or Power Distribution Board

**4x** Afro SimonK 20A OPTO ESCs

**4x** Sunnysky X2212 KV980 Brushless Motors

**2x** APC CW 8045 Multirotor Propellers

**2x** APC CCW 8045 Multirotor Propellers

**1x** Pack of 4" Zip Ties

**4x** Light Duty Swivel Casters

**1x** Package of Velcro Strips

**1x **Roll of Soft Double Sided Tape

## Step 3: Assemble the Parts and Build the Circuit

![](https://cdn.instructables.com/F0H/S680/JAMU2EX1/F0HS680JAMU2EX1.MEDIUM.jpg)

Once you have 3-D printed all of the necessary parts and purchased all other necessary components, it is time to start assembling Zippy! Refer to the first picture in this instructable in order to visualize how everything is put together.

The 3-D printed frame is very intuitive to put together, which is how I intended it to be. The two arms interlock to make an X frame and there is a bracket that fits over the arms. The electronics holster goes under the arms. The fan adaptors get mounted on the ends of each arm and the wheel adaptors slide right on to the legs of the frame. It should be very intuitive where to apply all the zip ties, however, if it is not, just look at the first picture on this intstructable! It is not absolutely necessary to apply zip ties in order to hold the top bracket onto the arms.

Once the frame has been assembled, it's time to wire and mount the electronics. The ESCs get mounted to the arms while the motors are to be mounted on the fan adaptors. Both the ESCs and motors are mounted with zip ties. The polarity needs to be reversed between the ESCs and motors on the front left and rear right arms so that they rotate clockwise. The other two arms will have motors that rotate counterclockwise. Therefore the clockwise props will be mounted onto the front left and rear right motors while the counterclockwise props will be mounted onto the front right and rear left motors. These opposite rotational directions produce opposing torques which assist in the stable performance of the bot.

Use velcro to mount the Arduino case as well as the LiPo battery on top of the center bracket. Use double sided tape to mount the IR sensor at the top center of the Arduino case, that way, it is in an optimal location to receive signals from the remote. All of the power distribution from the LiPo to the ESCs is fed through the electronics box which sits in the electronics holster. The signal wire from the Arduino to the ESCs are also fed through the electronics box. BE VERY CAREFUL not to criss-cross the wiring from the LiPo to the ESCs. This can easily damage the ESCs and potentially start a fire.

Refer to the circuit schematic which illustrates how everything is wired together.

## Step 4: Flash the Arduino

Once Zippy the Fanbot has been assembled, it's time to flash the Arduino with the necessary software. I have provided the Arduino sketch that is used to control Zippy. The code essentially requires 5 buttons to operate the fanbot. The best buttons to program are the navigation buttons on the remote control. It is intuitive that the up/down buttons will move the bot forwards/backwards while the left/right buttons will rotate the bot counterclockwise/clockwise. The center navigation button will act as a kill switch and stop all motors. If the remote you are using does not work with this code, remove the propellers from the bot and use the serial monitor in the Arduino IDE to reprogram the Arduino to work with the directional buttons on your remote. You simply need to press the button you want to use and observe what value shows up on the serial monitor. Then, replace the value in the appropriate if statement that is in the code I provided with the value you see on the serial monitor.

The code is rather simple as you will see. There are 5 conditional checks which determine which button is being pressed. For example, if the IR sensor detects that the up button is being pressed, the two front motors will spin, which pulls the bot forward. If the left navigation button is pressed, the front right and rear left motors will spin causing the bot to rotate counterclockwise. If a button for a certain maneuver is held down, the respective motors will continuously increase their speeds until a max speed is reached.

Let's say for a second that the bot is moving forward with its front motors spinning at their max speeds. If the user presses and holds the down button, the front motors will slow down until they have completely stopped and then the rear motors will activate and send the bot in reverse. This applies to the bot's rotational maneuvers as well. This allows the user to speed up or slow down the maneuvers that the bot is performing.

Now, let's say the bot is again moving forward at some speed. If the left or right directional button is pressed, the bot will immediately stop spinning all motors before activating the motors that make it turn. Therefore, the user can immediately switch between linear and rotational motion.

## Step 5: Have Fun Using Zippy and Be Safe

Now you are all set! Once you have built Zippy and gotten the Arduino code to work, it is time to play around. Be extremely careful though, especially around kids and animals. Make sure the propellers are balanced well and tightened down snug on the motors. The brushless motors used in this project spin at very high RPMs, therefore, the props are very capable of causing injuries. Have fun!

## Comments
