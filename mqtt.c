#include "Nano100Series.h"              // Device header
#pragma anon_unions

// http://blog.maxkit.com.tw/2014/02/mqttconnect-message.html
// https://cfw011566.gitbooks.io/mqtt-and-mosquitto/content/mqtt.html
typedef union {
	unsigned char data;
	struct {
		unsigned bit7 : 1;
	};
} FixedHeader;

// jansson
// https://github.com/windfire-cd/note/blob/master/jansson_using.md
// http://www.digip.org/jansson/
