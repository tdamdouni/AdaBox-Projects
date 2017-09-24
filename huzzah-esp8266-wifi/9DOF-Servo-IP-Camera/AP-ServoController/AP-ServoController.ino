
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi101.h>

#define SERVOMIN  150
#define SERVOMAX  600

uint8_t servonum = 0;

int led =  LED_BUILTIN;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



char ssid[] = "ServoName"; // created AP name
char pass[] = "password";      // AP password (needed only for WEP, must be exactly 10 or 26 characters in length)
int keyIndex = 0;                // your network key Index number (needed only for WEP)

int xpos = 375;
int ypos = 375;
int xcur = 375;
int ycur = 375;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
   Serial.begin(9600);
   delay(500);
   pwm.begin();
   pwm.setPWMFreq(60);
   pwm.setPWM(0, 0, xpos);
   pwm.setPWM(1, 0, ypos);
   
  WiFi.setPins(8,7,4,2);
  //Initialize serial and wait for port to open:
 
   //while (!Serial) {
   // ; // wait for serial port to connect. Needed for native USB port only
   // }

  Serial.println("Access Point Web Server");

  // pinMode(led, OUTPUT);      // set the LED pin mode

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    //Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // by default the local IP address of will be 192.168.1.1
  // you can override it with the following:
  // WiFi.config(IPAddress(10, 0, 0, 1));

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    // don't continue
    while (true);
  }

  // wait 3 seconds for connection:
  delay(3000);

  // start the web server on port 80
  server.begin();

  // you're connected now, so print out the status
   printWiFiStatus();

}

void loop() {
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      byte remoteMac[6];
      // a device has connected to the AP
      Serial.print("Device connected to AP, MAC address: ");
      digitalWrite(A3,1000);
      server.begin();
      delay(500);
      WiFi.APClientMacAddress(remoteMac);
      Serial.print(remoteMac[5], HEX);
      Serial.print(":");
      Serial.print(remoteMac[4], HEX);
      Serial.print(":");
      Serial.print(remoteMac[3], HEX);
      Serial.print(":");
      Serial.print(remoteMac[2], HEX);
      Serial.print(":");
      Serial.print(remoteMac[1], HEX);
      Serial.print(":");
      Serial.println(remoteMac[0], HEX);
    } else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
      digitalWrite(A3,LOW);
      status = WiFi.beginAP(ssid);
   }
  }
  
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      analogWrite(A3,1000);
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        
                                            // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
           // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
           break;
          }
          else {      // if you got a newline, then clear currentLine:
           Serial.println(currentLine);
           String xtmp = currentLine.substring(0,2);
           String ytmp = currentLine.substring(2,4);
           Serial.print (xtmp);
           Serial.println (ytmp);
           if (xtmp=="XL") {
           xpos=xpos-20;
           pwm.setPWM(0, 0, xpos);
           }
           else if (xtmp=="XR") {
           xpos=xpos+20;
           pwm.setPWM(0, 0, xpos);
           }
           else if (ytmp=="YU") {
           ypos=ypos-20;
           pwm.setPWM(1, 0, ypos);
           }
           else if (ytmp=="YD") {
           ypos=ypos+20;
           pwm.setPWM(1, 0, ypos);
           }
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    digitalWrite(A3,LOW);
    Serial.println("Client Lost");
  }
  
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

}
