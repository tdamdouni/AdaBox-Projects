/* 
 * Brian Leschke
 * August 8, 2017
 * Adafruit Huzzah ESP 8266 Neopixel Light
 * The ESP8266 will control a neopixel and change the color based on Weather events, Holidays, and Fire/EMS calls.
 * Version 1.4
 * 
 *
 * -- Credit and Recognition: --
 * Morse Code Beacon Code by Mark VandeWettering (k6hx@arrl.net)
 *
 * -- Changelog: -- 
 * 
 * 2/26/17 - Initial Release - Fire/EMS and Weather Alerts implemented
 * 2/27/17 - Added NTP Client and Morse Code
 * 2/28/17 - Added Date Events (Holidays)
 * 5/16/17 - Removed platformio support and OTA by platformio. Arduino software will only be used for updating. 
 * 8/8/17  - Modified weather alert parsing code
 *
 * 
*/

// includes
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <FS.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <SPI.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


// -------------------- CONFIGURATION --------------------

// ** mDNS and OTA Constants **
#define HOSTNAME "ESP8266-OTA-"     // Hostename. The setup function adds the Chip ID at the end.
#define PIN            0            // Pin used for Neopixel communication
#define NUMPIXELS      1            // Number of Neopixels connected to Arduino
// Neopixel Setup
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// ** WiFi connection and OTA Information **
const char*     ssid = "WIFI_SSID";       // Default SSID.
const char* password = "WIFI_PASSWORD";   // Default PSK.


// ** Wunderground Information **
WiFiClient client;
String responseString;
boolean startCapture;

const char   WxServer[]        = "api.wunderground.com"; // name address for Weather Underground (using DNS)
const String myKey             = "API_KEY";         //See: http://www.wunderground.com/weather/api/d/docs (change here with your KEY)
const String myWxAlertFeatures = "alerts";               // Do Not Change. See: http://www.wunderground.com/weather/api/d/docs?d=data/index&MR=1
const String myState           = "ABBREV_STATE";    //See: http://www.wunderground.com/weather/api/d/docs?d=resources/country-to-iso-matching
const String myCity            = "CITY";                 //See: http://www.wunderground.com/weather/api/d/docs?d=data/index&MR=1

long wxAlertCheckInterval           = 900000; // 15min default. Time (milliseconds) until next weather alert check
unsigned long previousWxAlertMillis = 0;      // Do not change.

// ** JSON Parser Information
const int buffer_size = 300;                        // Do not change. Length of json buffer
const int buffer=300;                               // Do not change.
int passNum = 1;                                    // Do not change.

char* weatherConds[]={                                // Do not change.
   "\"type\":",
   "\"description\":",
   "\"date\":",
   "\"expires\":",
};

int num_elements        = 4;  // number of conditions you are retrieving, count of elements in conds
unsigned long WMillis   = 0;  // temporary millis() register


// ** FIRE-EMS INFORMATION **
char SERVER_NAME[]    = "SERVER_ADDRESS"; // Address of the webserver
int SERVER_PORT       = SERVER_PORT;       // webserver port

char Str[11];
int prevNum           = 0; //Number of previous emails before check
int num               = 0; //Number of emails after check


// ** NTP SERVER INFORMATION **
// const char* timeHost = "time-c.nist.gov";
const char* timeHost    = "129.6.15.30";
const int timePort      = 13;

int ln = 0;
String TimeDate = "";


// ** MORSE CODE TRANSMISSION INFORMATION **
#define N_MORSE  (sizeof(morsetab)/sizeof(morsetab[0]))

#define SPEED  (12)
#define DOTLEN  (1200/SPEED)
#define DASHLEN  (3*(1200/SPEED))
int txPin = 5;

struct t_mtab { char c, pat; } ;

