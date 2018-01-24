# Minimizing ESP8266 Battery Drain

_Captured: 2017-12-04 at 22:33 from [hackaday.com](https://hackaday.com/2017/12/03/minimizing-esp8266-battery-drain/)_

![](https://hackadaycom.files.wordpress.com/2017/11/lp_testboard.jpg?w=800)

[Alex Jensen] wanted to build a [battery-powered weather station](https://www.cron.dk/esp8266-on-batteries-for-years-part-1/), using an ESP8266 breakout board to connect to WiFi. However, [Alex]'s research revealed that the ESP chip uses around 70mA per hour when the radio is on -- meaning that he'd have to change batteries a lot more than he wanted to. He really wanted a low power rig such that he'd only have to change batteries every 2 years on a pair of AAs.

The two considerations would be, how often does the ESP get powered up for data transmissions -- and how often the weather station's ATtiny85 takes sensor readings. Waking up the ESP from sleep mode takes about 16mA -- plus, once awake it takes about 3 seconds to reconnect, precious time at 70mA. However, by using a static IP address he was able to pare that down to half a second, with one more second to do the actual data transmission. In addition to the hourly WiFi connection, the Tiny85 must be powered, though its relatively modest 1.5mA per hour doesn't amount to much, even with the chip awake for 36 hours during the year. All told, the various components came to around 500 mAh per year, so using a pair of AA batteries should keep the rig going for years.

We're intrigued by stories of hackers eking out every last drop of power to make their projects work. We've posted about [ESPs low-power mode](https://hackaday.com/2017/09/24/datalogger-uses-esp32-and-esp8266-low-power-modes/) before, and what can be more low-power than a [watch running off a coin cell](https://hackaday.com/2017/02/15/chronio-diy-watch-slick-and-low-power/)?
