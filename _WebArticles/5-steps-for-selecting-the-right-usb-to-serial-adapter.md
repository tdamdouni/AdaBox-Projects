# 5 Steps for Selecting the Right USB to Serial adapter

_Captured: 2018-01-25 at 15:49 from [www.usconverters.com](http://www.usconverters.com/index.php?main_page=page&id=62)_

_\- A Serial Adapter White Paper _  
  


If you need to connect a serial device to your computer but your computer doesn't have a serial port, then you need a USB to Serial adapter. Finding the best adapter can be a challenge since there are so many differnt models, types and manufacturers. These 5 steps will help you make the right decision. 

**The Quick Checklist:**

  1. Minimum 5.0VDC output power at serial connector (ensures reliable data transmission)
  2. Build-in electro-static protection for at least 600W (protects against static electricity)
  3. LED lights for TX and RX activity (nice to have when troubleshooting)
  


U.S. Converters sells a line of USB to serial adapters that offers all of the above features. We recommend one of the following adapters for all newer operating systems: 

**The details:**

  1. Preferred processor chip: FTDI or Silabs.  
This is the utmost most important step. The reason why we highly recommend a USB to serial adapter with a processor chip from either FTDI or Silabs is because these are simply the best. We have extensive experience with these which shows us that these processor chips works with the majority of devices and equipment on the market. The drivers are very stable, easy to install and compatible with all versions of Windows 32/64-bit, Mac, Linux. 
  

  2. Preferred serial driver chip: Maxim, Exar or NI.  
The serial driver chip is what is actually communicating and providing the power signals for your device connected to the USB to serial adapter. We recommend a brand name driver chip from Exar, Maxim or NI because these are very reliable and works well with the FTDI and Silabs processor chips. 
  

  3. At least 5VDC output power at serial connector.  
We recommend a USB to serial adapter with at least 5VDC power output for the TX/RX signals. This will ensure a strong communication signal and that your device gets sufficient power. The output power is measured from signal ground to the Tx signal and the Rx signal.   
  

  4. Build-in static protection to at least 600W.  
Built-in static protection protects the USB to serial adapter against high voltage spikes created either by static electricity or by surges in the supply voltage. This problem can exist both at the USB end and the serial RS232 end.  
  

  5. LED lights for TX and RX activity.  
Not required but very nice to have. Being able to actually see when data is transmitted through the adapter is a big advantage when troubleshooting. This way its easier to find out where the problem lies; if its your computer, your device connected to the adapter or the adapter itself. 

Other things to consider would be _compatibility with Windows 10_. The manufacturer (FTDI) of the processor chips for our USB to Serial adapter "Ultimate", "PRO" and "Thunderlinx" versions have validated that the drivers are fully compatible with the Consumer Preview, Developer Preview versions and officially released consumer versions of Windows 10. 

This is great news since you now won't have to spend money on a new USB to serial adapter once you decide to upgrade to Windows 10.

**Things to avoid:**

  * Avoid adapters with a low-cost processor chip such as Prolific or WCH (WinChipHead). The drivers are poorly written, incompatible with newer operating systems and creates unreliable communication.
  * Avoid adapters with a low output power (less than 5VDC). Low output power makes the communication unreliable or even impossible.
  


**The Architecture of a USB to serial adapter**

The design and selection of components of a USB to serial adapter is what determines failure or successful data transfer. Most USB to serial converters has built-in ADDC (Automatic Data Direction Control) so they automatically can control the data flow direction, which makes handshaking obsolete, however this only applies to the RS485 protocol, not RS232.

Below is a simplified schematic of a typical well designed circuitry. 

![USB to serial adapter circuit](http://www.usconverters.com/images/usb-serial-adapter-circuit.jpg)

> _USB to serial adapter circuit_

  


At a block level a USB to serial adapter consists of a USB serial processor chip, a serial driver chip and if the adapter is isolated there will be optocouplers in front of the USB and / or serial ports. The above design consists of a FT2232 USB serial processor from FTDI, which is a dual serial port processor. This processor is combined with a SP213 high-speed RS232 transciever from Exar which makes the overall performance of the adapter solid and reliable. 

** Further reading:**  
Further reading: [Why most USB to Serial adapters does not work with Windows 7](http://www.usconverters.com/index.php?main_page=page&id=56&chapter=0)  
Windows 8: [USB to serial adapter ready for Windows 8 ](http://www.usconverters.com/index.php?main_page=page&id=68&chapter=0)  
Overview of all [USB to Serial RS232 adapters](http://www.usconverters.com/index.php?main_page=index&cPath=67).   
Small form factor adapter: [Mini USB to serial adapter ](http://www.usconverters.com/index.php?main_page=product_info&cPath=67&products_id=244)  
  
For further information regarding serial data communication, questions or suggestions please [contact us](http://www.usconverters.com/index.php?main_page=contact_us). 

  
  
  
_________ 

_Publishing rights_: You may republish this article at your website, newsletter or ebook on the condition that you agree to leave the article, author's signature and all links completely intact. 