struct t_mtab morsetab[] = {
  {'.', 106},
  {',', 115},
  {'?', 76},
  {'/', 41},
  {'A', 6},
  {'B', 17},
  {'C', 21},
  {'D', 9},
  {'E', 2},
  {'F', 20},
  {'G', 11},
  {'H', 16},
  {'I', 4},
  {'J', 30},
  {'K', 13},
  {'L', 18},
  {'M', 7},
  {'N', 5},
  {'O', 15},
  {'P', 22},
  {'Q', 27},
  {'R', 10},
  {'S', 8},
  {'T', 3},
  {'U', 12},
  {'V', 24},
  {'W', 14},
  {'X', 25},
  {'Y', 29},
  {'Z', 19},
  {'1', 62},
  {'2', 60},
  {'3', 56},
  {'4', 48},
  {'5', 32},
  {'6', 33},
  {'7', 35},
  {'8', 39},
  {'9', 47},
  {'0', 63}
} ;

// Uncomment the next line for verbose output over UART.
#define SERIAL_VERBOSE


// ---------- OTA CONFIGURATION - DO NOT MODIFY ----------

void setup()
{
  pixels.setPixelColor(0, pixels.Color(0,0,0)); // OFF
  pixels.show(); // This sends the updated pixel color to the hardware.
  
  String station_ssid = ""; // Do Not Change
  String station_psk = "";  // Do Not Change

  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(txPin, OUTPUT) ; // Initialize Morse Code transmission output.
  
  delay(100);
	
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    
    delay(2000);
    ESP.restart();
  }

  // Port defaults to 8266
  //ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  ArduinoOTA.setPassword((const char *)"OTA_PASSWORD");    // OTA auth password

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

// ---------- OTA CONFIGURATION - DO NOT MODIFY ----------

// ---------- ESP 8266 FUNCTIONS - CAN BE REMOVED ----------

void FireEmsCheck() {
  yield();
  WiFiClient client;
  if (client.connect(SERVER_NAME, SERVER_PORT)) {
    Serial.println("Fire/EMS email check: connected");
    // Make a HTTP request:
    client.println("GET /GetGmail.php");  // Apache server pathway.
    client.println();
    int timer = millis();
    delay(2000);
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("Fire/EMS email check: connection failed");  //cannot connect to server
  }

  // if there's data ready to be read:
  if (client.available()) {  
    int i = 0;   
    //put the data in the array:
    do {
      Str[i] = client.read();
      i++;
      delay(1);
    } while (client.available());
     
    // Pop on the null terminator:
    Str[i] = '\0';
    //convert server's repsonse to a int so we can evaluate it
    num = atoi(Str); 
     
    Serial.print("Server's response: ");
    Serial.println(num);
    Serial.print("Previous response: ");
    Serial.println(prevNum);
    if (prevNum < 0)
    { //the first time around, set the previous count to the current count
      prevNum = num; 
      Serial.println("First email count stored.");
    }
    if (prevNum > num)
    { // handle if count goes down for some reason
      prevNum = num; 
    }
  }
  else
    {
    Serial.println("No response from server."); //cannot connect to server.
    }
    Serial.println("Disconnecting."); //disconnecting from server to reconnect
    client.stop();
    
    // ---------------- FIRE\EMS: ALERT FOR FIRE\EMS CALL ----------------   
    
    if(num > prevNum) {
    Serial.println("FIRE/EMS ALERT!");  //alert for new email
    for(int x = 0; x < 200; x++)  // Neopixel LED blinks 60 times.
    {
      pixels.setPixelColor(0, pixels.Color(0,0,0)); // OFF  
      pixels.setPixelColor(0, pixels.Color(255,0,0)); // RED
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(150);
      pixels.setPixelColor(0, pixels.Color(0,0,0)); // OFF
      pixels.setPixelColor(0, pixels.Color(255,255,255)); // WHITE
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(150);
    } 
    prevNum = num;  //number of old emails =  number of new emails
  }
  else  //if email value is lower/equal to previous, no alert.
  {
    Serial.println("No New Alert Emails");
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // OFF
    pixels.setPixelColor(0, pixels.Color(255,255,255)); // DEFAULT WHITE
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  delay(2000);
}

void WeatherAlerts() {
yield();
// Use WiFiClient class to create TCP connections
WiFiClient client;
    //***** if you get a connection, report back via serial:
    if (!client.connect(WxServer, 80))
    {
      Serial.println("Connection Failed: Wunderground");
      return
    }
    
  String cmd = "GET /api/" + myKey + "/" + myWxAlertFeatures + "/q/" + myState + "/" + myCity + ".json HTTP/1.1; // build request_string cmd
  cmd += " HTTP/1.1\r\nHost: api.wunderground.com\r\n\r\n"; 
  delay(500);
  client.print(cmd);                                            
  delay(500);
  unsigned int i = 0;                                           // timeout counter
  char json[buffer_size]="{";                                   // first character for json-string is begin-bracket 
  int n = 1;                                                    // character counter for json
  
  
  for (int j=0;j<num_elements;j++){                             // do the loop for every element/condition
    boolean quote = false; int nn = false;                      // if quote=fals means no quotes so comma means break
    while (!client.find(weatherConds[j]))                         // If metro condition data is not available, try again.
    {
      pixels.setPixelColor(0, pixels.Color(255,255,255)); // DEFAULT WHITE
      pixels.show(); // This sends the updated pixel color to the hardware.
      Serial.println("No data available");
      return;
    }                            
  
    String Str1= weatherConds[j];                                     // Str1 gets the name of element/condition
  
    for (int l=0; l<(Str1.length());l++)                        // for as many character one by one
        {json[n] = Str1[l];                                     // fill the json string with the name
         n++;}                                                  // character count +1
    while (i<5000) {                                            // timer/counter
      if(client.available()) {                                  // if character found in receive-buffer
        char c = client.read();                                 // read that character
           Serial.print(c);                                     // 
           
// ************************ construction of json string converting comma's inside quotes to dots ******************** 
               if ((c=='"') && (quote==false))                  // there is a " and quote=false, so start of new element
                  {quote = true;nn=n;}                          // make quote=true and notice place in string
               if ((c==',')&&(quote==true)) {c='.';}            // if there is a comma inside quotes, comma becomes a dot.
               if ((c=='"') && (quote=true)&&(nn!=n))           // if there is a " and quote=true and on different position
                  {quote = false;}                              // quote=false meaning end of element between ""
               if((c==',')&&(quote==false)) break;              // if comma delimiter outside "" then end of this element
 // ****************************** end of construction ******************************************************
          json[n]=c;                                            // fill json string with this character
          n++;                                                  // character count + 1
          i=0;                                                  // timer/counter + 1
        }
        i++;                                                    // add 1 to timer/counter
      }                    // end while i<5000
     if (j==num_elements-1)                                     // if last element
        {json[n]='}';}                                          // add end bracket of json string
     else                                                       // else
        {json[n]=',';}                                          // add comma as element delimiter
     n++;                                                       // next place in json string
  }
  Serial.println(json);                                         // debugging json string 
  parseJSON(json);                                              // extract the conditions
  WMillis=millis();
}

void parseJSON(char json[300])
{
  StaticJsonBuffer<buffer> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
 
 if (!root.success())
{
  lcd.setCursor(0,3);
  lcd.print("?fparseObject() failed");
  //return;
}

 const char* type         = root["type"];
 const char* description  = root["description"];
 const char* date         = root["date"];
 const char* expires      = root["expires"];

 
 Serial.println(type);
 Serial.println(description);
 Serial.println(date);
 Serial.println(expires);
	
 if (type == "TOR") // Tornado Warning
 {
  Serial.println("Tornado Warning");
  for(int x = 0; x < 200; x++)  // Neopixel LED blinks 200 times.
    {
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF  
       pixels.setPixelColor(0, pixels.Color(255,0,0));   // RED
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF
       pixels.setPixelColor(0, pixels.Color(255,95,0)); // ORANGE
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
     } 
  }
  else if (type == "TOW") // Tornado Watch
  {
   Serial.println("Tornado Watch");
   for(int x = 0; x < 150; x++) // Neopixel LED blinks 150 times. 
     {
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF  
       pixels.setPixelColor(0, pixels.Color(255,0,0));   // RED
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF
       pixels.setPixelColor(0, pixels.Color(255,255,0)); // YELLOW
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
     } 
  }
  else if (type == "WRN") // Severe Thunderstorm Warning
  {
     Serial.println("Severe Thunderstorm Warning");
     for(int x = 0; x < 150; x++)  // Neopixel LED blinks 150 times.
     {
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF
       pixels.setPixelColor(0, pixels.Color(255,95,0)); // ORANGE
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
       pixels.setPixelColor(0, pixels.Color(0,0,0));     // OFF
       pixels.setPixelColor(0, pixels.Color(255,255,0)); // YELLOW
       pixels.show(); // This sends the updated pixel color to the hardware.
       delay(250);
      } 
    }    
    else if (type == "WIN") // Winter Weather
    {
      Serial.println("Winter Weather");
      for(int x = 0; x < 150; x++)  // Neopixel LED blinks 150 times.
      {
        pixels.setPixelColor(0, pixels.Color(0,0,0));       // OFF  
        pixels.setPixelColor(0, pixels.Color(255,162,178)); // Pink
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(250);
        pixels.setPixelColor(0, pixels.Color(0,0,0));       // OFF
        pixels.setPixelColor(0, pixels.Color(0,249,255));   // Light Blue
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(250);
      } 
    }
    else {
      pixels.setPixelColor(0, pixels.Color(255,255,255)); // DEFAULT WHITE
      pixels.show(); // This sends the updated pixel color to the hardware.
      Serial.println("No Reportable Weather Alerts");
    }
  }
}

