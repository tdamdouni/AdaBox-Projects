# 15 Arduino Uno Breadboard Projects

_Captured: 2018-03-08 at 18:20 from [www.makerspaces.com](https://www.makerspaces.com/15-simple-arduino-uno-breadboard-projects/?utm_content=buffer10372&utm_medium=social&utm_source=twitter.com&utm_campaign=buffer)_

![arduino-uno-breadboard-switch](https://www.makerspaces.com/wp-content/uploads/2017/02/arduino-uno-breadboard-switch.jpg)

The easiest way for beginners to get started with Arduino is by creating circuits using a solderless breadboard. These simple projects will teach you the basics of Arduino Uno, electronics and programming. In this tutorial, you will be creating circuits using the following electronic components:

  * LED
  * RGB LED
  * Temp Sensor
  * Pushbutton
  * Potentiometer
  * Photoresistor
  * Servo
  * Motor
  * Buzzer
  * LCD screen

This tutorial is going to allow you to jump right in and start building circuits. If you need some background on the Arduino Uno board or the tools that are needed, please check out post - [Arduino Uno For Beginners](https://www.makerspaces.com/arduino-uno-tutorial-beginners/).

Before you can start working with Arduino, you need to make sure you have the IDE software installed on your computer. This program allows you to write, view and upload the code to your Arduino Uno board. You can [download the IDE](https://www.arduino.cc/en/Main/Software) for free on Arduino's website.

Once the IDE is installed, you will need to connect your Arduino to your computer. To do this, plug one end of the USB cable to the Arduino Uno and then the other end of the USB to your computer's USB port.

## Select The Board

Once the board is plugged in, you will need to open the IDE and click on **Tools** > **Board** > **Arduino Uno **to select the board.

## ![select arduino board](https://www.makerspaces.com/wp-content/uploads/2017/02/select-arduino-board.png)

## Select Serial Port

Next, you have to tell the Arduino which port you are using on your computer. To select the port, go to **Tools > Port** and then select the port that says** Arduino.**

# ![select arduino port](https://www.makerspaces.com/wp-content/uploads/2017/02/select-arduino-port.png)

To complete the projects in this tutorial, you will need to download the project code which are known as sketches. A sketch is simply a set of instructions that tells the board what functions it needs to perform. For some of these projects, we are using open-source code that was released by the good people at [Sparkfun](https://www.sparkfun.com/) and[ Arduino](https://www.arduino.cc/). Use the link below to download the zip folder containing the code.

Once the file has been downloaded, you will need to unzip/extract the folder in order to use it.

The first project is one of the most basic and simple circuits you can create with Arduino. This project will test your Arduino by blinking an LED that is connected directly to the board.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) LED 5mm
  * (1) 220 Ω Resistor

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/1-Test-Arduino_SMALL.jpg)

> _Click Image To Enlarge_

**Project Steps**

  1. Twist a 220 Ω resistor to the long leg (+) of the LED.
  2. Push the short leg of the LED into the ground (GND) pin on the board.
  3. Push the resistor leg that's connected to the LED into the #13 pin.

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_01_TestArduino**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

This project is identical to project #1 except that we will be building it on a breadboard. Once complete, the LED should turn on for a second and then off for a second in a loop.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LED 5mm
  * (1) 220 Ω Resistor
  * (2) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/2-Blink-an-LED_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_02_Blink**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

Using a push button switch, you will be able to turn on and off an LED.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LED 5mm
  * (1) 220 Ω Resistor
  * (1) 10K Ω Resistor
  * (1) Push Button Switch
  * (6) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/3-Pushbutton_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_03_Pushbutton**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

Using a potentiometer, you will be able to control the resistance of an LED. Turning the knob will increase and decrease the frequency the LED blinks.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LED 5mm
  * (1) 220 Ω Resistor
  * (1) Potentiometer (10k Trimpot)
  * (6) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/4-Potentiometer_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_04_Potentiometer**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

By using a PWM pin on the Arduino, you will be able to increase and decrease the intensity of brightness of an LED.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LED 5mm
  * (1) 220 Ω Resistor
  * (2) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/5-Fade-an-LED_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_05_Fade**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

This project will blink 6 LEDs, one at a time, in a back and forth formation. This type of circuit was made famous by the show Knight Rider which featured a car with looping LEDs.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (6) LED 5mm
  * (6) 220 Ω Resistor
  * (7) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/6-For-Loop-Scrolling-LED_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_06_Scrolling**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

Using a potentiometer, you can control a series of LEDs in a row. Turning the potentiometer knob will turn on or off more of the LEDs.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) Potentiometer - Rotary
  * (10) LED 5mm
  * (10) 220 Ω Resistor
  * (11) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/7-Bar-Graph_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_07_BarGraph**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

This project will use 8 pins on the Arduino board to blink 8 LEDs at the same time.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (8) LED 5mm
  * (8) 330 Ω Resistor
  * (9) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/8-Multiple-LEDs_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_08_MultipleLEDs**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

This project will be using an RGB LED to scroll through a variety of colors. RGB stands for Red, Green and Blue and this LED has the ability to create nearly unlimited color combinations.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) RGB LED
  * (3) 330 Ω Resistor
  * (5) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/9-RGB-LED_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_09_RGBLED**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

A photoresistor changes the resistance a circuit gets based on the amount of light that hits the sensor. In this project, the brightness of the LED will increase and decrease based on the amount of light present.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LED 5mm
  * (1) 330 Ω Resistor
  * (1) 10K Ω Resistor
  * (1) Photoresistor
  * (6) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/10-Photoresistor_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_10_Photoresistor**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

A temperature sensor measures ambient temperatures of the world around it. In this project, we will be displaying the temperature in the serial monitor of the Arduino IDE.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) Temperature Sensor - TMP36
  * (5) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/11-Temp-Sensor_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_11_TempSensor**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

