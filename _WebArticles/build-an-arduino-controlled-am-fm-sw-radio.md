# Build an Arduino-Controlled AM/FM/SW Radio

_Captured: 2017-12-31 at 05:21 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/projects/build-an-arduino-controlled-am-fm-sw-radio/)_

Combine the Si4844-A10 analog-tuned radio receiver with an Arduino to make a full-featured multiband radio.

The idea of a single chip radio is intriguing. The prospect is especially interesting to me because, frankly, I envy the analog skills I associate with building a radio receiver. When I browsed the circuit literature in the area, I came across the Silicon Labs collection. One of their chips, the Si4844-A10 caught my attention. This receiver has AM/FM/SW capability with all the bells and whistles and it is designed to work with a microprocessor. Best of all, the support components required are mainly associated with the microprocessor display and control functions with only a small amount of antenna support needed. I couldn't resist taking the plunge.

### Reference Documents

Familiarity with the chip's data and application information is strongly encouraged. The three documents linked below are highly recommended for understanding and building the project:

### The Basic Circuit

![Radio receiver schematic](https://www.allaboutcircuits.com/uploads/articles/AMFMSW4-revised-s.jpg)

> _Figure 1. The radio receiver schematic (Full sized schematic here)_

Figure 1 presents the basic circuit for the receiver and the schematic is adapted from the Silicon Labs Si4844 datasheet and application notes. I used a reclaimed ferrite loop from a discarded portable AM/FM radio as the required AM antenna. I think that a higher quality and larger ferrite would be an improvement. Q1 is the amplifier for the SW/AM and I also used a reclaimed telescopic antenna in that section. It is notable that the design guide, linked above, gives several alternatives and different approaches for the antenna components.

The variable resistor (VR1) is a critical component since this will be used to adjust the receiver frequency - the tuning knob. It is recommended that a good quality linear potentiometer be used. For the audio out, I chose to use a set of "economical" amplified speakers that I had from a retired desktop PC. Certainly, a simple stereo amplifier could also be used. Everything on the board is 3.3v and all GNDs are connected.

The most difficult part of the construction is probably working with the chip's SSOP-24 form factor. If you don't have the experience and equipment to use SMT ICs, the use of a carrier board may be the easiest way to accomplish the task. I had an SSOP-28 carrier board and with a fine point soldering tip and a lot of patience (and some solder braid to undo bridges); I was able to mount the chip so that it could be accessed as a DIL package. The other potentially difficult components to work with are the couple of surface mount ferrite beads and capacitors. These components can also be hand soldered onto a carrier board and treated like a DIL package.

![SMT components on carrier board](https://www.allaboutcircuits.com/uploads/articles/Both_chips_800_x_600.jpg)

> _SMT components soldered onto carrier boards_

Parts list for the main circuit:

Part Description

B1
ferrite bead 2.5 kOhm (100 mHz)

C1,C2,C5
4.7 uf non polarized capacitor

C3,C4
22 pf non polarized capacitor

C6,C7,C9
.1 uf non polarized capacitor

C8
47 uf non polarized capacitor

C10,C11
.47 uf non polarized capacitor

C12,C14
33 nf non polarized capacitor

C13
33 pf non polarized capacitor

C15
10 pf non polarized capacitor

IC1
Si4844-A10 radio receiver

Q1
SS9018 NPN transistor

R1, R2
2.2K

R3
1K

R4,R7
100K

R5
10

R6
120K

R8
100

L1
270 nH Inductor

VR1
100K linear potentiometer

Y1
32.768 kHz crystal

ANT1
ferrite antenna

ANT2
telescopic/whip antenna

### Connecting an Arduino

The other piece that needs to be considered before powering up the circuit for testing is the Arduino interface. For this component, I chose to use the [Arduino Pro Mini, 3v/8Mhz ](http://www.sparkfun.com/products/11114)board. This tiny Arduino is entirely 3.3v and is compatible with the Si4448-A10 and that is a chief advantage. The small size of the board is an additional convenience. Connection to the Si4844-A10 is through four lines as described below:

Arduino to Si4844-A10 connections:

Arduino (3.3v) Si4844-A10

A5/SCL
SCLK

A4/SDA
SDIO

D2
INT

D12
RST

Additionally, a standard USB/Serial interface is used to connect the Arduino to a PC for programming. The exact connections will depend a bit upon the serial board that you use, but will include the usual TX, RX and GND connections. In this manner, you can essentially program and test the Si4844-A10 "in circuit", which facilitates development and experimentation. When completed, however, the connection can be eliminated for a stand-alone multiband radio. Powering both the radio board and the Arduino must be with an external 3.3v regulated power supply. Do not try to power them using the USB/serial board, even if it has a 3.3v output pin-- these cannot be depended upon to have the capability to provide the necessary current to drive both the Arduino and the Si4844-A10.

### Testing the Basic Circuit

Once you have the circuit bread-boarded, the Arduino connected, and the amplified speakers attached, you can run a test program that is included in this article (Si4844_Quick_Test.ino). The program performs a simple test of the circuit that will power up the device, set the band to FM, and provide the chip's version information. If all goes well, you should be able to tune the radio by turning VR1 and you will see the frequency dynamically displayed on the screen - and, of course, hear the radio output.

![Screen capture](https://www.allaboutcircuits.com/uploads/articles/SIss1.jpg)

> _Screen capture of the test program_

Once the basic circuit and Arduino connections are functional, construction of the full-featured radio can proceed.

### Arduino Programming

The Si radio chip in this project is an I2C slave device having a fixed address of 0x11, with the Arduino as the master device. The I2C communication speed of the chip, however, is relatively slow with 50 kHz as the maximum supported speed. Moreover, during a portion of the power up procedure, the speed must not exceed 10 kHz. To meet these requirements, we have to explicitly set the Arduino I2C speed, which is normally too fast for the Si4844-A10. Fortunately, aided by the wealth of documentation on Arduino I2C functions, we can easily accomplish the necessary changes.

Basically, I2C speed, for our purposes, is determined by two dedicated variables in the Arduino software. Those dedicated variables are TWBR and TWSR. Bit 0 and 1 of TWSR control a prescaler that works with the value of TWBR to set the I2C speed. The speed (clock frequency) of the I2C transmissions is calculated by: Frequency = CPU Clock frequency / (16 + (2 * (TWBR) * (Prescaler)). The Arduino Pro mini 3.3v runs at 8 mHz. To set I2C speed to 10 kHz, we use a TWBR value of 98 and we set the prescaler to 4 (by setting only bit 0 of TWSR). Thus, 8,000,000 / (16+(2*98 [TWBR value]*4 [prescaler]))=10,000 or 10 kHz. To set the I2C speed to 50 kHz, we use a TWBR value of 18 and we set the prescaler to 4 (by setting only bit 0 of TWSR). Thus, 8,000,000 / (16+(2*18 [TWBR value]*4 [prescaler]))=50,000 or 50 kHz.

See [Nick Gammon's excellent repository of Arduino I2C information](http://www.gammon.com.au/i2c) and the[ Arduino Library documentation ](http://playground.arduino.cc/Main/WireLibraryDetailedReference)for more information on this process. The bottom line, however, is that we can accomplish these I2C speed changes in just a couple of lines of code and you can see those in the test program.

Another important programming consideration is that we need to use an external interrupt service routine in our code. You can read some background on the use of external interrupts [here](https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/). We use INT0 on the Arduino and, basically, when that pin is set high by the Si4844-A10, the program will execute a simple routine that has been "attached" to the interrupt. All the routine will do is set a flag variable that can be examined and changed in other parts of the code. The Si4844-A10 will issue interrupts (i.e., bring the INT pin high) under certain conditions, most notably when the tuning potentiometer has been changed. Therefore, the Si4844-A10 tells the Arduino that you have moved the tuning knob and that the frequency display should be updated.

### Si4844-A10 Programming

Essentially, the Arduino sends the radio chip commands over the I2C bus and the radio chip subsequently replies to the commands by performing the requested action and returning status information. The Si chip can operate in several modes and some make it possible to configure some very detailed radio bands and properties. In this project, we are using the Si4844-A10 chip in a mode that accepts pre-defined or default radio bands with default properties. This mode was chosen because it easily accommodates a great deal of basic functionality while still offering a degree of customization.

Rather than simply setting an AM/FM/SW "register", the radio chip can be set to one of 41 different frequency bands. Bands 0-19 are FM, 87-109 mHz; bands 20-24 are AM, 504-1750 kHz; bands 25-40 are SW, 5.6-22.0 mHz. The bands, however, do not have simple equal-interval spacing, which might make tuning cumbersome. Instead, the frequency range of many of the bands are the same or differ only slightly, but with differing properties, such as de-emphasis (FM) or channel space (AM), stereo separation (FM) and RSSI thresholds. Consultation with the referenced datasheets and application notes is necessary to completely understand this scheme and you will see some clear tables for the bands as well as all of the modes, programming commands, and the status and reply formats.

In this project, the included software will enable access to all of the default bands as well as controlling basic properties including mode changes (AM/FM/SW), volume, tone, and mute.

### Add a Keypad

To control the radio, we need an input device. A simple membrane keyboard as pictured is sufficient for our purposes. These have been around for a while and are [easy to interface ](https://www.allaboutcircuits.com/projects/use-a-keypad-with-your-arduino/)with an Arduino. While I have illustrated the row and column orientation for the one that I used, you should verify that yours is the same.

![Membrane Keypad](https://www.allaboutcircuits.com/uploads/articles/Keyboard_arrows_s_trimmed.jpg)

> _Simple membrane keypad_

Keypad to Arduino connections:

Keypad Arduino

Row 1
D8

Row 2
D9

Row 3
D10

Row 4
D11

Col 1
D13

Col 2
D14

Col 3
D15

For keypad software, I used the [library](http://playground.arduino.cc/Code/Keypad) from Mark Stanley and Alexander Brevig which is released under the [GNU General Public License](https://en.wikipedia.org/wiki/GNU_General_Public_License). For the project, we will map functions to the keys as illustrated below.

![Keypad mapping](https://www.allaboutcircuits.com/uploads/articles/KeyMap_trimmed.jpg)

> _Keypad mapping for the radio functions_

Keypad Function Definitions:

  * AM : Switch to AM mode, band 22
  * FM : Switch to FM mode, band 8
  * SW : Switch to SW mode, band 31

Note that the default bands under the mode changes are configured in software and are easy to modify. Additionally, the current volume and tone values will be carried over in the new mode.

  * Vol+ / Vol- : Increase or decrease the volume by one step. There are 64 levels of volume. Because of the use of amplified speakers in the project, these are not so essential but are still nice to have.
  * Band+/Band- : Increase or decrease the band by one step, but within the available bands in the current mode.
  * B/T+ / B/T- : Increase or decrease the tone by one step. I admit that I am being somewhat liberal in my use of the term "tone". For the FM mode, this will increase or decrease the bass / treble level from 0 (max bass) to 8 (max treble). For the AM/SW bands, this will set a channel filter from 1-7. The filters are at 1.0 kHz, 1.8 kHz, 2.0 kHz, 2.5 kHz, 2.83 kHz, 4.0 kHz, and 6.0 kHz, respectively. Note also that for simplicity and programming convenience (i.e., laziness), levels of 0/1 and 7/8 can be made in AM/SW mode, but do not differ.
  * Mute: Toggles audio output on and off.

### Add a Display

With the input device set up, we need to be able to display the settings of the radio. I can think of no better screen to use with this project than one from the old Nokia 5110/3310 cell phones. I had a well-used one of these around (see pictured) and their old-school charm seems particularly appropriate.

![Nolia Display](https://www.allaboutcircuits.com/uploads/articles/Screen_both_trimmed.jpg)

> _Nokia display_

There are two important points to consider when interfacing this display. First, there are several varieties of these displays available and they can have different pinouts. You should verify the pin connections on yours to make certain that it is, in fact, a 3.3v device and that it is attached to the Arduino Pro Mini correctly. Second, because all of the I/O on the Arduino used in this project is 3.3v, I did not have to use the dropping resistors that you usually see when these screens are used with 5v flavors of Arduinos, like the UNO.

Display Pin / Function Arduino / Circuit

1-RST
D3

2-CE
D4

3-DC
D5

4-DIN
D6

5-CLK
D7

6-VCC
Vcc (3.3v)

7-LIGHT
GND

8-GND
GND

For software, I chose to use the [LCD5110_Basic library](http://www.rinkydinkelectronics.com/library.php?id=44) available under the [CreativeCommons license](http://www.rinkydinkelectronics.com/resource/licenses/CC_BY-NC-SA-3.0-Summary.pdf). This library is mature, very easy to use, and fast.

Pictured below is the populated radio display in use:

![Radio display ](https://www.allaboutcircuits.com/uploads/articles/Screen_full_on_800_x_600.jpg)

> _Radio display in use_

Starting from the top left, we display:

Row 1- Mode (AM/FM/SW) and the band number

Row 2- Band frequency range

Row 3- Volume and base/treble levels

Row 4- Current frequency (mHz or kHz)

Row 5- Stereo indicator (FM only) and mute (if on)

Of course, this information is constantly updated to represent changes from tuning or keyboard input.

### The Completed Radio

Depicted below is the assembled project on a breadboard - perhaps not as neat as it could be (ok, it's a mess), but completely functional. Certainly the performance can only improve by a more permanent layout.

![Project Breadboard](https://www.allaboutcircuits.com/uploads/articles/breadboard_2_800_x_600.jpg)

> _The completed radio on a breadboard_

The software to run the radio is available for download below. It is liberally commented and is, hopefully, both easy to understand and easy to modify, if desired. The main loop in the software is straightforward. It 1) checks and displays any change in the tuner frequency and 2) checks if a keypress has been made and, if so, executes the appropriate command. The rest of the program consists of all of the supporting functions.

I am very impressed by the reception that the circuit is able to achieve right on the breadboard. FM is very good. AM is good and I am able to get quite a few SW broadcasts. Nevertheless, reception can, undoubtedly, be increased through the use of specialized antennas.

### Closing Thoughts

This has been a challenging and enjoyable project. I am definitely impressed by the Si4844-A10 chip. There is a great deal of capability packed into a single chip and that always amazes me. I feel like I have only touched on the possibilities-- but, hopefully, this project can serve as a foundation if you are interested in experimenting.

### Code

Download the software for the project here:
