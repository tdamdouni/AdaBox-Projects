#include <DHT.h>
#include <AdafruitIO_WiFi.h>

DHT dht(2, DHT22);

char ioUser[] = "";
char ioKey[] = "";
char ssid[] = "";
char password[] = "";

AdafruitIO_WiFi io(ioUser, ioKey, ssid, password);
AdafruitIO_Feed *humFeed = io.feed("humidor-humidity");
AdafruitIO_Feed *tempFeed = io.feed("humidor-temperature");

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectToWifi();
}

void loop() {
  io.run();

  float hum = dht.readHumidity();
  float temp = dht.readTemperature(true);

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *F\t");
  Serial.println();

  humFeed->save(hum);
  tempFeed->save(temp);

  delay(10000);
}

void connectToWifi() {
  Serial.println();
  Serial.print("Connecting to network: ");
  Serial.print(ssid);

  io.connect();

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.println();

  Serial.println(io.statusText());
}
