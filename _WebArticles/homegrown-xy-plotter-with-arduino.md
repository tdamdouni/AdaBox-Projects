# Homegrown XY plotter with Arduino

_Captured: 2018-01-07 at 20:16 from [pilhuhn.blogspot.de](http://pilhuhn.blogspot.de/2018/01/homegrown-xy-plotter-with-arduino.html?m=1)_

[ _This is work in progress and only for myself. If you are looking for ready-made kit, then have e.g. a look at the [MaXYposi from German Make Magazine](https://www.heise.de/make/artikel/MaXYposi-Projektseite-zum-universellen-XY-Portalroboter-von-Make-3676050.html)_ ]

Back in school we had a HP plotter well hidden in some closet in the science department. I was able to play with it for a while and always had the desire to have one on my own (but why, where dot-matrix printers are so much versatile and useful).

![Bildschirmfoto 2018 01 03 um 12 11 22](https://lh3.googleusercontent.com/-wrAIkftgdfg/Wky6nC_TONI/AAAAAAAAGlQ/fS8ekzSU7KQDP1Tw1-Qf6-cHuMyOX300QCHMYCw/Bildschirmfoto%2B2018-01-03%2Bum%2B12.11.22.png?imgmax=1600)

> _Photo from Plotter in action._

[Video here](https://www.dropbox.com/s/nkk9bnghxywijzf/TRIM_20180102_154921.mp4?dl=0).

Fast forward many many years. Stepper motors are easily available, I am back into doing stuff with electronics and micro controllers and recently saw someone creating some displays with engraved acrylic. This triggered me to finally get started with the plotter (and later engraver etc).

To get going I got some parts and as I am an old-school 5V guy, I totally like the original Arduino UNO. In the list, I put in links for reference. I am not affiliated with those companies

  * [FabScan shield](http://www.watterott.com/de/Arduino-FabScan-Shield) \- physically hosts the Stepper motor drivers
  * [SilentStepSticks](http://www.watterott.com/de/SilentStepStick-TMC2130) \- motor drivers, as the Arduino itself can't handle the voltage and current that a stepper motor needs. I am using the ones with a Trinamic TMC2130 chip, but in standalone mode for now. Those are replacements for the Pololu 4988, but allow for much quieter operation.
  * [StepStick protectors](http://www.watterott.com/de/SilentStepStick-Protector) \- diodes that prevent the turning motor to fry your motor drivers (you want them, believe me)
  * Stepper motors - I took NEMA 17 ones with 12V ([Watterott](http://www.watterott.com/de/Schrittmotor-incl-Anschlusskabel), [Sparkfun](https://www.sparkfun.com/products/9238))
  * [Linear guard rails](https://www.ebay.de/itm/CNC-Set-12x-600mm-Linearfuhrung-Linear-Guide-Rail-Stage-3D-/322917927292?hash=item4b2f68897c)
  * Wooden base plate
  * Wood, screws, ..
  * GT2 belt, [GT2 timing pulley](http://www.watterott.com/de/OpenBuilds-GT2-2mm-Aluminium-Timing-Pulley)

As you can see in the next picture I started out much too big - I can't really have the plotter sit on my desk comfortably, but anyway :) I did it for learning purposes (and as I have to re-do some things, I'll also use smaller beams).

## Hardware side

![IMG 20180101 185406](https://lh3.googleusercontent.com/-rLeIGgcySko/Wky4T6GVBRI/AAAAAAAAGk8/wB8Dv8E4muY3zTPpNSUzR47idrTMI-ThACHMYCw/IMG_20180101_185406.jpg?imgmax=1600)

> _View of the plotter base plate with X-axis and Y-axis rails_

The belt is mounted on both sides of the rail and then slung around the motor with some helper wheels:

![](https://photos-4.dropbox.com/t/2/AACiGH_dG0C4a2nhr1tZuCTrFa-h-g_xSInBZ3Z6oAI84Q/12/21627069/jpeg/32x32/3/1514991600/0/2/IMG_20180103_110206.jpg/ENGZnRAYrxcgAigC/e2JCYDTjaCR2OKfF-hdIDV8EihDdQqJ8fjAR7bU83QI?dl=0&size=1280x960&size_mode=3)

> _Detail of the belt routing on the motor_

On the Arduino side there is a stack of things. On the bottom, the Arduino, then the FabScan shield, then on motor slots 1+2 a StepStick protector and then on top of them the SilentStepSticks. Note that the SCK and SDI pins are not connected

![IMG 20180103 110111](https://lh3.googleusercontent.com/-XA2HeEco8xU/Wky4te9ktYI/AAAAAAAAGlA/oy4KmssaGK0PBBEx-wfkuehu6SyeMu9XgCHMYCw/IMG_20180103_110111.jpg?imgmax=1600)

Setup on Arduino ([see here for a larger image](https://www.dropbox.com/s/7bp3bo5g2ujser8/IMG_20180103_110111.jpg?dl=0))

Btw be careful with the wires to the motor to correctly attach them. When in doubt have a look at the data sheet or a ohm-meter to figure out which wires belong together.

## Software side

I know that there is software like [Grbl](https://github.com/gnea/grbl), that can interpret so called G-codes for tool movement and other things and I could have just flashed that to the Arduino, but I am too curious for that and wanted to better understand things myself.

### Basics

To drive a stepper motor with the StepStick driver (or compatibles) one basically needs to send a high and then a low signal to the respective pin. Or in Arduino-terms

` digitalWrite(stepPin, HIGH);  
delayMicroseconds(30);  
digitalWrite(stepPin, LOW);  
`

Where `stepPin` is the pin number for the stepper - 3 for motor 1 and 6 for motor 2.

Before the stepper does any work, it needs to be enabled.

` digitalWrite(enPin, LOW); `

Actually the StepStick knows three states for the pin here

  * LOW: motor is enabled
  * HIGH: motor is disabled
  * pin not connected: motor is enabled but goes into some energy saving after a while

When a motor is enabled, its coils are powered and it keeps its position. It is almost impossible to manually turn its axis. This is good for precision purposes, but also means that both motors and driver chips are "flooded" with power and will thus warm up.

And not last but not least, we need a way to determine the direction

` digitalWrite(dirPin, direction); `

The following table lists the functions and the pins

FunctionMotor1Motor2

enable
2
5

direction
4
7

step
3
6

Before we can use the pins, we need to set them to OUTPUT mode, best in the `setup()` section of the code

` pinMode(enPin1, OUTPUT);  
pinMode(stepPin1, OUTPUT);  
pinMode(dirPin1, OUTPUT);  
digitalWrite(enPin1, LOW); `

With that knowledge we can easily get the stepper to move around:
    
    
     totalRounds = ... for (int rounds =0 ; rounds < 2*totalRounds; rounds++) { if (dir==0){ // set direction digitalWrite(dirPin2, LOW); } else { digitalWrite(dirPin2, HIGH); } delay(1); // give motors some breathing time dir = 1-dir; // reverse direction for (int i=0; i < 6400; i++) { int t = abs(3200-i) / 200; digitalWrite(stepPin2, HIGH); delayMicroseconds(70 + t); digitalWrite(stepPin2, LOW); delayMicroseconds(70 + t); } } 

This will make the slider move left and right. When you execute that code, you can also see that this only deals with one stepper, but for a XY-plotter we have two axis to cater for.

### Command interpreter

I started to implement a simple command interpreter that allows to use path specifications like
    
    
    "X30|Y30|X-30 Y-30|X-20|Y-20|X20|Y20|X-40|Y-25|X40 Y25

to describe relative movements in millimetres (internally 1mm equals 80 steps).

## Next

Next steps are obviously a way to raise and lower the pen from software, then add some end-detectors (but I may skip them and use the StallGuard mode of the TMC2130).

And a way to feed command strings with arbitrary length from the computer via serial code.

And then perhaps in the future I add a real z-Axis than can hold an engraver to do wood milling or PCB drilling or engraving of acrylic or .... :-) (A laser comes to mind as well).

## More ...

That's it for now. The software is available at <https://github.com/pilhuhn/xy-plotter> and comes without any warranty.
