/*
 * HTMLUtil.h
 *
 *  Created on: 19 déc. 2016
 *      Author: olamotte
 */

#ifndef IOT_HTMLUTIL_H_
#define IOT_HTMLUTIL_H_

#include "Arduino.h"

class HTMLUtil {
public:
	HTMLUtil(String _version);
	virtual ~HTMLUtil();

	String getHtmlHeader();

	String getCloseHtmlHeader();

	String getHeader();

	String getCloseHeader();

	String getJavaScript();

	String getCloseJavaScript();

	String getCSSStyle();

    String getBodyHeader(String title);

	String getBodyFooter();
	
	String getVersionTag();

	String getConfirmationFrame(String const title, String const msg);

	String getErrorFrame(String const msg);

	String getUtbmLogo();

private:
	String version;
};

#endif /* IOT_HTMLUTIL_H_ */
