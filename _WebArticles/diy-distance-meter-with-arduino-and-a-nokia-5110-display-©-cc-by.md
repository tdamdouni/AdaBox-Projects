# DIY Distance Meter with Arduino and a Nokia 5110 Display © CC BY

_Captured: 2017-11-29 at 11:09 from [create.arduino.cc](https://create.arduino.cc/projecthub/nickthegreek82/diy-distance-meter-with-arduino-and-a-nokia-5110-display-117778?ref=platform&ref_id=424_recent___&offset=2)_

In this tutorial we are going to see how to build a very useful **Distance meter with a big Nokia 5110 LCD** display using Arduino. Easily measure the distance from your Arduino and build interesting devices with this project!

Building a **distance meter** is a great learning experience. When you finish building this project you will have a better understanding of how the ultrasonic distance sensor works, you will know how to wire a Nokia 5110 lcd display and you are going to see in action how powerful the Arduino platform can be. With this project as a base and the experience gained, you will be able to easily build more complex projects in the future.

We can use this project to measure the distance index in Real Time so we can use it in my projects

Without any further delay, let's get started!

![](https://hackster.imgix.net/uploads/attachments/384940/FVNP17NITY6ICM1.MEDIUM.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

The parts needed in order to build this project are these:

3\. Arduino Uno ▶ <http://educ8s.tv/part/ArduinoUno>

4\. Small Breadboard ▶ <http://educ8s.tv/part/SmallBreadboard>

5\. Wires ▶ <http://educ8s.tv/part/Wires>

The cost of the project is very low, it is about 10$.

![](https://hackster.imgix.net/uploads/attachments/384941/FPBVP8JITY6ICT8.MEDIUM.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

The HC-SR04 is a very interesting sensor. It use ultrasounds in order to measure the distance from it's closest object. Let's take a look at the specifications:

Ultrasonic ranging module HC - SR04 provides 2cm - 400cm non-contact measurement function, the ranging accuracy can reach to 3mm.

The modules includes ultrasonic transmitters, receiver and control circuit.

This is how the sensor works:

  * Using IO trigger for at least 10us high level signal, 
  * The Module automatically sends eight 40 kHz signals and detect whether there is a pulse signal back. 
  * If the signal is back, through high level , time of high output IO duration is the time from sending ultrasonic to returning. Test distance = (high level time×velocity of sound (340M/S) / 2

In simpler words, the sensor, sends an ultrasound, then it detects wheather this ultrasound has bounced off of an object or not. If the ultrasound has bounced off, it measures the time that it took it to bounce. Since we know the speed of sound, we can easily measure the distance that the ultrasound traveled!

![](https://hackster.imgix.net/uploads/attachments/384942/F2TI7HWISCB8MPK.MEDIUM.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

The Nokia 5110 is my favorite display for my Arduino Projects.

The Nokia 5110 is a basic graphic LCD screen which was originally intended for as a cell phone screen. It uses the PCD8544 controller which is a low power CMOS LCD controller/driver. Because of this this display has an impressive power consumption. It uses only 0.4mA when it is on but the backlight is disabled. It uses less than 0.06mA when in sleep mode! That's one of the reasons that make this display my favorite. The PCD8544 interfaces to microcontrollers through a serial bus interface. That makes the display very easy to use with Arduino.

You only need to connect 8 wires and use the following library: [ http://www.rinkydinkelectronics.com/library.php?i...](http://www.rinkydinkelectronics.com/library.php?id=47)

This impressive library is developed by Henning Karlsen who has put a huge amount of effort to help the Arduino community move forward with his libraries. I

have prepared a detailed tutorial on how to use the Nokia 5110 LCD display with Arduino. I have attached that video in this tutorial, it will provide may useful information about the display, so I encourage you to watch it carefully.

Now, let's move on!

![](https://hackster.imgix.net/uploads/attachments/384943/FBCVD6GITY6IEBL.MEDIUM.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

Let's now connect all the parts together.

At first we connect the HC-SR04 distance sensor module. It only has 4 pins.

**Connecting the Distance Sensor **

Vcc Pin goes to Arduino's 5V

Trig goes to Digital Pin 7 of the Arduino

Echo goes to Digital Pin 6 of the Arduino

GND pin goes ton Arduino's GND

The next step is to connect the Nokia 5110 LCD display.

**Connecting the Nokia 5110 LCD Display**

RST goes to Digital Pin 12 of the Arduino

CE goes to Digital Pin 11 of the Arduino

DC goes to Digital Pin 10 of the Arduino

DIN goes to Digital Pin 9 of the Arduino

CLK goes to Digital Pin 8 of the Arduino

VCC goes to Arduino 3.3V

LIGHT goes to Arduino GND (backlight on)

GND goes to Arduino GND

Now that we have connected all the parts together, all we have to do is to load the code. Now **we can start measuring the distance Real Time!**

The code of the project consists of2 files.

  * ui.c 
  * Distance_Sensor_Nokia.ino

**ui.c Code - The User Interface **

In the file ui.c, there are the binary values of user interface that appears after the the project shows the splash screen. Please watch the attached video I have prepared in order to see how to load your custom graphics to your Arduino Project.

D**istance_Sensor_Nokia.ino Code - Main Program**

The main code of the project is very simple. We need to include the Nokia 5110 library. Next we declare some variables. We initialize the display and we print the ui icon once. Then we read the analog value from the sensor 50msec. All the magic happens in the following function:
    
    
    <p>String readSensor()<br>{
      String distanceS = "0";
     digitalWrite(trigPin, LOW); 
     delayMicroseconds(2); </p><p> digitalWrite(trigPin, HIGH);
     delayMicroseconds(10); 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     distance = duration/58.2;
     distanceS = String(distance);
    </p><p>if(distance>maximumRange || distance <minimumRange</p><p> {
       distanceS = "---";
     }
     delay(50);
     return distanceS;
    }</p>
    

In this function we read the distance from the sensor and we convert it to String variable in order to be printed on the display.

I have attached the code to this tutorial. In order to download the latest version of the code you can visit the project's webpage: <http://educ8s.tv/hcsr04-ultrasonic-sensor/>

![](https://hackster.imgix.net/uploads/attachments/384944/FEPEGIBITY6IEBV.MEDIUM.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

Now that the code is loaded we can test the distance meter and see the distance in real time on the Nokia 5110 LCD display.

As you can see in the attached photos, **the Distance Meter works fine.** We can see the distance in cms and it updates every 50ms! Great isn't it?

As you can see, this project is a great demonstration of what open source hardware and software is capable of. Within a few minutes one can build such an impressive project! This project is ideal for beginners and as I said in the beginning, this project is a great learning experience.

I would love to hear your opinion on this project. Do you find it useful? Are there any improvements that can be implemented to this project? Please post your comments or ideas in the comments section below!
