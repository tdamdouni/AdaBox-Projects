# Weather Clock

_Captured: 2017-11-17 at 09:28 from [www.instructables.com](http://www.instructables.com/id/Weather-Clock-1/)_

![](https://cdn.instructables.com/FWJ/IBV8/J9OWE4PR/FWJIBV8J9OWE4PR.MEDIUM.jpg)

Great looking desktop clock with date & weather display.

## Step 1: Download and Install Software for the RaspberryPI

![](https://cdn.instructables.com/FJC/9JUN/J9OWE4PT/FJC9JUNJ9OWE4PT.MEDIUM.jpg)

**Download "RASPBIAN JESSIE LITE" [ https://www.raspberrypi.org/downloads/raspbian/](https://www.raspberrypi.org/downloads/raspbian/)**

**Create your new hard disk for DashboardPI**

Insert the microSD to your computer via USB adapter and create the disk image using the dd command

Locate your inserted microSD card via the df -h command, unmount it and create the disk image with the disk copy dd command

$ df -h /dev/sdb1 7.4G 32K 7.4G 1% /media/XXX/1234-5678

$ umount /dev/sdb1

Caution: be sure the command is completely accurate, you can damage other disks with this command

if=location of RASPBIAN JESSIE LITE image file of=location of your microSD card

$ sudo dd bs=4M if=/path/to/raspbian-jessie-lite.img of=/dev/sdb (note: in this case, it's /dev/sdb, /dev/sdb1 was an existing factory partition on the microSD)

**Setting up your RaspberriPi**

Insert your new microSD card to the raspberrypi and power it on with a monitor connected to the HDMI port

Login

user: pi pass: raspberry

Change your account password for security

sudo passwd pi

Enable RaspberriPi Advanced Options

sudo raspi-config

Choose: 1 Expand File System

9 Advanced Options

A2 Hostname change it to "EnvironmentClock"

A4 SSH Enable SSH Server

A7 I2C Enable i2c interface

**Enable the English/US Keyboard**

sudo nano /etc/default/keyboard Change the following line: XKBLAYOUT="us"

**Reboot PI for Keyboard layout changes / file system resizing to take effect**

$ sudo shutdown -r now

**Auto-Connect to your WiFi**

sudo nano /etc/wpa_supplicant/wpa_supplicant.conf Add the following lines to have your raspberrypi automatically connect to your home WiFi (if your wireless network is named "linksys" for example, in the following example)

network={ ssid="linksys" psk="WIRELESS PASSWORD HERE" }

**Reboot PI to connect to WiFi network**

$ sudo shutdown -r now

Now that your PI is finally on the local network, you can login remotely to it via SSH. But first you need to get the IP address it currently has.

$ ifconfig Look for "inet addr: 192.168.XXX.XXX" in the following command's output for your PI's IP Address

**Go to another machine and login to your raspberrypi via ssh**

$ ssh pi@192.168.XXX.XXX

**Start Installing required packages**

$ sudo apt-get update

$ sudo apt-get upgrade

$ sudo apt-get install vim git python-smbus i2c-tools python-imaging python-smbus build-essential python-dev rpi.gpio python3 python3-pip libi2c-dev

**Update local timezone settings**

$ sudo dpkg-reconfigure tzdata select your timezone using the interface

**Setup the simple directory l command [optional]**

$ vi ~/.bashrc

add the following line:

$ alias l='ls -lh'

$ source ~/.bashrc

**Fix VIM default syntax highlighting [optional]**

$ sudo vi /etc/vim/vimrc

uncomment the following line:

syntax on

**Clone Clock repository**

$ cd ~

$ git clone [ https://github.com/khinds10/EnvironmentClock.git   
  
](https://github.com/khinds10/EnvironmentClock.git)**Install i2c Backpack Python Drivers**

$ cd ~

$ git clone [ https://github.com/adafruit/Adafruit_Python_LED_B...](https://github.com/adafruit/Adafruit_Python_LED_Backpack)

$ cd Adafruit_Python_LED_Backpack/

$ sudo python setup.py install

**DHT11 Install**

$ cd ~

$ git clone [ https://github.com/adafruit/Adafruit_Python_DHT.g...](https://github.com/adafruit/Adafruit_Python_DHT.git)

$ cd Adafruit_Python_DHT/

$ sudo python setup.py install

$ sudo python ez_setup.py

$ cd examples/

$ vi simpletest.py Change the following line:

sensor = Adafruit_DHT.DHT11 Comment the line out

pin = 'P8_11' Uncomment the line and change the pin number to 16

pin = 16 Run the test

python simpletest.py

You should see a metric reading of Temp and Humidity displayed on the command line.

## Step 2: Supplies Needed: 1.2 Inch LED Display

![](https://cdn.instructables.com/FL5/F4N9/J9OWE4MK/FL5F4N9J9OWE4MK.MEDIUM.jpg)

## Step 3: Supplies Needed: DHT11 Humidistat 

![](https://cdn.instructables.com/FL4/Y9J6/J9OWE4N1/FL4Y9J6J9OWE4N1.MEDIUM.jpg)

## Step 4: Supplies Needed:​ 2.6" Digole Display 

![](https://cdn.instructables.com/FFE/YMAQ/J9OWE4ND/FFEYMAQJ9OWE4ND.MEDIUM.jpg)

## Step 6: Build and Wire the Display

![](https://cdn.instructables.com/FWX/VN37/J9OWE4NQ/FWXVN37J9OWE4NQ.MEDIUM.jpg)

## Step 7: Print the Project Enclosure

![](https://cdn.instructables.com/FHQ/WZGY/J9OWE4OL/FHQWZGYJ9OWE4OL.MEDIUM.jpg)

Using a 3D printer print the enclosure files included in the 'enclosure/' folder. .x3g files are MakerBot compatible. You can also use the .stl and .blend (Blender Program) files to edit and create your own improvements to the design.

Using 4 screws drill and attach the front panel (with the 2 holes) to the 4 sided body. Then fit the displays in each of the holes.

## Step 8: Attach the 7 Segment and Digole Display Using Hot Glue Gun to Hold Them in Place.

![](https://cdn.instructables.com/F87/9RWC/J9OWE4MX/F879RWCJ9OWE4MX.MEDIUM.jpg)

## Step 9: ​Prepare the Wires for Connection

![](https://cdn.instructables.com/FH9/RIWI/J9OWE4QZ/FH9RIWIJ9OWE4QZ.MEDIUM.jpg)

I use standard jumping wires and a wire cutter to strip the wire bare in the middle of the wires so I can have a bunch connected together glued with a hot glue gun. (In the image below is my grouped together 5V / GND / SCA / and SCL wires.)

## Step 10: 

![](https://cdn.instructables.com/F5W/FZ55/J9OWE4TG/F5WFZ55J9OWE4TG.MEDIUM.jpg)

Begin wiring the unit using the wiring diagram below as a guide.

**The 7 Segment display **  
D -> SDA   
C -> SCL   
\+ -> 5v   
GND -> GND   
IO -> 5v

**Digole Display **  
GND -> GND   
DATA -> SDA   
CLK -> SCL   
VCC -> 3V

**DHT11 Humidistat **  
VCC -> 5V   
GND -> GND   
DATA -> GPIO 16 / PIN 36

## Step 11: Connect All the Parts Inside the Printed Case

![](https://cdn.instructables.com/F39/FTIK/J9OWE4S6/F39FTIKJ9OWE4S6.MEDIUM.jpg)

## Step 12: Connect All the Parts Inside the Printed Case

![](https://cdn.instructables.com/FUM/3G9D/J9OWE4MW/FUM3G9DJ9OWE4MW.MEDIUM.jpg)

## Step 13: Finish the Construction

![](https://cdn.instructables.com/FDR/TZ6R/J9OWE4N0/FDRTZ6RJ9OWE4N0.MEDIUM.jpg)

Glue the humidistat to the back panel, and run a USB cable through the other back panel hole to power the unit. Attach the back with only 2 screws in case you need to disassemble for repair.

## Step 14: Setup Startup Scripts

$ crontab -e

Add the following lines:

@reboot nohup python /home/pi/EnvironmentClock/clock.py >/dev/null 2>&1

@reboot nohup python /home/pi/EnvironmentClock/display.py >/dev/null 2>&1

Verify the display starts working on reboot

$ sudo reboot

**OPTIONAL: Temp Logger to API script each 10 minutes**

$ crontab -e Add the following lines:

*/10 * * * * python /home/pi/EnvironmentClock/temp-check.py

**OPTIONAL: Creating your own weather images to render on the display**

Upload your own 128x128 file to the following URL:

Choose your image file to upload, add what size you want it to be on the screen (Width/Height)

Select "256 Color for Color OLED/LCD(1 byte/pixel)" in the "Used for" dropdown

Obtain the hex output.

Add the hex output to a display/build/ header (.h) file, use the other ones as guides for syntax.

Include the new file in the digole.c file #include "myimage.h

Include a new command line hook to your image file in the. Note: the command below is saying draw your image at position 10 pixels over 10 pixels down. You can change it to different X,Y coordinates, you can also change the values 128,128 to whatever size your new image actually is.

} else if (strcmp(digoleCommand, "myimage") == 0) { drawBitmap256(10, 10, 128, 128, &myimageVariableHere,0); // myimageVariableHere is defined in your (.h) file }

Now rebuild (ignore the errors) below to have your new image render with the following command.

$ ./digole myimage

**Re-Building [Included] Digole Display Driver for your optional changes**

$ cd display/build $ gcc digole.c $ mv a.out ../../digole $ chmod +x ../../digole

## Step 15: Finished! (alternate White Construction)

![](https://cdn.instructables.com/FJ2/9BD1/J9OWDHLW/FJ29BD1J9OWDHLW.MEDIUM.jpg)
