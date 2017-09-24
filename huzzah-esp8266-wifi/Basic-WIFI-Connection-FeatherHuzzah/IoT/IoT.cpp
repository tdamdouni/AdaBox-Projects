/*
 * IoT.cpp
 *
 *  Created on: 18 déc. 2016
 *      Author: olamotte
 */
#include "IoT.h"


IoT::IoT(const String clientUID, LOG_LEVEL logLevel, String _ap_ssid, String _ap_pwd, int _webServerPort) {

	this->setLogLevel(logLevel);

	webServerPort = _webServerPort;

	WiFi.setAutoConnect(false);

	util = new HTMLUtil(this->VERSION);

	apConfig = new APConfig(_ap_ssid, _ap_pwd);
	networkConfig = new NetworkConfig();
	brokerConfig = new BrokerConfig(clientUID);

	// Register wifi event handler
	wifiAPConnectedHandler = WiFi.onSoftAPModeStationConnected(std::bind(&IoT::handleWifiAPConnectedEvent, this, std::placeholders::_1));
	wifiAPDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(std::bind(&IoT::handleWifiAPDisconnectedEvent, this, std::placeholders::_1));
	wifiStationConnectedHandler = WiFi.onStationModeConnected(std::bind(&IoT::handleWifiStationConnectedEvent, this, std::placeholders::_1));
	wifiStationDisconnectedHandler = WiFi.onStationModeDisconnected(std::bind(&IoT::handleWifiStationDisconnectedEvent, this, std::placeholders::_1));

	// Configure the Wifi
	WiFi.mode(WIFI_AP_STA);
	WiFi.enableAP(false);
	WiFi.enableSTA(false);
}

IoT::~IoT() {
	delete apConfig;
	delete networkConfig;
}

String IoT::getClientUID() {
	return brokerConfig->getMQTTUID();
}

void IoT::setLogLevel(IoT::LOG_LEVEL level) {
	this->level = level;
}

void IoT::log(LOG_LEVEL msgLevel, String msg) {
	log(msgLevel, msg, "");
}
void IoT::log(LOG_LEVEL msgLevel, String msg, String data) {
	if (msgLevel == LOG_OFF) return;

	if (msgLevel <= this->level) {
		if (!msg.startsWith("[")) {
			if (msgLevel == LOG_DEBUG) Serial.print(F(">>>>>>>>>> [DEBUG]: "));
			if (msgLevel == LOG_ERROR) Serial.print(F("[ERROR]: "));
			if (msgLevel == LOG_WARNING) Serial.print(F("[WARNING]: "));
			if (msgLevel == LOG_INFO) Serial.print(F("[INFO]: "));
			if (msgLevel == LOG_FINE) Serial.print(F("[FINE]: "));
			if (msgLevel == LOG_FINEST) Serial.print(F("[FINEST]: "));
		}
		Serial.print(msg);
		Serial.print(data);
	}
}
void IoT::logln(LOG_LEVEL msgLevel, String msg) {
	logln(msgLevel, msg, "");
}
void IoT::logln(LOG_LEVEL msgLevel, String msg, String data) {
	if (msgLevel == LOG_OFF) return;
	log(msgLevel, msg, data);
	if (msgLevel <= this->level) Serial.println();
}
void IoT::logln(LOG_LEVEL msgLevel, String msg, int data) {
	if (msgLevel == LOG_OFF) return;
	log(msgLevel, msg, "");
	Serial.println(data);
	if (msgLevel <= this->level) Serial.println();
}


String IoT::getCurrentIP() {
	if (WiFi.status() == WL_CONNECTED) {
		if (WiFi.getMode() == WIFI_AP) {
			return WiFi.softAPIP().toString();
		}
		return WiFi.localIP().toString();
	}
	return "";
}


