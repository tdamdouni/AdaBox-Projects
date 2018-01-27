// ConstantStrings.h

#ifndef _CONSTANTSTRINGS_h
#define _CONSTANTSTRINGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

const String _HomePage =
"<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>"
"* {box-sizing: border-box;}body{background-color: black;color: white;margin: 0px;}"
".row::after {content: \"\";clear: both;display: table;}"
".row{display: table;width: 100%;}"
".col{width: 50%;display: table-cell;} "
"html {font-family: \"Lucida Sans\", sans-serif;}"
".header{background-color: #3FC003;color: #ffffff;padding: 1px 6px 1px 6px;}"
".outSide{background-color:#005E80;padding: 6px 12px;text-align:right;font-size:18px;}"
".inSide{background-color: #008044;padding: 6px 12px;text-align:right;font-size: 18px;}"
".value {text-align:right;display:inline;}"
".unit{text-align:left;float:right;display:block;padding-left:6px;min-width:50px;}"
".vuLine{padding:1px;}"
".footer{background-color:#111111;color:#666666;text-align:left;font-size:12px;padding: 6px 12px;}"
".footer p{white-space: pre-wrap;}"
"@media only screen and (max-width: 450px) {.col {width: 100%;display: block;}}"
".device{position:sticky;font-size: 12px;margin-left:-6px;text-align:left;float:left;color:lightgreen;}"
".topLine{display:block;float:none;font-size:12px;margin: -3px -6px 3px -6px;}"
".roomLine{font-size:15px;font-weight:bold;float:left;text-align:left;}"
".dateLine{color:#999999;text-align:right;padding: 3px 0px 0px 0px;}"
"h1,h2,h3,h4,h5, p{margin:0px;}"
"</style></head><body>"
"<div class=\"header\"><h2>ESP32-Server</h2></div>"
"<div class=\"row\"><div class=\"col outSide\">"
"<div class=\"topLine\"><div class=\"roomLine\">Garden</div><div class=\"dateLine\">{Time_OUT}</div></div>"
"<div class=\"device\">EE060</div>"
"<div class=\"vuLine\"><div class=\"value temperature\">{Temp_OUT}</div><div class=\"unit\">°C</div></div>"
"<div class=\"vuLine\"><div class=\"value humidity\">{RH_OUT}</div><span style=\"visibility:hidden\">.0</span><div class=\"unit\">%RH</div></div></div>"
"</div></div>"
"<div class=\"footer\"><p>Resize the browser window to see how the content respond to the resizing.</p></div></body></html>";

#endif

