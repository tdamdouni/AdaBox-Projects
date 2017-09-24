/*
 * Config.cpp
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#include "Config.h"

Config::Config() {

	this->fsMount = SPIFFS.begin();

}

Config::~Config() {
}

bool Config::isFSMount() const {
	return this->fsMount;
}

