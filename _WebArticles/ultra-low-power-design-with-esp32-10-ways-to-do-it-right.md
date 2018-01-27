# Ultra low power design with ESP32 – 10 ways to do it right

_Captured: 2017-11-14 at 20:01 from [iot-bits.com](http://iot-bits.com/ultra-low-power-design-esp32-10-tips/)_

Have you experienced your ESP32 modules going burning hot when running absolutely no work load? All at the same time when Espressif [claims](http://espressif.com/en/products/hardware/esp32/overview) that the chip is really low power? Well - every chip is really low power these days if you know how to cut down on power consumption the right way. In here, **we explore 10 ways** of getting low power design with ESP32 right, in a decreasing order of priority.

![low power design esp32](http://iot-bits.com/wp-content/uploads/2017/11/low-power-design-esp32-.jpg)

The ESP32 does not always need to operate in beast mode! You do not usually need **240MHz x 2** worth of grunt to blink an LED.

You need to realize that in MOST applications, the ESP32 is going to be doing nothing at all except waiting for something to happen. That's what real-time systems do!  
If your application is somewhat like this - scale the core frequency down to 80 MHz. That usually does the business really well.

The problem with microcontrollers is that their power consumption does not go down when you stop performing calculations. You burn almost the same amount of power running an empty while loop as you would burn with some heavy processing.

So when you feel that your application is capable of working on one core - go for it. Crush and push your application into that one core and shut the other down to save power. In most applications, it is better to have one core running at 160MHz and being 60% busy than running 2 cores at 160 MHz each and keeping them 30% busy each.

If you think about the inverse square law of radiation and then think about Wi-Fi data rates and range - you would realize that the radio is probably dumping away more juice than the cores are.

Do you need to keep scanning for a Wi-Fi SSID 10 times a second? Isn't that a little impractical? But well, that's what you might be doing!  
Try to keep the radio in control and stop it snowballing your power consumption figures while you tear your hair out trying to optimize your code and I2C pull-up resistors!

Yes, they are easy to code. But they are meant for always-on systems and are no way the best way to code energy-efficient solutions. You will absolutely need to get down to the raw networking APIs to cut down on "blocking" time that sequential APIs enforce on you.

Having the flexibility to add reasonable time-outs to all your networking operations will significantly help reduce power consumption. Being able to measure time also lets you make intelligent decisions.

In a battery powered application, if sending one TCP packet with acknowledgement takes 3 seconds (when you know it should take 200ms), isn't it a good idea to just shut down and try again later rather than have the socket API take forever to send the data out?

The LNA pin impedance of the ESP32 is not exactly 50 ohms. If you are trying to use a 50 ohm antenna directly tied to the LNA pin with no matching network, you will still be able to have proper communication - however, because of poor power transfer characteristics to the antenna, you will end up having low range and sensitivity.

This in turn means that you lost the opportunity to use a lower RF output power for the same range and potentially also suffered from data re-transmission when it was not even needed.

The data and instruction caches make it really easy to prevent unnecessary fetch cycles from the flash memory. The flash memory is a power hungry device in itself when you consider ultra low power applications. Not only that, the serial interface to the flash also means additional clock and processing overhead as well.

By placing code in RAM or avoiding wild jumps, you can reduce flash access events and tune your power consumption down to a lower level. This can be very tricky - but very beneficial to an always-on application in the long run.

You do not always need a ton of log output. Adding logs not just takes up a lot of memory, but also wastes time sending data out over UART.  
You can check the flash memory content sanity once in every 50 boot cycles if your application does not implement OTA or write data to the flash chip. There is no point being so paranoid that you checksum the flash content after every 5 seconds of deep sleep...

Find out if your bootloader is too paranoid. If it is, make sure you make it skip checking the flash contents and partitions every time it wakes up. Flash memory is usually very reliable if you do things right!
