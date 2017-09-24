/*
 * APConfig.cpp
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#include "APConfig.h"

APConfig::APConfig() {
	this->init("", "");
}
APConfig::APConfig(String _ssid) {
	this->init(_ssid, "");
}
APConfig::APConfig(String _ssid, String _pwd) {
	this->init(_ssid, _pwd);
}

void APConfig::init(String _ssid, String _pwd) {
	if (ssid.length() > 0) {
		this->forcedSsid = _ssid;
		this->forcedPwd = _pwd;
	} else {
		this->load();
	}
}

APConfig::~APConfig() {
}

void APConfig::setSSID(String _ssid) {
	this->ssid = _ssid;
}

void APConfig::setPWD(String _pwd) {
	this->pwd = _pwd;
}

String APConfig::getSSID() const {
	if (forcedSsid.length() == 0) {
		String trimSsid = this->ssid;
		trimSsid.trim();
		return trimSsid;
	}
	return forcedSsid;
}

String APConfig::getPWD() const {
	if (forcedPwd.length() == 0) {
		String trimPwd = this->pwd;
		trimPwd.trim();
		return trimPwd;
	}
	return forcedPwd;
}

bool APConfig::save() {
	if (this->isFSMount()) {
		File apConfigFile = SPIFFS.open(this->AP_CONFIG_FILE, "w");
		if (apConfigFile) {
			apConfigFile.println(this->ssid);
			apConfigFile.println(this->pwd);
			apConfigFile.flush();
			apConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool APConfig::load() {
	if (this->isFSMount()) {
		File apConfigFile = SPIFFS.open(this->AP_CONFIG_FILE, "r");
		if (apConfigFile) {
			this->ssid = apConfigFile.readStringUntil('\n');
			this->pwd = apConfigFile.readStringUntil('\n');
			apConfigFile.close();
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
