# Arduino composite video out using only 3 resistors

_Captured: 2018-05-19 at 12:07 from [www.suppertime.co.uk](http://www.suppertime.co.uk/blogmywiki/2017/01/arduino-tvout/)_

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/Screen-Shot-2017-01-15-at-20.05.58.png)

> _arduino video on CRT TV_

It's supposed to be easy - 2 or 3 resistors and you can get your Arduino micro controller to produce low-resolution black and white composite video. Well, it wasn't for me. It took me hours to get it working, but I finally cracked it. It's possible I was unlucky, stupid or possibly both - but I'm writing it up before I forget how I did it and in case someone else has the same problem.

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/Screen-Shot-2017-01-15-at-20.05.181-1024x692.png)

I tried about 4 different projects on different web sites which all broadly worked the same way: you connect a couple of resistors to some pins on the Arduino, wire them up to a phono plug, install the TV Out library in the Arduino IDE, compile and flash the code and off you go.

I could not get any of the sample code to compile in the current version of the Arduino IDE. I lost track of the different error messages I got. I'd make progress then something else would break. Googling error messages kept telling me to install the TV Out libraries - which I had.

Spookily I'd decided to try an old version of the Arduino IDE at the same time that @gadgetoid on Twitter made the same suggestion. In the end I compiled and uploaded working code using version 1.0.1 of the Arduino IDE on an old Lenovo Ideapad running MacOS X 10.6 (Snow Leopard). I could not get any demo code to compile using the current version of the Arduino IDE, nor could I install an old version of the IDE on my MacBook because they required older versions of Java. Thank goodness for the old hackintosh!

I used:

  * An old Arduino UNO (perhaps its age was part of the problem)
  * a phono / RCA plug
  * some jumper wires
  * a small breadboard
  * A 470 ohm resistor
  * A 1K ohm resistor
  * A 75 ohm resistor
  * An old laptop to program the Arduino
  * an old CRT TV with a composite video input (most modern LCD TVs have such inputs - or you can use a SCART adaptor)

Here's how I wired it up. (In the photo there are 4 resistors not 3 because I lacked a certain value and wired two together in series).

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/Screen-Shot-2017-01-15-at-20.11.17.png)

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/TVOut-Uno-1024x639.png)

(I am grateful to [microcontrollerelectronics.com](https://microcontrollerelectronics.com/tv-video-output-from-the-arduino/) for hosting the Fritzing diagram of their project - the only difference here is that I had to move the green video wire to pin 7 (not 8) as I am using an Arduino UNO not a Leonardo as they did.)

The version of the TV Out library that I think I used finally (there were so many) was [TVOutBeta1.zip](https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/arduino-tvout/TVoutBeta1.zip) - unpacked the zip file and put the 3 folders **pollserial**, **TVout** and **TVoutfonts** in the Arduino/Libraries folder like this:

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/Screen-shot-2017-01-15-at-19.40.01.png)

> _TV Out libraries in place_

This is the code that finally worked - I'm afraid I can't remember where I copied it from now, I had so many snippets of code on the go. If it's yours I will of course credit and link (or remove it).

Here it is working on a modern LCD TV rather than the retro CRT model at the top of the page:

![](http://www.suppertime.co.uk/blogmywiki/wp-content/uploads/2017/01/Screen-Shot-2017-01-15-at-20.04.54.png)

> _arduino video on LCD TV_

Now I wonder if I can remember why I wanted to get this working in the first place..?
    
    
    #include <TVout.h>
    #include <fontALL.h>
    
    TVout TV;
    unsigned char x,y;
    
    void setup()  {
      x=0;
      y=0;
      TV.begin(PAL);	//for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
      TV.select_font(font6x8);
    }
    
    void loop() {
      TV.clear_screen();
      x=0;
      y=0;
      for (char i = 32; i < 127; i++) {     TV.print_char(x*6,y*8,i);     x++;     if (x >= TV.char_line()) {
          y++;
          x=0;
        }
      }
      TV.delay(1000);
      TV.clear_screen();
      TV.println("Fill the Screen\nPixel by Pixel");
      TV.delay(1000);
      TV.clear_screen();
      for(x=0;x
