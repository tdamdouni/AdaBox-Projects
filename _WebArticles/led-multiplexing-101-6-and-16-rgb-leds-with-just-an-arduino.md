# LED Multiplexing 101: 6 and 16 RGB LEDs With Just an Arduino

_Captured: 2017-11-18 at 14:25 from [www.instructables.com](http://www.instructables.com/id/LED-Multiplexing-101-6-and-16-RGB-LEDs-With-Just-a/)_

![](https://cdn.instructables.com/FPB/G4EN/J9YJFZHD/FPBG4ENJ9YJFZHD.MEDIUM.jpg)

There are multiple ways to light a lot of LEDs off an Arduino (or any other microcontroller): shift registers, LED drivers, programmable LEDs, but the more LEDs you want to control, the closer you're getting to the multiplexing: the ultimate technique for driving hundreds and thousands of LEDs. There are a lot of Instructables dealing with multiplexing, but most of them describe the particular project and do not cover the basics; I decided to amend that. And to do this, I built a couple of devices that use the bare minimum of hardware between the Arduino and the RGB LEDs to make the clearest possible picture of how the multiplexing works.

I will show two projects here. The first one drives 6 RGB LEDs using just three MOSFETs; the second one drives 16 LEDs but needs eight MOSFETs and a demultiplexing chip. The first project will be common-anode LEDs and P-Channel MOSFETs, the second one will use common cathode LEDs and N-Channels. In most cases, you should stick to the first pair while dealing with LEDs, as all the LED drivers are current-sinking devices. But, alas, I have only three P-Channels MOSFETs in breadboard-friendly packages. It's very easy to switch between the N- and P-Channel MOSFETs, provided you also use a different type of LEDs and demux chip; I'll give the details.

So, to test the stuff explained here, you'll need:

\- An Arduino

\- 6 or 16 RGB LEDs, either common anode or common cathode

\- 3 or 8 MOSFETs, P-Channel or N-Channel respectfully

\- 1 demux chip, either 74HC138 or 74HC238

\- 6 220 Ohm resistors

Also, grab the sketches [from GitHub](https://github.com/Ontaelio/ArduinoMultiplexing101).

Please note that this Instructable is educational, not practical. There are better ways to control multiple RGB LEDs off an Arduino. With these two projects, I'm trying to help better understand the ways multiplexing, timers and interrupts work. There is a certain wow-factor, however, so some fun will be provided.

But first, theory!

## Step 1: Charlieplexing Vs Multiplexing

There are two main techniques employed when multiplexing LEDs. These techniques are often mixed up, but, while their basic principle (persistence of vision) and their end result are relatively the same, the ways they achieve this result are fundamentally different, and it is important to understand the difference right from the start to avoid confusion later.

Charlieplexing relies on the tri-state nature of the microcontroller pins. These pins can be active high, active low and passive (aka input, or high impedance state). As the LEDs turn on only when they have voltage on the anode and ground on the cathode and do nothing in any other situation, it is possible to connect a lot of LEDs to a small number of microcontroller pins in all the physically possible ways and turn them on one by one, turning one pin high, one low, and keeping the rest in input mode. If you switch between the LEDs really fast, the persistence of vision will make them look like they're all on. There are tons of Charlieplexing Instructables, you can read about its theory [ here](https://en.wikipedia.org/wiki/Charlieplexing) . For now, let's just note that Charlieplexing a) works with microcontrollers and not with shift registers or LED drivers and b) turns on only one LED at any given time.

'Normal' multiplexing deals with just two states of controlling pins (an active high/low and 'the other' one) and can turn on multiple LEDs at the same time. The basic multiplexing structure is a 2D matrix with all rows and columns connected to controlling sources. If your LEDs cathodes are connected to rows and anodes to columns, you may turn a particular LED in this matrix on by providing voltage to the appropriate column and ground to the appropriate row, while keeping the rest in their respective 'off' states. To turn on more than one LED in a single row, simply provide more columns with voltage, while keeping only one row grounded. By quickly switching between different rows, while providing new column values with each switch, you'll invoke the persistence of vision effect. The fact that multiple LEDs can be on at a single row at the same time means rows cannot be connected to the controller directly; transistors are a must.

From a practical standpoint, Charlieplexing can light more LEDs with fewer pins and can be arranged on a single microcontroller, hence its popularity in the Arduino world, especially with LED cubes (check this [excellent RGB example](https://aglick.com/charliecube.html)). On the downside, Charlieplexing has an obvious limitation to the number of connected LEDs due to its one-LED-at-a-time inherent vice, so no huge LED screens here. 'Normal' multiplexing can light up an unlimited amount of LEDs, but this comes at a price of some additional hardware in the form of transistors, demultiplexers, LED drivers, video controllers, bigger MCs and a lot of other stuff depending on the device complexity. However, a simple educational multiplexing experiment can be made without a lot of additional stuff on a single Arduino, as will be shown in this Instructable. I'll use just MOSFETs and a single demux chip here, and the latter only in the bigger contraption.

We're doing with the 'normal' multiplexing here. We use the usual PWM outputs of the Arduino, but multiply them using timers and an interrupt service routine(ISR). I'd love to explain it all in a short passage, but it's not possible (I tried), so please bear with me. It is necessary to understand the works.

## Step 2: PWM

When you light up an LED on an Arduino with the analogWrite() function, you're using the Atmega328 inbuilt PWM, the rude digital approximation of an analog signal. Using inbuilt PWM is not the 'true' multiplexing way, or, at least, not the most used one. As far as I know, in most industrial applications a different modulation way is employed, the one that can thread multiplexing right into the modulation (or vice versa; the idea is that a lot of outputs share the same modulation cycle). In fact, even PWM algorithm is not the most popular one. But for hobby projects, PWM is ok, good even, as it allows the microcontroller to do something else as well. But we need to understand how it works.

There is a lot of information about PWM. Just in case you missed it, here are the helpful links:

[ Atmega328p da tasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf) - always keep this stuff at hand. In fact, open it in a different tab right now. You don't have to read it all (it's a very exquisite torture), but you should check it all the time; I'll drop page numbers.

Secrets of Arduino PWM - an excellent work by Ken Sheriff, you can read the [ original ](http://www.righto.com/2009/07/secrets-of-arduino-pwm.html)or an [abridged ](https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM)version.

Almost everything is in there, no need to repeat. But I have to point out these multiplex-specific nuances that are either sparsely covered or missed there.

**PWM Modes** There are two main PWM modes for each timer: the fast mode and the phase correct mode. The second one is intended for use with motors, not LEDs (in fact, this is even noted in the datasheet). So we'll stick with the fast PWM. In this mode, the timer simply ticks from 0 (BOTTOM) to 255 (TOP), changing output state when it detects a match between the current timer and a set value. When the timer reaches TOP, it resets to BOTTOM and resets the output. In the normal mode the output starts HIGH then turns LOW on compare match; in the inverted mode, it starts LOW then turns HIGH. By default, Arduino library sets up Timer 0 to the normal fast mode and two remaining timers to the normal phase correct mode, we need to change this.

**PWM Buffering** The PWM technique is a digital emulation of an analog signal. The important thing is PWM requires a fixed time period (PWM cycle) to emulate the analog value correctly. If you stop the cycle in the middle or change the PWM value in the middle of the cycle, the emulation would fail. Thus PWM engines protect the PWM cycle from interference by buffering any new incoming PWM data, unless you explicitly specify the PWM cycle interruption. Any value you write into the PWM register (or send to an LED driver) will be buffered and then used on the next PWM cycle. It is a very important (and often missed) thing to remember while multiplexing, as you will want to change the PWM values each cycle (or at least synchronize these changes with the PWM cycles).

**PWM Frequency** Another thing resulting from the way PWM works is the frequency limitation. As the engine emulates analog signal by distributing digital signals over a fixed time period, this time period is always a lot longer than a simple tick of the microcontroller. An 8-bit PWM requires 256 PWM clock steps to complete one cycle, a 16-bit PWM needs 65536 steps; even with no prescaling on timers, this means a base frequency of 62.5 KHz and 244 Hz respectfully on a 16 MHz microcontroller. These numbers are then further divided by the multiplexing factor (the number of rows that turn on consequently, providing the persistence of vision effect). The overall refresh frequency of the multiplexing contraption must not be lower than 60 Hz to avoid flicker. It is better to calculate these values and find the right ones right from the start.

**Missing Zero** The nature of the Atmega328 PWM doesn't allow it to produce zero output (or 100% output in inverted mode). When the counter reaches TOP and resets to BOTTOM, the output in normal mode instantly turns HIGH. The comparison between the current clock value and the PWM value happens after that, and if the PWM value is zero, the flag is set, but the output change will happen only on the next tick of the PWM clock, producing a short spike instead of a flat low output. With the other extreme, when the PWM value equals TOP, everything's fine, as the change simply doesn't happen due to PWM clock reset. As we cannot afford zeroes being ones in LED multiplexing (all the LEDs will be always dimly on), we'll have instead to ditch the absolute maximum value of 255 by inverting either the PWM signal, or the physical logic of our scheme (use P-Channel, or PNP, transistors). In any case, the logic will have to be inverted in our code, 255 meaning off and 0 meaning full on (although in fact, it will be 1/255 less than full-on, but no one will notice).

## Step 3: ​Timers and Delays

PWM uses timers, heavily. In fact, PWM is all about timers. And we'll need timers to do the multiplexing thing. So, let's see how timers work.

Again, check these links, as I will only cover nuances needed for this particular experiment.

The official timers tutorial: [ http://www.atmel.com/Images/Atmel-2505-Setup-and-...](http://www.atmel.com/Images/Atmel-2505-Setup-and-Use-of-AVR-Timers_ApplicationNote_AVR130.pdf)

An unofficial quick guide: [ https://sites.google.com/site/qeewiki/books/avr-g...](https://sites.google.com/site/qeewiki/books/avr-guide/timers-on-the-atmega328)

An interesting Instructable: [ https://www.instructables.com/id/Arduino-Timer-Int...](https://www.instructables.com/id/Arduino-Timer-Interrupts/)

There are three timers in the Atmega328; two are 8-bit, one is 16-bit. This buggered me a lot at first, as I thought that 16-bit timer on an 8-bit architecture won't be synchronized due to the extra byte. Thankfully, this is not so; this 16-bit timer works exactly as the two remaining ones in 8-bit mode.

These three timers control 6 PWM outputs of the Arduino. We'll need all six PWM outputs for this project, which means we'll fully use all the available timers, which in turn means we'll turn our Arduino into a programmable LED driver of a rather limited use. It won't be able to do much else.

Thankfully, we will still be able to use one of the timers for our ISR (Interrupt Service Routine), but that was to be expected, as our ISR's timing is related to the PWM cycle. We just attach the ISR to one of the cycles' ends (also called an overflow interrupt).

But we'll lose a lot of Arduino timer-related functions, most notably millis(), delay(), delayMicroseconds() and anything else of that persuasion. Yes, the delay() will still work, but it will interfere with the PWM output, turning some of the LEDs on. The microseconds variation will turn different ones on. In any case, we need an alternative delay, the one that won't rely on timers.

The obvious way of using an empty loop won't work because the compiler optimizes the code and simply skips such loops right to the end, as they don't influence anything else…

And here was a rather fancy chapter about the different ways to set up a delay cycle without the timers, but with some recent strange happenings it started to grow out of hand and I decided to [move it to my blog](http://www.ultiblink.com/2017/11/09/optimization-gone-weird/).

So, to make the long story short, just use _delay_ms() function from the [AVR Libc library](http://nongnu.org/avr-libc/user-manual/) (Arduino IDE is built on it, so it's included by default). It works the same as delay() but doesn't use timers. It also requires that the value passed to it is known at the compilation time.

Another way is a loop with the Assembler NOP (do nothing for one cycle) command:
    
    
    // alternative Delay (approx 1.3m ticks per second)
    
    void justWait (uint32_t period){
    
        for (uint32_t z = 0; z<period; z++) __asm__("nop\n\t");
    
    }

If these two don't work for you, or if you're just curious, go check that blog link above for some evil optimization magick.

## Step 4: ​Hardware

![](https://cdn.instructables.com/FIL/UNVD/J9YJFAYF/FILUNVDJ9YJFAYF.MEDIUM.jpg)

Even if we have only 6 LEDs, let's think of them as a matrix. By common convention, the lines of LEDs quickly lighting up one after the other are called rows, and the lines that have only one LED on at any given time are called columns. As we're dealing with RGB LEDs, the R, G and B lines should be columns and the anode/cathode lines are rows. So, we have a vertical 'screen' with 2x3 'resolution'.

What we intend to do is:

1) Provide RGB values for the 2 LEDs of the first row;

2) Turn on the MOSFET that powers up the first row;

3) Wait a very small amount of time;

4) Turn that MOSFET off;

5) Change RGB values to the ones of the second row;

6) Turn on the MOSFET that powers up the second row;

7) And so on until all three rows are shown, then back to step 1.

We connect all the R, G and B columns to 6 PWM pins of the Arduino and three rows to our MOSFETs' drains. The MOSFETs' gates are connected to three non-PWM Arduino pins; they should be on the same Atmega328 port for speed, so they are either 2, 4 and 7 or 8, 12 and 13. We'll use the former. MOSFETs' sources are connected to 5v, as we use P-Channel ones and common anode LEDs. In the case of N-Channels and common cathode LEDs the sources go to GND, but the rest of the setup remains the same. Because we are connecting MOSFET gates to the tri-state pins of the Arduino, we don't need any pullup/pulldown resistors on them.

We will still need resistors on PWM pins, the usual ones we use with the LEDs, like 220 Ohms. We can change them to 10 Ohms after we are 100% sure our sketch works.

## Step 5: ​Setup

Ok, time to do some programming. First, the [ArduinoMultiplexDemo-6LEDs-P-Channel sketch](https://github.com/Ontaelio/ArduinoMultiplexing101/blob/master/ArduinoMultiplexDemo-6LEDs-P-Channel/ArduinoMultiplexDemo-6LEDs-P-Channel.ino).

As our multiplexing relies on timers and an ISR, we need to set it all up first. Microcontrollers are multifunctional devices, each of their pins has a bunch of modes of work, and these modes are selected by writing particular bits into the control bytes, or registers. In fact every microcontroller program starts with such setup but with the Arduino/Wiring IDE we don't see it because it is done in the background by simply writing the 'most popular' values into the registers before executing our sketch. These default settings won't work with our project, so we'll have to rewrite them.

So, let's go through our setup() function and understand what is happening here.

First, we're setting up pins. This can be done with Arduino functions pinMode() and digitalWrite() because this is a setup and there's no need to hurry here, but as we will have to use [direct port manipulation](https://www.arduino.cc/en/Reference/PortManipulation) later we can as well start right now and save some space. So:
    
    
    DDRD  |= 0b11111100; //set pins 2-7 to OUTPUT
    
    PORTD |= 0b10010100; //set pins 2, 4, 7 HIGH; replace |= with &= ~ for N-Channel (LOW)
    
    DDRB  |= 0b00001110; //set pins 9-11 to OUTPUT

Next, we will stop the timers that were started by the unseen Arduino setup. We will reconfigure them and then start them again simultaneously (check page 188 of the datasheet):
    
    
    GTCCR |= _BV(TSM) | _BV(PSRASY) | _BV(PSRSYNC);

Next step is setting up a non-inverted Fast PWM mode. The WGM bits of the Timer Compare Control Register select the PWM mode, and the COM bits are setting its behavior on compare match for compare modules A and B. Note that timers 0 and 2 are 8-bit, so their settings are similar. Timer 1 is 16-bit and its Fast PWM bits are different. More on this on pages 138, 170 and 203 of the datasheet.
    
    
    //setup fast PWM
    
    //timer0 A non-inverted | B non-inverted | fast PWM (WGM0 = 11)
    
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    
    
    
    //timer1 A non-inverted | B non-inverted | fast PWM 8 bit (WGM1 = 01 01)
    
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
    
    TCCR1B = _BV(WGM12); // fast PWM cntd
    
    
    
    //timer2 A non-inverted | B non-inverted | fast PWM (WGM2 = 11)
    
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

(for common anode LEDs and N-Channel MOSFETs get the inverted variant from the second project in this Instructable)

Now we set up the prescalers. The prescalers make the timers run slower than the microcontroller (clk/prescaler), allowing the latter to do some other stuff. If we set the prescalers to 1, the MC will spend most of its time doing our multiplexing routine. Prescalers influence the refresh rate of our multiplexing device.

How to determine the best prescaler value? The refresh rate must not be lower than 60Hz (60 refreshes per second) to avoid visible flicker. 100Hz is better. Let's take 100 and multiply it by the number of rows and the number of PWM steps: 100 * 3 * 256 = 76,800, or 76.8KHz; that's the optimal frequency for our timers. Divide MCs frequency by this number: 16M / 76.8K = 208 - the optimal prescaler.

You can find the prescaler values for the three timers on pages 142, 173 and 206 of the datasheet. We need the same prescaler on all three timers, so the numbers we can choose from are 1, 8, 64, 256 and 1024. In fact, with the current project it's best to use the 256 prescaler and have a healthy 80Hz refresh rate:
    
    
    TCCR0B = _BV(CS02) ; // prescaler = 256 (CS0 = 100)
    
    TCCR1B |= _BV(CS12); // prescaler = 256 (CS1 = 100) (keeping WGM bit intact)
    
    TCCR2B = _BV(CS22) | _BV(CS21) ; // prescaler = 256 (CS2 = 110)

(note the '|=' in the TCCR1B line; we already filled one bit of this register and need to keep it.)

Once the timer modes are set up, we'll fill all the Output Compare Registers (the ones analogWrite() is working with) with max values, which in the case of inverted logic mean no light:
    
    
    OCR0A = 255;
    
    OCR0B = 255;
    
    OCR1A = 255;
    
    OCR1B = 255;
    
    OCR2A = 255;
    
    OCR2B = 255;

As the timers were started by the hidden Arduino setup routine, and they were started in different modes, their counters now hold some different values, we need to reset them:
    
    
    TCNT0 = 0;
    
    TCNT1H = 0; // high byte
    
    TCNT1L = 0; // low byte
    
    TCNT2 = 0;

Almost done, let's enable the overflow interrupt that'll trigger our multiplexing routine (Timer Interrupt Mask Register, page 211):
    
    
    TIMSK2 |= _BV(TOIE2);

And start the timers synchronized (General Timer/Counter Control Register, page 144):
    
    
    GTCCR = 0;

That's it! Let's review what we've done here.

Firstly, we configured the three timers to work exactly the same. The timers are different, so different control registers were used, but the end result is everything is identical and synchronized. The timers are in the non-inverted Fast PWM mode, meaning they start at 0 and go up to 255 and then reset. At the start, the outputs of their compare modules (6 in total) are HIGH and turn LOW once the timers pass the value stored in their Output Compare Registers. As we're using P-Channel MOSFETs, that means the LEDs are off at the start and turn on when the threshold is passed, if that happens. Due to prescaler being set at 256, the PWM cycles happen 244.1 times per second, so our 3-row multiplexing device refresh rate is 81.4Hz.

Secondly, we attached an interrupt routine to the overflow of the Timer2. This means that at the moment it resets the microcontroller will try to run some function associated with this interrupt. We are yet to declare this function.

Time to put all this to some use.

## Step 6: ​Software

The sketch consists of three major components:

1\. The Refresh routine. This ISR controls the multiplexing, runs automatically in the background and is triggered by a timer. We will set it up at the beginning of our sketch and then forget about it.

2\. The main code. This is the usual loop() function of our sketch where we calculate the RGB values for our LEDs and do whatever we want to achieve.

3\. The video memory. This is a simple array of bytes that holds the current LED values and serves as a connection between the Refresh and the main code. Instead of analogWriting values directly into the pins, we'll be storing them in this array, and the Refresh routine will be getting them from here. A single array will be enough for the simple projects in this Instructable. For bigger matrices, you'll need video pages to avoid artifacts and palettes to conserve memory, but let's leave these for some future article(s).

### Video Memory

For the time being a single array will suffice:
    
    
    volatile uint8_t colors[6][3] = {
      {255, 255, 255},
      {255, 255, 255},
      {255, 255, 255},
      {255, 255, 255},
      {255, 255, 255},
      {255, 255, 255}};

These values represent our six RGB LEDs. Note that all the variables that are used in interrupt routines must always be declared as volatile.

### Refresh ISR

As we want to make our multiplexing work fast, we will have to deal with the ports and registers directly and discard the handy digitalWrite(), analogWrite() and pinMode().

First, let's define some macros for readability. The first group will be used to set RGB values (columns) for our LEDs:
    
    
    #define setRed0(val) (OCR2B = val)
    #define setRed1(val) (OCR1A = val)
    #define setGreen0(val) (OCR0B = val)
    #define setGreen1(val) (OCR1B = val)
    #define setBlue0(val) (OCR0A = val)
    #define setBlue1(val) (OCR2A = val)

Here we're writing into the timers Output Compare Registers. This is similar to analogWrite(), but ways faster. In our mode of operation these values represent the threshold when the PWM should switch its output. Check 'The Fast PWM Mode' on page 132 of the datasheet for more details.

The second group turns the rows of LEDs on and off:
    
    
    #define Leds3off PORTD |= _BV(7)
    #define Leds1on PORTD &= ~_BV(2)
    #define Leds1off PORTD |= _BV(2)
    #define Leds2on PORTD &= ~_BV(4)
    #define Leds2off PORTD |= _BV(4)
    #define Leds3on PORTD &= ~_BV(7)

This is simpler, as we deal with Port D that controls the outputs. Details obtainable at the [ Arduino web-page](https://www.arduino.cc/en/Reference/PortManipulation). If you're using common anode LEDs and N-Channel MOSFETs, just switch 'on' and 'off' defines here.

Finally, we will need a counter variable that will keep track of the currently active row (again, volatile):
    
    
    volatile uint8_t count;

Now we declare the ISR function:
    
    
    ISR (TIMER2_OVF_vect){

This code tells the compiler that this function must be called each time the Timer2 overflows (OVF_vect). Timer2 also controls one of our PWM engines, so its overflow happens at the end of the PWM cycle. Note that while this call is being implemented the timer continues ticking, so any new PWM values we send inside the ISR will be buffered and used on the next cycle.

The refresh function itself consists of three parts: first, switch the active row, then increment the counter, and then buffer new RGB values for the next cycle:
    
    
    // first, switch off the mosfets, as they will display the values buffered on previous interrupt
    PORTD |= 0b10010100; //set pins 2, 4, 7 HIGH; replace |= with &= ~ for N-Channel
    
    // turn on the right row
      switch (count) {
        case 0: Leds1on; break;
        case 1: Leds2on; break;
        case 2: Leds3on; break;
        default: break;
      }
    
    // increment the counter
      count++;
      count%=3;
    
    // write new values to the buffers
    setRed0 (colors[count][0]);
    setGreen0 (colors[count][1]);
    setBlue0 (colors[count][2]);
    setRed1 (colors[count+3][0]);
    setGreen1 (colors[count+3][1]);
    setBlue1 (colors[count+3][2]);
    
    }

### The Main code

Here you program your device to show whatever you need. To turn on the LEDs we just need to provide values to the 'video memory' array. For example, to get red color on the first LED we can simply do
    
    
    colors[0][0] = 0; // you do remember the inverted logic, right? 

in the loop() and that's it.

I have a couple of functions in the code at GitHub, you can play around with them. Here's the one that turns on LEDs one by one (with fades) to show everything works:
    
    
    void testFor(uint32_t dperiod)
    {
     for (uint8_t y = 0; y<18; y++)
    {
      for (uint8_t k = 255; k>5; k--) 
        {
           colors[y/3][y%3] = k;    
           justWait(dperiod);
        }
      for (uint16_t k = 5; k<256; k++) 
       {
           colors[y/3][y%3] = k; 
           justWait(dperiod);
       }
     }
    }

![](https://cdn.instructables.com/FSD/25LQ/J9YJFT6T/FSD25LQJ9YJFT6T.MEDIUM.jpg)
