/*
 * Config.h
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_CONFIG_H_
#define IOT_CONFIG_H_

#include "FS.h"

class Config {
public:
	Config();
	virtual ~Config();

	bool isFSMount() const;

	virtual bool load() = 0;
	virtual bool save() = 0;

private:
	bool fsMount = false;
};

#endif /* IOT_CONFIG_H_ */
