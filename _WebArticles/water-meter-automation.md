# Water Meter Automation

_Captured: 2017-11-18 at 14:16 from [www.instructables.com](http://www.instructables.com/id/Water-Meter-Automation/)_

![](https://cdn.instructables.com/FH5/0DFP/J9JG0EAT/FH50DFPJ9JG0EAT.MEDIUM.jpg)

Have you got some water meters at your home? Probably you have. How do you like to check them every month? I do not like this process because my water meters are installed in tiny dark place under the kitchen sink. Usually you should use some kind of inspection light or torch to be able to see the water meter's values. Fortunately, my water meters have the pair of wire allowing to read the data remotely. The principle is very simple: each water meter has the reed switch inside which is short when the last digit goes through 0 to 3 and is "open" otherwise. This kind of water meter can be connected to the simple controller to count the amount of the water that have gone through the tube.

For convenience, it would be nice to see the water meter data through the Internet by using web server or Blynk and receive the e-mail notifications periodically. For this we can use esp8266 IOT controller!

In this guide we will build the two layer automation system: first layer is a battery powered controller that counts the water usage and the second layer is a IOT controller witch receives the messages from layer one controller and interacts with a user via web, Blynk and e-mail.

The project is based on arduino IDE, esp8266 micro controller and atmega328p-pu micro controller.

## Step 1: Layer One. Water Meter Counter.

![](https://cdn.instructables.com/FAS/BOON/J9JG0DW7/FASBOONJ9JG0DW7.MEDIUM.jpg)

![](https://cdn.instructables.com/FHD/L4K6/J9OWGYFT/FHDL4K6J9OWGYFT.MEDIUM.jpg)

The esp8266 controller is not very power efficient and cannot run on the batteries for long time. And we would like to use it as web server any time, so it must be powered by the external power supply. It is not good idea to connect the water meter directly to the esp8266 controller because usually the water meters are installed in the dark, tiny space without any access to the external power outlet and WiFi access.

The water meter controller can be placed near the water meters, for example under the kitchen sink, and powered by two AA batteries. This controller just counts the water passed through the water meter and periodically sends this data via the radio channel to the central IOT module (esp8266). The controller supports two water meters for hot and cold water. The data is sent by means of the packet that contain the following fields:

  * Uniq ID of the controller (hard coded in th the controller sketch). 
  * Counter data for the hot water. 
  * Counter data for the cold water. 
  * Internal battery voltage in mV. 

The controller is built on atmega328p-pu chip powered by two AA batteries and wireless transmitter si4432. You should program the atmega328p-pu micro controller to run at 1 MHZ and setup the minimum startup voltage 1.8 volts. There are a lot of [instructables](https://forum.mysensors.org/topic/3018/tutorial-how-to-burn-1mhz-8mhz-bootloader-using-arduino-ide-1-6-5-r5) in the Internet about how to program fuses of this micro controller.

As to the wireless transmitter module, I have started with nrf2401 because it is widely used in the home automation projects. Unfortunately, in my concrete house the signal from this module was too weak to work properly. So, another, long-distance controller was selected for this project, si4432. This controller proves excellent signal quality and rich set of features.Surely, I can recommend it.

There is some hint that simplifies soldering of this radio module. The si4432 module have very small connector (1mm step). To simplify soldering or prototyping projects with this module on the breadboard, you can buy sop16/ssop16 adapter (see the photo) and cut if half by the metal-cut scissors. Actually we need just 8 pins to connect the module to the arduino controller.

## Step 2: Layer 2. the IOT Controller.

![](https://cdn.instructables.com/FEX/HH6G/J9JG0DWM/FEXHH6GJ9JG0DWM.MEDIUM.jpg)

![](https://cdn.instructables.com/FBA/MB7R/J9JG0DW9/FBAMB7RJ9JG0DW9.SMALL.jpg)

![](https://cdn.instructables.com/FWX/RFQ0/J9JG0DWZ/FWXRFQ0J9JG0DWZ.SMALL.jpg)

![](https://cdn.instructables.com/FI8/4DTJ/J9OWGZN3/FI84DTJJ9OWGZN3.SMALL.jpg)

This module used to provide user friendly interface to all water meter data installed in your home. It receives the signal from one or several water meter controllers described in the previous step and presents this information to the user by means of set of interfaces: through internal WEB server, via Blynk or via e-mail notification. As you can see on the photo, this module is relatively small and can be placed inside old power adapter case. Then you can just plug this 'adapter' to the outlet.

The main component of this module is esp8266 micro controller. You can choose any available variant with at least 1MB of flash memory: esp-07, esp-12e, esp-12f, nodeMCU-0.9 or wemos. In the photo you can see the esp-07 variant. You should configure this module to use SPIFFS file system with space at least of 512kB. If you use exp12-e module or so, use 3 MB SPIFFS. The controller uses this space to store the configuration information and data log of the water meters.

If you use stand alone variant like i did, you probably should buy the adapter like shown in the photo. Note that there are three resistors already installed on the adapter and you should duplicate them. To communicate the controller you can use USB-to-Serial adapter? f like cp2102.

The radio module, si4432, is connected to the esp controller using SPI interface (see the schematics later on).

The module has one external led that used to show the current ruining status of the module.

## Step 3: Blynk Setup.

![](https://cdn.instructables.com/FPE/L1N4/J9OWH9K8/FPEL1N4J9OWH9K8.SMALL.jpg)

To publish water meter data in the Blynk cloud service you should create your account on blynk site and create new authentication key for this project. This key should be entered into the IOT module through the WEB setup form.

Then you should create the Blynk items for your project as described bellow. All the elements are 'connected' to the virtual pins of the esp micro controller. And all of them, expect the first one, are just a text fields.

  * V0: The menu item and name 'select the controller' or so. This element allows you to chose the water meter controller from the list of the available controllers in your home. 
  * V1: The text item and name 'Serial number'. Here you will see the serial number of the water meter of cold water. 
  * V2: The text item and name 'WM data'. Is used to display current data of cold water counter. 
  * V3: The text item and name 'next inspection' Displays the date of the next inspection date of the water meter. Usually the water meter should be checked every 4-6 years. 
  * V4: The text item and name 'Serial number'. Here you will see the serial number of the water meter of hot water. 
  * V5: The text item and name 'WM data'. Is used to display current data of hot water counter. 
  * V3: The text item and name 'next inspection' Displays the date of the next inspection date of the water meter. 

The list of the menu element will be updated automatically from the main module.

## Step 4: The IOT Controller Modes.

To achieve a stable production of the main module in case of Blynk or WiFi network failure, several working modes implemented:

  * Main mode: The controller is connected to WiFi and to the Blynk cloud service; 
  * The module is trying to connect to WiFi network; 
  * The module successfully connected to WiFi and is trying to connect to Blynk cloud; 
  * The module is running Access Point mode for initial setup.

The led indicates the current running mode of the module:

  * Blinks every 5 seconds in main mode; 
  * Blinks every 10 second while trying to connect to the WiFi; 
  * Double blinks every 10 seconds while trying to connect to the Blynk;
  * Blinks twice every second in Access point mode;

When the module starts, it tries to load the configuration file from SPIFFS, if the configuration does not exist or WiFi ssid is not defined, the module switches to the Access Point mode and waits for the main setup parameters: wifi ssid, password and so on. In this mode you can connect to the module using WiFi ssid 'esp8266-wm' and typing '192.168.4.1' in the address field of your browser. The main setup page will be displayed. After all the parameters would be entered into the setup page, you should power-cycle the module.

If the module failed to connect to WiFi in 5 minutes after start, it again switched to the Access Point mode for initial setup. If the module have successfully connected to the WiFi it would never goes to the Access Point mode even after long period of WiFi inactivity. The module would be trying to reconnect to the WiFi network forever.

In the main running mode the module is running the WEB server showing the water meter data, updates the data in the Blynk cloud service and periodically sends e-mail alerts to the configured e-mail address. In case of Blynk connection failure, it tries to reconnect to Blynk cloud. The WEB and e-mail services are continue to work. In case of WiFi connection failure, the module tries to restore the network connection.

## Step 5: The WEB Interface: Setup

![](https://cdn.instructables.com/FXW/Q17X/J9STGHG8/FXWQ17XJ9STGHG8.MEDIUM.jpg)

The setup page is the first one you should visit. This page is available as a root document in the Access Point mode and can be examined in the main WEB mode through the upper menu by selecting 'setup' item**_._**

In the setup page you can enter the flowing parameters:

  * wifi ssid 
  * wifi password 
  * blynk auth key 
  * ntp server name 
  * Greenwich time difference in minutes

ntp server is used to determine the current time and date. The module does not have internal clock. When the data received from the Water Meter controller (layer 1) it accomplished with the time stamp. This allows to check the communication with the layer1 controller. Also the time stamp is written to the log data file.

## Step 6: The WEB Interface: Main Screen

![](https://cdn.instructables.com/FMY/94OI/J9STGHFE/FMY94OIJ9STGHFE.MEDIUM.jpg)

The main scree shows the water meter data. It formatted into the table which has the following columns:

  * The water meter controller location. You can connect to the main module up to 4 controllers without the code modification; 
  * The serial number of the water meter; 
  * The current data of the water meter; 
  * The next inspection date of the water meter; 
  * The voltage of the Water meter controller battery;

The layer2 module receives the message from the layer1 module(s) and shows the information on the main page. Each layer1 controller has uniq ID witch is displayed on the controller setup page. You can setup the name (or location) of each controller. This name could be convenient one like a 'kitchen' or 'bath room' and the layer2 controller saves it into the SPIFFS file system. You can change the controller name as you like. If the layer2 module 'does not know' the name of the layer1 controller, the controller ID would be displayed in the table.

You should define configuration data for each layer1 controller by 'clicking' on the controller ID or its name in the table or use corresponding menu item.

## Step 7: The WEB Interface: Layer1 Controller Setup

![](https://cdn.instructables.com/F3P/BCZM/J9STGHH4/F3PBCZMJ9STGHH4.MEDIUM.jpg)

This page allows you to define the configuration of the water meters in the layer1 controller:

  * The controller name or location 
  * Water meter serial numbers (both hot and cold water) 
  * Water meter next inspection date 
  * Water meter current data
  * The fraction size

The controller name is used for your convenience to remember the layer1 controller in case you have several layer1 controllers. The name can be up to 32 symbols.

Each water meter has uniq serial number which must be written in the form. This number will be shown in the main page, Blynk application and e-mail notifications.

Next inspection date is useful to send warning and alert e-mail messages to inform you about the date when the water meter should be inspected.

The controller counters the amount of water through the water meter, it could not know the current value on the water meter. You must specify the actual data of each water meter only once. The layer2 controller saves in the configuration the starting data value of each water meter then it calculates the actual water meter data accordingly.

The fraction size determines how many decimal digits are meaningful after the cubic meters. The water meter of the first picture has three decimal digits after integer part. But the controller cannot count the last digit. Remember, the switch is short whel the las digit is going through 0 to 3. In this example, the fraction size is 2.

## Step 8: The WEB Interface: E-mail Notofications.

![](https://cdn.instructables.com/FSF/1I9U/J9STGHFD/FSF1I9UJ9STGHFD.MEDIUM.jpg)

The layer2 controller supports sending e-mail notifications. You have to configure the relay server that will be used to send e-mail messages, source and destination e-mail addresses. Also, you can configure the period of the regular e-mail notification of current data of the water meter. The parameter 'send at' is validated depending on the period:

  * the hour of the daily notification 
  * the weekday for every week notification 
  * the day of month for every month notification

This version of the software support open relay server configuration only.

## Step 9: The Component List.

![](https://cdn.instructables.com/F9Q/9QQO/J9OWHGB0/F9Q9QQOJ9OWHGB0.MEDIUM.jpg)

![](https://cdn.instructables.com/FH3/6CNV/J9OWHGB1/FH36CNVJ9OWHGB1.MEDIUM.jpg)

Here is the hardware component list to build the project.

**layer1 controller**

  * atmega328p-pu microcontroller 
  * si4432 radio module 
  * SOP16/SSOP16 to DIP16 converter board (used for two modules) 
  * resistor 220 Ohm 
  * resistor 10 kOhm 
  * resistor 1 MOhm - 2 pcs 
  * ceramic capaticor 100n - 4 pcs 
  * capacitor 10 uF 
  * AA battery case 
  * pin headers

**layer2 controller**

  * esp8266-07 
  * controller board 
  * si4432 radio module 
  * SOP16/SSOP16 to DIP16 converter board 
  * resistor 220 Ohm 
  * resistor 1 kOhm 
  * resistor 10 kOhm 
  * ceramic capatitor 100n - 2 pcs 
  * capaitor 1000 uF 
  * capacitor 10 uF 
  * general purpose bipolar npn transistor, 2n2222 or analog 
  * ams1117-3.3 voltage regulator
  * AC-DC 5v power supply

The source of both modules available in the git hub [repository](https://github.com/sfrwmaker/WaterMeter).

## Step 10: Conclusion.

The project describes the automation system that simplifies procedure of home water meter accounting. The water meter data is available through the web interface and blynk. This allow you to monitor your water meters remotely. Also, the e-mail notifications are implemented about current status of the water meter and about the time of the next inspection.

The project uses the brilliant software library written for esp8266 micro controller that supports WiFi connectivity and web server requests. I believe that esp8266 and arduino IDE integration provides the great platform for many interesting projects.
