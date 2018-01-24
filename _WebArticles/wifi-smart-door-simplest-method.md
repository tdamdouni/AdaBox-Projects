# Wifi Smart Door(simplest Method)

_Captured: 2017-11-11 at 18:11 from [www.instructables.com](http://www.instructables.com/id/Wifi-Smart-Doorsimplest-Method/)_

![](https://cdn.instructables.com/FJ5/K0KG/J9JFN7XG/FJ5K0KGJ9JFN7XG.MEDIUM.jpg)

![](https://cdn.instructables.com/FVQ/QMUC/J8UH273L/FVQQMUCJ8UH273L.SMALL.jpg)

![](https://cdn.instructables.com/F2U/XKPR/J9JFMNYV/F2UXKPRJ9JFMNYV.MEDIUM.jpg)

This is a simple project made with the arduino uno R3,the aim is to control a door lock without keys,and using a smart phone to accomplish this,the communication medium will be the internet(**wifi module-ESP8266**).

I have already posted an instructable about the same project with **bluetooth** module,you can refer it for any clarifications.([click here](https://www.instructables.com/id/Smart-BT-Door-Locksimple-Arduino/)).

In this instructable you will be knowing about the simple IOT project of controlling the lock of your door with wifi module.

This is one of the **simplest method to use ESP-8266.**

## Step 1: Collecting the Items Required

![](https://cdn.instructables.com/FU1/4C54/J8UH1Z8D/FU14C54J8UH1Z8D.MEDIUM.jpg)

1.Arduino UNO R3

to control the servo and interface with the ESP 8266(GPIO pin-0 )

the concept is very simple we are going to control the ESP8266 (GPIO pin 0) from our smart phone with an app.

if GPIO -pin 0

LOW----------------------------------- lock state-closed.

HIGH-----------------------------------lock state-open.

the GPIO pin 0 state will be recognised by arduino using the digitalRead command and does the required operations on the Servo.

## Step 2: ESP-8266 Wifi Module

![](https://cdn.instructables.com/FTZ/E5EP/J9JFMOT9/FTZE5EPJ9JFMOT9.MEDIUM.jpg)

![](https://cdn.instructables.com/FIT/8EII/J9JFMQJV/FIT8EIIJ9JFMQJV.MEDIUM.jpg)

This will help our project to get connected to the cloud.this is very cheap and easy to use.

In this project we will be using only the GPIO pin-0 of the ESP8266.

## Step 3: High Torque Servo

![](https://cdn.instructables.com/FFV/HLDR/J8UH1Z8A/FFVHLDRJ8UH1Z8A.MEDIUM.jpg)

![](https://cdn.instructables.com/FBX/JVKV/J8UH25KE/FBXJVKVJ8UH25KE.SMALL.jpg)

![](https://cdn.instructables.com/FMT/T36K/J8UH25JI/FMTT36KJ8UH25JI.MEDIUM.jpg)

to turn the lock lever when signal is sent from the arduino

it is powered by the arduino **5v pin** itself and it works well with it.(only when the arduino is powered with** usb **cable)

## Step 4: Sheet Metal

![](https://cdn.instructables.com/FSQ/9MIW/J8UH1Z8B/FSQ9MIWJ8UH1Z8B.MEDIUM.jpg)

this is used to make the case for the servo motor which allows it to properly hold the motor on the door and the rotating part properly fixed to the lever of the lock.

the case is up to your creativity you can use any other material/thing to make the case. TO HOLD THE MOTOR ON THE DOOR

## Step 5: 3.3V FTDI Programmer

![](https://cdn.instructables.com/F1G/1ADD/J9JFMS8X/F1G1ADDJ9JFMS8X.MEDIUM.jpg)

This is used only in the making of the project,to program the ESP8266 module as it can't be programmed directly from arduino.

## Step 6: Setup for ESP8266

![](https://cdn.instructables.com/FKQ/4R9E/J9JFMU47/FKQ4R9EJ9JFMU47.MEDIUM.jpg)

You only need to establish a serial communication between your FTDI programmer and your ESP8266.

Connections:  
RX -> TX

TX -> RX

CH_PD -> 3.3V

VCC -> 3.3V

GND -> GND

## Step 7: Uploading Code to ESP(simplified Software)

![](https://cdn.instructables.com/FJ5/K2WG/J9JFMVMH/FJ5K2WGJ9JFMVMH.MEDIUM.jpg)

using the ESPlorer IDE which is a program created by 4refr0nt to send commands to your ESP8266.

Follow these instructions to download and install ESPlorer IDE:

1.[Click here](https://esp8266.ru/esplorer/#tutorials) to download ESPlorer

2.Unzip that folder

3.Go to the main folderRun "ESPlorer.jar" file

4.Open the ESPlorer IDE

5.Connect your FTDI programmer to your computer

6.Select your FTDI programmer port

7.Press Open/Close

8.Select NodeMCU+MicroPtyhon tab

9.Create a new file called init.lua  
10.Press Save to ESP

11.Everything that you need to worry about or change is highlighted in red box.

12.Upload the following code into your ESP8266 using the preceding software. Your file should be named **"init.lua"**.

add your network name (SSID) and password to the script

ADD YOUR WIFI **NETWORK NAME(SSID)** AND **PASSWORD** TO THE SCRIPT

**Your ESP IP Address**  
When your ESP8266 restarts, it prints in your **serial monitor** the ESP IP address. Save that IP address, because you'll need it later.

## Step 8: Coding the Arduino With IDE

![](https://cdn.instructables.com/FIE/C7R5/J8UH2168/FIEC7R5J8UH2168.MEDIUM.jpg)

## Step 9: Inventing Your Own App

![](https://cdn.instructables.com/F3X/3R8E/J9JFN0JZ/F3X3R8EJ9JFN0JZ.MEDIUM.jpg)

![](https://cdn.instructables.com/FKI/ABI5/J9JFN0K2/FKIABI5J9JFN0K2.MEDIUM.jpg)

![](https://cdn.instructables.com/F7Z/AXYD/J8UH21IQ/F7ZAXYDJ8UH21IQ.SMALL.jpg)

![](https://cdn.instructables.com/F85/W34L/J8UH2545/F85W34LJ8UH2545.MEDIUM.jpg)
