#include "Nano100Series.h"              // Device header

void esp8266_start(void(*)(uint32_t), char*, char*, char*, uint16_t);
void esp8266_close(void(*)(uint32_t));
void esp8266_post(void(*)(uint32_t), char*, char*, char*, int);
