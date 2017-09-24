/*
 * NetworkConfig.h
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_NETWORKCONFIG_H_
#define IOT_NETWORKCONFIG_H_

#include "Config.h"

class NetworkConfig: public Config {
public:
	NetworkConfig();
	virtual ~NetworkConfig();

	void setSSID(String _ssid);
	void setPWD(String _pwd);
	void setUserNAME(String _userName);
	void setUserPWD(String _userPwd);

	String getSSID() const;
	String getPWD() const;
	String getUserNAME() const;
	String getUserPWD() const;

	bool load();
	bool save();

private:

	const String ESP_CONFIG_FILE = "/espConfig.txt";

	String ssid;
	String pwd;
	String userName;
	String userPwd;

};

#endif /* IOT_NETWORKCONFIG_H_ */
