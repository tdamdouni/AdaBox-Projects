#include <SPI.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#include "Pubvars.h"
// needed to avoid link error on ram check
extern "C" {
#include "user_interface.h"
uint16 readvdd33(void);
}
ADC_MODE(ADC_VCC);


// Defines
#define DHTPIN 14
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);

//Button A is #0
//Button B is #16
//Button C is #2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error ("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

DHT dht(DHTPIN, DHTTYPE,12);                        // this constant won't change:
int buttonStateIP                   = LOW;          // current state of the button
int lastButtonStateIP               = HIGH;         // previous state of the button
int buttonStateTemp                 = LOW;          // current state of the button
int lastButtonStateTemp             = HIGH;         // previous state of the button
int buttonStateToggleDisplay        = LOW;         // current state of the button
int lastButtonStateToggleDisplay    = HIGH;          // last state of the botton
bool toggleDisplay                  = true;        // Turns the display on or off
int tracker                         = 0;            // How many times it has tried to connect
byte mac[6];                                        // the MAC address of your Wifi shield
String hardwareID;                                  // Display of the mac address
Varstore vault;
int lastArea                        = 9;

WiFiServer server(vault.readServerPort());

float pfDew,pfHum,pfTemp,pfVcc,pfTempF,battery;     // Setting up some variable states


String macToStr(const uint8_t* mac)
{
String result;
for (int i = 0; i < 6; ++i) {
result += String(mac[i], 16);
if (i < 5)
result += ':';
}
return result;
}

void connectionInfo () {
    if(lastArea != 0){
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println(vault.readSSID());
        display.println(WiFi.localIP());
        WiFi.macAddress(mac);
        hardwareID = macToStr(mac);
        // display.println("Device Location");
        display.println(vault.readDeviceName());
        // display.println("");
        display.println(hardwareID);
        display.display();
    }
}
/**
 * Display Temperature data to OLED screen
 * @method displayTempValues
 */
void displayTempValues(){
        if( pfTemp > 0) { // We are only going to show data if we have data
            if(lastArea !=1){
                display.clearDisplay();
                display.display();
                display.setCursor(0,0);
                display.setTextSize(1);
                display.setTextColor(WHITE);
                display.print("Temp C: ");
                display.println(pfTemp);
                display.print("Temp F: ");
                display.println(pfTempF);
                display.print("Humidity: ");
                display.println(pfHum);
                display.print("Duepoint: ");
                display.println(pfDew);
                display.display();
            }
        }
}
/**
 * Read Temperature data from DHT sensor
 * @method readTempValues
 */
void readTempValues() {
        pfTemp = dht.readTemperature();
        pfHum = dht.readHumidity();
        pfTempF = dht.readTemperature(true);
        float a = 17.67;
        float b = 243.5;
        float alpha = (a * pfTemp)/(b + pfTemp) + log(pfHum/100);
        pfDew = (b * alpha)/(a - alpha);

        pfDew = pfTemp - ((100 - pfHum )/5);

        displayTempValues();


        Serial.println(pfTemp);
        Serial.println(pfTempF);
        Serial.println(pfHum);
        Serial.println(pfDew);
}
void showDisplay(){
        if(toggleDisplay) { //The display is to be shown
                toggleDisplay = false;
        } else { // We should hide the display
                toggleDisplay = true;
        }
}

bool readRequest(WiFiClient& client) {
        bool currentLineIsBlank = true;
        while (client.connected()) {
                if (client.available()) {
                        char c = client.read();
                        if (c == '\n' && currentLineIsBlank) {
                                return true;
                        } else if (c == '\n') {
                                currentLineIsBlank = true;
                        } else if (c != '\r') {
                                currentLineIsBlank = false;
                        }
                }
        }
        return false;
}