IoT::CONNECT_RESULT IoT::autoConnect(bool connectMQTTBroker) {

	logln(LOG_DEBUG, "WiFiStatus: ", (WiFi.status() == WL_CONNECTED) ? "CONNECTED" : "NOT CONNECTED");
	if (WiFi.status() == WL_CONNECTED) logln(LOG_DEBUG, "WiFi IP: ", WiFi.localIP().toString());
	logln(LOG_DEBUG, "pubSub: ", (pubSub != NULL) ? "NOT NULL" : "NULL");
	logln(LOG_DEBUG, "configWebSiteActive: ", (configWebSiteActive) ? "TRUE" : "FALSE");
	logln(LOG_DEBUG, "apActive: ", (apActive) ? "TRUE" : "FALSE");
	logln(LOG_DEBUG, "requestConfigMode: ", (requestConfigMode) ? "TRUE" : "FALSE");

	// Config mode requested
	if (requestConfigMode) {


		if (WiFi.status() == WL_CONNECTED) {
			WiFi.disconnect(false);
		}

		if (!apActive) {

			// We start the AccessPoint
			WiFi.mode(WIFI_AP);
			apActive = WiFi.softAP(apConfig->getSSID().c_str(), apConfig->getPWD().c_str(), 1, false);

			if (apActive) {
				logln(LOG_INFO, F("AP Started with IP : "), WiFi.softAPIP().toString());

				// We start the DNS
				if(!MDNS.begin("ESP", WiFi.softAPIP())) {
					logln(LOG_WARNING, F("DNS fail for AccessPoint !"));
				}

			} else {
				logln(LOG_ERROR, F("AP not started !"));
				return AP_ERROR;
			}
		}

		// Display configuration web site
		logln(LOG_INFO, F("Start configuration web site..."));

		// We start the configuration WebSite
		if (!configWebSiteActive) {
			startConfigurationWebSite();
			if (_onConfigWebSiteStartedCallback != NULL) {
				(*_onConfigWebSiteStartedCallback)(WiFi.softAPIP());
			}
			configWebSiteActive = true;

			logln(LOG_INFO, F("Configuration web site started with IP: "), WiFi.softAPIP().toString());

			// First update
			if (server != NULL) {
				server->handleClient();
			}
		}

		// To avoid entering in this part of code during the next loop
		requestConfigMode = false;

		return CONFIG_WS_STARTED;


	} else { // Not configuration mode request


		// We check if we can update web site and pubSub
		if (configWebSiteActive) {

			if (server != NULL) {
				server->handleClient();
				logln(LOG_FINEST, F("Configuration web site updated !"));
				return CONFIG_WS_UPDATED;
			}
			logln(LOG_ERROR, F("Update configuration web site failed..."));
			requestConfigMode = true;
			return CONFIG_WS_UPDATE_FAILED;
		}


		if (WiFi.status() != WL_CONNECTED) { // We are not connected to the Network

			// We try to connect network
			WiFi.mode(WIFI_STA);

			String ssid = networkConfig->getSSID();
			String pwd = networkConfig->getPWD();

			logln(LOG_INFO, F("Try to connect network : "));
			logln(LOG_INFO, F("  - SSID="), ssid);
			logln(LOG_INFO, F("  - PWD="), pwd);

			WiFi.begin(ssid.c_str(), pwd.c_str());

			if (WiFi.waitForConnectResult() == WL_CONNECTED) { // If we are connected

				logln(LOG_INFO, F("Network connected with IP : "), WiFi.localIP().toString());

				if (apActive) {
					logln(LOG_FINE, F("Disable AP..."));
					WiFi.enableAP(false);
					apActive = false;
				}

				return IoT::NETWORK_CONNECTED;

			} else { // If we are not connected
				requestConfigMode = true;
				return IoT::NETWORK_CONNECTION_FAILED;
			}

		} else { // We are connected

			// We check if we are connected to the mqtt broker
			if (pubSub->connected()) {
				logln(LOG_FINEST, F("MQTT Callback updated !"));
				// Update pubSub
				pubSub->loop(); // First update loop


				// Start the confirmation or user's custom web site
				if (!confirmOrCustomWebSiteActive) {

					CONNECT_RESULT result;


					// Check if a custom web site exists
					if (_displayCustomWebSite != NULL) {
						logln(LOG_INFO, F("Custom web site exists, try to launch it..."));

						(*_displayCustomWebSite)(std::move(server));

						logln(LOG_INFO, F("Custom web site launched !"));

						if (_onCustomWebSiteStartedCallback != NULL) {
							(*_onCustomWebSiteStartedCallback)(WiFi.localIP());
						}

						result = CUSTOM_WS_STARTED;

					} else {
						logln(LOG_INFO, F("Try to launch confirmation web site..."));

						startConfirmationWebSite();

						logln(LOG_INFO, F("Confirmation web site launched !"));

						if (_onConfirmWebSiteStartedCallback != NULL) {
							(*_onConfirmWebSiteStartedCallback)(WiFi.localIP());
						}

						result = CONFIRM_WS_STARTED;
					}


					confirmOrCustomWebSiteActive = true;
					return result;

				}

				server->handleClient();
				logln(LOG_FINEST, F("Broker and WebSite updated !"));
				return WS_AND_BROKER_UPDATED;

			} else {
				logln(LOG_FINE, F("Try to connect PubSub client..."));

				while (pubSubConnectionTestCount < MAX_PUB_SUB_TEST_COUNT && !pubSub->connected()) {
					logln(LOG_WARNING, "Trying connect MQTT Broker: ", pubSubConnectionTestCount);
					if (!autoConnectPubSubClient()) {
						pubSubConnectionTestCount++;
					}
					delay(500);
				}

				if (pubSubConnectionTestCount >= MAX_PUB_SUB_TEST_COUNT) {
					pubSubConnectionTestCount = 0;
					requestConfigMode = true;
					return IoT::BROKER_CONNECTION_FAILED;
				} else {
					logln(LOG_FINE, F("Broker connected !"));
					return BROKER_CONNECTED;
				}
			}

		}
	}
}

