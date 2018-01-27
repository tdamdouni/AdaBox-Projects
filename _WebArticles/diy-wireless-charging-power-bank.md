# DIY Wireless Charging Power Bank

_Captured: 2017-12-13 at 10:03 from [www.instructables.com](http://www.instructables.com/id/DIY-Wireless-Charging-Power-Bank/)_

![](https://cdn.instructables.com/FN5/GYXW/JAWTWRYK/FN5GYXWJAWTWRYK.MEDIUM.jpg)

![](https://cdn.instructables.com/F2V/GXW7/JAWTWSMK/F2VGXW7JAWTWSMK.MEDIUM.jpg)

![](https://cdn.instructables.com/FLV/LGU2/JAWTWSL2/FLVLGU2JAWTWSL2.SMALL.jpg)

![](https://cdn.instructables.com/FIA/E3OM/JAWTWSIY/FIAE3OMJAWTWSIY.SMALL.jpg)

![](https://cdn.instructables.com/FAH/1488/JAWTWRXI/FAH1488JAWTWRXI.SMALL.jpg)

![](https://cdn.instructables.com/FTN/ZU02/JAWTWSEI/FTNZU02JAWTWSEI.SMALL.jpg)

As Phones get smarter and come packed with a heavier processor, it gives us a great performance, but the only down side to this is the battery life. While in intensive use the Phones may provide only a few hours of battery life, fortunately there is a wide range of power banks which are capable of charging your phone three to five times.

But when it comes to wireless charging, there are only a few power banks that offer that and are relatively quite expensive, so in this instructable I'm going to show you how to build your own **Wireless charging power bank**, that can charge your phone and other wearable devices.

You can also video a video on how to build this project.

## Step 1: Tools and Components

![](https://cdn.instructables.com/FT1/L79H/JAYJ62X6/FT1L79HJAYJ62X6.MEDIUM.jpg)

![](https://cdn.instructables.com/FTA/A45F/JAYJ635W/FTAA45FJAYJ635W.SMALL.jpg)

![](https://cdn.instructables.com/FAD/8H66/JAWTWRE1/FAD8H66JAWTWRE1.SMALL.jpg)

![](https://cdn.instructables.com/FBE/7WAZ/JAWTWRDW/FBE7WAZJAWTWRDW.SMALL.jpg)

Here is a list of the components and tools required, the list is simple and all you need is -

**Tools Required **

  * Soldering Iron 
  * Multimeter (Optional) 
  * 3D Printer (Optional)

## Step 2: Li-ion Batteries 

![](https://cdn.instructables.com/F6T/T41S/JAYJ62EK/F6TT41SJAYJ62EK.MEDIUM.jpg)

![](https://cdn.instructables.com/FF4/PWM3/JAYJ62PS/FF4PWM3JAYJ62PS.SMALL.jpg)

![](https://cdn.instructables.com/FM8/FRP1/JAWTWRHU/FM8FRP1JAWTWRHU.SMALL.jpg)

The main component in this project is the batteries, I have used the 18650 batteries which I salvaged from an old laptop battery pack, there are usually 6 of these in a battery pack and for this project you will need four. The batteries which I found were rated at 2200mAH and I am using three of them in parallel which would give me 6600mAH.

I soldered wires directly to all the batteries and connected them in parallel, i.e positive to positive and negative to negative. In the end, I left out some extra wire to connect to the Boost converter.

**Note -** If you have a hard time soldering the batteries use a sand paper to rough out both the terminals this will make soldering a lot easier.

## Step 3: Boost Converter 

![](https://cdn.instructables.com/FSG/PE54/JAYJ63C8/FSGPE54JAYJ63C8.MEDIUM.jpg)

![](https://cdn.instructables.com/F06/R639/JAWTWRBX/F06R639JAWTWRBX.SMALL.jpg)

![](https://cdn.instructables.com/FUS/781A/JAWTWRB8/FUS781AJAWTWRB8.SMALL.jpg)

After you have connected all the batteries in parallel you should be able to measure a voltage of about 3.7V. But a phone requires 5V to charge it, to step up the voltage from 3.7 to 5V we can use a Boost converter. For this project we will be using the XL6009 boost converter, which you can purchase one at a hardware store or on EBay.

The positive terminals of the batteries should be connected the positive input terminal of the Boost converter and the negative input to the negative input terminal of the Boost converter. Once the connection is complete, use a multimeter to measure the output voltage and vary the on board pot until you have 5V across the output terminals.

## Step 4: Wireless Charging 

![](https://cdn.instructables.com/F4W/6K9N/JAWTWRLF/F4W6K9NJAWTWRLF.MEDIUM.jpg)

![](https://cdn.instructables.com/FC7/J574/JAWTWRWG/FC7J574JAWTWRWG.SMALL.jpg)

![](https://cdn.instructables.com/FF3/YGTX/JAWTWRXH/FF3YGTXJAWTWRXH.SMALL.jpg)

![](https://cdn.instructables.com/F60/OGTI/JAWTWRF8/F60OGTIJAWTWRF8.SMALL.jpg)

![](https://cdn.instructables.com/FJC/FK9X/JAWTWRES/FJCFK9XJAWTWRES.SMALL.jpg)

For the wireless charging part of the project I'm using one circuit which I bought from EBay. Make sure the one you purchase has a feature, that turns on the coil only when a mobile phone or any wireless charging device is placed on it. I connected mine to an Oscilloscope and notice that the circuit Which I had sent a sine wave with a peak to peak voltage of about 16V and at a frequency of 205kHz when a mobile is placed on the coil and when there is no mobile on the coil it sends a short sine wave every few seconds to check for the phone.

This saves the battery rather than continuously generating a sine wave, furthermore the circuit has a coil with a ferrite back this improves the efficiency of the overall circuit and charges when a mobile phone is placed on the opposite side of the ferrite plate.

## Step 5: USB Port

![](https://cdn.instructables.com/F8I/8QWV/JAWTWRIP/F8I8QWVJAWTWRIP.MEDIUM.jpg)

![](https://cdn.instructables.com/FLT/7J2F/JAWTWSI9/FLT7J2FJAWTWSI9.SMALL.jpg)

![](https://cdn.instructables.com/FJ0/QG71/JAWTWRIB/FJ0QG71JAWTWRIB.SMALL.jpg)

I also needed a USB output port to charge devices without wireless charging, the USB port is connected in parallel to the wireless charging circuit and hence gets the same 5V. The positive terminal is connected to the VCC pin of the USB port which is the right most pin when the USB port output is facing towards you. The opposite end is the GND port which needs to be connected to the negative terminal of the boost converter output.

At this stage your USB circuit is done, plug in your phone cable and give it a try. If your phone is charging slowly then you can enable fast charge by soldering the middle two pins of the USB port together, this will enable your phone to charge much faster.

## Step 6: Li-ion Battery Charger 

![](https://cdn.instructables.com/FM6/DX89/JAWTWRK5/FM6DX89JAWTWRK5.MEDIUM.jpg)

![](https://cdn.instructables.com/FIS/79NO/JAWTWRKN/FIS79NOJAWTWRKN.SMALL.jpg)

![](https://cdn.instructables.com/F62/AOW7/JAWTWRJ2/F62AOW7JAWTWRJ2.SMALL.jpg)

![](https://cdn.instructables.com/FG2/UODH/JAWTWRAV/FG2UODHJAWTWRAV.SMALL.jpg)

Now its time to check all the components are working fine test out the wireless charging by placing a phone on it and the USB port by plunging a phone to it. If everything works fine now it is time to add the part of the circuit which charges the Li-ion battery. There are a variety of charging circuits online, but the most common one is the TP4056 based charging circuit which features overcharging protection and has LEDs which indicate when the batteries are charging and when it is complete. This circuit charges the Li-ion batteries by connecting an 5v source to the micro USB port of the device, so any standard mobile phone charger should be able to charge the power bank. I de-soldered the onboard LEDs of the circuit and soldered the regular 3mm LEDs to the terminals which I will later plug into the 3D printed case.

## Step 7: 3D Printed Case

![](https://cdn.instructables.com/FJO/RP04/JAWTWRGD/FJORP04JAWTWRGD.MEDIUM.jpg)

![](https://cdn.instructables.com/FAE/R69G/JAWTWRCF/FAER69GJAWTWRCF.SMALL.jpg)

![](https://cdn.instructables.com/F8S/ZJ0L/JAWTWRDT/F8SZJ0LJAWTWRDT.SMALL.jpg)

![](https://cdn.instructables.com/FTB/QT9P/JAWTWRD4/FTBQT9PJAWTWRD4.SMALL.jpg)

![](https://cdn.instructables.com/F2J/9OGF/JAWTWRH4/F2J9OGFJAWTWRH4.SMALL.jpg)

![](https://cdn.instructables.com/F77/CO5E/JAWTWRFN/F77CO5EJAWTWRFN.SMALL.jpg)

Now that the complete circuit is completed it is time to put it in an enclosure, I designed an enclosure in fusion 360 which I later printed using an ultimaker 3D printer. The files can be found in the link below and the printer settings I used are as follows.

  * Printer - Ultimaker 2+ 
  * Infill - 20% 
  * Filament - PLA 
  * Layer Height - 0.1mm

3D Printing Files - <https://www.thingiverse.com/thing:2699169>

## Step 8: Finishing 

![](https://cdn.instructables.com/FEL/R700/JAWTWSK8/FELR700JAWTWSK8.MEDIUM.jpg)

![](https://cdn.instructables.com/FMH/L0PS/JAWTWSKT/FMHL0PSJAWTWSKT.SMALL.jpg)

![](https://cdn.instructables.com/F4B/RMT7/JAWTWSIB/F4BRMT7JAWTWSIB.SMALL.jpg)

After printing the case put all the components together, make sure you are covering any uninsulated wire terminals using electrical tape and use hot glue to hold the components in place. After placing all the components in the case you should have a power bank that looks like the one in the image.

Now you have a power bank ready to be used and you don't have to worry about charging your phone or wearables anymore, you can plug it into this to get the extra few charges.
