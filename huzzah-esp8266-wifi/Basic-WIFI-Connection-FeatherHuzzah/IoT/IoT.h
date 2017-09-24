/*
 * IoT.h
 *
 *  Created on: 18 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_H_
#define IOT_H_

#define DEFAULT_AP_SSID "ESPAccessPoint"
#define PGMSTR(x) (__FlashStringHelper*)(x)


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

extern "C"{
 #include "user_interface.h"
}

#include "APConfig.h"
#include "NetworkConfig.h"
#include "BrokerConfig.h"
#include "HTMLUtil.h"




class IoT {

public:

	const String VERSION = "1.0";

	// Enumeration of stored data type
	static const byte ACCESS_POINT = 00000001;
	static const byte NETWORK = 00000010;
	static const byte BROKER = 00000100;

	enum LOG_LEVEL {LOG_DEBUG = 6, LOG_FINEST = 5, LOG_FINE = 4, LOG_INFO = 3, LOG_WARNING = 2, LOG_ERROR = 1, LOG_OFF = -1};

	enum CONNECT_RESULT {AP_ERROR, 					// AccessPoint error
						 CONFIG_WS_STARTED, 		// Configuration site started
						 CONFIG_WS_UPDATED,			// Configuration site updated
						 CONFIG_WS_UPDATE_FAILED,	// Configuration site update failed
						 NETWORK_CONNECTED,			// Network connected
						 NETWORK_CONNECTION_FAILED, // Network connection failed
						 BROKER_CONNECTED,			// Broker connected
						 BROKER_CONNECTION_FAILED,	// Broker connection failed
						 WS_AND_BROKER_UPDATED,		// Broker and WebSite updated
						 WS_UPDATE_FAILED,			// Web site update failed
						 BROKER_UPDATE_FAILED,		// Broker update failed
						 CONFIRM_WS_STARTED,		// Confirmation web site started
						 CUSTOM_WS_STARTED};		// Custom web site started


	// IoT constructor
	//
	// Construct an instance of the IoT and load configuration previously stored if exists.
	//
	// _ap_ssid and _ap_pwd the ssid name and password to use for the access point if it's needed
	IoT(const String clientUID = "", LOG_LEVEL logLevel = LOG_ERROR, String _ap_ssid = DEFAULT_AP_SSID, String _ap_pwd = "", int _webServerPort = 80);
	virtual ~IoT();

	// Set the log level
	void setLogLevel(LOG_LEVEL level = LOG_OFF);


	// Try to connect the network with the stored configuration parameters.
	// If this connexion failed, the ESP switch in AccessPoint mode and provide a web wite for its configuration.
	// The access point ssid and password used are these given in parameters of the IoT constructor.
	// Otherwise, the previously stored parameters. And finally the default configuration.
	CONNECT_RESULT autoConnect(bool connectMQTTBroker = true);

	String getClientUID();

	bool createPubSubClient(void (*pubSubCallback)(char*, byte*, unsigned int));
	bool createPubSubClient(String serverIp, String port, String UID, void (*pubSubCallback)(char*, byte*, unsigned int));

	bool autoConnectPubSubClient();

	bool mqttSubscribe(String topic);
	bool mqttPublish(String topic, String payload);

	void displayConfirmationWebSite();
	void setCustomUserWebSite(void(*func)(std::unique_ptr<ESP8266WebServer> const));


	String getCurrentIP();


	// Delete configuration file of AccessPoint, Network, Broker
	bool resetConfig(byte const configToErase);

	// Restart the ESP
	// Note : after a sketch upload, the first restart doesn't work. The ESP must be restart manually for the first time.
	void restart(bool configMode = false);

	bool disconnectNetwork();

	bool isNetworkConnected();
	bool isMQTTBrokerConnected();

	//------------------------------------------------------------------------
	//		HANDLERS
	//------------------------------------------------------------------------
	void onConfigWebSiteStarted(void(*func)(IPAddress));
	void onConfirmWebSiteStarted(void(*func)(IPAddress));
	void onCustomWebSiteStarted(void(*func)(IPAddress));

	void onBrokerConnected(void(*func)(void));
	void onBrokerConnectionFailed(void(*func)(void));


	void onNetworkDisconnectRequest(void(*func)(void));
	void onRestartRequest(void(*func)(void));

	void onAPConfigStored(void(*func)(void));
	void onNetworkConfigStored(void(*func)(void));
	void onBrokerConfigStored(void(*func)(void));
	void onWebServerConfigDeleted(void(*func)(const byte));


	//------------------------------------------------------------------------
	//		CALLBACKS
	//------------------------------------------------------------------------
	// AP Station connected callback
	void setAPConnectedCallback( void (*func)(const WiFiEventSoftAPModeStationConnected& event));
	// AP Station disconnected callback
	void setAPDisconnectedCallback( void (*func)(const WiFiEventSoftAPModeStationDisconnected& event));
	// Station connected callback
	void setStationConnectedCallback( void (*func)(const WiFiEventStationModeConnected& event));
	// Station disconnected callback
	void setStationDisconnectedCallback( void (*func)(const WiFiEventStationModeDisconnected& event));

	// Format the mac address in a printable String
	static String convertMacAddress(uint8 mac[]) {
		String result;
		for (byte i = 0; i < 6; ++i) {
			char buf[3];
			sprintf(buf, "%02X", mac[i]);
			result += buf;
			if (i < 5) result += ':';
		}
		return result;
	}

private:

	HTMLUtil *util;

	WiFiClient wifiClient;
	PubSubClient *pubSub = NULL;

	int webServerPort;

	APConfig *apConfig;
	NetworkConfig *networkConfig;
	BrokerConfig *brokerConfig;

	std::unique_ptr<ESP8266WebServer> server = NULL;

	short pubSubConnectionTestCount;
	const short MAX_PUB_SUB_TEST_COUNT = 3;

	bool apActive = false;
	bool stationActive = false;
	bool configWebSiteActive = false;
	bool confirmOrCustomWebSiteActive = false;

	bool requestConfigMode = false;

	LOG_LEVEL level = LOG_OFF;
	void log(LOG_LEVEL msgLevel, String msg);
	void log(LOG_LEVEL msgLevel, String msg, String data);
	void logln(LOG_LEVEL msgLevel, String msg);
	void logln(LOG_LEVEL msgLevel, String msg, String data);
	void logln(LOG_LEVEL msgLevel, String msg, int data);


	// Start the ESP configuration web site
	void startConfigurationWebSite();

	// Start a default web site that inform on the connection status
	void startConfirmationWebSite();

	// Handle WebServer pages
	void handleRoot();
	String getMainMenuBody() const;
	void returnToRoot();

	void handleStartConfig();
	void handleDisconnectNetwork();
	void handleNotFound();

	void handleConfigNetwork();
	String getConfigNetworkBody() const;
	String getFillNetworkInfoScript() const;
	void handleSubmitNetworkConfig();

	void handleConfigBroker();
	String getFillConfigBrokerScript() const;
	String getConfigBrokerBody() const;
	void handleSubmitBrokerConfig();

	void handleChangeAPConfig();
	String getChangeAPConfigBody() const;
	String getFillAPInfoScript() const;
	void handleSubmitAPConfig();

	void handleCloseConfig();
	String getCloseConfigBody() const;

	void handleConfirmationRoot();
	String getConfirmationRootBody() const;

	void handleLogin();
	String getLoginBody() const;
	void returnToLogin();
  bool isAuthentified();

	// Return the custom we site or null
	void (*_displayCustomWebSite)(std::unique_ptr<ESP8266WebServer> server) = NULL;

	// Handle webServer event
	void (*_onConfigWebSiteStartedCallback)(IPAddress) = NULL;
	void (*_onConfirmWebSiteStartedCallback)(IPAddress) = NULL;
	void (*_onCustomWebSiteStartedCallback)(IPAddress) = NULL;

	void (*_onBrokerConnectedCallback)(void) = NULL;
	void (*_onBrokerConnectionFailedCallback)(void) = NULL;

	void (*_onNetworkDisconnectRequestCallback)(void) = NULL;

	void (*_onRestartRequestCallback)(void) = NULL;

	void (*_onAPConfigStoredCallback)(void) = NULL;
	void (*_onNetworkConfigStoredCallback)(void) = NULL;
	void (*_onBrokerConfigStoredCallback)(void) = NULL;
	void (*_onConfigDeletedCallback)(const byte) = NULL;

	// Handle AP Connected event
	void (*_apConnectedCallback)(const WiFiEventSoftAPModeStationConnected& event) = NULL;
	WiFiEventHandler wifiAPConnectedHandler;
	void handleWifiAPConnectedEvent(const WiFiEventSoftAPModeStationConnected& event);
	// Handle AP Disconnected event
	void (*_apDisconnectedCallback)(const WiFiEventSoftAPModeStationDisconnected& event) = NULL;
	WiFiEventHandler wifiAPDisconnectedHandler;
	void handleWifiAPDisconnectedEvent(const WiFiEventSoftAPModeStationDisconnected& event);
	// Handle Station Connected event
	void (*_stationConnectedCallback)(const WiFiEventStationModeConnected& event) = NULL;
	WiFiEventHandler wifiStationConnectedHandler;
	void handleWifiStationConnectedEvent(const WiFiEventStationModeConnected& event);
	// Handle Station Disconnected event
	void (*_stationDisconnectedCallback)(const WiFiEventStationModeDisconnected& event) = NULL;
	WiFiEventHandler wifiStationDisconnectedHandler;
	void handleWifiStationDisconnectedEvent(const WiFiEventStationModeDisconnected& event);
};

#endif /* IOT_H_ */