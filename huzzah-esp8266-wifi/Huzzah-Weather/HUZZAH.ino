#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <bmp180.h>
#include <Wire.h>

#define HTDU21D_ADDRESS 0x40
#define TRIGGER_TEMP_MEASURE_HOLD  0xE3
#define TRIGGER_HUMD_MEASURE_HOLD  0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD  0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD  0xF5
#define WRITE_USER_REG  0xE6
#define READ_USER_REG  0xE7
#define SOFT_RESET  0xFE
#define SHIFTED_DIVISOR 0x988000

const byte statusLed = 4;
const byte flashLed= 5;

long timeStamp=0;
int delayTime=20000;
int rstCounter=0;

const char* apiKey        = " ";
const char* ssid     = "";
const char* password = "";
const char* server   = "api.thingspeak.com";
bmp180 bmp;
WiFiClient client;

void flash(int pin, int timems){
  digitalWrite(pin,HIGH);
  delay(timems);
  digitalWrite(pin,LOW);
  delay(timems);
  digitalWrite(pin,HIGH);
  delay(timems);
  digitalWrite(pin,LOW);
}
void postResults(float temp, float pressure, float rh)
{

if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(temp);
postStr +="&field2=";
postStr += String(pressure);
postStr +="&field3=";
postStr += String(rh);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+(String)apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

Serial.println("Data sent to Thingspeak");


}
client.stop();
flash(flashLed, 50);
Serial.println("Waiting...");
// thingspeak needs minimum 15 sec delay between updates
}
byte check_crc(uint16_t message_from_sensor, uint8_t check_value_from_sensor)
{
  //Test cases from datasheet:
  //message = 0xDC, checkvalue is 0x79
  //message = 0x683A, checkvalue is 0x7C
  //message = 0x4E85, checkvalue is 0x6B

  uint32_t remainder = (uint32_t)message_from_sensor << 8; //Pad with 8 bits because we have to add in the check value
  remainder |= check_value_from_sensor; //Add on the check value

  uint32_t divsor = (uint32_t)SHIFTED_DIVISOR;

  for (int i = 0 ; i < 16 ; i++) //Operate on only 16 positions of max 24. The remaining 8 are our remainder and should be zero when we're done.
  {
    //Serial.print("remainder: ");
    //Serial.println(remainder, BIN);
    //Serial.print("divsor:    ");
    //Serial.println(divsor, BIN);
    //Serial.println();

    if( remainder & (uint32_t)1<<(23 - i) ) //Check if there is a one in the left position
      remainder ^= divsor;

    divsor >>= 1; //Rotate the divsor max 16 times so that we have 8 bits left of a remainder
  }

  return (byte)remainder;
}

float htureadHumidity(void)
{
	//Request a humidity reading
	Wire.beginTransmission(HTDU21D_ADDRESS);
	Wire.write(TRIGGER_HUMD_MEASURE_NOHOLD); //Measure humidity with no bus holding
	Wire.endTransmission();

	//Hang out while measurement is taken. 50mS max, page 4 of datasheet.
	delay(55);

	//Comes back in three bytes, data(MSB) / data(LSB) / Checksum
	Wire.requestFrom(HTDU21D_ADDRESS, 3);

	//Wait for data to become available
	int counter = 0;
	while(Wire.available() < 3)
	{
		counter++;
		delay(1);
		if(counter > 100) return 998; //Error out
	}

	byte msb, lsb, checksum;
	msb = Wire.read();
	lsb = Wire.read();
	checksum = Wire.read();

	/* //Used for testing
	byte msb, lsb, checksum;
	msb = 0x4E;
	lsb = 0x85;
	checksum = 0x6B;*/

	unsigned int rawHumidity = ((unsigned int) msb << 8) | (unsigned int) lsb;

	if(check_crc(rawHumidity, checksum) != 0) return(999); //Error out

	//sensorStatus = rawHumidity & 0x0003; //Grab only the right two bits
	rawHumidity &= 0xFFFC; //Zero out the status bits but keep them in place

	//Given the raw humidity data, calculate the actual relative humidity
	float tempRH = rawHumidity / (float)65536; //2^16 = 65536
	float rh = -6 + (125 * tempRH); //From page 14

	return(rh);
}


void setup()
{
  pinMode(statusLed, OUTPUT);
  pinMode(flashLed, OUTPUT);
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(statusLed,HIGH);
    rstCounter++;
    if(rstCounter >=25)
    {
      flash(statusLed,500);
      delay(1000);
      ESP.restart();
    }
  }

  digitalWrite(statusLed, LOW);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(13,12); //SDA,SCL
  bmp.begin();


}
void loop()
{
float temp=bmp.readTemp();
float pres=bmp.readPressure();
float rh=htureadHumidity();



if(millis()- timeStamp > delayTime){
  postResults(temp,pres,rh);
  timeStamp=millis();
}
}
