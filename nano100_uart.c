#include "Nano100Series.h"              // Device header
#include "nano100_uart.h"

// 實驗板預設將其接到 CH341(9600)
void init_UART0(uint32_t baudrate) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(UART0_MODULE);
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
	// 指定 UART0_RX 由 PB0 輸出
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB0_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB0_MFP_UART0_RX;
	// 指定 UART0_TX 由 PB1 輸出
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB1_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB1_MFP_UART0_TX;
	SYS_LockReg();

	UART_Open(UART0, baudrate);

	UART_ENABLE_INT(UART0, UART_IER_RDA_IE_Msk);	// Rx ready interrupt
	NVIC_EnableIRQ(UART0_IRQn);
}

// 實驗板預設將其接到 ESP8266
void init_UART1(uint32_t baudrate) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(UART1_MODULE);
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
	// 指定 UART1_RX 由 PB4 輸出
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB4_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB4_MFP_UART1_RX;
	// 指定 UART1_TX 由 PB5 輸出
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB5_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB5_MFP_UART1_TX;
	SYS_LockReg();

	UART_Open(UART1, baudrate);

	UART_ENABLE_INT(UART1, UART_IER_RDA_IE_Msk);	// Rx ready interrupt
	NVIC_EnableIRQ(UART1_IRQn);
}

void transmit_UART(void(*delay_ms)(uint32_t), UART_T* uart, uint32_t delay, const char* string) {
	while (*string) {
		uart->THR = *(string++);
		delay_ms(delay);
	}
}
