#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>

const char* ssid = "[SSID]";
const char* password = "[PASSWORD]";

ESP8266WebServer server(80);

const int led = 0;

void handleRoot() {

  String html = "";
  html="<script src=\"https://cdnjs.cloudflare.com/ajax/libs/annyang/2.6.0/annyang.min.js\"></script>\
<script>\
var xhttp = new XMLHttpRequest();\
if (annyang) {\
  var commands = {\
      'up': function() {\
        xhttp.open(\"GET\", \"up\", true);\
        xhttp.send();\
    },\
      'down': function()\
      {\
        xhttp.open(\"GET\", \"down\", true);\
        xhttp.send();\
      },\
      'left': function() {\
        xhttp.open(\"GET\", \"left\", true);\
        xhttp.send();\
    },\
      'right': function() {\
        xhttp.open(\"GET\", \"right\", true);\
        xhttp.send();\
    },\
      'stop': function() {\
        xhttp.open(\"GET\", \"stop\", true);\
        xhttp.send();\
    }\
  };\
  annyang.addCommands(commands);\
  annyang.start();\
}\
</script>\
";
  

  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  Wire.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/up",[](){
    Wire.beginTransmission(8);
    Wire.write("u");
    Wire.endTransmission();
//    digitalWrite(0,1);
//    delay(1000);
//    digitalWrite(0,0);
    Serial.println("Received up");
  });
    server.on("/down",[](){
    Wire.beginTransmission(8);
    Wire.write("d");
    Wire.endTransmission();
//    digitalWrite(0,1);
//    delay(1000);
//    digitalWrite(0,0);
    Serial.println("Received down");
  });
      server.on("/left",[](){
    Wire.beginTransmission(8);
    Wire.write("l");
    Wire.endTransmission();
//    digitalWrite(0,1);
//    delay(1000);
//    digitalWrite(0,0);
    Serial.println("Received left");
  });
  server.on("/right",[](){
    Wire.beginTransmission(8);
    Wire.write("r");
    Wire.endTransmission();
//    digitalWrite(0,1);
//    delay(1000);
//    digitalWrite(0,0);
    Serial.println("Received right");
  });
    server.on("/stop",[](){
    Wire.beginTransmission(8);
    Wire.write("s");
    Wire.endTransmission();
//    digitalWrite(0,1);
//    delay(1000);
//    digitalWrite(0,0);
    Serial.println("Received stop");
  });
  

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
