# Thermal Printer Remotely Controlled through an ESP32

_Captured: 2017-11-17 at 16:11 from [trandi.wordpress.com](https://trandi.wordpress.com/2017/11/16/thermal-printer-remotely-controlled-through-an-esp32/)_

Again one of these things that I've been wanting to do for a long time, but never found the time to… having one of these little thermal printers that spit out your receipt at the till in a supermarket, and hack it to print little snippets of information like reminders or shopping lists, etc. …

So a while ago I got an old but still functional such a printer from eBay for 20£ or so, but couldn't make it work after a few attempts through its dedicated RS422 connector.  
Bought a TTL to RS485 adapter given that I had read that RS485 was a superset of RS422 (though I'm still not sure I understand exactly what the exact differences are and what people mean when saying that nowadays the "hardware is almost always RS485", especially the 4 vs 2 wires, etc. …) but to no avail.

Not being able to talk to this printer using such a standard serial protocol became very frustrating, so it finally forced me to buy an logic analyser and try to understand what was happening on the wires.  
Before I could start doing that that though, I realised that I could sidestep the RS422 card at the back of the printer and tap directly into the TTL serial lines of the main micro-controller. Which would obviously be much simpler given that I wanted to interact with a TTL speaking MCU, and would obviate the need for a TTL to RS485 adapter…

![Wth a lovely Wemos ESP32 board, with integrated OLED](https://trandi.files.wordpress.com/2017/11/2017-11-16_thermalprinter_tm-t88.jpg?w=208&h=266)

![Soldered GND, VCC, TX & RX directly to the main board.](https://trandi.files.wordpress.com/2017/11/2017-11-16_thermalprinter_tm-t88_mainboard2.jpg?w=260&h=266)

![Initial configuration, without VCC](https://trandi.files.wordpress.com/2017/11/2017-11-15_thermalprinter_tm-t88_mainboard.jpg?w=150&h=266)

Once I got the above set up (thanks to finding the "Technical Manual TM-T88 Series" pdf only with the schematic of the main board and also after some probing with the multimetre), everything became super easy.  
I had to configure the switches inside the printer to allow for software flow control and increase the serial speed to 19200bps (not that the default 9600 was a problem…) and then write some very basic Arduino code for the lovely Wemos ESP32 OLED integrated board (apparently these have actually nothing to do with Wemos, but are probably clones of [this one from Tindie](https://www.tindie.com/products/lspoplove/d-duino-32esp32-and-096oled-display/) ) which you can find on [my github page](https://github.com/trandi/esp32-thermal_printer).

As usual, please let me know in the comments if you like it or if you can think of any improvements…
