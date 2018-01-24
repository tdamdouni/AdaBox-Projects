# ESP8266 on batteries for years – part 4

_Captured: 2017-11-15 at 20:18 from [www.cron.dk](https://www.cron.dk/esp8266-on-batteries-for-years-part-4/)_

### Python Server

The python source code can be found on [github here](https://github.com/x821938/UltraLowPower_WeatherStation/tree/master/PythonServer).

The program starts up a TCP listener on a defined port. Whenever there is an incoming connection it spawns a thread that handles the incoming data. The data packet is parsed and each measurement is stored in Influx-db with name, value and timestamp.

##### important files

  * **main.py**: Here is the configuration of which port/interface the TCP server should listen on. Also here you will find the credentials for the Influx-db server. 
    1. A connection to database is made.
    2. Then a parser instance for each deviceID is set up. Because each device can have different timings/sensor configuration we need an instance for each one of them. This also makes the application thread safe.
    3. Finally the TCP server is started with the list of parser instances so that it knows how to handle incoming packets
  * **influx.py**: When the class is instantiated a connection is made to the database. It has a writeData method that is responsible of storing one measurement in the Influx-db database. This will be used by the sensorParser class.
  * **server.py**: Binds to the TCP listening port defined and loops forever to handle incoming requests. When it receives a packet, it examines what deviceID it comes from and sends it to the correct sensorParse object for parsing.
  * **generalParser.py**: This is a general class for handling an incoming packet. It dissects the packet and and looks at the device statistics it received: 
    * Device ID
    * Time between the AtTiny's measurements
    * How often the ESP wakes up
    * How many sensors it has

It then starts traversing the measurement data one measurement at a time and let the overloaded handleNextMeasurement method take care of the data. The overloaded method will be using some helping methods like getFloat, getUint, getByte to actually interpret the data.

  * **sensorParse.py**: It's main purpose is to overload the handleNextMeasurement method of the generalParser class. In this method all the logic specific to the deviceID is handled. So here the measurements are actually named before they are stored in the Influx-db database. If you plan on adding/changing sensors, this is where you should do it.
