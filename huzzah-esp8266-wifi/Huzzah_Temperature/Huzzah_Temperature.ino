/***************************************************
Adafruit ESP8266 Sensor Module

Must use ESP8266 Arduino from:
https://github.com/esp8266/Arduino
Works great with Adafruit's Huzzah ESP board:
----> https://www.adafruit.com/product/2471
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
Written by Tony DiCola for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/

// Libraries
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT.h"
#include <Time.h>
#include <TimeLib.h>

// OTA Setup
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
const char* host = "esp8266-ota";
const uint16_t aport = 8266;
WiFiServer TelnetServer(aport);
WiFiClient Telnet;
WiFiUDP OTA;

// DHT 11 sensor
#define DHTPIN 5
#define DHTTYPE DHT22 

// WiFi parameters
#define WLAN_SSID       "Wisdom"
#define WLAN_PASS       "asoccinnr3316"

// Adafruit IO
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "WisdomWolf"
#define AIO_KEY         "aad2a690116830b5c78c86426ed35b76212ae3d7"

// DHT sensor
DHT dht(DHTPIN, DHTTYPE, 15);

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Store the MQTT server, client ID, username, and password in flash memory.
const char MQTT_SERVER[] PROGMEM = AIO_SERVER;

// Set a unique MQTT client ID using the AIO key + the date and time the sketch
// was compiled (so this should be unique across multiple devices for a user,
// alternatively you can manually set this to a GUID or other random value).
const char MQTT_CLIENTID[] PROGMEM = AIO_KEY __DATE__ __TIME__;
const char MQTT_USERNAME[] PROGMEM = AIO_USERNAME;
const char MQTT_PASSWORD[] PROGMEM = AIO_KEY;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, AIO_SERVERPORT, MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);/****************************** Feeds ***************************************/

																											 // Setup feeds for temperature & humidity
const char TEMPERATURE_FEED[] PROGMEM = AIO_USERNAME "/feeds/temperature";
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, TEMPERATURE_FEED);

const char HUMIDITY_FEED[] PROGMEM = AIO_USERNAME "/feeds/humidity";
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, HUMIDITY_FEED);

// NTP Servers:
IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
										// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
										// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov


const int timeZone = -5;  //Same as GMT/UTC Offset

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

								/*************************** Sketch Code ************************************/

void setup() {

	// Init sensor
	dht.begin();

	Serial.begin(115200);
	Serial.println(F("Adafruit IO Example"));

	// Connect to WiFi access point.
	Serial.println(); Serial.println();
	delay(10);
	Serial.print(F("Connecting to "));
	Serial.println(WLAN_SSID);

	WiFi.begin(WLAN_SSID, WLAN_PASS);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(F("."));
	}
	Serial.println();

	Serial.println(F("WiFi connected"));

	MDNS.begin(host);
	MDNS.addService("arduino", "tcp", aport);
	OTA.begin(aport);
	TelnetServer.begin();
	TelnetServer.setNoDelay(true);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	Udp.begin(localPort);
	printDebug("waiting for sync");
	setSyncProvider(getNtpTime);
	while (timeStatus() == timeNotSet)
		;

	// connect to adafruit io
	connect();

}

void printDebug(const char* ch) {
	String c = String(ch);
	printDebug(c);
}

void printDebug(const __FlashStringHelper* fh) {
	String c = String(fh);
	printDebug(c);
}

void printDebug(String c) {
	//Prints to telnet if connected
	String uSC = "_";
	String M = String(month());
	String d = String(day());
	String y = String(year());
	String h = String(hour());
	String m = String(minute());
	String s = String(second());
	String timeNow = M + d + y + "_" + h + ":" + m + ":" + s + " - ";
	Serial.print(timeNow);
	Serial.println(c);

	if (Telnet && Telnet.connected()) {
		Telnet.print(timeNow);
		Telnet.println(c);
	}
}