bool IoT::createPubSubClient(void (*pubSubCallback)(char*, byte*, unsigned int)) {
	return createPubSubClient(brokerConfig->getMQTTServer(), brokerConfig->getMQTTPort(), brokerConfig->getMQTTUID(), pubSubCallback);
}

bool IoT::createPubSubClient(String serverIp, String port, String UID, void (*pubSubCallback)(char*, byte*, unsigned int)) {
	if (pubSubCallback == NULL) return false;

	if (this->pubSub == NULL) {
		logln(LOG_INFO, F("Configure MQTT Broker..."));

		IPAddress brokerIp;
		brokerIp.fromString(brokerConfig->getMQTTServer());

		logln(LOG_FINE, "Broker server ip ", brokerIp.toString());
		logln(LOG_FINE, "Broker port ", brokerConfig->getMQTTPort().toInt());

		this->pubSub = new PubSubClient(brokerIp, brokerConfig->getMQTTPort().toInt(), pubSubCallback, wifiClient);

		if (pubSub != NULL) {
			logln(LOG_INFO, "MQTT Broker configured!");
		} else {
			logln(LOG_ERROR, "MQTT Broker configuration failed!");
			return false;
		}
	}
	return true;
}

bool IoT::autoConnectPubSubClient() {

	if (pubSub != NULL && !pubSub->connected()) {

		pubSub->connect(brokerConfig->getMQTTUID().c_str());

		int state = pubSub->state();

		if (state != MQTT_CONNECTED) {
			switch (state) {
			case(MQTT_CONNECT_FAILED) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_FAILED");
			break;
			case(MQTT_CONNECTION_TIMEOUT) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECTION_TIMEOUT");
			break;
			case(MQTT_CONNECT_UNAUTHORIZED) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_UNAUTHORIZED");
			break;
			case(MQTT_CONNECT_UNAVAILABLE) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_UNAVAILABLE");
			break;
			case(MQTT_CONNECT_BAD_CLIENT_ID) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_BAD_CLIENT_ID");
			break;
			case(MQTT_CONNECT_BAD_CREDENTIALS) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_BAD_CREDENTIALS");
			break;
			case(MQTT_CONNECT_BAD_PROTOCOL) :
																	logln(LOG_ERROR, "Connect Broker Error ", "MQTT_CONNECT_BAD_PROTOCOL");
			break;
			default:
				logln(LOG_ERROR, "Connect Broker Error");
				break;
			}
			(*_onBrokerConnectionFailedCallback)();
		} else {
			logln(LOG_INFO, "MQTTBroker connected");
			(*_onBrokerConnectedCallback)();
			return true;
		}

		return false;
	}

	return true;
}

bool IoT::mqttSubscribe(String topic) {
	return pubSub->subscribe(topic.c_str());
}
bool IoT::mqttPublish(String topic, String payload) {
	return pubSub->publish(topic.c_str(), payload.c_str());
}


bool IoT::disconnectNetwork() {
	configWebSiteActive = false;
	confirmOrCustomWebSiteActive = false;
	return WiFi.disconnect(false);
}

void IoT::startConfigurationWebSite() {

	server.reset(new ESP8266WebServer(webServerPort));

	server->on("/", std::bind(&IoT::handleRoot, this)); //Main frame
	server->on("/login", std::bind(&IoT::handleLogin, this)); //Login frame
	server->on("/configNetwork", std::bind(&IoT::handleConfigNetwork, this));
	server->on("/configBroker", std::bind(&IoT::handleConfigBroker, this));

	server->on("/submitNetworkConfig", std::bind(&IoT::handleSubmitNetworkConfig, this));

	server->on("/changeAPConfig", std::bind(&IoT::handleChangeAPConfig, this));
	server->on("/closeConfig", std::bind(&IoT::handleCloseConfig, this));

	server->on("/submitAPConfig", std::bind(&IoT::handleSubmitAPConfig, this));

	server->on("/submitBrokerConfig", std::bind(&IoT::handleSubmitBrokerConfig, this));

	server->onNotFound(std::bind(&IoT::handleNotFound, this));

  const char * headerKeys[] = {"Cookie"};
  size_t headerKeysSize = sizeof(headerKeys)/sizeof(char*);
  server->collectHeaders(headerKeys, headerKeysSize);
	server->begin();

}

void IoT::setCustomUserWebSite(void(*func)(std::unique_ptr<ESP8266WebServer> const)) {
	_displayCustomWebSite = func;
}

