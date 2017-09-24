#include "IoT.h"
#include "Arduino.h"


// TODO :
// => Revoir le mode config qui force la page de configuration...
// - Faire la page web de configuration du Broket et gérer le pubsub
// - Faire la page de configuration du AP

const String ESP_NAME = "PROTO_1";
unsigned long aliveCount = 0;

IoT* iot;

const int resetPin = 12;

unsigned long aliveTime;
unsigned int alivePause = 1000;

void requestReset() {
	iot->restart(true);
}

void handleAPConnectedEvent(const WiFiEventSoftAPModeStationConnected& event) {
	Serial.println("#IOT> A connection occurs on Access Point");
	Serial.print("#IOT> Mac: ");
	Serial.println(IoT::convertMacAddress((unsigned char *)event.mac));
	Serial.println();
}

void handleAPDisconnectedEvent(const WiFiEventSoftAPModeStationDisconnected& event) {
	Serial.println("#IOT> A disconnection occurs on Access Point");
	Serial.print("#IOT> Mac: ");
	Serial.println(IoT::convertMacAddress((unsigned char *)event.mac));
	Serial.println();
}

void handleStationConnectedEvent(const WiFiEventStationModeConnected& event) {
	Serial.println("#IOT> A connection occurs on station => ");
	Serial.print("#IOT> SSID: ");
	Serial.println(event.ssid);
	Serial.print("#IOT> Channel: ");
	Serial.println(event.channel);
	Serial.println();
}

void handleStationDisconnectedEvent(const WiFiEventStationModeDisconnected& event) {
	Serial.println("#IOT> A disconnection occurs on station => ");
	Serial.print("#IOT>SSID: ");
	Serial.println(event.ssid);
	Serial.println();
}



void configWebSiteStarted(IPAddress ip) {
	Serial.print("#IOT> ConfigWebSiteStarted with IP ");
	Serial.println(ip.toString());
}

void confirmWebSiteStarted(IPAddress ip) {
	Serial.print("#IOT> ConfirmWebSiteStarted with IP ");
	Serial.println(ip.toString());
}

void customWebSiteStarted(IPAddress ip) {
	Serial.print("#IOT> CustomWebSiteStarted with IP ");
	Serial.println(ip.toString());
}

void networkDisconnectRequest() {
	Serial.println("#IOT> networkDisconnectRequest");
}

void apConfigStoredEvent() {
	Serial.println("#IOT> webServerAPConfigStored");
}

void networkConfigStoredEvent() {
	Serial.println("#IOT> webServerNetworkConfigStored");
}

void brokerConfigStoredEvent() {
	Serial.println("#IOT> webServerBrokerConfigStored");
}

void webServerConfigDetetedEvent(const byte deletedConfig) {
	if (deletedConfig & IoT::ACCESS_POINT) {
		Serial.println("#IOT> AccessPoint config deleted");
	}
	if (deletedConfig & IoT::NETWORK) {
		Serial.println("#IOT> Network config deleted");
	}
	if (deletedConfig & IoT::BROKER) {
		Serial.println("#IOT> Broker config deleted");
	}
}


void pubSubCallback(char* topic, byte* payload, unsigned int length) {
	Serial.print("#IOT> PubSub callback on topic: ");
	Serial.print(topic);
	Serial.print(" = ");

	// Read the incomming message
	String mqttIncommingMsg = "";
	for (unsigned int i = 0; i < length; i++) {
		mqttIncommingMsg += (char)payload[i];
	}

	Serial.println(mqttIncommingMsg);
}

