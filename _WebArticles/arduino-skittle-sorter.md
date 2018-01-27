# Arduino Skittle Sorter

_Captured: 2017-12-08 at 11:09 from [www.instructables.com](http://www.instructables.com/id/Arduino-Skittle-Sorter/)_

![](https://cdn.instructables.com/FGC/AN4R/JASJPG2C/FGCAN4RJASJPG2C.MEDIUM.jpg)

![](https://cdn.instructables.com/FQY/RYHB/JASJPFX9/FQYRYHBJASJPFX9.MEDIUM.jpg)

Picky candy lovers everywhere often find themselves wasting their precious time sorting through their candy. Does that sound familiar? Have you ever wanted to build a machine that can sort Skittles for you? This instructable will show you exactly how to do that. Using an Arduino, a couple Servos, 3D printed and laser cut parts, and lots of glue and tape, you can build your own. When you are finished, all you have to do is dump the skittles into the funnel, turn the handle, then sit back, relax and enjoy as your skittles are sorted by color. First, let's talk about the materials you will need.

## Step 1: Materials

![](https://cdn.instructables.com/FU4/K903/JASJPHUU/FU4K903JASJPHUU.MEDIUM.jpg)

![](https://cdn.instructables.com/FLS/GR8W/JASJPHSL/FLSGR8WJASJPHSL.SMALL.jpg)

![](https://cdn.instructables.com/FSW/R0U8/JASJPHT5/FSWR0U8JASJPHT5.MEDIUM.jpg)

![](https://cdn.instructables.com/F0E/OHK8/JASJPHQY/F0EOHK8JASJPHQY.SMALL.jpg)

![](https://cdn.instructables.com/FCX/89S6/JASJPHQB/FCX89S6JASJPHQB.SMALL.jpg)

![](https://cdn.instructables.com/FOH/QKWW/JASJPHQ8/FOHQKWWJASJPHQ8.SMALL.jpg)

For this project, you will need a 3D printer and laser cutter (use either one of your own or use any public printer or cutter, an Arduino Uno with cable, a continuous rotation Servo and a Vex 180 Servo, 15-20 jumper wires, a 4 by 4 inch lazy susan, a funnel (specific type), and acrylic glue (links to all of these products except printer and cutter below). You may also need a standard ruler or other measuring tools. You will also need several software programs including Cura (for Ultimaker 3d printer), Arduino software and the Adafruit sensor library, Adobe Illustrator (or any program that can modify DXF files for the laser cutter), and Fusion 360 (if you want to modify the STL files).

Arduino Uno - [ https://www.adafruit.com/product/50](https://www.adafruit.com/product/50)

Arduino USB cable - [https://www.amazon.com/PlatinumPower-Cable-Arduino...](https://www.amazon.com/PlatinumPower-Cable-Arduino-Mega2560-Mega328/dp/B01MCUVHTQ/ref=sr_1_4?s=electronics&ie=UTF8&qid=1512504423&sr=1-4&keywords=arduino+uno+usb+cable)

Continuous Rotation Servo - [ https://www.adafruit.com/product/2442 ](https://www.adafruit.com/product/2442)

Vex 180 Servo - [ https://www.vexrobotics.com/motors.html ](https://www.vexrobotics.com/motors.html)

4x4 Lazy Susan - [ https://www.amazon.com/gp/product/B002TIKEQ6/ref=...](https://www.amazon.com/gp/product/B002TIKEQ6/ref=oh_aui_detailpage_o02_s00?ie=UTF8&p)

Funnel - [ https://www.amazon.com/dp/B074WT7DWL/ref=cm_sw_r_...](https://www.amazon.com/dp/B074WT7DWL/ref=cm_sw_r_sms_apip_ArQOEdain5cIz)

Acrylic Glue - [ https://www.amazon.com/SCIGRIP-Acrylic-Cement-Low...](https://www.amazon.com/SCIGRIP-Acrylic-Cement-Low-VOC-Medium/dp/B005ZH31W2/ref=sr_1_5?ie=UTF8&qid=1512499458&sr=8-5&keywords=acrylic+glue)

RGB Sensor Library - <https://github.com/adafruit/Adafruit_TCS34725>

## Step 2: Creating the Physical Components

The next step is to laser cut and 3D print your parts. Using the files attached, you will use your laser cutter to cut the two side support pieces, the trough, the servo support pieces, the receptacle base piece, the machine base pieces (two of the Base1 copies and one Base2 copy), and the two lock rings. You will then use your 3D printer to print the gumball mechanism, the trapdoor, the sorting chamber, the lid for the sorting chamber and the base plate for the sorting chamber. The printing will take several days, so make sure you set aside time for this to take place.

## Step 3: Assemble the Trough

![](https://cdn.instructables.com/FQT/DS6N/JASJPJVY/FQTDS6NJASJPJVY.MEDIUM.jpg)

![](https://cdn.instructables.com/F96/3IGY/JASJPKHT/F963IGYJASJPKHT.SMALL.jpg)

After you've cut out and printed all of your parts, it's time to assemble. Start by applying glue to the gaps in the grooves of one side of the trough bottom (Figure 3A). Then, press and hold this piece into the slots on one of the vertical supports (Figure 3B). Make sure the narrow end of the trough is at the short end of the vertical support. Then, repeat this with the other side of the trough bottom and the other vertical support.

## Step 4: Assemble the Servo Receptacle Housing

![](https://cdn.instructables.com/FCI/WEA7/JASJPLP0/FCIWEA7JASJPLP0.MEDIUM.jpg)

![](https://cdn.instructables.com/F74/O3U5/JASJPLOZ/F74O3U5JASJPLOZ.MEDIUM.jpg)

![](https://cdn.instructables.com/FRA/LLOJ/JASJPO8G/FRALLOJJASJPO8G.SMALL.jpg)

While these parts are drying, go ahead and assemble the receptacle servo housing. Start by sliding screws through one edge of the lazy susan and into the top of the receptacle servo housing (Figure 4A). Next, insert nuts into the two T-joints on each of the side pieces of the receptacle servo housing (Figure 4B), and hold them steady while screwing the screws down into them. After that, insert the continuous rotation servo into the rectangular opening in the top piece, and screw it in place using the screw holes and the screws which came with the servo. Figure 4D shows what the whole Sorting Chamber Unit should look like when assembled.

## Step 5: Assemble the Sorting Chamber Base

![](https://cdn.instructables.com/FG8/W79P/JASJPOXU/FG8W79PJASJPOXU.MEDIUM.jpg)

![](https://cdn.instructables.com/FSQ/M0PP/JASJPPJZ/FSQM0PPJASJPPJZ.MEDIUM.jpg)

After the receptacle servo is screwed into its housing, attach the provided servo horn (the one which looks like an X, as shown in Figure 5A). Next, screw the top edge onto the chamber base (Figure 5B) into the top edge of the lazy susan (the screw head should be under the top edge of the lazy susan). Figure 5C shows the completed sorting chamber base and receptacle housing.

*****IMPORTANT NOTE(S)*****

Be careful not to tighten the chamber base too much. Only tighten the nuts enough to hold it in place. Also, when screwing down the chamber base, be sure that the servo horn fits into the extrusion on the bottom of the base piece.

## Step 6: Assemble the Moving Plate

Next, assemble the moving plate of the gumball mechanism. Grab the handle and glue it to the moving plate, making sure the direction of the handle lines up with the hole. Also make sure the square shape in the handle fits the square extrusion on the moving plate. Next, put a tiny screw in the hole on the handle to act as the actual handle part (for users to grab onto to spin the plate).The moving plate is now finished (Figure 6A).

## Step 7: Assemble the Skittle Dispenser

After assembling the Sorting Chamber Unit, the Trough, and the moving plate, the next step is to assemble the Skittle Dispensing Unit. First, you will get the stationary plate of the gumball mechanism that you 3D printed and glue it into the mouth of the funnel. Make sure the funnel fits inside of this plate, so it creates a "shell" for the mouth of the funnel. Important, make sure the hole in this plate lines up with the handle on the funnel. This will make it easier for users to know when a skittle will drop. Next, place the moving plate of the gumball mechanism inside of the funnel on top of the stationary plate. Finally, glue the two lock rings to the funnel right above the moving plate to keep this plate from lifting up when you rotate it. Once all this is done, you should have a working dispenser (Figure 7A). Now, you will attach this dispenser to the top of the trough. Line up the dispenser so the hole is over the trough (making sure the skittle will actually land in the trough). Once you have a good position, slightly lift up the dispenser and add glue to the supports of the trough where the dispenser is going to go. Hold the dispenser on this spot until the glue is dry.

*****IMPORTANT NOTE(S)*****

This dispenser has a slight flaw in it. The hole on the moving plate is lined up with the moving plate handle, and the hole in the stationary plate lines up with the funnel handle. When you dispense a skittle, quickly spin these holes past one another so there is only time for one skittle to drop. If it is done too slowly, multiple skittles will drop at once.

## Step 8: Trapdoor Mechanism

Insert your 3D printed trapdoor piece into your trapdoor servo (the non-continuous one). Carefully line up the trapdoor piece with the end of the trough, making sure there is little to no space between the end of the trough and the trapdoor piece. Mark with a marker or pen where where the servo must be attached to the vertical support in order to maintain this trapdoor positioning. Next, using either glue or tape (depending on whether or not you want to be able to remove your servo) attach the servo to the vertical support piece. Figure 8A shows what this should look like.

## Step 9: Circuit

![](https://cdn.instructables.com/FV6/FHBW/JASJPSKF/FV6FHBWJASJPSKF.MEDIUM.jpg)

Solder the pins into the color sensor breakout board according to the instructions given by Adafruit (https://learn.adafruit.com/adafruit-color-sensors/assembly-and-wiring). Next, tape the color sensor to the underside of the trough bottom at the narrow end, being sure to have the screw holes lined up slightly outside of the edge of the trough (Figure 9A). After that is done, screw the Arduino Uno onto the side of the vertical support that has screw holes. Finally, use jumper wires and a breadboard to hook up the arduino, color sensors, and servos according to the Figure 9B.

## Step 10: Test RGB Sensor

Download the attached file for the code and open it in the Arduino software. Before you use the main program, open the color-testing program. The numbers for each color vary depending on the lighting in the environment around you. Use this testing program to see the R, G, and B numbers for each color. Make sure to write these numbers down as intervals. For example, if after a few trials you see that the R value for yellow is almost always over 6000, you can remember it as >6000\. To be more robust, you can cap this interval, e.g. from 6000-8000 (this may not be the correct number). Remember a closed interval as >6000 and <8000\. These numbers will be used for later. Once you have written down the values for each color, open the main program. Scroll to the function sortColor(). In this function, you will see several if statements determining the value of the R, G, and B of the sensor outputs. You will see in each statement a print("COLOR Skittle\n"). This is to help you know which statement corresponds to which color. Replace the rd, grn, and blu in each if statement with the correct values you found earlier. This should make the program work with the specific lighting of the environment around you during your testing.

https://github.iu.edu/epbower/CandySorter

## Step 11: Final Step: Run the Main Program

Once you have built the machine and updated the values for the RGB Sensor, you are ready to run the program. Plug the Arduino into the USB port on your computer. A light on the Arduino should turn on. With the main program open, compile the code by clicking on the checkmark at the top left of the window. This ensures there are no errors in the code. If there are, a warning message will show up at the bottom of the screen with information about the error. If all is well, it will say it is done compiling. Once this is done, upload the program to the Arduino by clicking the arrow next to the checkmark. Once you click this, the Arduino will automatically start controlling the machine. Note that the only way to stop the Arduino is to either disconnect the cable from your computer or pressing the reset button on the Arduino. If you click the reset button, you will need to re-upload the code to the Arduino. If you simply disconnect the power, it will immediately start working once it is plugged back into power.
