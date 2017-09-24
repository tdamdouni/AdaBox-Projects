# ESP8266_Adafruit_MQTT_DHT11
Sending DHT11 (temperature and humidity) details to Adafruit MQTT server using ESP8266 Board.

### Procedure:
- Update the ESP8266 board using board manager in Arduino IDE.
- Connect the DHT11's sensor pin to D6 of NodeMCU board.
- Connect GND of NodeMCU to GND pin of DHT11.
- Connect VCC (3V3) of NodeMCU to VCC pin of DHT11.
- Change the code for your SSID, PASSWORD, Adafruit account details (AIO username and KEY) to connect to the MQTT server.
- Install the Adafruit ESP8266 MQTT library using 'Manage Libraries' option in Arduino IDE.
- Upload the .ino file into ESP8266 (NodeMCU) using Arduino IDE.
- Now you should get the temperature and humidity values in Adafruit dashboard.
