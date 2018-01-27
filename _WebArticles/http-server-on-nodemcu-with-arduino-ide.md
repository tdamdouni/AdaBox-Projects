# HTTP Server on NodeMCU with Arduino IDE

_Captured: 2017-11-15 at 16:26 from [www.electronicwings.com](http://www.electronicwings.com/nodemcu/http-server-on-nodemcu-with-arduino-ide)_

# **Introduction**

The Hypertext Transfer Protocol (HTTP) is standard application layer protocol which functions as a request response protocol in between server and client.

It is widely used in IoT (Internet of Things) embedded applications, where every sensor is connected to a server and we have access to control them over the internet.

NodeMCU has Wi-Fi functionality available on board. With this Wi-Fi functionality NodeMCU can connect to any wi-fi network as client or it can create a network to which other wi-fi enabled devices can connect.

# **NodeMCU as HTTP Server using Wi-Fi AP mode**

NodeMCU wi-fi has Access Point (AP) mode through which it can create Wireless LAN to which any wi-fi enabled device can connect as shown in below figure.

![NodeMCU as HTTP Server using Wi-Fi AP mode](http://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Server/NodeMCU_WiFi_AP_Mode.png)

> _NodeMCU as HTTP Server using Wi-Fi AP mode_

We can set SSID and Password for AP mode which will be used to authenticate other devices while connecting to it.

# **NodeMCU as HTTP Server using Wi-Fi STA mode**

NodeMCU has Station (STA) mode using which it can connect to existing wi-fi network and can act as HTTP server with IP address assigned by that network.

![NodeMCU as HTTP Server using Wi-Fi STA mode](http://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Server/NodeMCU_WiFi_STA_Mode.png)

> _NodeMCU as HTTP Server using Wi-Fi STA mode_

NodeMCU gets IP from Wi-Fi router to which it is connected. With this IP address, it can act as an HTTP server to which any wi-fi device can connect.

# **Example**

Let's write Arduino Sketch to enable NodeMCU as HTTP server with Wi-Fi STA/AP mode and control an LED connected at server side from client side.

Here we have connected LED to the pin no. 2 i.e. D2 pin on NodeMCU board as shown in below figure.

![NodeMCU LED interface](http://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Server/NodeMCU%20LED.png)

> _HTML page for client_

As we are making HTTP server for LED on/off functionality, we are going to make simple HTML page which will be visible at client side and able to take user input for LED on/off. It is user friendly representation of button input which takes input from user on click.

We need to write two HTML pages for LED ON and LED OFF state i.e. when client clicks the LED ON button, then in next action we need to provide option for LED OFF. Below are the two HTML code snippets for LED ON and LED OFF state presentation.

# **HTML Code Snippet for LED ON**
    
    
    <!DOCTYPE html>
    <html>
    <head><title>LED Control</title></head>
    <body>
    <h1>LED</h1>
    <p>Click to switch LED on and off.</p>
    <form method="get">
    <input type="button" value="LED ON" onclick="window.location.href='/ledon'">
    </form>
    </body>
    </html>

# **HTML Code** **Snippet for LED OFF**
    
    
    <!DOCTYPE html>
    <html>
    <head><title>LED Control</title></head>
    <body>
    <h1>LED</h1>
    <p>Click to switch LED on and off.</p>
    <form method="get">
    <input type="button" value="LED OFF" onclick="window.location.href='/ledoff'">
    </form>
    </body>
    </html>
    

From above two HTML snippets we can see that only forms are different for LED ON and LED OFF state.

Let's have a look at HTML lines

**<!DOCTYPE html>**: This declaration defines that document as an HTML and helps browsers to display web pages correctly. It must only appear once, at the top of the page.

**<html>**: This element is the root element of an HTML page

**<head>**: This element contains meta information about the document

**<title>**: This element specifies a title for the document

**<body>**: This element contains the visible page content i.e. body of document

**<h1>**: This element defines the largest font size for heading. Similarly, we can use <h2>/<h3>and so on for smaller font sizes of the header.

**<p>**: This element defines a paragraph.

**<form>**: This element defines a form that is used to collect user input

**window.location.href** : This is a property that will tell us the current URL location. Changing the value of the property will redirect the page.

e.g.`window.location.href='/ledon'` will redirect the current page to the URL `current_url/ledon `page. If current location is `http://192.168.0.1` then it will redirect to `http://192.168.0.1/ledon `page. Page redirect action is taken on click event (e.g. click on button).

Here we are using above mentioned concept (page redirect) to redirect the client from LED ON page to LED OFF page and vice versa.

To learn more about HTML refer <https://www.w3schools.com/html/default.asp>

Now we can send above HTML snippets when client connects to the server and also when client clicks on button.

**Program**

In Wi-Fi Access Point (AP) mode, NodeMCU creates server hence we can set its IP address, IP subnet mask and IP gateway.

Let's take below SSID, Password to join network and addresses for AP mode

  * SSID = "NodeMCU"
  * Password = "12345678"
  * IP = "192.168.2.1"
  * Sub netmask = "255.255.255.0"
  * Gateway = "192.168.2.1"

# **Arduino Sketch for HTTP server with wi-fi AP mode**
    
    
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    
    /* Put your SSID & Password */
    const char* ssid = "NodeMCU";  // Enter SSID here
    const char* password = "12345678";  //Enter Password here
    
    /* Put IP Address details */
    IPAddress local_ip(192,168,2,1);
    IPAddress gateway(192,168,2,1);
    IPAddress subnet(255,255,255,0);
    
    ESP8266WebServer server(80);
    
    uint8_t LEDpin = D2;
    bool LEDstatus = LOW;
    
    void setup() {
      Serial.begin(9600);
      pinMode(LEDpin, OUTPUT);
    
      WiFi.softAP(ssid, password);
      WiFi.softAPConfig(local_ip, gateway, subnet);
      delay(100);
      
      server.on("/", handle_OnConnect);
      server.on("/ledon", handle_ledon);
      server.on("/ledoff", handle_ledoff);
      server.onNotFound(handle_NotFound);
    
      server.begin();
      Serial.println("HTTP server started");
    }
    void loop() {
      server.handleClient();
      if(LEDstatus)
      digitalWrite(LEDpin, HIGH);
      else
      digitalWrite(LEDpin, LOW);
    }
    
    void handle_OnConnect() {
      LEDstatus = LOW;
      server.send(200, "text/html", SendHTML(false)); 
    }
    
    void handle_ledon() {
      LEDstatus = HIGH;
      server.send(200, "text/html", SendHTML(true)); 
    }
    
    void handle_ledoff() {
      LEDstatus = LOW;
      server.send(200, "text/html", SendHTML(false)); 
    }
    
    void handle_NotFound(){
      server.send(404, "text/plain", "Not found");
    }
    
    String SendHTML(uint8_t led){
      String ptr = "<!DOCTYPE html>\n";
      ptr +="<html>\n";
      ptr +="<head>\n";
      ptr +="<title>LED Control</title>\n";
      ptr +="</head>\n";
      ptr +="<body>\n";
      ptr +="<h1>LED</h1>\n";
      ptr +="<p>Click to switch LED on and off.</p>\n";
      ptr +="<form method=\"get\">\n";
      if(led)
      ptr +="<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/ledoff'\">\n";
      else
      ptr +="<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/ledon'\">\n";
      ptr +="</form>\n";
      ptr +="</body>\n";
      ptr +="</html>\n";
      return ptr;
    }
    

**Note:** After successful uploading of above sketch client needs to connect to the network created by NodeMCU first.

After connecting to NodeMCU network from wifi enter the server address in browser i.e. `http://server_ip_address` e.g. in our case it is `http://192.168.2.1`_. _After press Enter key we can see the HTML page response from server as shown in below image. Now just click the button to change the state of LED.

![LED control HTML page ](http://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Server/HTML%20response%20from%20server.png)

> _Now, let's do the HTTP server to NodeMCU using Wi-Fi station mode._

In Wi-Fi Station (STA) mode, NodeMCU gets IP addresses from Wi-Fi router (access point). If we are also in same network then we can directly connect to NodeMCU HTTP Server using IP address only.

# **Arduino Sketch for HTTP server with wi-fi STA mode**
    
    
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    
    /*Put your SSID & Password*/
    const char* ssid = "ssid";  // Enter SSID here
    const char* password = "password";  //Enter Password here
    
    ESP8266WebServer server(80);
    
    uint8_t LEDpin = D2;
    bool LEDstatus = LOW;
    
    void setup() {
      Serial.begin(9600);
      delay(100);
      pinMode(LEDpin, OUTPUT);
    
      Serial.println("Connecting to ");
      Serial.println(ssid);
    
      //connect to your local wi-fi network
      WiFi.begin(ssid, password);
    
      //check wi-fi is connected to wi-fi network
      while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected..!");
      Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
    
      server.on("/", handle_OnConnect);
      server.on("/ledon", handle_ledon);
      server.on("/ledoff", handle_ledoff);
      server.onNotFound(handle_NotFound);
    
      server.begin();
      Serial.println("HTTP server started");
    }
    void loop() {
      server.handleClient();
      if(LEDstatus)
      digitalWrite(LEDpin, HIGH);
      else
      digitalWrite(LEDpin, LOW);
    }
    
    void handle_OnConnect() {
      LEDstatus = LOW;
      server.send(200, "text/html", SendHTML(false)); 
    }
    
    void handle_ledon() {
      LEDstatus = HIGH;
      server.send(200, "text/html", SendHTML(true)); 
    }
    
    void handle_ledoff() {
      LEDstatus = LOW;
      server.send(200, "text/html", SendHTML(false)); 
    }
    
    void handle_NotFound(){
      server.send(404, "text/plain", "Not found");
    }
    
    String SendHTML(uint8_t led){
      String ptr = "<!DOCTYPE html>\n";
      ptr +="<html>\n";
      ptr +="<head>\n";
      ptr +="<title>LED Control</title>\n";
      ptr +="</head>\n";
      ptr +="<body>\n";
      ptr +="<h1>LED</h1>\n";
      ptr +="<p>Click to switch LED on and off.</p>\n";
      ptr +="<form method=\"get\">\n";
      if(led)
      ptr +="<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/ledoff'\">\n";
      else
      ptr +="<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/ledon'\">\n";
      ptr +="</form>\n";
      ptr +="</body>\n";
      ptr +="</html>\n";
      return ptr;
    }
    

**Note:** in wi-fi station mode we need to enter the ssid and password of existing network. After connecting to WiFi network enter the server address in browser i.e. `http://assigned_ip_address`_._ After pressing Enter key we can see the HTML page response from server in the browser as shown above for AP mode

# **Video**
