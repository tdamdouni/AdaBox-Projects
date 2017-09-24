/*
 * NetworkConfig.cpp
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#include "NetworkConfig.h"

NetworkConfig::NetworkConfig() {
	this->load();
}

NetworkConfig::~NetworkConfig() {
}


void NetworkConfig::setSSID(String _ssid) {
	this->ssid = _ssid;
}

void NetworkConfig::setPWD(String _pwd) {
	this->pwd = _pwd;
}

void NetworkConfig::setUserNAME(String _userName) {
	this->userName = _userName;
}

void NetworkConfig::setUserPWD(String _userPwd) {
	this->userPwd = _userPwd;
}


String NetworkConfig::getSSID() const {
	String trimSsid = this->ssid;
	trimSsid.trim();
	return trimSsid;
}

String NetworkConfig::getPWD() const  {
	String trimPwd = this->pwd;
	trimPwd.trim();
	return trimPwd;
}

String NetworkConfig::getUserNAME() const {
	String trimUserName = this->userName;
	trimUserName.trim();
	return trimUserName;
}

String NetworkConfig::getUserPWD() const {
	String trimUserPwd = this->userPwd;
	trimUserPwd.trim();
	return trimUserPwd;
}



bool NetworkConfig::load() {
	if (this->isFSMount()) {
		File espConfigFile = SPIFFS.open(this->ESP_CONFIG_FILE, "r");
		if (espConfigFile) {
			this->ssid = espConfigFile.readStringUntil('\n');
			this->pwd = espConfigFile.readStringUntil('\n');
			this->userName = espConfigFile.readStringUntil('\n');
			this->userPwd = espConfigFile.readStringUntil('\n');
			espConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool NetworkConfig::save() {
	if (this->isFSMount()) {
		File espConfigFile = SPIFFS.open(this->ESP_CONFIG_FILE, "w");
		if (espConfigFile) {
			espConfigFile.println(this->ssid);
			espConfigFile.println(this->pwd);
			espConfigFile.println(this->userName);
			espConfigFile.println(this->userPwd);
			espConfigFile.flush();
			espConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