void loop() {
	if (OTA.parsePacket()) {
		IPAddress remote = OTA.remoteIP();
		int cmd = OTA.parseInt();
		int port = OTA.parseInt();
		int size = OTA.parseInt();

		Serial.print("Update Start: ip:");
		Serial.print(remote);
		Serial.printf(", port:%d, size:%d\n", port, size);
		uint32_t startTime = millis();

		WiFiUDP::stopAll();

		if (!Update.begin(size)) {
			printDebug("Update Begin Error");
			return;
		}

		WiFiClient client;
		if (client.connect(remote, port)) {

			uint32_t written;
			while (!Update.isFinished()) {
				written = Update.write(client);
				if (written > 0) client.print(written, DEC);
			}
			Serial.setDebugOutput(false);

			if (Update.end()) {
				client.println("OK");
				Serial.printf("Update Success: %u\nRebooting...\n", millis() - startTime);
				ESP.restart();
			}
			else {
				Update.printError(client);
				Update.printError(Serial);
			}
		}
		else {
			Serial.printf("Connect Failed: %u\n", millis() - startTime);
		}
	}
	//IDE Monitor (connected to Serial)
	if (TelnetServer.hasClient()) {
		if (!Telnet || !Telnet.connected()) {
			if (Telnet) Telnet.stop();
			Telnet = TelnetServer.available();
		}
		else {
			WiFiClient toKill = TelnetServer.available();
			toKill.stop();
		}
	}
	if (Telnet && Telnet.connected() && Telnet.available()) {
		while (Telnet.available())
			Serial.write(Telnet.read());
	}
	if (Serial.available()) {
		size_t len = Serial.available();
		uint8_t * sbuf = (uint8_t *)malloc(len);
		Serial.readBytes(sbuf, len);
		if (Telnet && Telnet.connected()) {
			Telnet.write((uint8_t *)sbuf, len);
			yield();
		}
		free(sbuf);
	}

	// ping adafruit io a few times to make sure we remain connected
	if (!mqtt.ping(3)) {
		// reconnect to adafruit io
		if (!mqtt.connected())
			connect();
	}

	// Grab the current state of the sensor
	int humidity_data = (int)dht.readHumidity();
	int temperature_data = (int)dht.readTemperature(true);

	// Verify data
	if (temperature_data > 200)
		printDebug(F("Temperature data invalid, pausing"));
	delay(30000);

	// Publish data
	if (!temperature.publish(temperature_data))
		printDebug(F("Failed to publish temperature"));
	else
		printDebug(F("Temperature published!"));
	Serial.print("Temp: ");
	Serial.println(temperature_data);

	if (!humidity.publish(humidity_data))
		printDebug(F("Failed to publish humidity"));
	else
		printDebug(F("Humidity published!"));
	Serial.print("Humidity: ");
	Serial.print(humidity_data);
	Serial.println("%");

	// Repeat every 10 seconds
	delay(10000);

}

// connect to adafruit io via MQTT
void connect() {

	printDebug(F("Connecting to Adafruit IO... "));

	int8_t ret;

	while ((ret = mqtt.connect()) != 0) {

		switch (ret) {
		case 1: printDebug(F("Wrong protocol")); break;
		case 2: printDebug(F("ID rejected")); break;
		case 3: printDebug(F("Server unavail")); break;
		case 4: printDebug(F("Bad user/pass")); break;
		case 5: printDebug(F("Not authed")); break;
		case 6: printDebug(F("Failed to subscribe")); break;
		default: printDebug(F("Connection failed")); break;
		}

		if (ret >= 0)
			mqtt.disconnect();

		printDebug(F("Retrying connection..."));
		delay(5000);

	}

	printDebug(F("Adafruit IO Connected!"));

}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
	while (Udp.parsePacket() > 0); // discard any previously received packets
	Serial.println("Transmit NTP Request");
	sendNTPpacket(timeServer);
	uint32_t beginWait = millis();
	while (millis() - beginWait < 1500) {
		int size = Udp.parsePacket();
		if (size >= NTP_PACKET_SIZE) {
			Serial.println("Receive NTP Response");
			Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
			unsigned long secsSince1900;
			// convert four bytes starting at location 40 to a long integer
			secsSince1900 = (unsigned long)packetBuffer[40] << 24;
			secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
			secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
			secsSince1900 |= (unsigned long)packetBuffer[43];
			return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
		}
	}
	Serial.println("No NTP Response :-(");
	return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;     // Stratum, or type of clock
	packetBuffer[2] = 6;     // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
							 // 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;
	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp:                 
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer, NTP_PACKET_SIZE);
	Udp.endPacket();
}