void dash()
{
  digitalWrite(txPin, HIGH) ;
  delay(DASHLEN);
  digitalWrite(txPin, LOW) ;
  delay(DOTLEN) ;
}

void dit()
{
  digitalWrite(txPin, HIGH) ;
  delay(DOTLEN);
  digitalWrite(txPin, LOW) ;
  delay(DOTLEN);
}

void send(char c)
{
  yield();
  int i ;
  if (c == ' ') {
    Serial.print(c) ;
    delay(7*DOTLEN) ;
    return ;
  }
  for (i=0; i<N_MORSE; i++) {
    if (morsetab[i].c == c) {
      unsigned char p = morsetab[i].pat ;
      Serial.print(morsetab[i].c) ;

      while (p != 1) {
          if (p & 1)
            dash() ;
          else
            dit() ;
          p = p / 2 ;
      }
      delay(2*DOTLEN) ;
      return ;
    }
  }
  /* if we drop off the end, then we send a space */
  Serial.print("?") ;
}

void sendmsg(char *str)
{
  yield();
  while (*str)
    send(*str++) ;
  Serial.println("");
}


void timeDateEvents()
{
  yield();
  Serial.print("connecting to ");
  Serial.println(timeHost);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(timeHost, timePort)) {
    Serial.println("NIST Timeservers: connection failed");
    return;
  }
  
  // This will send the request to the server
  client.print("HEAD / HTTP/1.1\r\nAccept: */*\r\nUser-Agent: Mozilla/4.0 (compatible; ESP8266 NodeMcu Lua;)\r\n\r\n");

  delay(100);

  // Read all the lines of the reply from server and print them to Serial
  // expected line is like : Date: Thu, 01 Jan 2015 22:00:14 GMT
  char buffer[12];

  while(client.available())
  {
    String line = client.readStringUntil('\r');

    if (line.indexOf("Date") != -1)
    {
      Serial.print("=====>");
    } else
    {
      // Serial.print(line);
      // date starts at pos 10. We don't need the year.
      TimeDate = line.substring(10);
      Serial.println("UTC Time and Date:");
      Serial.println(TimeDate);
      // time starts at pos 14
      TimeDate = line.substring(10, 15);
      TimeDate.toCharArray(buffer, 10);
      Serial.println("UTC Date:");    // MM-DD
      Serial.println(buffer);
      //TimeDate = line.substring(16, 24);
      //TimeDate.toCharArray(buffer, 10);
      //Serial.println(buffer);

      if (stricmp ("01-01",buffer) == 0)
      {
	Serial.println("Happy New Year!");
  	colorWipe(pixels.Color(255, 0, 0), 50); // Red
  	colorWipe(pixels.Color(0, 255, 0), 50); // Green
  	colorWipe(pixels.Color(0, 0, 255), 50); // Blue
  	rainbow(20);
  	rainbowCycle(20);
      }
      else if (stricmp ("07-04",buffer) == 0)
      {
	Serial.println("Happy 4th of July!");
  	colorWipe(pixels.Color(255, 0, 0), 50);     // Red
  	colorWipe(pixels.Color(255, 255, 255), 50); // White
  	colorWipe(pixels.Color(0, 0, 255), 50);     // Blue
  	rainbow(20);
  	rainbowCycle(20);
      }
      else if (stricmp ("10-11",buffer) == 0)
      {
	Serial.println("Happy National Coming Out Day!");
  	colorWipe(pixels.Color(255, 0, 0), 50); // Red
  	colorWipe(pixels.Color(0, 255, 0), 50); // Green
  	colorWipe(pixels.Color(0, 0, 255), 50); // Blue
  	rainbow(20);
  	rainbowCycle(20);
      }
      else if (stricmp ("12-25",buffer) == 0)
      {
	Serial.println("Merry Christmas!");
  	colorWipe(pixels.Color(255, 0, 0), 50); // Red
  	colorWipe(pixels.Color(0, 255, 0), 50); // Green
  	rainbow(20);
  	rainbowCycle(20);
      }
      else
      {
	Serial.print("No date events for: ");
        Serial.print(buffer);
        Serial.println("");
        pixels.setPixelColor(0, pixels.Color(0,0,0)); // OFF
        pixels.setPixelColor(0, pixels.Color(255,255,255)); // WHITE
        pixels.show(); // This sends the updated pixel color to the hardware.
      }

    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
      pixels.show();
      delay(wait);
  }
}
 
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
 
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// ---------- ESP 8266 FUNCTIONS - SOME CAN BE REMOVED ----------