bool IoT::isNetworkConnected() {
	return WiFi.status() == WL_CONNECTED;
}
bool IoT::isMQTTBrokerConnected() {
	return pubSub != NULL && pubSub->connected();
}


bool IoT::resetConfig(byte const config) {

	bool resultAP = false;
	if (config & ACCESS_POINT) {
		apConfig->setSSID(DEFAULT_AP_SSID);
		apConfig->setPWD("");
		resultAP = apConfig->save();
	}

	bool resultNetwork = false;
	if (config & NETWORK) {
		networkConfig->setSSID("");
		networkConfig->setPWD("");
		networkConfig->setUserNAME("");
		networkConfig->setUserPWD("");
		resultNetwork = networkConfig->save();
	}

	bool resultBroker = false;
	if (config & BROKER) {
		brokerConfig->setMQTTServer("");
		brokerConfig->setMQTTPort("");
		brokerConfig->setMQTTUID("");
		resultBroker = brokerConfig->save();
	}

	if (_onConfigDeletedCallback != NULL) {
		byte deleted = 00000000;
		if (resultAP) {
			deleted = deleted | IoT::ACCESS_POINT;
		}
		if (resultNetwork) {
			deleted = deleted | IoT::NETWORK;
		}
		if (resultBroker) {
			deleted = deleted | IoT::BROKER;
		}

		if (resultAP || resultNetwork || resultBroker) {
			(*_onConfigDeletedCallback)(deleted);
		}
	}

	return resultAP || resultNetwork || resultBroker;
}


void IoT::restart(bool configMode) {
	if (_onRestartRequestCallback) {
		(*_onRestartRequestCallback)();
	}
	requestConfigMode = configMode;
	ESP.restart();
}



// ----------------------------------------------------------------------------
// MAIN ROOT FRAME
// ----------------------------------------------------------------------------
/**
 * Handle the root
 */
void IoT::handleRoot() {
	if(!isAuthentified()){
		returnToLogin();
    return;
	}
	String message = util->getHtmlHeader();   // Html
	message += util->getHeader();       		// Header
	message += util->getCSSStyle();     		// CSS Style
	message += util->getCloseHeader();  		// Close Header
	message += getMainMenuBody(); 			// Body
	message += util->getCloseHtmlHeader();    // Close Html
	server->send(200, F("text/html"), message);
}
/**
 * Main Menu Frame Body
 */
String IoT::getMainMenuBody() const {
	String body = F("<body>");

	body += util->getBodyHeader("ESP8266 Config");

	body += F("<fieldset><legend>Configuration</legend>");
	body += F("<form action=\"/configBroker\" method=\"post\"><button type=\"submit\">Configuration Broker MQTT</button></form>");
	body += F("<form action=\"/configNetwork\" method=\"post\"><button type=\"submit\">Configuration réseau</button></form>");
	body += F("<form action=\"/changeAPConfig\" method=\"post\"><button type=\"submit\">Configuration AP</font></button></form>");
	body += F("<form action=\"/closeConfig\" method=\"post\"><button type=\"submit\">Redémarrer ESP</font></button></form>");
	body += F("</fieldset>");

	// Détail de l'ESP
	
	body += F("<fieldset><legend>Informations</legend>");
	body += F("<div align=\"center\"><details>");
	body += F("<summary>Informations ESP</summary><ul>");
	body += F("<li>Adresse MAC: ");
	body += WiFi.softAPmacAddress();
	body += F("</li>");
	body += F("<li>Adresse IP: ");
	body += WiFi.softAPIP();
	body += F("</li>");
	body += F("<li>Version SDK: ");
	body += ESP.getSdkVersion();
	body += F("</li>");
	body += F("<li>Cadence CPU: ");
	body += ESP.getCpuFreqMHz();
	body += F("</li>");
	body += F("<li>Espace libre sketch: ");
	body += ESP.getFreeSketchSpace();
	body += F("</li>");
	body += F("<li>Espace libre dans la pile: ");
	body += ESP.getFreeHeap();
	body += F("</li>");
	body += F("<li>Vcc: ");
	body += ESP.getVcc();
	body += F("</li>");
	body += F("</ul></details></div>");
	body += F("</fieldset>");

	//Lien de d�connexion
	body+= F("<fieldset><a href=\"/login?DISCONNECT=YES\">Déconnexion</a></fieldset>");

	// Footer
	body += F("<footer>");
	body += util->getVersionTag();
	body += F("</footer>");
	body += F("</body>");
	return body;
}

