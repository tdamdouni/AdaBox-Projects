#ifndef PRINT_DEFN_H
#define PRINT_DEFN_H

#if defined (DEBUG) || defined (ADC_CAL)
#include <pgmspace.h>

void StreamPrint_progmem(Print &out,PGM_P format,...)
{
	// program memory version of printf - copy of format string and result share a buffer
	// so as to avoid too much memory use
	char formatString[256], *ptr;
	strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
	// null terminate - leave last char since we might need it in worst case for result's \0
	formatString[ sizeof(formatString)-2 ]='\0'; 
	ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
	va_list args;
	va_start (args,format);
	vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
	va_end (args);
	formatString[ sizeof(formatString)-1 ]='\0'; 
	out.print(ptr);

}

#define Debugprintf(format, ...) (StreamPrint_progmem(Serial,(PSTR(format)),##__VA_ARGS__))
#else
#define Debugprintf(format, ...)

#endif //  #ifdef DEBUG

#ifdef ADC_CAL
#define ADCprintf(format, ...) (StreamPrint_progmem(Serial,(PSTR(format)),##__VA_ARGS__))
#else
#define ADCprintf(format, ...)
#endif



bool feedPrintf_P(Adafruit_MQTT_Publish &feed,PGM_P format,...) {
	char formatString[256], *ptr;
	strncpy_P( formatString, format, sizeof(formatString) ); // copy in from program mem
	// null terminate - leave last char since we might need it in worst case for result's \0
	formatString[ sizeof(formatString)-2 ]='\0';
	ptr=&formatString[ strlen(formatString)+1 ]; // our result buffer...
	va_list args;
	va_start (args,format);
	vsnprintf(ptr, sizeof(formatString)-1-strlen(formatString), formatString, args );
	va_end (args);
	formatString[ sizeof(formatString)-1 ]='\0';
	feed.publish(ptr);
}

#define logFeedPrintf(format, ...) (feedPrintf_P(log_feed,(PSTR(format)),##__VA_ARGS__))

#endif // PRINT_DEFN_H
