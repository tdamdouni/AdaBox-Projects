#include <PubSubClient.h>
#include <Adafruit_Si7021.h>
#include <ESP8266WiFi.h>

// Replace these with your WiFi credentials
const char* ssid     = "getoffmylan";
const char* password = "correcthorsebatterystaple";

// Replace these with your MQTT connection info
const char* mqtt_server = "192.168.1.34";
const char* mqtt_user = "mqtt_username";
const char* mqtt_password = "mqtt_password";

// Define which MQTT topics the data is published to
#define humidity_topic "sensor/basement/humidity"
#define temperature_topic "sensor/basement/temperature"

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_Si7021 sensor;

void setup() {

  // Configure the two LEDs
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(2, HIGH);
  
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Blink the LED until we're connected
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(0, i % 2);
    delay(500);
    Serial.print(".");
    i++;
  }

  digitalWrite(0, LOW);

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Connect to MQTT
  client.setServer(mqtt_server, 1883);

  // Initiate the sensor
  sensor = Adafruit_Si7021();
  if (sensor.begin()) {
    Serial.println('Sensor ready');
  } else {
    // TODO: We should probably reset the device if this happens
    Serial.println('SENSOR FAILED TO START');
  }

  delay(50);
  digitalWrite(0, LOW);
}

// Attempts to reconnect to MQTT if we're ever disconnected
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    digitalWrite(0, HIGH);
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      digitalWrite(0, LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// Helps check whether any value change is significant enough to warrant a data push
bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

long lastMsg = 0;
float temp = 0.0;
float hum = 0.0;
float diff = 0.1;

void loop() {
  // Ensure we stay connected
  if (!client.connected()) {
    reconnect();
  }

  // Let MQTT do it's thing
  client.loop();

  digitalWrite(0, LOW);

  bool sent = false;

  // Check the temp and humidity once per second
  long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;

    // Read the values from the sensor
    float newTemp = sensor.readTemperature();
    float newHum = sensor.readHumidity();

    // Check whether the temperature has changed
    if (checkBound(newTemp, temp, diff)) {
      temp = newTemp;
      Serial.print("New temperature:");
      Serial.println(String(temp).c_str());
      client.publish(temperature_topic, String(temp).c_str(), true);
      sent = true;
    }

    // Check whether the humidity has changed
    if (checkBound(newHum, hum, diff)) {
      hum = newHum;
      Serial.print("New humidity:");
      Serial.println(String(hum).c_str());
      client.publish(humidity_topic, String(hum).c_str(), true);
      sent = true;
    }

    // If any data was sent (due to a change) then blink the blue LED
    if (sent) {
      sent = false;
      digitalWrite(2, LOW);
      delay(300);
      digitalWrite(2, HIGH);
    }
  }
}