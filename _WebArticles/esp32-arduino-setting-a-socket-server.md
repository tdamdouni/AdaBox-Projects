# ESP32 Arduino: Setting a socket server

_Captured: 2017-11-14 at 14:10 from [techtutorialsx.com](https://techtutorialsx.com/2017/11/13/esp32-arduino-setting-a-socket-server/)_

The objective of this post is to explain how to create a simple socket server on the ESP32, using the Arduino core. The tests of this ESP32 tutorial were performed using a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **  
Introduction**

The objective of this post is to explain how to create a simple socket server on the ESP32, using the Arduino core. It will act as an echo server which will return back to the client any content it sends.

In order to test our server, we will develop a very simple Python socket client. The Python version used was 2.7 and the code was tested on Windows 8.

The tests of this ESP32 tutorial were performed using a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **  
The Python code**

We will start our code by importing the Python [socket](https://docs.python.org/3/library/socket.html#module-socket) module, which will allow us to connect to the ESP32 server.

1
`import` `socket`

Next we will create an object of class **socket**, which has the methods needed to connect to the server.

1
`sock ``=` `socket.socket()`

To connect to the server, we will need to know both its IP and the port where it is listening for incoming connections. We will store both values in two variables.

For the port, we will use **80** (we will set it to the same value on the Arduino code).

For the IP, we will need to use the one assigned to our ESP32 upon connecting to the WiFi network. If you don't know the local IP of your ESP32 when it connects to your network, you can use a dummy value for now, since we will later print its value on the Arduino code.

12
`host ``=` `"192.168.1.78"``port ``=` `80`

To perform the actual connection, we will now call the** connect** method on our socket object and pass as input a [tuple](https://www.tutorialspoint.com/python/python_tuples.htm) with the host and the port.

1
`sock.connect((host, port))`

Since the ESP32 will act as an echo server, we will send it a message and then get the result back. To send a message to the server, we will simply call the **send** method of the socket object and pass as input the content. In this case, we will send a simple "hello world" message.

We will now get content from the server until the whole message we have sent is echoed back to us.

To get data, we call the [recv](https://docs.python.org/2/library/socket.html#socket.socket.recv) method of the socket object. This method receives as input a number with the maximum amount of data that can be received at once and returns a string representing the data received [1] (I'm using Python 2.7, but some Python [versions](https://docs.python.org/3/library/socket.html#socket.socket.recv) return a byte object rather than a String).

Since we know that the server will echo the message back, we want to receive as much data as we sent. So, we will declare an empty string and keep asking for data and append it to that string until its size is equal to the size of the string we sent.

We will specify 1 for the input argument of the **recv** method, so we know that each call will return a string with only one character.

123456
`data ``=` `""       ``while` `len``(data)< ``len``(message):``data ``+``=` `sock.recv(``1``)``print``(data)`

After receiving and printing the echoed message we call the **close** method on the socket object to close the connection. The final code can be seen below and already includes this call.

1234567891011121314151617181920
`import` `socket               ``sock ``=` `socket.socket()``host ``=` `"192.168.1.78"` `#ESP32 IP in local network``port ``=` `80` `#ESP32 Server Port    ``sock.connect((host, port))``message ``=` `"Hello World"``sock.send(message)``data ``=` `""       ``while` `len``(data) < ``len``(message):``data ``+``=` `sock.recv(``1``)``print``(data)``sock.close()`

##  **  
The Arduino code**

We start our code by importing the **WiFi.h** library, in order for us to be able to connect the ESP32 to a WiFi network.

Next we will declare two global variables to store the WiFi network credentials, more precisely, the network name (ssid) and the password. You should place here the credentials for the WiFi network you are going to connect to.

We will also need a final global variable, which will be an object of class **WiFiServer**. This class has the methods we will need to set a socket server and accept connections from clients.

The constructor of this class receives as input an integer with the port number where the server will be listening. We will use port **80**, which matches the value used on the Python client code.

In our setup function, we will start by opening a serial connection, for later outputting some information messages from our program.

Next, we will connect to the WiFi network. If you need a detailed explanation on how to do it, please consult [this](https://techtutorialsx.com/2017/10/21/esp32-espruino-connection-to-a-wifi-network/) previous post.

To finalize the setup function, we will call the **begin** method on our **WiFiServer** object, which will initialize our socket server. You can check the full setup function below.

123456789101112131415161718
`void` `setup() {``Serial.begin(115200);``delay(1000);``WiFi.begin(ssid, password);``while` `(WiFi.status() != WL_CONNECTED) {``delay(1000);``Serial.println(``"Connecting to WiFi.."``);``}``Serial.println(``"Connected to the WiFi network"``);``Serial.println(WiFi.localIP());``wifiServer.begin();``}`

Now that we have finished the setup function, we will handle the actual client connections and data exchange on the Arduino main loop.

To start, we will check if a client has connected by calling the **available** method on our **WiFiServer** global object. This method takes no arguments and returns an object of class **WiFiClient**.

Next, we need to check if a client is indeed connected. We can do this both by calling the **connected** method of the **WiFiClient** object or by checking that object with an **IF** condition. Note that the **connected** method returns true if a client is connected and false otherwise.

Regarding the second option of enclosing the **WiFiClient** object inside an **IF** condition, this is possible because in the [implementation](https://github.com/espressif/arduino-esp32/blob/81f225a4c56a938b3f18e717ef62eec3ca8fb35e/libraries/WiFi/src/WiFiClient.h) of the class, the C++ bool operator is overloaded and it actually calls the **connected** method and returns its value.

Note that [operator overloading](http://en.cppreference.com/w/cpp/language/operators) is an advanced feature of the C++ language (which is the language on top of which Arduino is built) that we don't need to worry about and I'm just mentioning this for information.

If the previous condition is true, we will then start a loop while the client is connected. In this case, we will explicitly call the **connected** method of the **WiFiClient** object.

When the previous loop breaks, it means the client is no longer connected. Thus, we call the **stop** method on our **WiFiClient** to free all the resources and then print a message indicating the client disconnected.

12345678
`if` `(client) {``while` `(client.connected()) {``// Data exchange with the client``}``client.stop();``Serial.println(``"Client disconnected"``);``}`

Inside the previously mentioned while loop, we can check if the client has sent data with the **available** method. This method returns the number of bytes available for reading.

So, while the number of bytes is greater than zero, we will keep reading byte by byte with a call to the **read** method of the **WiFiClient** object, which will return a byte for each call.

Then, we will simply echo each byte back to the client with the call to the **write** method, passing as input the byte to send.

The final source code can be seen below and already includes these function calls.

1234567891011121314151617181920212223242526272829303132333435363738394041424344454647
`#include <WiFi.h>``const` `char``* ssid = ``"YourNetworkName"``;``const` `char``* password =  ``"YourNetworkPassword"``;``WiFiServer wifiServer(80);``void` `setup() {``Serial.begin(115200);``delay(1000);``WiFi.begin(ssid, password);``while` `(WiFi.status() != WL_CONNECTED) {``delay(1000);``Serial.println(``"Connecting to WiFi.."``);``}``Serial.println(``"Connected to the WiFi network"``);``Serial.println(WiFi.localIP());``wifiServer.begin();``}``void` `loop() {``WiFiClient client = wifiServer.available();``if` `(client) {``while` `(client.connected()) {``while` `(client.available()>0) {``char` `c = client.read();``client.write(c);``}``delay(10);``}``client.stop();``Serial.println(``"Client disconnected"``);``}``}`

## **  
Testing the code**

To test the whole system, simply upload the code to your ESP32 using the Arduino IDE. Then open the IDE serial monitor and copy the IP address that gets printed upon a successful connection of the ESP32 to the WiFi network. That is the IP that should be used on the Arduino code.

Next, with the ESP32 already running the server code, run the Python code. You should get an output similar to figure 1, which shows the data sent to the server being echoed back, as expected.

![ESP32 socket server Python client.png](https://techtutorialsx.files.wordpress.com/2017/11/esp32-socket-server-python-client.png)

**Figure 1** - Output of the Python client program.

If you go back to the serial monitor, a message indicating that the client disconnected should be printed, as shown in figure 2. This indicates that the server correctly detected that the client is no longer connected, which is the expected behavior after the Python code calls the close method to end the connection.

![ESP32 Arduino socket server client disconnected.png](https://techtutorialsx.files.wordpress.com/2017/11/esp32-arduino-socket-server-client-disconnected.png)

**Figure 2** - Output of the ESP32 program, after the client disconnects.

## **  
References**

[1] <https://docs.python.org/2/library/socket.html#socket.socket.recv>
