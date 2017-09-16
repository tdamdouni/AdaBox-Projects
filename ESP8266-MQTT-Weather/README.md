## [ESP8266/Arduino](https://github.com/esp8266/Arduino) MQTT Weather Station 
Station wakes up every minute, connects to WiFi, collects measurements for 3 seconds, publishes results to an MQTT broker,
and goes back to low-power deep sleep.

* ESP8266 connects to local WiFi, and then to [Adafruit IO](https://io.adafruit.com)
via [MQTT](http://www.hivemq.com/blog/mqtt-essentials-part-1-introducing-mqtt)
* DSTH01 relative humidity sensor ([library link](https://github.com/igg2/Arduino-DSTH01))
* BMP180 pressure & temperature sensor ([library link](https://github.com/igg2/Arduino-BMP180))
* ESP8266 (using [Adafruit HUZZAH](https://www.adafruit.com/products/2471))
* Sensors communicate over I2C/TWI with ESP8266.
* ESP8266 monitors battery voltage with on-board ADC.
* Other libraries/dependencies:
	* [Adafruit_MQTT](https://github.com/adafruit/Adafruit_MQTT_Library) - Adafruit's MQTT library for Arduino.
	* [CumulStats](https://github.com/igg2/CumulStats) - Cumulative statistics library
	* [SimpleTimer](http://playground.arduino.cc/Code/SimpleTimer) - Provides 50 ms timing for main sampling loop
	* [ESP8266httpUpdate](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266httpUpdate) - Over-The-Air (OTA) flash updates. Part of [ESP8266/Arduino](https://github.com/esp8266/Arduino) library. Not yet working.

