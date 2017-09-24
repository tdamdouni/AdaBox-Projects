/*
 * HTMLUtil.cpp
 *
 *  Created on: 20 déc. 2016
 *      Author: olamotte
 */

#include "HTMLUtil.h"

HTMLUtil::HTMLUtil(String _version) {
	this->version = _version;
}
HTMLUtil::~HTMLUtil() {

}

String HTMLUtil::getHtmlHeader() {
	String result = F("<!DOCTYPE html><html><head><meta charset=\"UTF-8\" />\n");
	return result;
}

String HTMLUtil::getCloseHtmlHeader() {
  return F("</html>");
}

String HTMLUtil::getHeader() {
  return F("<head>");
}

String HTMLUtil::getCloseHeader() {
  return F("</head>\n");
}

String HTMLUtil::getJavaScript() {
  return F("<script LANGUAGE=\"JavaScript\">");
}

String HTMLUtil::getCloseJavaScript() {
  return F("</Script>");
}

String HTMLUtil::getCSSStyle() {
	String style = F("<style type=\"text/css\">\n");
	style += F("body{color:#000;font:normal100%'DroidSans',arial,sans-serif;line-height:2em;background-color:#f9f9f9;}\n");
	style += F("fieldset{clear:right;letter-spacing:0em;padding:000.5em0;font:bold140%'NewsCycle',arial;margin:1em;padding:0.5em;}\n");
	style += F("legend{font-weight:bold;color:#0000cc;}\n");
	style += F("button{font-size:15pt;background-color:#262626;color:#f9f9f9;text-align:center;border-radius:8px;width:100%;}\n");
	style += F("button:hover{background-color:#f9f9f9;color:#0000cc;}\n");
	style += F("label{display:block;width:50%;float:left;text-align:right;}\n");
	style += F("footer{display:block;font-size:11pt;}\n");
	style += F("#utbm_logo{float:right}");
	style += F(".header h1{position: relative;}");
	style += F("ul {text-align:center;list-style:none;}");
	style += F("</style>\n");
	return style;
}


String HTMLUtil::getBodyHeader(String title) {
  String result = F("<div class=\"header\">");
  result += getUtbmLogo();
  result += F("<h1>");
  result += title;
  result += F("</h1></div>");
  return result;
}

String HTMLUtil::getBodyFooter() {
	String result = F("<footer><form action=\"/ \">");
	result += F("<span style=\"float:left\"><button style=\"font-size: 8pt;\">Menu principal</button></p></span>");
	result += F("<span style=\"float:right\">");
	result += getVersionTag();
	result += F("</span></form></footer>");
	return result;
}

String HTMLUtil::getVersionTag(){
	String result = F("p align=\"right\">");
	result += this->version;
	result += F(" © Olivier Lamotte, Guillaume Prost, 2017</p>");
	return result;
}

String HTMLUtil::getConfirmationFrame(String const title, String const msg) {
  String result = this->getHtmlHeader();
  result += this->getHeader();
  result += getCSSStyle();
  result += this->getCloseHeader();
  result += F("<body><h1>");
  result += title;
  result += F("</h1>");
  result += F("<fieldset><div>");
  result += msg;
  result += F("</div></fieldset>");
  result += F("<footer><form action=\"/\">");
  result += F("<span style=\"float:left\"><button style=\"font-size: 8pt;\">Menu principal</button></p></span>");
  result += F("<span style=\"float:right\">");
  result += getVersionTag();
  result += F("</span></form></footer>");
  
  result += F("</body>");
  result += this->getCloseHtmlHeader();
  return result;
}

String HTMLUtil::getErrorFrame(String const msg) {
  String result = this->getHtmlHeader();
  result += this->getCSSStyle();
  result += F("<body><h1><font color=\"red\">");
  result += msg;
  result += F("</font></h1>");
  result += F("<footer><form action=\"/\">");
  result += F("<span style=\"float:left\"><button style=\"font-size: 8pt;\">Menu principal</button></p></span>");
  result += F("<span style=\"float:right\">");
  result += getVersionTag();
  result += F("</span></form></footer>");
  result += F("</body>");
  return result;
}

String HTMLUtil::getUtbmLogo(){
  String result = F("<img id=\"utbm_logo\" src=\"data:image/jpg;base64,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\" width=\"166\" height=\"71\"/>");
   return result;
}
