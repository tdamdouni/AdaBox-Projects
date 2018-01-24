# ESP-IDF : Controlling ESP32 connected Servo postion remotely using Android app

_Captured: 2017-12-10 at 15:14 from [icircuit.net](http://icircuit.net/esp-idf-controlling-esp32-connected-appliances-remotely-using-android-app/2110)_

We had fun controlling the servo position from computer in the previous [post,](http://icircuit.net/esp-idf-connected-servo-control-servo-remote-location/2101) but my friend [Siva](https://www.linkedin.com/in/sivakumar-sk-5608a121/) says this is mobile era, everything has to be controlled by mobile now as it offers lot more convenience and easy access. Mobile became an integral part of the IoT. Lets extend our Network servo to android as well. Though we can use the same network code with out any modifications, we just need to provide the IP of the ESP32 to the android app. But the challenge is we may not know the IP address of the ESP32, In order to know the IP either we need to connect a serial monitor to ESP32 or login to the router config page to see the IP. Thus this approach requires unwanted steps and affects the seamless experience…

Hence the android app should be made dynamic enough to get the ESP32 IP automatically and send the angle input to servo regardless whatever IP ESP32 gets…

Given below is the architecture diagram for this approach

![Servo_esp32_ANdroid](http://icircuit.net/wp-content/uploads/2017/09/Android_servo.jpg)

> _Architecture for Remote servo using Android app (credit : siva)_

### How are we going to do this: Broadcast, Listen,decipher IP

We will extend our network servo code to broadcast its service name on UDP port 3000 (nothing special with the port, just a random number). Android app will be listening on this port for available services. whenever the android app receives expected message ("network_servo" in this case) , it will extract the IP address from the received message and uses this IP address to send the servo position commands (we already know the port on which ESP32 will be listening for the commands, if the port is dynamic on ESP end, we include the port also in the service message broadcast) .

### ESP32 Code :

We will take the [network servo](http://icircuit.net/esp-idf-connected-servo-control-servo-remote-location/2101) code and a new task for sending service broadcasts every 30 seconds. We need to create a UDP socket as usual , but to send a broadcast we need to set SO_BROADCAST flag
    
    
    setsockopt(s,SOL_SOCKET,SO_BROADCAST,&opt_flag,sizeof(opt_flag));

To send UDP broadcast , we need to use the _**sendto **_method available in socket api
    
    
    sendto(s, SERVC_NAME,sizeof(SERVC_NAME),0,(struct sockaddr*)&cast_addr,sizeof(cast_addr));

The broadcast address depends on the network mask and gateway IP, for most the home networks 192.168.1.255 will work. for on this check this [thread](https://github.com/esp8266/Arduino/issues/1252)

With this changes we cared udp_boardcast task (task will only start sending boardcasts after connecting to the network)

![](http://icircuit.net/wp-content/uploads/2017/09/android_network_servo.png)

Load the code to ESP and install android app. APK is available in [git repo](https://github.com/sankarcheppali/esp32_posts/tree/master/android_network_servo) along with the ESP code. Connect mobile to the same network to which ESP32 is connected and open the app. App should navigate to the following screen in couple of seconds

![](http://icircuit.net/wp-content/uploads/2017/09/android_network_servo_seek.jpeg)

Thanks to [Arun](https://www.linkedin.com/in/arunshankar-adhimoolam-1997a021/) and [Meghna](https://www.linkedin.com/in/meghna-s-moorthy-b9a9529b/) for helping me with the android app design.
