# MQTT Temperature and Humidity Monitor for Home Assistant

_Captured: 2017-09-15 at 10:38 from [www.hackster.io](https://www.hackster.io/colinodell/mqtt-temperature-and-humidity-monitor-for-home-assistant-27b8d1)_

![MQTT Temperature and Humidity Monitor for Home Assistant](https://hackster.imgix.net/uploads/attachments/347899/2017-09-09_08_27_50_je3B5PKdrq.jpg?auto=compress%2Cformat&w=900&h=675&fit=min)

I live in a three-story townhouse with a single heating/cooling zone. It's very common for the different levels to be at slightly different temperatures. In order to monitor the temperature and humidity I've created a simple ESP8266-based device which tracks that data and sends it to Home Assistant via MQTT.

This project was very simple - only two components are needed: **[Adafruit Feather HUZZAH with ESP8266 WiFi](https://www.adafruit.com/product/2821)**

This board has built-in wifi and supports I2C which I need for the sensor. It also uses USB for both power (for which I have a plethora of wall chargers) and programming. In the future I may take advantage of its LiPo battery support.

This sensor seems to be more accurate than the cheap DHT11 sensors. It also uses I2C which makes interfacing with it super easy!

Only four connections are needed:

  * 3.3V to VIN
  * GND to GND
  * SCL to SCL
  * SDA to SDA
![](https://hackster.imgix.net/uploads/attachments/347902/2017-08-26_10_56_53_p7ayJoMH5T.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _The project wired up on a breadboard_

Once I had everything working I chose to solder them onto a prototyping board so it would be more permanent:

![](https://hackster.imgix.net/uploads/attachments/347903/2017-09-09_08_27_50_9MIhBV66bj.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Top side showing the two components. They fit perfectly!_

![](https://hackster.imgix.net/uploads/attachments/347904/2017-09-09_08_28_11_ClyTVTDUSA.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Bottom side. I only soldered the corner pins (to keep it attached) and the pins being used._

The software for this is fairly straight-forward:
    
    
    #include <PubSubClient.h> 
    #include <Adafruit_Si7021.h>
    #include <ESP8266WiFi.h> 
    // Replace these with your WiFi credentials 
    const char* ssid     = "getoffmylan"; 
    const char* password = "correcthorsebatterystaple"; 
    // Replace these with your MQTT connection info 
    const char* mqtt_server = "192.168.1.34"; 
    const char* mqtt_user = "mqtt_username"; 
    const char* mqtt_password = "mqtt_password"; 
    // Define which MQTT topics the data is published to 
    #define humidity_topic "sensor/basement/humidity" 
    #define temperature_topic "sensor/basement/temperature" 
    WiFiClient espClient; 
    PubSubClient client(espClient); 
    Adafruit_Si7021 sensor; 
    void setup() { 
     // Configure the two LEDs 
     pinMode(0, OUTPUT); 
     pinMode(2, OUTPUT); 
     digitalWrite(0, LOW); 
     digitalWrite(2, HIGH); 
     Serial.begin(115200); 
     delay(100); 
     // We start by connecting to a WiFi network 
     Serial.println(); 
     Serial.println(); 
     Serial.print("Connecting to "); 
     Serial.println(ssid); 
     WiFi.begin(ssid, password); 
     // Blink the LED until we're connected 
     int i = 0; 
     while (WiFi.status() != WL_CONNECTED) { 
       digitalWrite(0, i % 2); 
       delay(500); 
       Serial.print("."); 
       i++; 
     } 
     digitalWrite(0, LOW); 
     Serial.println(""); 
     Serial.println("WiFi connected");   
     Serial.println("IP address: "); 
     Serial.println(WiFi.localIP()); 
     Serial.println(""); 
     // Connect to MQTT 
     client.setServer(mqtt_server, 1883); 
     // Initiate the sensor
     sensor = Adafruit_Si7021(); 
     if (sensor.begin()) { 
       Serial.println('Sensor ready'); 
     } else { 
       // TODO: We should probably reset the device if this happens 
       Serial.println('SENSOR FAILED TO START'); 
     } 
     delay(50); 
     digitalWrite(0, LOW); 
    } 
    // Attempts to reconnect to MQTT if we're ever disconnected 
    void reconnect() { 
     // Loop until we're reconnected 
     while (!client.connected()) { 
       digitalWrite(0, HIGH); 
       Serial.print("Attempting MQTT connection..."); 
       // Attempt to connect 
       if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) { 
         Serial.println("connected"); 
         digitalWrite(0, LOW); 
       } else { 
         Serial.print("failed, rc="); 
         Serial.print(client.state()); 
         Serial.println(" try again in 5 seconds"); 
         // Wait 5 seconds before retrying 
         delay(5000); 
       } 
     } 
    } 
    // Helps check whether any value change is significant enough to warrant a data push 
    bool checkBound(float newValue, float prevValue, float maxDiff) { 
     return !isnan(newValue) && 
            (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff); 
    } 
    long lastMsg = 0; 
    float temp = 0.0; 
    float hum = 0.0; 
    float diff = 0.1; 
    void loop() { 
     // Ensure we stay connected 
     if (!client.connected()) { 
       reconnect(); 
     } 
     // Let MQTT do it's thing 
     client.loop(); 
     digitalWrite(0, LOW); 
     bool sent = false; 
     // Check the temp and humidity once per second 
     long now = millis(); 
     if (now - lastMsg > 1000) { 
       lastMsg = now; 
       // Read the values from the sensor 
       float newTemp = sensor.readTemperature(); 
       float newHum = sensor.readHumidity(); 
       // Check whether the temperature has changed 
       if (checkBound(newTemp, temp, diff)) { 
         temp = newTemp; 
         Serial.print("New temperature:"); 
         Serial.println(String(temp).c_str()); 
         client.publish(temperature_topic, String(temp).c_str(), true); 
         sent = true; 
       } 
       // Check whether the humidity has changed 
       if (checkBound(newHum, hum, diff)) { 
         hum = newHum; 
         Serial.print("New humidity:"); 
         Serial.println(String(hum).c_str()); 
         client.publish(humidity_topic, String(hum).c_str(), true); 
         sent = true; 
       } 
       // If any data was sent (due to a change) then blink the blue LED 
       if (sent) { 
         sent = false; 
         digitalWrite(2, LOW); 
         delay(300); 
         digitalWrite(2, HIGH); 
       } 
     } 
    } 
    

The red LED blinks during startup and turns solid once WiFi and MQTT connections have been established. The blue LED will flash whenever a change in temperature or humidity has been detected and published via MQTT. This makes it easy to monitor the status of the device.

I chose MQTT because it was a lightweight protocol that was also supported by Home Assistant. To get the data into HA you will need to first configure the [MQTT platform](https://home-assistant.io/components/mqtt/).

Once that's done, use the [MQTT Sensor component](https://home-assistant.io/components/sensor.mqtt/) to collect the data:
    
    
    sensor:
     - platform: mqtt
       state_topic: sensor/basement/temperature
       name: "Basement Temperature"
       unit_of_measurement: "°C"
     - platform: mqtt
       state_topic: sensor/basement/humidity
       name: "Basement Humidity"
       unit_of_measurement: "%" 
    

You should then be able to view the temperature and humidity:

![](https://hackster.imgix.net/uploads/attachments/347906/capture4_82AJvrBz6g.PNG?auto=compress%2Cformat&w=680&h=510&fit=max)

Clicking on the sensors will show you a nice chart of historic data:

![](https://hackster.imgix.net/uploads/attachments/347916/untitled_mfrls038xT.png?auto=compress%2Cformat&w=680&h=510&fit=max)

I only have one of these running so far, but I may create several more and spread them throughout the house.

The HUZZAH board can be run from a LiPo battery which means I could put this device anywhere without needing a USB wall wart. However, because WiFi is a major power drain, I'd have to modify the firmware to sleep itself and only connect when a significant temp/humidity change has been detected.

I could also look at building some kind of enclosure. The WiFi module gives off heat though which could skew the data, so I'd have to use significant ventilation and see whether I should disable WiFi when I'm not transmitting data.

![Capture zocuatk8iw](https://halckemy.s3.amazonaws.com/uploads/attachments/347898/capture_zOcuAtk8Iw.PNG)

![Capture5 bfemixqcc8](https://halckemy.s3.amazonaws.com/uploads/attachments/347909/capture5_BfemIXQcc8.PNG)
