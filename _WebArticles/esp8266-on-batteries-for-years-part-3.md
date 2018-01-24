# ESP8266 on batteries for years – part 3

_Captured: 2017-11-15 at 20:17 from [www.cron.dk](https://www.cron.dk/esp8266-on-batteries-for-years-part-3/)_

### AtTiny85 Firmware

The arduino source code can be found on [github here](https://github.com/x821938/UltraLowPower_WeatherStation/tree/master/AtTiny85).

The main loop is a state machine that keeps track of if the AtTiny is sleeping, measuring, waking up ESP, or sending its data. When a measurement is taken it's stored in RAM. If it doesn't fit in RAM, the oldest measurements are discarded.

##### Inportant files

  * **Setup.h**: Here is all the important setup. The deviceID uniquely identifies this device. Also here is found how often measurements are done and how often the ESP will be woken up to send data over WiFi.
  * **Power.h**: Methods for turning power on/off to sensors. Method for waking up ESP. Method for going to deep sleep for 1 second.
  * **Storage.h**: An abstract class for storing measurements in a RAM buffer. All measurements are stored in a SensorData struct thats is passed to this class. The class also has a couple of methods for getting the data byte by byte - This is needed to send the raw data over the I2C bus to the ESP. Each struct is just added after the previous one. So if the Python Server knows the struct, it can easily get one measurement at the time by traversing the raw data.
  * **Sensor.h**: Here are the methods to talk to the two sensors (TSL2541 light sensor and SI7021 temperature/humidity sensor). I have scraped off all unnecessary code because the AtTiny is somewhat limited. Here the AtTiny is acting as an I2C master.
  * **SlaveI2C.h**: This takes care of slave mode. It takes commands from ESP I2C master. It's also responsible for sending data that the ESP master asks for.

##### I2C commands in slave mode

The AtTiny understands these one-byte commands from the ESP:

  * **'B'**. ESP wants statistics. We respond in this format: AABBCCDEF. 
    * AA (uint16) = Bytes of measurement data we have for the ESP
    * BB (uint16) = ESP wake up frequency in seconds
    * CC (uint16) = Measurement frequency in seconds
    * D (uint8) = Size of SensorData struct in bytes
    * E (uint8) = DeviceID (0-9 is allowed). Unique per device.
    * F (uint8) = Number of logical sensors attached (not physical). The Python server needs to know how many measurement values it can expect from each measurement.
  * **'D'**. ESP want the raw measurement data. We give the ESP the first byte of the datastorage and then the next each time he ask for a byte. The ESP know by the statistics how much he should poll for.
  * **'A'**. ESP has successfully passed on the data to the server. We are going to empty our databuffer.
  * **'Z'**. ESP is immediately going to sleep. We can start our cycle again.

### ESP8266 Firmware

The arduino source code can be found on [github here](https://github.com/x821938/UltraLowPower_WeatherStation/tree/master/ESP).

The code for the ESP is very simple. It will get it's wifi configuration from EEPROM and connect with static IP to the AP, to keep things moving as fast as possible and to save battery! When connected to Wifi, it polls the AtTiny for statistics and then gets the measurement data.

Both are sent in one TCP packet to the Python Server. After this it informs the AtTiny that it can delete it's data and then the ESP goes back to sleep.

##### important files

  * **MyWifi.h**: If the internally pulled high GPIO14 is found low during boot, the ESP enters WifiManager mode. This means that it starts up as an Access Point allowing the user to configure: 
    * Static IP address
    * Subnet address
    * Gateway address
    * Remote IP of the Python Server that will handle the measurement data
    * Remote Port (that the server will be listening on)

All this will be stored in EEPROM and loaded next time ESP is booted with GPIO14 high.  
It also has a method to send raw data to the python server.

  * **MasterI2C.h**: This class handles all communication to the AtTiny slave. It can get statistics and all the measurement data.

Basically the ESP doesn't know anything about the data it gets from the AtTiny. It just acts as a stupid gateway from I2C to the Python Server over WiFi.

### The I2C headache

For quite some time I was fighting with the USIWire library for the AtTiny. I just couldn't get it switching between master and slave mode. Because debugging arduino on the AtTiny is quite daunting, it took me some extra time to figure out a bug in the library.

I made a pull request and Puuu has put my correction into a testbranch. You would want to [clone that from here](https://github.com/puuu/USIWire/tree/testing). You can read the [reported github issue here](https://github.com/puuu/USIWire/issues/5).

That will save you from same headaches!