void setup()
{

	aliveTime = millis();

	pinMode(resetPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(resetPin), requestReset, FALLING);

	Serial.begin(115200);
	delay(1000);
	Serial.println(F("#IOT> Template sketch"));

	Serial.println(F("#IOT> Create the IoT instance"));
	iot = new IoT(ESP_NAME);
	iot->setLogLevel(IoT::LOG_FINE);
//	iot->setAPConnectedCallback(handleAPConnectedEvent);
//	iot->setAPDisconnectedCallback(handleAPDisconnectedEvent);
//	iot->setStationConnectedCallback(handleStationConnectedEvent);
//	iot->setStationDisconnectedCallback(handleStationDisconnectedEvent);

//	iot->onConfigWebSiteStarted(configWebSiteStarted);
//	iot->onConfirmWebSiteStarted(confirmWebSiteStarted);
//	iot->onCustomWebSiteStarted(customWebSiteStarted);

//	iot->onNetworkDisconnectRequest(networkDisconnectRequest);

	iot->onAPConfigStored(apConfigStoredEvent);
	iot->onNetworkConfigStored(networkConfigStoredEvent);
	iot->onBrokerConfigStored(brokerConfigStoredEvent);
	iot->onWebServerConfigDeleted(webServerConfigDetetedEvent);

	iot->createPubSubClient(pubSubCallback);
//	if (iot->mqttSubscribe("IOT/ESP_IN")) {
//		Serial.println("#IOT> Subscribe OK");
//	} else {
//		Serial.println("#IOT> Subscribe NOK");
//	}
}

bool firstLoop = true;

void loop()
{
	IoT::CONNECT_RESULT result = iot->autoConnect();
	switch (result) {
	case (IoT::AP_ERROR) :
		Serial.println("#INO> AccessPoint error");
	break;
	case (IoT::CONFIG_WS_STARTED) :
		Serial.println("#INO> Configuration site started");
	break;
	case(IoT::CONFIG_WS_UPDATED) :
		//Serial.println("#INO> Configuration site updated");
	break;
	case (IoT::CONFIG_WS_UPDATE_FAILED) :
		Serial.println("#INO> Configuration site update failed");
	break;
	case (IoT::NETWORK_CONNECTED) :
		Serial.println("#INO> Network connected");
	break;
	case (IoT::NETWORK_CONNECTION_FAILED) :
		Serial.println("#INO> Network connection failed");
	break;
	case (IoT::BROKER_CONNECTED) :
		Serial.println("#INO> Broker connected");
	break;
	case (IoT::BROKER_CONNECTION_FAILED) :
		Serial.println("#INO> Broker connectio failed");
	break;
	case (IoT::WS_AND_BROKER_UPDATED) :
		Serial.println("#INO> Broker and Web site updated");
	break;
	case (IoT::WS_UPDATE_FAILED) :
		Serial.println("#INO> Web site update failed");
	break;
	case (IoT::BROKER_UPDATE_FAILED) :
		Serial.println("#INO> Broker update failed");
	break;
	case (IoT::CONFIRM_WS_STARTED) :
		Serial.println("#INO> Confirmation web site started");
	break;
	case (IoT::CUSTOM_WS_STARTED) :
		Serial.println("#INO> Custom web site updated");
	break;
	}
	delay(500);

	uint16 potValue = system_adc_read();
//	Serial.print("#IOT> Position value: ");
//	Serial.println(potValue);
	if (iot->isNetworkConnected() && iot->isMQTTBrokerConnected()) {
		if (firstLoop) {
			firstLoop = false;
			String topic = "IOT/"+ESP_NAME+"/IN";
			if (iot->mqttSubscribe(topic)) {
				Serial.print("#IOT> Subscribe ");
				Serial.print(ESP_NAME);
				Serial.println(" OK");
			} else {
				Serial.print("#IOT> Subscribe ");
				Serial.print(ESP_NAME);
				Serial.println(" NOK");
			}
		}

		if (millis() >= aliveTime + alivePause) {
			aliveTime = millis();
			String topicAlive = "IOT/"+ESP_NAME+"/OUT/ALIVE";
			String msg = String(aliveCount);
			aliveCount++;
			iot->mqttPublish(topicAlive, msg);
		}

		String topicManip = "IOT/"+ESP_NAME+"/OUT/MANIP_POS";
		String msgManip = String(potValue);
		iot->mqttPublish(topicManip, msgManip);
	}




}
