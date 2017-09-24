/*
 * BrokerConfig.h
 *
 *  Created on: 21 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_BROKERCONFIG_H_
#define IOT_BROKERCONFIG_H_

#include "Config.h"

class BrokerConfig: public Config {
public:
	BrokerConfig(String clientUID = "");
	virtual ~BrokerConfig();

	void setMQTTServer(String _mqttServer);
	void setMQTTPort(String _mqttPort);
	void setMQTTUID(String _mqttUID);

	String getMQTTServer();
	String getMQTTPort();
	String getMQTTUID();

	bool load();
	bool save();

private:

	const String MQTT_CONFIG_FILE = "/mqttConfig.txt";

	String forcedMqttUID;

	String mqttServer;
	String mqttPort;
	String mqttUID;

};

#endif /* IOT_BROKERCONFIG_H_ */
