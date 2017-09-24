/*
 * APConfig.h
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_APCONFIG_H_
#define IOT_APCONFIG_H_

#include "Config.h"

class APConfig : Config {
public:
	APConfig();
	APConfig(String _ssid);
	APConfig(String _ssid, String _pwd);
	virtual ~APConfig();

	void setSSID(String _ssid);
	void setPWD(String _pwd);

	String getSSID() const;
	String getPWD() const;

	bool load();
	bool save();

private:
	String ssid = "ESPAccessPoint";
	String pwd;

	String forcedSsid;
	String forcedPwd;

	const String AP_CONFIG_FILE = "/apConfig.txt";

	void init(String _ssid, String _pwd);
};

#endif /* IOT_APCONFIG_H_ */