void IoT::returnToRoot(){
  server->sendHeader("Location", "/");
  server->sendHeader("Cache-Control", "no-cache");
  server->send(301);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// ConfigNetwork frame
// ----------------------------------------------------------------------------
void IoT::handleConfigNetwork() {
	if(!isAuthentified()){
		returnToLogin();
	}else{
	  String message = util->getHtmlHeader();
	  message += util->getHeader();
	  message += util->getJavaScript();
	  message += "\n";
	  message += getFillNetworkInfoScript();
	  message += "\n";
	  message += util->getCloseJavaScript();
	  message += util->getCSSStyle();
	  message += util->getCloseHeader();
	  message += getConfigNetworkBody();
	  message += util->getCloseHtmlHeader();
	  server->send(200, F("text/html"), message);
	}
}
String IoT::getConfigNetworkBody() const {
	String body = F("<body onload=\"fillNetworkInfo()\">");
  body += util->getBodyHeader("Configuration manuelle");
	body += F("<form name=\"formNetwork\" action=\"/submitNetworkConfig\">");
	body += F("<fieldset><legend>Configuration réseau</legend>");

	// Existing scanned networks
	body += F("<Fieldset><legend>Réseaux détectés</legend>");
	int numSsid = WiFi.scanNetworks();
	if (numSsid == -1) {
		body += F("<div style=\"text-align: center;\">Aucun réseau à portée...</div>");
	} else {
		for (int netIdx = 0; netIdx < numSsid; netIdx++) {
			body += F("<a href=\"#\" onclick=\"document.getElementById(&apos;ssid&apos;).value=&apos;");
			body += ((ESP8266WiFiScanClass)WiFi).SSID(netIdx);
			body += F("&apos;; document.getElementById(&apos;btSvgNetwork&apos;).disabled=false;\">");
			body += ((ESP8266WiFiScanClass)WiFi).SSID(netIdx);
			body += F("</a></br>");
		}
	}
	body += F("</fieldset><br />");

	// Network field
	body += F("<div><label for=\"ssid\">SSID: </label><input type=\"text\" size=\"30\" name=\"ssid\" id=\"ssid\"><br /></div>");
	body += F("<div><label for=\"pwd\">Mot de passe: </label>");
	body += F("<input type=\"password\" size=\"30\" name=\"pwd\" id=\"pwd\">");
	body += F("<input type=\"checkbox\" onchange=\"document.getElementById(&apos;pwd&apos;).type = this.checked ? &apos;text&apos; : &apos;password&apos;\"> Afficher...</div></fieldset>");

	// Authentification field
	body += F("<fieldset><legend>Authentification de l&apos;utilisateur <font size=\"1pt\">(optionnel)</font></legend>");
	body += F("<div><label for=\"userLogin\">Login utilisateur: </label><input type=\"text\" size=\"30\" name=\"userLogin\" id=\"userLogin\"><br /></div>");
	body += F("<div><label for=\"userPwd\">Mot de passe: </label><input type=\"password\" size=\"30\" name=\"userPwd\" id=\"userPwd\">");
	body += F("<input type=\"checkbox\" onchange=\"document.getElementById(&apos;userPwd&apos;).type = this.checked ? &apos;text&apos; : &apos;password&apos;\"> Afficher...<br /></div></fieldset>");

	body += F("<div style=\"text-align: center;\"><button type=\"submit\" id=\"btSvgNetwork\">Sauvegarder et connecter</button></div>");
	body += F("<div style=\"text-align: center;\"><button type=\"reset\">Tout effacer</div></form><br />");
	body += util->getBodyFooter();
	body += F("</body>");
	return body;
}
String IoT::getFillNetworkInfoScript() const {
	String script = F("function fillNetworkInfo() {");

	script += F(" document.getElementById('ssid').value = '");
	script += networkConfig->getSSID();
	script += F("';");

	script += F(" document.getElementById('pwd').value = '");
	script += networkConfig->getPWD();
	script += F("';");

	script += F(" document.getElementById('userLogin').value = '");
	script += networkConfig->getUserNAME();
	script += F("';");

	script += F(" document.getElementById('userPwd').value = '");
	script += networkConfig->getUserPWD();
	script += F("';");

	script += F("}");

	return script;
}
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
// Configure Broker frame
// ----------------------------------------------------------------------------
void IoT::handleConfigBroker() {
	if(!isAuthentified()){
		returnToLogin();
	}else{
	  String message = util->getHtmlHeader();
	  message += util->getHeader();
	  message += util->getJavaScript();
	  message += getFillConfigBrokerScript();
	  message += util->getCloseJavaScript();
	  message += util->getCSSStyle();
	  message += util->getCloseHeader();
	  message += getConfigBrokerBody();
	  message += util->getCloseHtmlHeader();
	  server->send(200, F("text/html"), message);
	}
}
String IoT::getFillConfigBrokerScript() const {
	String script = F("function fillBrokerInfo() {");

	script += F(" document.getElementById('MQTTServer').value = '");
	String ssidTmp = brokerConfig->getMQTTServer();
	script += ssidTmp;
	script += F("';");

	script += F(" document.getElementById('MQTTPort').value = '");
	script += brokerConfig->getMQTTPort();
	script += F("';");

	script += F(" document.getElementById('MQTTUID').value = '");
	script += brokerConfig->getMQTTUID();
	script += F("';");

	script += F("}");

	return script;
}
String IoT::getConfigBrokerBody() const {
	String body = F("<body onload=\"fillBrokerInfo()\">");
  body += util->getBodyHeader("Configuration du broker MQTT");
	body += F("<form name=\"formBroker\" action=\"/submitBrokerConfig\">");
	body += F("<fieldset><legend>Paramètres</legend>");
	body += F("<div><label for=\"MQTTServer\">IP du server: </label><input type=\"text\" size=\"30\" name=\"MQTTServer\" id=\"MQTTServer\"><br /></div>");
	body += F("<div><label for=\"MQTTPort\">Port: </label><input type=\"text\" size=\"30\" name=\"MQTTPort\" id=\"MQTTPort\"><br /></div>");
	body += F("<div><label for=\"MQTTUID\">UID: </label><input type=\"text\" size=\"30\" name=\"MQTTUID\" id=\"MQTTUID\"><br /></div></fieldset>");
	body += F("<div style=\"text-align: center;\"><button type=\"submit\" id=\"btSvgBroker\">Sauvegarder</button></div>");
	body += F("<div style=\"text-align: center;\"><button type=\"reset\">Tout effacer</div></form><br />");
	body += util->getBodyFooter();
	body += F("</body>");
	return body;
}
void IoT::handleSubmitBrokerConfig() {
	// Get submit arguments value
	brokerConfig->setMQTTServer(server->arg("MQTTServer"));
	brokerConfig->setMQTTPort(server->arg("MQTTPort"));
	brokerConfig->setMQTTUID(server->arg("MQTTUID"));

	if (brokerConfig->save()) {
		if (_onBrokerConfigStoredCallback != NULL) {
			(*_onBrokerConfigStoredCallback)();
		}
	}

	String message = util->getConfirmationFrame("Configuration enregistrée", "Vous devez redémarer l'ESP pour appliquer les modifications");
	server->send(200, F("text/html"), message);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Close Config frame
// ----------------------------------------------------------------------------
void IoT::handleSubmitNetworkConfig() {
	// Get submit arguments value
	networkConfig->setSSID(server->arg("ssid"));
	networkConfig->setPWD(server->arg("pwd"));
	networkConfig->setUserNAME(server->arg("userLogin"));
	networkConfig->setUserPWD(server->arg("userPwd"));

	if (networkConfig->save()) {
		if (_onNetworkConfigStoredCallback != NULL) {
			(*_onNetworkConfigStoredCallback)();
		}
	}

	String message = util->getConfirmationFrame("Configuration enregistrée", "Vous devez redémarer l'ESP pour appliquer les modifications");
	server->send(200, F("text/html"), message);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Close Config frame
// ----------------------------------------------------------------------------
void IoT::handleCloseConfig() {
	configWebSiteActive = false;
	apActive = false;
	restart();
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Page not found frame
// ----------------------------------------------------------------------------
void IoT::handleNotFound() {
	server->send(404, F("text/html"), F("<html><body><h1>Not found !</h1></body></html>"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Login frame
// ----------------------------------------------------------------------------
void IoT::handleLogin(){
  if (server->hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server->header("Cookie");
    Serial.println(cookie);
  }
  if (server->hasArg("DISCONNECT")){
    Serial.println("Disconnection");
    server->sendHeader("Location","/login");
    server->sendHeader("Cache-Control","no-cache");
    server->sendHeader("Set-Cookie","ESPSESSIONID=0");
    server->send(301);
    return;
  }
  if (server->hasArg("LOGIN_USERNAME") && server->hasArg("LOGIN_PASSWORD")){
    if (server->arg("LOGIN_USERNAME") == networkConfig->getUserNAME() &&  server->arg("LOGIN_PASSWORD") == networkConfig->getUserPWD() ){
      server->sendHeader("Location","/");
      server->sendHeader("Cache-Control","no-cache");
      server->sendHeader("Set-Cookie","ESPSESSIONID=1");
      server->send(301);
      Serial.println("Log in Successful");
      return;
    }
  Serial.println("Log in Failed");
  }
  String message = util->getHtmlHeader();
  message += util->getHeader();
  message += util->getCSSStyle();
  message += util->getCloseHeader();
  message += getLoginBody();
  message += util->getCloseHtmlHeader();
  server->send(200, F("text/html"), message);

}

String IoT::getLoginBody() const {

	String body = util->getBodyHeader("Identification");
	body += F("<form name=\"formLogin\" action=\"/login\"method=\"POST\">");
	body += F("<fieldset><legend>Identifiants</legend>");
	body += F("<div><label for=\"LOGIN_USERNAME\">Nom d'utilisateur : </label><input type=\"text\" size=\"30\" name=\"LOGIN_USERNAME\" id=\"LOGIN_USERNAME\"><br /></div>");
	body += F("<div><label for=\"LOGIN_PASSWORD\">Mot de passe: </label><input type=\"password\" size=\"30\" name=\"LOGIN_PASSWORD\" id=\"LOGIN_PASSWORD\"><br /></div></fieldset>");
	body += F("<div style=\"text-align: center;\"><button type=\"submit\" id=\"btLogin\">Valider</button></div>");
	body += F("<div style=\"text-align: center;\"><button type=\"reset\">Effacer</div></form><br />");// Footer
	body += F("<footer>");
	body += util->getVersionTag();
	body += F("</footer>");
	body += F("</body>");
	return body;
}

bool IoT::isAuthentified(){
  Serial.println("Enter is_authentified");
  if (server->hasHeader("Cookie") || server->hasHeader("Set_Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server->header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

void IoT::returnToLogin(){
	server->sendHeader("Location", "/login");
  server->sendHeader("Cache-Control", "no-cache");
  server->send(301);
}
// ----------------------------------------------------------------------------

void IoT::handleConfirmationRoot() {
	if(!isAuthentified()){
		returnToLogin();
	}else{
	String message = util->getHtmlHeader();
	message += util->getHeader();
	message += util->getCSSStyle();
	message += util->getCloseHeader();
	message += getConfirmationRootBody();
	message += util->getCloseHtmlHeader();
	server->send(200, F("text/html"), message);
	}
}
String IoT::getConfirmationRootBody() const {
	String body = util->getBodyHeader("Connexion établie");
	body += F("<fieldset><legend>Information réseau</legend>");

	body += F("<div>SSID: ");
	body += WiFi.SSID();
	body += F("<br /></div>");

	body += F("<div>IP: ");
	body += WiFi.localIP().toString();
	body += F("<br /></div>");

	body += F("</fieldset>");
	body += F("<form action=\"/disconnectNetwork\" method=\"post\"><button type=\"submit\"><font size=2pt>Déconnexion...</font></button></form>");
	body += F("<form action=\"/startConfig\" method=\"post\"><button type=\"submit\"><font size=2pt>Configuration...</font></button></form>");

	// Footer
	body += F("<footer>");
	body += util->getVersionTag();
	body += F("</body>");
	return body;
}

void IoT::handleDisconnectNetwork() {
	if (_onNetworkDisconnectRequestCallback) {
		(*_onNetworkDisconnectRequestCallback)();
	}
	server->send(200, F("text/html"), F("<html><body><h1>Déconnecté...</h1></body></html>"));
	WiFi.disconnect(false);
	configWebSiteActive = false;
	confirmOrCustomWebSiteActive = false;
}

void IoT::handleStartConfig() {
	String body = F("<html><body><h1>Site de configuration démarré, actualisez la page...</h1><br />");
	body += F("<form action=\"/\" method=\"post\"><button type=\"submit\"><font size=2pt>REFRESH</font></button></form>");
	body += F("</body></html>");

	server->send(200, F("text/html"), body);
	requestConfigMode = true;
	configWebSiteActive = false;
	confirmOrCustomWebSiteActive = false;
}

void IoT::handleChangeAPConfig() {
	if(!isAuthentified()){
		returnToLogin();
	}else{
	String message = util->getHtmlHeader();
	message += util->getHeader();
	message += util->getJavaScript();
	message += getFillAPInfoScript();
	message += util->getCloseJavaScript();
	message += util->getCSSStyle();
	message += util->getCloseHeader();
	message += getChangeAPConfigBody();
	message += util->getCloseHtmlHeader();
	server->send(200, F("text/html"), message);
	}
}
String IoT::getFillAPInfoScript() const {
	String script = F("function fillAPInfo() {");

	script += F(" document.getElementById('ssid').value = '");
	script += apConfig->getSSID();
	script += F("';");

	script += F(" document.getElementById('pwd').value = '");
	script += apConfig->getPWD();
	script += F("';");

	script += F("}");

	return script;
}
String IoT::getChangeAPConfigBody() const {
	String body = F("<body onload=\"fillAPInfo()\">");
	body += util->getBodyHeader("Configuration de l&apos;AccessPoint");
	body += F("<form name=\"formNetwork\" action=\"/submitAPConfig\">");
	body += F("<fieldset><legend>Information de connection</legend>");
	body += F("<div><label for=\"ssid\">SSID: </label><input type=\"text\" size=\"30\" name=\"ssid\" id=\"ssid\"><br /></div>");
	body += F("<div><label for=\"pwd\">Mot de passe: </label>");
	body += F("<input type=\"password\" size=\"30\" name=\"pwd\" id=\"pwd\">");
	body += F("<input type=\"checkbox\" onchange=\"document.getElementById(&apos;pwd&apos;).type = this.checked ? &apos;text&apos; : &apos;password&apos;\"> Afficher...</div></fieldset>");
	body += F("<div style=\"text-align: center;\"><button type=\"submit\" id=\"btSvgNetwork\">Sauvegarder et connecter</button></div>");
	body += F("<div style=\"text-align: center;\"><button type=\"reset\">Tout effacer</div></form><br />");
	body += util->getBodyFooter();
	body += F("</body>");
	return body;
}

void IoT::handleSubmitAPConfig() {
	// Get submit arguments value
	apConfig->setSSID(server->arg("ssid"));
	apConfig->setPWD(server->arg("pwd"));

	if (apConfig->save()) {
		if (_onAPConfigStoredCallback != NULL) {
			(*_onAPConfigStoredCallback)();
		}
	}

	String message = util->getConfirmationFrame("Configuration enregistrée", "Vous devez redémarer l'ESP pour appliquer les modifications");
	server->send(200, F("text/html"), message);
}

void IoT::startConfirmationWebSite() {

	server.reset(new ESP8266WebServer(webServerPort));

	server->on("/", std::bind(&IoT::handleConfirmationRoot, this));	// Main Confirmation Frame
	server->on("/disconnectNetwork", std::bind(&IoT::handleDisconnectNetwork, this));
	server->on("/startConfig", std::bind(&IoT::handleStartConfig, this));

	server->begin();

}


// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Manage WebServer event
// ----------------------------------------------------------------------------
void IoT::onConfigWebSiteStarted(void(*func)(IPAddress)) {
	_onConfigWebSiteStartedCallback = func;
}

void IoT::onConfirmWebSiteStarted(void(*func)(IPAddress)) {
	_onConfirmWebSiteStartedCallback = func;
}

void IoT::onCustomWebSiteStarted(void(*func)(IPAddress)) {
	_onCustomWebSiteStartedCallback = func;
}

void IoT::onBrokerConnected(void(*func)(void)) {
	_onBrokerConnectedCallback = func;
}

void IoT::onBrokerConnectionFailed(void(*func)(void)) {
	_onBrokerConnectionFailedCallback = func;
}

void IoT::onNetworkDisconnectRequest(void(*func)(void)) {
	_onNetworkDisconnectRequestCallback = func;
}

void IoT::onRestartRequest(void(*func)(void)) {
	_onRestartRequestCallback = func;
}

void IoT::onAPConfigStored(void(*func)(void)) {
	_onAPConfigStoredCallback = func;
}
void IoT::onNetworkConfigStored(void(*func)(void)) {
	_onNetworkConfigStoredCallback = func;
}
void IoT::onBrokerConfigStored(void(*func)(void)) {
	_onBrokerConfigStoredCallback = func;
}
void IoT::onWebServerConfigDeleted(void(*func)(const byte)) {
	_onConfigDeletedCallback = func;
}
// ----------------------------------------------------------------------------





// ----------------------------------------------------------------------------
// Manage wifi event
// ----------------------------------------------------------------------------
void IoT::handleWifiAPConnectedEvent(const WiFiEventSoftAPModeStationConnected& event) {
	if (_apConnectedCallback != NULL) {
		(*_apConnectedCallback)(event);
	}
}
void IoT::handleWifiAPDisconnectedEvent(const WiFiEventSoftAPModeStationDisconnected& event) {
	if (_apDisconnectedCallback != NULL) {
		(*_apDisconnectedCallback)(event);
	}
}
void IoT::handleWifiStationConnectedEvent(const WiFiEventStationModeConnected& event) {
	if (_stationConnectedCallback != NULL) {
		(*_stationConnectedCallback)(event);
	}
}
void IoT::handleWifiStationDisconnectedEvent(const WiFiEventStationModeDisconnected& event) {
	if (_stationDisconnectedCallback != NULL) {
		(*_stationDisconnectedCallback)(event);
	}
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// Wifi Handler
// ----------------------------------------------------------------------------
void IoT::setAPConnectedCallback( void (*func)(const WiFiEventSoftAPModeStationConnected& event)) {
	_apConnectedCallback = func;
}
void IoT::setAPDisconnectedCallback( void (*func)(const WiFiEventSoftAPModeStationDisconnected& event)) {
	_apDisconnectedCallback = func;
}
void IoT::setStationConnectedCallback( void (*func)(const WiFiEventStationModeConnected& event)) {
	_stationConnectedCallback = func;
}
void IoT::setStationDisconnectedCallback( void (*func)(const WiFiEventStationModeDisconnected& event)) {
	_stationDisconnectedCallback = func;
}
// ---------------------------------------------------------------------------
