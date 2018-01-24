# ESP8266 on batteries for years – part 2

_Captured: 2017-11-15 at 20:16 from [www.cron.dk](https://www.cron.dk/esp8266-on-batteries-for-years-part-2/)_

### Build materials

ESP8266 12E Modules: 2$ at [aliexpress](https://www.aliexpress.com/wholesale?catId=0&initiative_id=AS_20171105224319&SearchText=esp8266+12e+module)

TSL2561 Breakout board: 1$ at [aliexpress](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20171105224744&SearchText=tsl2561+breakout)

SI7021 Breakout board: 2$ at [aliexpress](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20171106115514&SearchText=SI7021)

AtTiny85 DIP mcu: 1.3$ at [aliexpress](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20171105224916&SearchText=attiny85+DIP)

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_part_esp8266-150x150.jpg)

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_part_tsl2561-150x150.jpg)

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_part_attiny85-150x150.jpg)

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_part_si7021-150x150.jpg)

Here you can find the main components for my device. I only link to the search and show the picture of my device, because products/companies comes and goes. If you don't want the hazzle of soldering the ESP directly you can buy it with a breakout board [like this](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20171105225822&SearchText=esp8266+adapter+plate).

### Schematics

Here are the schematics of the weather sensor:

![](https://www.cron.dk/wp-content/uploads/2017/11/lp_schematic.jpg)

> _Fritzing diagram can be downloaded from: github here._

The ESP and ATtiny are connected on the same I2C bus as the light sensor and the temperature/humidity sensor. I didn't add pull-up resistors because they are already present on the breakout boards of the sensors.

The two sensors are powered by output pin PB4 on the AtTiny. This gives an extra possibility to save some power when the AtTiny is sleeping.

All measurements are buffered up in the AtTiny and when it wants it can wake up the ESP by pulling PB1 low for some milliseconds.

There are two programming connectors:

  * One for the ESP. To start programming: 1) Remove "PGM protect" jumper. 2) Pull PGM low. Power up. And program with a RS232 converter connected to TX/RX. Stop pulling PGM low.
  * One for the AtTiny. To start programming: connect SPI pins ( Reset, Mosi, Miso, SCK and GND) to the programmer. I am using a TinyUsbIsp.

The "PGM protect" jumper should always be on in normal operation. Only during programming of the ESP it should be removed, so that the AtTiny doesn't disturb the programming.

### Lifecycle of the device

  1. The AtTiny deep sleeps and wakes up every second to see if it should do a measurement. If not, it goes immediately back to sleep to save power.
  2. After 2 minutes of deep sleep it powers up the sensors.
  3. It does a reading of all the sensors (By acting as an I2C master on the bus) and stores the measurements in RAM.
  4. The AtTiny goes back to sleep
  5. After 1 hour (and 30 measurements) it wakes up the ESP and switches itself into I2C slave mode. It now waits for the ESP.
  6. The ESP fetches all measurements from the AtTiny and some statistics
  7. The ESP connects to WiFi and sends the raw data to the Python Server.
  8. It then tells the AtTiny it has finished and that it can safely delete the data.
  9. ESP goes to deep sleep.
  10. AtTiny restarts its cycle.
