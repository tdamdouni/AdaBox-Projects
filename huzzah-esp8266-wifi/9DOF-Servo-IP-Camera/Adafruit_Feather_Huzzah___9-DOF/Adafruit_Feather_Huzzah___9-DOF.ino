/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

ESP8266WiFiMulti WiFiMulti;

// WebClient
WiFiClient client;
char ssid[] = "SERVO-ACCESSPOINT-NAME"; //  your network SSID (name)
char pass[] = "PASSWORD";    // your network password (use for WPA, or use as key for WEP)

const uint16_t port = 80;
const char * host = "SERVER-IP";


/* Assign a unique ID to the sensors */
Adafruit_9DOF                dof   = Adafruit_9DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);

/* Update this with the correct SLP for accurate altitude measurements */
float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;


void initSensors()
{
  if(!accel.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void setup() {
    Serial.begin(115200);
    delay(3000);

    initSensors();
    
    // Connect To AP
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFiMulti.addAP(ssid, pass);
  delay(4000);
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  delay(4000);
  
  Serial.println("\nStarting connection to server...");
  client.connect(host, port);
    
}


void loop() {

  sensors_event_t accel_event;
  sensors_event_t mag_event;
  sensors_vec_t   orientation;
  
      accel.getEvent(&accel_event);
      if (dof.accelGetOrientation(&accel_event, &orientation))
          { 
          String xPos;
          String yPos;
          String totPos;
          if(orientation.roll > 10){
            xPos = "XR";
          }
           else if(orientation.roll < -10){
            xPos = "XL";
          }
          else{
            xPos = "XX";
          }
          if(orientation.pitch > 10){
            yPos = "YD";
          }
           else if(orientation.pitch < -10){
            yPos = "YU";
          }
          else{
            yPos = "YY";
          }
          totPos = xPos + yPos;
          client.println(totPos);
          Serial.println(totPos);    
          delay(200);
         }    
    
}
      

