/**
 * Variable Defines for Feather OLED Temp
 * Created by Joseph D. Harry, January 31, 2017.
 * Released GPL 3
 */

#include "Pubvars.h"

/**
 * Getters
 */

const char* Varstore::readSSID(){
    return _ssid;
}

const char* Varstore::readPassword(){
    return _password;
}

const char* Varstore::readDeviceName(){
    return _deviceName;
}

const int Varstore::readDeviceID(){
    return _deviceID;
}

const int Varstore::readButtonPinIP(){
    return _buttonPinIP;
}

const int Varstore::readButtonPinTemp(){
    return _buttonPinTemp;
}

const int Varstore::readButtonPinDisplay(){
    return _buttonPinDisplay;
}

const int Varstore::readServerPort(){
    return _webServerPort;
}

/**
 * Returns hardwareID variable`
 * @method Varstore::readHardwareID
 * @return MAC Address
 */
char* Varstore::readHardwareID() {
    return _hardwareID;
}

/**
 * Setters
 */

/**
 * Method to set the hardwareID or MAC address
 * @method Varstore::setHardwareID
 * @param  id                      MAC Address (00:00:00:00:00:00:00)
 * @return                         [description]
 */
char* Varstore::setHardwareID(char* id) {
    _hardwareID = id;
}
