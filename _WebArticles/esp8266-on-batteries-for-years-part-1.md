# ESP8266 on batteries for years – part 1

_Captured: 2017-11-15 at 20:15 from [www.cron.dk](https://www.cron.dk/esp8266-on-batteries-for-years-part-1/)_

### The ultra low power weather station

For some time I have been fascinated by the possibilities of the ESP8266, but I never really considered it good for a life on batteries. I got an idea of making an outdoor weather station that would send measured light level, temperature and humidity to my home automation server.

The ESP is a hungry beast when it's doing WiFi. According to different sources on the internet it uses about 70 mA on average when WiFi is on! This would mean that I have to change batteries on my sensor quite some times every year.

I instead came up with the idea of a design using an AtTiny85 for doing frequent measurements and then once in a while to wake up the ESP beast to transmit it's recorded data to the server.

##### Wanted specs

  * A solution where I only have to change batteries every 2 years
  * Device doing 1 measurement every 2 minutes of: 
    * Temperature in degrees C
    * Humidity in %
    * Light level in Lux
  * Every 1 hour data is transmitted via WiFi to a Python Server. If the server is unreachable, the measurements would be buffered up.
  * The server would store data in an [Influx-db](https://www.influxdata.com/time-series-platform/influxdb/) database.
  * User interface would be [Grafana](https://grafana.com/) graphing on top.

### First prototype

All software has been developed on my small test board:

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_testboard.jpg)

> _The programming was done with a USBTinyIsp-clone for the AtTiny85 and a 3.3v generic rs232 converter. Both are shown in the picture._

### Design decisions

My first thoughts was to only use an ESP in deep sleep mode most of the time. By waking it up with the radio disabled it takes about 16mA. The downside was that when you then needed the radio it needed to do a full re-calibration making it take 3 seconds just to connect. That is a long time and a lot of battery usage!

I spend some time experimenting getting the awake time down. By using static IP I can get the time down to 0.5 seconds. But about 10% of the times it takes 1.5 seconds. I haven't been able to track down what causes this. Maybe WiFi collisions, because it seems less at night?

I settled on the AtTiny85 for doing most of the work. I let it turn on/off the sensers, getting measurements via I2C from sensors, wake up the ESP and act as an I2C slave for the ESP to fetch the data.

##### Calculations

Before I started I did some calculations from the specs:

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_power_calc.jpg)

![](https://www.cron.dk/wp-content/uploads/2017/11/lp_power_calc.jpg)

> _The spreadsheet can be downloaded here if your want to play with the numbers._

Two alkaline AA batteries should hold about 2000 mAh, which would be sufficient to run my sensor device 4 years according to my (best scenario) calculations. In real life probably only half. That will be shown when I have the final power measurements in the end of this series.

### Example

Here is a final example of the last days outdoor measurements presented in grafana:

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_measurement_example.jpg)

### In this series

I will go through the entire design process. All the way from the electronics to the source code of the AtTiny85 to the code for the ESP8266 and the python code for the server end.

  * [Part 2](https://www.cron.dk/esp8266-on-batteries-for-years-part-2/): Electronics and schematics
  * [Part 3](https://www.cron.dk/esp8266-on-batteries-for-years-part-3/): Source code for the two microcontrollers
  * [Part 4](https://www.cron.dk/esp8266-on-batteries-for-years-part-4/): Source code for the python server
  * [part 5](https://www.cron.dk/esp8266-on-batteries-for-years-part-5/): Real measurements of current consumptions.