JsonObject& prepareResponse(JsonBuffer& jsonBuffer) {
        JsonObject& root = jsonBuffer.createObject();
        JsonArray& JSONDeviceName = root.createNestedArray("DeviceName");
        JSONDeviceName.add(vault.readDeviceName());
        JsonArray& JSONDeviceID = root.createNestedArray("DeviceID");
        // JSONDeviceID.add(vault.readDeviceID());
        JSONDeviceID.add(vault.readDeviceID());
        JsonArray& JSONHardwareID = root.createNestedArray("HardwareID");
        JSONHardwareID.add(hardwareID);
        JsonArray& JSONtempF = root.createNestedArray("tempF");
        JSONtempF.add(pfTempF);
        JsonArray& JSONtempC = root.createNestedArray("tempC");
        JSONtempC.add(pfTemp);
        JsonArray& JSONhumiValues = root.createNestedArray("humidity");
        JSONhumiValues.add(pfHum);
        JsonArray& JSONdewpValues = root.createNestedArray("dewpoint");
        JSONdewpValues.add(pfDew);
        JsonArray& JSONsystemV = root.createNestedArray("Systemv");
        JSONsystemV.add(pfVcc/1000,3);
        JSONsystemV.add(battery/1000,3);
        return root;
}

void writeResponse(WiFiClient& client, JsonObject& json) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: application/json");
        client.println("Connection: close");
        client.println();
        json.prettyPrintTo(client);
}

void setup() {
        Serial.begin(115200);
        Serial.print("Connecting to ");
        Serial.println(vault.readSSID());
        delay(100);
        // Connect to WiFi network
        WiFi.begin(vault.readSSID(), vault.readPassword());
        WiFi.softAPdisconnect();
        // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)
        delay(200);

        // Clear the buffer.
        display.clearDisplay();
        while (WiFi.status() != WL_CONNECTED) {
                delay(2000);
                Serial.print("");
                Serial.println("");
                Serial.print("Connecting to: ");
                Serial.print(vault.readSSID());
                Serial.println("");
                // Serial.print("Password: ");
                // Serial.print(vault.readPassword());
                // Serial.println("");
                Serial.print("Status: ");
                Serial.print(WiFi.status());
                Serial.println("");
                Serial.print("IP Address: ");
                Serial.print(WiFi.localIP());
                Serial.println("");
                Serial.print("Loop: ");
                Serial.print(tracker);
                Serial.println("");

                display.clearDisplay();
                display.setTextColor(WHITE);
                display.setCursor(0,0);
                display.println("Connecting to: ...");
                display.println(vault.readSSID());
                display.display();
                tracker++;
        }

        dht.begin();

        connectionInfo();
        delay(5000);

        // Start the server
        server.begin();
        Serial.println("Server started");

        // initialize the button pin as a input:
        pinMode(vault.readButtonPinIP(), INPUT_PULLUP);
        pinMode(vault.readButtonPinTemp(), INPUT_PULLUP);
        pinMode(vault.readButtonPinDisplay(), INPUT_PULLUP);
}

void loop() {
        WiFiClient client = server.available();
        if (client) { // We have a client connected
                bool success = readRequest(client);
                if (success) {
                        delay(1000); // Wait a second to ensure that we do not overload the seonsor
                        readTempValues();
                        StaticJsonBuffer<500> jsonBuffer;
                        JsonObject& json = prepareResponse(jsonBuffer);
                        writeResponse(client, json);
                }
                delay(10); // pause 10 milliseconds and then kill the connection
                client.stop();
        }

        // read the pushbutton input pin:
        buttonStateIP = digitalRead(vault.readButtonPinIP());
        // compare the buttonState to its previous state
        if (buttonStateIP != lastButtonStateIP) {
                // if the state has changed, increment the counter
                connectionInfo();
                lastArea = 0;
        }

        buttonStateTemp = digitalRead(vault.readButtonPinTemp());
        // compare the buttonState to its previous state
        if (buttonStateTemp != lastButtonStateTemp) {
                // if the state has changed, increment the counter
                readTempValues();
                lastArea = 1;
        }
        // @TODO:This needs to be finished and the two buttons above need to work
        buttonStateToggleDisplay = digitalRead(vault.readButtonPinDisplay());
        // compare the buttonState to its previous state
        if (buttonStateToggleDisplay != lastButtonStateToggleDisplay ) {
                // if the state has changed, increment the counter
                showDisplay();
                lastArea = 2;
        }
        // Serial.print("lastArea: ");
        // Serial.println(lastArea);

}
