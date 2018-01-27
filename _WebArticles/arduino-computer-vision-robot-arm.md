# Arduino Computer Vision Robot Arm

_Captured: 2017-11-23 at 10:20 from [www.instructables.com](http://www.instructables.com/id/Computer-Vision-Robot-Arm/)_

![](https://cdn.instructables.com/F25/Z3OS/J9YJJAZG/F25Z3OSJ9YJJAZG.MEDIUM.jpg)

![](https://cdn.instructables.com/F9O/LG4O/J9YJJB5Q/F9OLG4OJ9YJJB5Q.MEDIUM.jpg)

The main idea with this instructable was just make a simple 3DOF robot arm that collect objects and place them in the right place.

Materials:

4 servo SG90

MDF 4mm

Arduino Nano

Jumpers

Laptop

Glue

Nylon

## Step 1: Sketch

![](https://cdn.instructables.com/FP4/8H3Z/J9YJJCDQ/FP48H3ZJ9YJJCDQ.MEDIUM.jpg)

![](https://cdn.instructables.com/FP7/Z4WA/J9YJJCAI/FP7Z4WAJ9YJJCAI.MEDIUM.jpg)

First of all I just made a few drawings looking for the size of the links and the effector.

a1 = 10cm

a2 = 8.5cm

a3 = 10cm

But it's easy for you because I used Rhino to model the final structure, and then I did a laser cut.

****Attached vector files if you want to use them***

## Step 2: Solve the Puzzle

![](https://cdn.instructables.com/FDB/SDQK/J9YJJBAA/FDBSDQKJ9YJJBAA.MEDIUM.jpg)

![](https://cdn.instructables.com/FP0/BEQO/J9YJJBBI/FP0BEQOJ9YJJBBI.SMALL.jpg)

![](https://cdn.instructables.com/FXN/NVZX/J9YJJBA7/FXNNVZXJ9YJJBA7.SMALL.jpg)

![](https://cdn.instructables.com/FUC/4GCZ/J9YJJB7P/FUC4GCZJ9YJJB7P.SMALL.jpg)

![](https://cdn.instructables.com/FGQ/PM4R/J9YJJB72/FGQPM4RJ9YJJB72.SMALL.jpg)

![](https://cdn.instructables.com/F9H/JY0S/J9YJJB81/F9HJY0SJ9YJJB81.SMALL.jpg)

It is completely easy to assemble the cutted parts, just follow the pictures, they show where to place the servos.

## Step 3: Finishing the Robot

![](https://cdn.instructables.com/FG0/O7MG/J9YJJB02/FG0O7MGJ9YJJB02.MEDIUM.jpg)

![](https://cdn.instructables.com/FPA/7BCP/J9YJJB43/FPA7BCPJ9YJJB43.SMALL.jpg)

![](https://cdn.instructables.com/FXE/ABX8/J9YJJB64/FXEABX8J9YJJB64.SMALL.jpg)

![](https://cdn.instructables.com/FGG/WO3X/J9YJJB3M/FGGWO3XJ9YJJB3M.SMALL.jpg)

![](https://cdn.instructables.com/FPR/UPIS/J9YJJAZU/FPRUPISJ9YJJAZU.SMALL.jpg)

I just used a little bit of nylon for the effector, as you can see in the pictures.

## Step 4: Computer Vision

![](https://cdn.instructables.com/FFN/ASLA/J9YJJB1V/FFNASLAJ9YJJB1V.MEDIUM.jpg)

In the cad files I attached early, you can see the structure for the webcam. The cam is connected to matlab and this is the process:

1\. You've got to install the driver in matlab

2\. Then install the arduino package for matlab that let you program the arduino.

3\. Once you have installed the webcam driver and the arduino the code works capturing a snapshot and then analyze it.

4\. The software divide the image in 3 layers R, G and B.

5\. Using inverse cinematic the webcam gives to arduino the coordinates

where the color is and then the robot goes to that place and take the object.

6\. Finally i decided where the robot leaves the object.

I attached the code explained. Sorry, only spanish.

that's all. sorry for my english.
