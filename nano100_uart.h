#include "Nano100Series.h"              // Device header

void init_UART0(uint32_t);
void init_UART1(uint32_t);

void transmit_UART(void(*)(uint32_t), UART_T*, uint32_t, const char*);