void loop()
{
  // Handle OTA server.
  ArduinoOTA.handle();
  yield();
  

  // ---------- USER CODE GOES HERE ----------

  // ** Transmit Morse Code **
  sendmsg("CALLSIGN"); // FCC callsign and Message
 

  // ** FireEMS Alert Check **
  FireEmsCheck();

  // ** Receive Time (NTP) and run events**
  timeDateEvents();  //20 is the amount of speed delay for color changing

  // ** Weather Alert Check **
  unsigned long currentWxAlertMillis = millis();
  
  if(currentWxAlertMillis - previousWxAlertMillis >= wxAlertCheckInterval) {
    Serial.println("Checking for Weather Alerts");
    WeatherAlerts();
    previousWxAlertMillis = currentWxAlertMillis; //remember the time(millis)
  }
  else {
    Serial.println("Bypassing Weather Alert Check. Less than 15 minutes since last check.");
    Serial.println("Previous Millis: ");
    Serial.println(previousWxAlertMillis);
    Serial.println("Current Millis: ");
    Serial.println(currentWxAlertMillis);
    Serial.println("Subtracted Millis");
    Serial.println(currentWxAlertMillis-previousWxAlertMillis);
    Serial.println();
  }
  
  // ---------- USER CODE GOES HERE ----------
}
