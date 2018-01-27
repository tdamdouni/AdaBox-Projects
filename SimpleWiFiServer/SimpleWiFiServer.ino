/*
 SimpleWifiServer
 Don't forget to set SSID and password
 */

#include "ConstantStrings.h"
#include "AnalogReader.h"
#include <WiFi.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <HTTPClient.h>
#include "esp32-hal.h"
#include "OledDriver\SSD1306.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "AnalogReader.h"
#include "ConstantStrings.h"

bool _BLEClientConnected = false;
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.temperature.xml
//#define CHAR_TEMP 0x2A6E
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.humidity.xml
//#define CHAR_HUMIDITY 0x2A6F
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.analog.xml
//#define CHAR_ANALOG 0x2A58  //could be used for CO2
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.pollen_concentration.xml&u=org.bluetooth.characteristic.pollen_concentration.xml
//#define CHAR_POLLEN_CONCENTRATION 0x2A75  //could be mis-used for CO2
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.environmental_sensing.xml
//#define ENV_SERVICE 0x181A
//https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.characteristic_user_description.xml
//#define USER_DESCRIPTION 0x2901

BLEDescriptor outdoorHumidityDescriptor(BLEUUID((uint16_t)0x2901));
BLEDescriptor outdoorTemperatureDescriptor(BLEUUID((uint16_t)0x2901));

BLECharacteristic outHumidityCharacteristic(BLEUUID((uint16_t)0x2A6F), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLECharacteristic outTemperatureCharacteristic(BLEUUID((uint16_t)0x2A6E), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);


class MyServerCallbacks : public BLEServerCallbacks {
	void onConnect(BLEServer* pServer) {
		_BLEClientConnected = true;
	};

	void onDisconnect(BLEServer* pServer) {
		_BLEClientConnected = false;
	}
};


void ReadAnalog();
void GetAnalogData(AnalogData *pData);
void GetBLEData(BLEData *pData);

SSD1306  display(0x3c, SDA, SCL);
AnalogReader *pAnalogReader;


const int _TZOffset = 1;
const int _DSTOffset = 0;


//semaphore to access analog reader
SemaphoreHandle_t shAnalogReader;
//semaphore to access the display
SemaphoreHandle_t shDisplay;

float _InternalTemperature;
const byte DISPLAY_OFF = 0;
const byte DISPLAY_VALUES = 1;
const byte DISPLAY_LOG = 2;
byte _DisplayState = 0;

byte _Touch1Counter = 0;
byte _Touch1Check = 0;
byte _Touch2Counter = 0;
byte _Touch2Check = 0;

bool _AwakeLedOn = false;
byte _LoopCounter = 0;

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

const char *_SerialNumberEE800 = "1532150000157B";
const char *_DeviceNameEE800 = "ESP32-EE800";
int _DeviceIdEE800 = 0;
int _FirmwareMajorEE800 = 1;
int _FirmwareMinorEE800 = 0;

const char *_SerialNumberEE060 = "S08719";
const char *_DeviceNameEE060 = "ESP32-EE060";
int _DeviceIdEE060 = 0;
int _FirmwareMajorEE060 = 1;
int _FirmwareMinorEE060 = 0;

WiFiServer server(80);


void InitBLE() {
	BLEDevice::init("ESP32-EE060");

	// Create the BLE Server
	BLEServer *pServer = BLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x181A));

	outdoorHumidityDescriptor.setValue("Humidity 0 to 100%");
	outdoorTemperatureDescriptor.setValue("Temperature -40-60°C");

	outHumidityCharacteristic.addDescriptor(&outdoorHumidityDescriptor);
	outTemperatureCharacteristic.addDescriptor(&outdoorTemperatureDescriptor);

	// https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
	// Create a BLE Descriptor
	outHumidityCharacteristic.addDescriptor(new BLE2902());
	outTemperatureCharacteristic.addDescriptor(new BLE2902());

	pService->addCharacteristic(&outHumidityCharacteristic);
	pService->addCharacteristic(&outTemperatureCharacteristic);
	pService->start();

	// Start advertising
	pServer->getAdvertising()->start();
}
String ToJSONDateTime(tm *pTime) {
	char buffer[30];
	strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S.0Z", pTime);
	return(String(buffer));
}
String ToLocalDateTime(tm *pTime) {
	char buffer[30];
	strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", pTime);
	return(String(buffer));
}
tm TryToGetLocalDateTime() {
	tm tmInfo;
	if(!getLocalTime(&tmInfo)) {
		tmInfo.tm_year = 100; //2000
		tmInfo.tm_hour = 0;
		tmInfo.tm_min = 0;
		tmInfo.tm_sec = 0;
		tmInfo.tm_mon = 1;
		tmInfo.tm_mday = 1;
	}
	return(tmInfo);
}

tm TryToGetUTCDateTime() {
	tm tmInfo = TryToGetLocalDateTime();
	if(tmInfo.tm_year > 100) {
		tmInfo.tm_hour -= _TZOffset;
		tmInfo.tm_hour -= _DSTOffset;
	}
	return(tmInfo);
}