The project will use a piezo buzzer/speaker to play a little melody.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) Piezo Buzzer/Speaker
  * (2) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/12-Tone-Melody_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_12_ToneMelody**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

In this project, you will be able to sweep a servo back and forth through its full range of motion.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) Servo
  * (6) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/13-Servo_-SMALL2.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_13_Servo**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

Using a switching transistor, we will be able to control a DC motor. If everything is connected correctly, you should see the motor spinning.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) DC Motor
  * (1) 330 Ω Resistor
  * (1) Diode 1N4148
  * (1) NPN Transistor
  * (6) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/14-Motor_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_14_Motor**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.

An LCD is a liquid crystal display that is able to display text on its screen. In this project, you should see the words "hello,world!" displayed on the screen. The potentiometer is used to adjust the contrast of the display.

**Parts Needed**

  * (1) Arduino Uno
  * (1) USB A-to-B Cable
  * (1) Breadboard - Half Size
  * (1) LCD Screen
  * (1) Potentiometer
  * (16) Jumper Wires

**Project Diagram**

![arduino uno projects for beginners](https://www.makerspaces.com/wp-content/uploads/2017/05/15-LCD-Screen_SMALL.jpg)

> _Click Image To Enlarge_

**Project Code**

  1. Connect the Arduino board to your computer using the USB cable.
  2. Open project code - **Circuit_15_LCD**
  3. Select the board and serial port as outlined in earlier section.
  4. Click upload button to send sketch to the Arduino.
  * Make sure your board and serial port is selected in the IDE. To do this, plug your board in and go to **Tools > Board >Arduino** to select your board. Next, go to **Tools > Port >Com (Arduino)** to select your serial port.
  * The long leg of the LED is the (+) positive and the short leg is the (-) negative. Make sure the correct leg of the LED is in the proper pin of the Arduino or breadboard as directed.
  * It can be easy to put a component or jumper into the wrong pin on the Arduino or the breadboard. Double check the correct pin is being used.
