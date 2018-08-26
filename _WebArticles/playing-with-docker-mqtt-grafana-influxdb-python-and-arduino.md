# Playing With Docker, MQTT, Grafana, InfluxDB, Python, and Arduino

_Captured: 2018-06-19 at 17:49 from [dzone.com](https://dzone.com/articles/playing-with-docker-mqtt-grafana-influxdb-python-a?edition=383217&utm_source=Zone%20Newsletter&utm_medium=email&utm_campaign=iot%202018-06-19)_

I must admit that this post is just an excuse to play with [Grafana](https://grafana.com/) and [InfluxDB](https://www.influxdata.com/). InfluxDB is a cool database specifically designed to work with time series data. Grafana is one open source tool used for time series analytics. I want to build a simple prototype. The idea is:

  * One Arduino device ([ESP32](https://www.espressif.com/en/products/hardware/esp32/overview)) emits an MQTT event to a [Mosquitto](https://mosquitto.org/) server. I'll use a potentiometer to emulate one sensor. For example, imagine a temperature sensor instead of a potentiometer. This is a circuit I've used in previous [projects](https://gonzalo123.com/?s=iot).
  * One Python script will be listening to the MQTT event on my Raspberry Pi and will persist the value to the InfluxDB database.
  * I will monitor the state of the time series given by the potentiometer with Grafana.
  * I will create one alert in Grafana when the average value within 10 seconds is above a threshold. This will trigger a WebHook when the alert changes its state.
  * One Python [Flask](http://flask.pocoo.org/) server, a microservice, will be listening to the WebHook and emit an MQTT event, depending on its state.
  * One [NodeMcu](http://www.nodemcu.com/index_en.html), a type of Arduino device, will be listening to this MQTT event and activate an LED. It will signal a red LED if the alert is ON and a green LED if the alert is OFF.

## **The Server**

As I've said before, we'll need three servers:

  * MQTT server (Mosquitto)
  * InfluxDB server
  * Grafana server

We'll use Docker. The Docker host will be running on a Raspberry Pi3. The Raspberry Pi is an ARM device, so we will need Docker images for this architecture.

## **ESP32**

The ESP32 part is very simple. We will only need to connect our potentiometer to the Esp32. The potentiometer has three pins: GND, Signal, and Vcc. For Signal, we'll use pin 32.

We only need to configure our Wi-Fi network, connect to our MQTT server, and emit the potentiometer value within each loop.
    
    
        client.publish((char * ) topic.c_str(), (char * ) value.c_str());
    
    
        int current = (int)((analogRead(potentiometerPin) * 100) / 4095);

## **MQTT Listener**

The ESP32 emits an event ("/pot") with the value of the potentiometer. So, we're going to create an MQTT listener that listens to MQTT and persists the value to InfluxDB.
    
    
        current_time = datetime.datetime.utcnow().isoformat()
    
    
    client.on_connect = lambda self, mosq, obj, rc: self.subscribe("/pot")
    
    
    client.on_message = lambda client, userdata, msg: persists(msg)

## **Grafana**

In Grafana, we need to do two things. First, we will create one data source from our InfluxDB server. From here, it's pretty straightforward.

Next, we'll create a dashboard. We only have one time series within the value of the potentiometer. I must admit that my dashboard has a lot of things that I've created just for fun.

That's the query that I'm using to plot the main graph.

Here, we can see the dashboard.

![](https://gonzalo123.files.wordpress.com/2018/03/dashboard.png)

> _Here, we can see my alert configuration:_

![](https://gonzalo123.files.wordpress.com/2018/03/alert.png)

I've also created a notification channel with a WebHook. Grafana will use this WebHook for notifications when the state of the alert changes.

## **WebHook Listener**

Grafana will emit a WebHook, so we'll need a REST endpoint to collect the WebHook calls. I normally use PHP/Lumen to create REST servers, but, in this project, I'll use Python and Flask.

We need to handle the HTTP Basic Auth and emit an MQTT event. MQTT is a very simple protocol, but it has one very nice feature that fits like a glove here. Let me explain.

Imagine that we've got our system up and running and the state is "ok". Now, we connect one device (for example one big red/green light). Since the "ok" event was fired before we connect the light, our green light will not switch on. We need to wait for the "alert" event if we want to see any light. That's not cool.

MQTT allows us to "retain" messages. That means that we can emit messages with the "retain" flag to one topic, and, when we connect one device later to this topic, it will receive the message. Here, it's exactly what we need.

## **NodeMcu**

Finally, the NodeMcu. This part is similar to the ESP32 one. Our LEDs are on pins 4 and 5. We also need to configure the Wi-Fi and connect to the MQTT server. NodeMcu and ESP32 are similar devices, but not the same. For example, we need to use different libraries to connect to the Wi-Fi.

This device will be listening to the MQTT event and trigger one LED or another, depending on its state.

Here, you can see the working prototype in action.

And, here is the source [code](https://github.com/gonzalo123/iot.grafana).
