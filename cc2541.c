#include "Nano100Series.h"              // Device header
#include "cc2541.h"
#include "nano100_uart.h"
#include "default.h"

void cc2541_init(void(*delay_ms)(uint32_t)){
	transmit_UART(delay_ms, UART1, 0, "AT+HOSTEN3");
	delay_ms(100);
	transmit_UART(delay_ms, UART1, 0, "AT+CLSSE0");
	delay_ms(100);
	transmit_UART(delay_ms, UART1, 0, "AT+RST");
	delay_ms(500);
	
//	transmit_UART(delay_ms, UART1, 0, "AT+STRUUIDFDA50693A4E24FB1AFCFC6EB07647825");
//	delay_ms(100);
//	transmit_UART(delay_ms, UART1, 0, "AT+MAJOR000A");
//	delay_ms(100);
//	transmit_UART(delay_ms, UART1, 0, "AT+MINOR0007");
//	delay_ms(100);
//	transmit_UART(delay_ms, UART1, 0, "AT+VID88");
//	delay_ms(100);
//	
//	transmit_UART(delay_ms, UART1, 0, "AT+NAMEJDY-08-IoT");
//	delay_ms(100);
//	transmit_UART(delay_ms, UART1, 0, "AT+PASS110500");
//	delay_ms(100);
}

void cc2541_temp(void(*delay_ms)(uint32_t), const char *temp){
	//char *string = string_concatenation("AT+TEMP", temp);
	
	transmit_UART(delay_ms, UART1, 0, "AT+TEMP33");
	delay_ms(100);
}
