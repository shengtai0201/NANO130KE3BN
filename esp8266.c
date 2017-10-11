#include "Nano100Series.h"              // Device header
#include "esp8266.h"
#include <stdio.h>
#include "nano100_uart.h"
#include <string.h>

// 單連接透傳

void esp8266_start(void(*delay_ms)(uint32_t), char* ssid, char* password, char* server_ip, uint16_t port) {
	char buffer[64];
	
	// 設置 WiFi 模式
	transmit_UART(delay_ms, UART1, 10, "AT+CWMODE=3\r\n");
	delay_ms(100);
	
	// 連接路由
	sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(15000);
	
	// 查詢設備 IP 地址 
	transmit_UART(delay_ms, UART1, 10, "AT+CIFSR\r\n");
	delay_ms(100);
	
	// 設備作為 TCP client 連接 TCP server
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", server_ip, port);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(500);
	
	transmit_UART(delay_ms, UART1, 10, "AT+CIPMODE=1\r\n");
	delay_ms(100);
}

void esp8266_close(void(*delay_ms)(uint32_t)) {
	transmit_UART(delay_ms, UART1, 10, "AT+CIPMODE=0\r\n");
	delay_ms(100);
	
	transmit_UART(delay_ms, UART1, 10, "AT+CIPCLOSE\r\n");
	delay_ms(100);
}

// 發送數據
void esp8266_post(void(*delay_ms)(uint32_t), char* url, char* host, char* content, int content_length) {
	char buffer[64];
	
	transmit_UART(delay_ms, UART1, 10, "AT+CIPSEND\r\n");
	delay_ms(100);
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "POST %s HTTP/1.1\r\n", url);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(100);
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "Content-Length: %d\r\n", content_length);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(100);
	
	transmit_UART(delay_ms, UART1, 10, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8\r\n");
	delay_ms(100);
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "Host: %s\r\n", host);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(100);
	
	transmit_UART(delay_ms, UART1, 10, "Connection: Keep-Alive\r\n");
	delay_ms(100);
	
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, "%s\r\n", content);
	transmit_UART(delay_ms, UART1, 10, buffer);
	delay_ms(100);
	
	transmit_UART(delay_ms, UART1, 10, "+++\r\n");
	delay_ms(100);
}