void ReadAnalog() {
	if(xSemaphoreTake(shAnalogReader, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		//analog reads may take some time - meanwhile this we need exclusive access
		pAnalogReader->ReadAnalog();	//read analog data to buffer
		xSemaphoreGive(shAnalogReader); // Now free or "Give" the reader to others
	}	
}

void GetAnalogData(AnalogData *pData) {
	if(xSemaphoreTake(shAnalogReader, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		//analog reads may take some time - meanwhile this we need exclusive access
		pAnalogReader->GetData(pData);	//obtain analog data
		xSemaphoreGive(shAnalogReader); // Now free or "Give" the reader to others
	}
}

void GetBLEData(BLEData *pData) {
	if(xSemaphoreTake(shAnalogReader, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		//analog reads may take some time - meanwhile this we need exclusive access
		pAnalogReader->GetBLEData(pData);	//obtain BLE data
		xSemaphoreGive(shAnalogReader); // Now free or "Give" the reader to others
	}
}

String BuildHomepage() {
	String strHP = _HomePage;	//copy base
	tm tM = TryToGetLocalDateTime();

	String strLocalTime = ToLocalDateTime(&tM);
	strHP.replace("{Time_OUT}", strLocalTime);

	AnalogData *aD = new AnalogData();
	GetAnalogData(aD);



	strHP.replace("{RH_OUT}", String(aD->RHOut));
	strHP.replace("{Temp_OUT}", String(aD->TempOut, 1));
	delete(aD);
	return(strHP);
}

void gotTouch1() {
	_Touch1Counter++;	//simply increment - no need to lock - see loop for details
}

void gotTouch2() {
	_Touch2Counter++;	//simply increment - no need to lock - see loop for details
}
void DisplayOn() {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		display.displayOn();
		display.clear();		//clear content
		display.display();		//write to the screen
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}
void DisplaySetFont(bool pBig) {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		if(pBig) {
			display.setFont(ArialMT_Plain_16);
		}
		else {
			display.setFont(ArialMT_Plain_10);
		}
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}

void DisplayOff() {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		display.displayOff();  //turn it on
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}
void DisplayData(AnalogData *aD) {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		// We were able to obtain or "Take" the semaphore and can now access the shared resource.
		display.clear();    //clear content   
		display.drawRect(0, 0, 128, 64);
		display.drawLine(0, 21, 128, 21);

		display.setTextAlignment(TEXT_ALIGN_RIGHT);
		display.drawString(55, 2, String(aD->TempOut, 1) + "°C");
		display.drawString(125, 2, String(aD->RHOut, 0) + "%RH");

		display.display();    //write to the screen
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}
void LogString(const String &s) {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		display.println(s);
		if(_DisplayState == DISPLAY_LOG) {
			// We were able to obtain or "Take" the semaphore and can now access the shared resource.
			display.clear();    //clear content   
								// Draw it to the internal screen buffer
			display.drawLogBuffer(0, 0);
			// Display it on the screen
			display.display();
		}
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}
void DisplayClear() {
	if(xSemaphoreTake(shDisplay, (TickType_t)10) == pdTRUE) {
		display.clear();		//clear content
		display.display();		//write to the screen
		xSemaphoreGive(shDisplay); // Now free or "Give" the display to others
	}
}
void HandleTouch1() {
	//handle touch button
	if(_DisplayState == DISPLAY_OFF) {
		_DisplayState = DISPLAY_VALUES;
		DisplayOn();
		DisplaySetFont(true);
		DisplayAnalogValues();
		return;
	}
	if(_DisplayState == DISPLAY_VALUES) {
		_DisplayState = DISPLAY_LOG;
		DisplaySetFont(false);
		LogString("Log activated");
		return;
	}
	_DisplayState = DISPLAY_OFF;
	DisplayOff();
}
void HandleTouch2() {
	//handle touch button 2
}
void DisplayAnalogValues() {
	AnalogData *aD = new AnalogData();
	GetAnalogData(aD);
	DisplayData(aD);
	delete(aD);
}
void TransferBLE() {
	BLEData *aD = new BLEData();
	GetBLEData(aD);
	outHumidityCharacteristic.setValue(aD->RelativeHumidity(), 2);
	outHumidityCharacteristic.notify();
	outTemperatureCharacteristic.setValue(aD->Temperature(), 2);
	outTemperatureCharacteristic.notify();
	vTaskDelay(1);  // one tick delay (15ms) for stability
	delete(aD);
}
void HandleAnalogValues() {
	//nothing to display if off
	//and if DISPLAY_LOG the display will be handled by logging itself
	if(_DisplayState == DISPLAY_VALUES) {	//in this case show the values
		DisplayAnalogValues();
	}
	if(_BLEClientConnected) {
		TransferBLE();
	}
}
void WebTask(void *parameter) {
	while(true) {	//task never ends...
		vTaskDelay(2);  // two ticks delay (30ms) for stability
		WiFiClient client = server.available(); // listen for incoming clients
		if(client) {	// if there is a client
			String currentLine = "";	// make a String to hold incoming data from the client
			while(client.connected()) {	// loop while the client's connected
				if(client.available()) {	// if there's bytes to read from the client,
					char c = client.read(); // read a byte, then
					if(c == '\n') { // if the byte is a newline character
									// if the current line is blank, you got two newline characters in a row.
									// that's the end of the client HTTP request, so send a response:
						if(currentLine.length() == 0) {
							// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
							// and a content-type so the client knows what's coming, then a blank line:
							client.println("HTTP/1.1 200 OK");
							client.println("Content-type:text/html");
							client.println();
							String strHP = BuildHomepage();
							// the content of the HTTP response follows the header:
							client.print(strHP);
							LogString("Homepage sent");
							// The HTTP response ends with another blank line:
							client.println();
							// break out of the while loop:
							break;
						}
						else { // if you got a newline, then clear currentLine:
							currentLine = "";
						}
					}
					else if(c != '\r') { // if you got anything else but a carriage return character,
						currentLine += c; // add it to the end of the currentLine
					}
				}
			}
			// close the connection:
			client.stop();
			_InternalTemperature = temperatureRead();
		}
	}
	//the next should never occur
	Serial.println("Ending WebTask");
	vTaskDelete(NULL);
}

void setup() {
	Serial.begin(115200);

	// Semaphores should only be used whilst the scheduler is running, but we can set it up here.
	// create a semaphore to access analog reader
	if(shAnalogReader == NULL) {// check to confirm that the Semaphore has not already been created.	
		shAnalogReader = xSemaphoreCreateMutex();  // Create a mutex semaphore
		if((shAnalogReader) != NULL)
			xSemaphoreGive((shAnalogReader));  // allow access by "Giving" the Semaphore.
	}
	// create a semaphore to access display
	if(shDisplay == NULL) {// check to confirm that the Semaphore has not already been created.	
		shDisplay = xSemaphoreCreateMutex();  // Create a mutex semaphore
		if((shDisplay) != NULL)
			xSemaphoreGive((shDisplay));  // allow access by "Giving" the Semaphore.
	}

	display.init();
	// allocate memory to store 8 lines of text and 30 chars per line.
	display.setLogBuffer(5, 30);
	display.setContrast(255);

	pinMode(LED_BUILTIN, OUTPUT);

	//create analog reader (this initially reads analog values)
	pAnalogReader = new AnalogReader();
	
	touchAttachInterrupt(T7, gotTouch1, 30);
	touchAttachInterrupt(T6, gotTouch2, 30);

	delay(1000);
	InitBLE();


	// We start by connecting to a WiFi network
	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	for(int nX = 0; nX < 30; nX++) {
		WiFi.begin(ssid, password);
		int nInnerTest = 0;
		while(WiFi.status() != WL_CONNECTED) {
			delay(500);
			Serial.print(".");
			if(nInnerTest++ > 10) {
				break;
			}
		}
	}
	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	configTime(_TZOffset * 3600, _DSTOffset * 3600, "pool.ntp.org");

	server.begin();
	delay(1000);
	Serial.println("Starting web task");
	xTaskCreate(WebTask,   /* Task function. */
		"WebTask", /* String with name of task. */
		10000,     /* Stack size in words. */
		NULL,      /* Parameter passed as input of the task */
		2,         // Priority, with 1 being the highest, and 4 being the lowest.
		NULL);     /* Task handle. */
				   // Now set up two Tasks to run independently.
	Serial.println("Web task started");
}


void loop() {
	ReadAnalog();	//every half second do this
	if(((_LoopCounter++) % 4) == 0) {
		//every 2 seconds read and distribute analog values
		HandleAnalogValues();
	}
	//"lock free" touch check
	//the counters get incremented in the interrupt handlers
	//assume we got one single touch - counter will be 1 check 0
	//we do our work and remember the one
	//or assume while we work other touches occur
	//in this case we remember the count AFTER work and delay
	//if the button is released while work / delay - we get no new value in the next loop
	//if the button is still pressed AFTER the work we recognize it in the next loop
	if(_Touch1Counter != _Touch1Check) {
		HandleTouch1();	//do the work
		if(_Touch2Counter != _Touch2Check) {
			HandleTouch2();	//do the work
			delay(350);	//delay most of the time here
			_Touch2Check = _Touch2Counter;	//remember the current value
		}
		else {	//don't delay if already done for touch2
			delay(350);	//delay most of the time here if only touch1 was pressed
		}
		_Touch1Check = _Touch1Counter;	//now remember the current value
	}
	else {	//no touch1
		if(_Touch2Counter != _Touch2Check) {
			HandleTouch2();	//do the work
			delay(350);	//delay most of the time here
			_Touch2Check = _Touch2Counter;	//remember the current value
		}
		else {	//don't delay if already done for touch2
			delay(350);	//delay most of the time here if only no touches occurred
		}
	}
	//set the led
	if(_AwakeLedOn) {
		digitalWrite(LED_BUILTIN, LOW);
		_AwakeLedOn = false;
	}
	else {
		digitalWrite(LED_BUILTIN, HIGH);
		_AwakeLedOn = true;
	}
	delay(150);	//delay a bit of the time here
	//doing this we can recognize continuous touches in the next loop
}

