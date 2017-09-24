/*
 * BrokerConfig.cpp
 *
 *  Created on: 21 déc. 2016
 *      Author: olamotte
 */

#include "BrokerConfig.h"

BrokerConfig::BrokerConfig(String clientUID) {
	this->load();
	this->forcedMqttUID = clientUID;
}

BrokerConfig::~BrokerConfig() {
}


void BrokerConfig::setMQTTServer(String _mqttServer) {
	this->mqttServer = _mqttServer;
}
void BrokerConfig::setMQTTPort(String _mqttPort) {
	this->mqttPort = _mqttPort;
}
void BrokerConfig::setMQTTUID(String _mqttUID) {
	this->mqttUID = _mqttUID;
}

String BrokerConfig::getMQTTServer() {

	String trimMqttServer = this->mqttServer;
	trimMqttServer.trim();
	return trimMqttServer;
}
String BrokerConfig::getMQTTPort() {
	String trimMqttPort = this->mqttPort;
	trimMqttPort.trim();
	return trimMqttPort;
}
String BrokerConfig::getMQTTUID() {
	if (forcedMqttUID.length() == 0) {
		String trimMqttUID = this->mqttUID;
		trimMqttUID.trim();
		return trimMqttUID;
	}
	return forcedMqttUID;
}

bool BrokerConfig::load() {
	if (this->isFSMount()) {
		File mqttConfigFile = SPIFFS.open(this->MQTT_CONFIG_FILE, "r");
		if (mqttConfigFile) {
			this->mqttServer = mqttConfigFile.readStringUntil('\n');
			this->mqttPort = mqttConfigFile.readStringUntil('\n');
			this->mqttUID = mqttConfigFile.readStringUntil('\n');
			mqttConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
bool BrokerConfig::save() {
	if (this->isFSMount()) {
		File mqttConfigFile = SPIFFS.open(this->MQTT_CONFIG_FILE, "w");
		if (mqttConfigFile) {
			mqttConfigFile.println(this->mqttServer);
			mqttConfigFile.println(this->mqttPort);
			mqttConfigFile.println(this->mqttUID);
			mqttConfigFile.flush();
			mqttConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
