# Using MQTT and Apache NiFi With Onion Omega for IoT Ingest

_Captured: 2018-02-13 at 15:49 from [dzone.com](https://dzone.com/articles/using-mqtt-and-apache-nifi-with-onion-omega-for-io?edition=361106&utm_source=Zone%20Newsletter&utm_medium=email&utm_campaign=iot%202018-02-13)_

[Download Red Hat's blueprint for building an open IoT platform](https://dzone.com/go?i=250323&u=https%3A%2F%2Fwww.redhat.com%2Fen%2Fresources%2Fintelligent-systems-solution-internet-things)--open source from cloud to gateways to devices.

The Onion Omega 2+ is a small IoT device that runs a simple busybox Linux and can run Micropython. This lets you run some simple applications and interact with some sensors and an OLED.

![](https://community.hortonworks.com/storage/attachments/56510-onionomegalogin.png)

![](https://community.hortonworks.com/storage/attachments/56512-onionomegapowerdock.png)

Onion Omega 2+ stats:

Setting up the Omega:
    
    
     -----------------------------------------------------
    
    
     -----------------------------------------------------

Attributes related to MQTT message sent:

![](https://community.hortonworks.com/storage/attachments/56508-omegafiles.png)

Example flow file containing JSON:

![](https://community.hortonworks.com/storage/attachments/56509-omegajson.png)

> _Apache NiFi flow file to process:_

![](https://community.hortonworks.com/storage/attachments/56511-onionomegaprocessing.png)

> _Running MQTT on a Mac:_

In our simple example, we are just reading the time and IP address of the device and formatting it in JSON to send as MQTT messages to an MQTT server read by Apache NiFi. This is a good framework to start with on tiny devices. With the Onion platform, you can add GPS, sensors, USB devices, USB webcam, and other inputs. These can easily be added to the Python script to send to Apache NiFi as JSON.

![](https://community.hortonworks.com/storage/attachments/56513-onionomegaoled.png)

> _Source code: https://github.com/tspannhw/onionomega-mqtt-micropython_

Python script:
    
    
                return answer[0] if answer else None
    
    
    status = oledExp.scroll (0, 0, 0, 8-1);
    
    
    row = [ { 'end': str(end), 'endtime': str(endtime), 'ipaddress': str(ipaddress) } ]
    
    
    client1= client.Client("onion")                           #create client object
    
    
    client1.connect(broker,port)                                 #establish connection
    
    
    ret= client1.publish("omega",json_string)

[Build an open IoT platform](https://dzone.com/go?i=250322&u=https%3A%2F%2Fwww.redhat.com%2Fen%2Fresources%2Fintelligent-systems-solution-internet-things) with Red Hat--keep it flexible with open source software.
