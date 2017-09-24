/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <OneWire.h> // Library for One-Wire interface
#include <DallasTemperature.h> // Library for DS18B20 temp. sensor

const char* ssid     = "*****";
const char* password = "*****";

const char* host = "*****";

#define ONE_WIRE_GPIO 4 // Data pin of the bus is connected to pin 4

// Setting up the interface for OneWire communication
OneWire oneWire (ONE_WIRE_GPIO);

// Creating an instans of DallasTemperature Class with reference to OneWire interface
DallasTemperature TempSensors(&oneWire);

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;
uint8_t i;

void loop() {
  delay(5000);
  ++value;

  TempSensors.begin(); // initializing the sensors
  Serial.println("Sensors Initialized"); 

  // getting the number of sensors
  uint8_t sensors_count = TempSensors.getDeviceCount();
  // Requesting temp. data 
  Serial.print("Sensors found = ");
  Serial.println(sensors_count);

  // Requesting temp. data 
  Serial.println("Requesting Temp. Data"); // Serial indication

  // Recording time in took to respond
  long time_start = millis(); // recording start time
  TempSensors.requestTemperatures(); // requesting data
  long time_end = millis();

  // Printing response time
  Serial.print("Done .. ");
  Serial.println(time_end - time_start);
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int tcpPort = 9999;
  if (!client.connect(host, tcpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // This will send the request to the server
  // Printing temperature in a loop
  for (i = 0; i < sensors_count; i++)
  {
    client.print("Sensor " + String(i+1) + " = " + String(TempSensors.getTempCByIndex(i)));
    delay(100);
  }
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
