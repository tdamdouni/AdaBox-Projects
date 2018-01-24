# ESP32 Arduino: Websocket server over soft AP

_Captured: 2017-11-05 at 14:22 from [techtutorialsx.com](https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server-over-soft-ap/)_

The objective of this post is to explain how to set a Websocket server on the ESP32 operating as soft AP. The software framework used will be the Arduino core for the ESP32. The tests of this ESP32 tutorial were performed using a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **  
Introduction**

The objective of this post is to explain how to set a Websocket server on the ESP32 operating as soft AP. The software framework used will be the Arduino core for the ESP32.

The code needed for setting a Websocket server was explained in detail in [this](https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server/) previous post. We will use the same code here and thus the explanation will have less detail. We will also use a Python client for testing that can be analyzed in that same post.

Regarding the code needed for making the ESP32 work as a soft AP, you can also check it in more detail on [this](https://techtutorialsx.com/2017/07/26/esp32-arduino-setting-a-soft-ap/) previous post.

In our application, the ESP32 will be acting as an echo Websocket server, which will return back to the client any content it sends.

Since the ESP32 will be operating as a soft AP, we don't need an external WiFi network hosted by a router to establish the connection between the client and the server.

Thus, the computer that will run the Python code needs to connect to the WiFi network hosted by the ESP32 and then it can transparently send and receive data from it.

The tests of this ESP32 tutorial were performed using a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **The Python code**

As said in the introductory section, we will reuse the Python websocket client code from the [previous post](https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server/). That post has the instructions for the installation of the [websocket-client](https://pypi.python.org/pypi/websocket-client) module needed.

So we will start our code by importing the **websocket** module and the **time** module. Then, we instantiate an object of class **WebSocket** and establish the connection to our ESP32 websocket server with a call to the **connect** method on that object.

Note that we need to use the correct IP address of the ESP32 in order to be able to reach the server. In this tutorial, since the ESP32 will act as soft AP, we need to use its own IP address, which we will print to the serial console on the Arduino code.

12345
`import` `websocket``import` `time``ws ``=` `websocket.WebSocket()``ws.connect(``"<ws://192.168.4.1/>"``)`

After establishing the connection, we will do a loop where we will send data to the server and then obtain the response it echoes back. After finishing the interaction with the server, we close the connection with a call to the **close** method on our **WebSocket** object.

The final source code for the Python websocket client can be checked below.

1234567891011121314151617
`import` `websocket``import` `time``ws ``=` `websocket.WebSocket()``ws.connect(``"<ws://192.168.4.1/>"``)``i ``=` `0``nrOfMessages ``=` `30``while` `i<nrOfMessages:``ws.send(``"Soft AP mode: message nr "` `+` `str``(i))``result ``=` `ws.recv()``print``(result)``i``=``i``+``1``time.sleep(``1``)``ws.close()`

## **  
The Arduino code**

The Arduino code will also be very similar to the one on the [previous tutorial](https://techtutorialsx.com/2017/11/03/esp32-arduino-websocket-server/). So, we start by including the **WiFi.h** library and the **WebSocketServer.h** library. The first one will be using for setting our soft AP and the second one to handle the Websocket related functionalities.

We will need an object of class **WiFiServer**, which we will use to create a TCP server that accepts connections from clients. The constructor of this class receives as optional input the port where the server will be listening. We will use port 80.

We will create the Websocket server on top of our TCP server. So, for the Websocket related functionalities, we will need an object of class **WebSocketServer**. This will be a wrapper that will handle the Websocket protocol details, so we only need to worry about exchanging data with the client.

We are also going to need the name for the network we will create (ssid) and the password for accessing it.

12345678
`#include <WiFi.h>``#include <WebSocketServer.h>``WiFiServer server(80);``WebSocketServer webSocketServer;``const` `char` `*ssid = ``"MyESP32AP"``;``const` `char` `*password = ``"testpassword"``;`

Moving on to the Arduino setup function, we will start by opening a serial connection to print the data received from the client.

Next we will set the soft AP with a call to the **softAP** method of the **WiFi** extern variable that is available from including the **WiFi.h** library. It is the same extern variable that we use when connecting to a WiFi network hosted by a router.

After that, to print the IP of the ESP32, we call the **softAPIP** method on the same WiFi variable. For more details on how to set a soft AP on the ESP32, please consult [this](https://techtutorialsx.com/2017/07/26/esp32-arduino-setting-a-soft-ap/) previous post.

123456
`Serial.begin(115200);``delay(4000);``WiFi.softAP(ssid, password);``Serial.println(WiFi.softAPIP());`

We finish the setup function by initializing the TCP server. This is done by calling the **begin** method on the global **WiFiServer** object we declared before.

Now, in the main loop function, we will check if a client has connected by calling the **available** method on our **WiFiServer** object.

This method call returns an object of type **WiFiClient**. To check if a client is connected, we then call the **connected** method on this object. This method will return true if the client is connected and false otherwise.

If the client is connected, we then need to perform the Websocket protocol handshake. This is done by calling the **handshake** method on the **WebSocketServer** global object we declared before.

This method will receive as input the **WiFiClient** object we obtained and returns true if the handshake is performed successfully.

Inside the previous conditional block, we will declare a variable to act as data buffer for receiving the data from the client. Then, we will loop while the client is connected and accept data from it, print it to the serial console and then echo the data back to the client.

We get data from the Websocket by calling the **getData** method on the **WebSocketServer** object. This method receives no parameters and returns a String with the data received.

To send the data back to the client, we simply call the **sendData** method and pass as input a string with the content. In our case, it will be the data previously received from the client, since our server is acting as an echo server.

The final source code can be seen below and already includes the exchange of data with the client. Note that when the previously mentioned loop ends, it means that the client has disconnected and thus we print that information to the serial console.

## **  
Testing the code**

To test the code, first compile it and upload it to your ESP32 using the Arduino IDE. After the procedure is finished, open the IDE serial monitor and copy the IP address that gets printed. You should use that IP address in the **connect** method on the Python program.

Once the ESP32 WiFi network is detected by your computer, just connect to it. You can check below at figure 1 how it looks on Windows 8.

![ESP32 Soft AP on Windows 8.png](https://techtutorialsx.files.wordpress.com/2017/11/esp32-soft-ap-on-windows-8.png)

**Figure 1** - ESP32 WiFi network detected on Windows 8 (menus in Portuguese).

After that, simply run the Python code. You should get an output similar to figure 2 on the console. As can be seen, the messages sent to the server are echoed back to the client, as expected.

![ESP32 websocket server Python client over soft AP](https://techtutorialsx.files.wordpress.com/2017/11/esp32-websocket-server-python-client-over-soft-ap.png)

**Figure 2** - Output of the Python program.

If you go back to the Arduino IDE serial monitor, you should get a result like the one shown in figure 3. As can be seen, the messages sent from the client were received and printed in the serial console.

![ESP32 Soft AP Websocket server](https://techtutorialsx.files.wordpress.com/2017/11/esp32-soft-ap-websocket-server.png)

**Figure 3** - Data received from the client printed on the serial console.

## **  
Related content**
