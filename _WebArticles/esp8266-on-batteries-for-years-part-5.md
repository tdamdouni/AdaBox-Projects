# ESP8266 on batteries for years – part 5

_Captured: 2017-11-15 at 20:19 from [www.cron.dk](https://www.cron.dk/esp8266-on-batteries-for-years-part-5/)_

### Actual power consumption measurements

##### The power beast - ESP8266

One of the very first and most important measurements is how much the ESP consumes when its waken up. I used [my voltage/current](https://www.cron.dk/wifi-currentvoltage-datalogger/) logger to measure this. This is the result:

![](https://www.cron.dk/wp-content/uploads/2017/11/lp_esp_wakeup.jpg)

> _It shows that the ESP is awake for about 0.7 seconds and on average it uses 78mA. The raw data can be_

[downloaded here](https://github.com/x821938/UltraLowPower_WeatherStation/raw/master/Misc/Power-Measurement-ESP-alive.xlsx).

##### AtTiny85 and the sensors

Next is measuring the cycle of the AtTiny when it does it's measurements. The chip uses so little power that I had to change shunt resistor of my INA219 from 0.1R to 10R, giving it 100 times more sensitivity.

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_attiny_wakeup.jpg)

It shows that a measurement takes about 180 ms and uses about 1.35 mA on average. The raw data can be [downloaded here](https://github.com/x821938/UltraLowPower_WeatherStation/raw/master/Misc/Power-Measurement-AtTiny-alive.xlsx). I have deliberately reduced the clock frequency on the AtTiny from 8 MHz to 1 MHz. This makes it go from 10+ mA down to about 1 mA.

My modification to my datalogger:

![](https://www.cron.dk/wp-content/uploads/2017/11/lp_shunt.jpg)

##### Sleeping power consumption

With a multi-meter I was able to measure 23.5uA for the entire device when both the AtTiny and the ESP are sleeping. This is without any power regulator or DC-DC converter. I still havn't decided which way I will go here. But it should be possible to find a solution under 10uA quiescent current.

##### Final calculation

With the above measurements I can now do the real world calculation of the battery consumption. And it was quite close to my first calculation.

![](https://www.cron.dk/wp-content/uploads/2017/10/lp_power_usage.jpg)

> _This should be fine for running some years on AA batteries_

### Next

I will add more info about power regulators / DC-DC converters when they arrive from china. This can take 1-2 month. I hope you enjoyed reading about my little project.

Comments are welcome
