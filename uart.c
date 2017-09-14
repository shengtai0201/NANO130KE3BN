#include "Nano100Series.h"              // Device header
#include "uart.h"

void init_UART0(uint32_t baudrate){
	SYS_UnlockReg();
	CLK_EnableModuleClock(UART0_MODULE);
	CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB0_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB0_MFP_UART0_RX;
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB1_MFP_Msk;
	SYS->PA_L_MFP |= SYS_PB_L_MFP_PB1_MFP_UART0_TX;
	SYS_LockReg();
	
	UART_Open(UART0, baudrate);
	UART_ENABLE_INT(UART0, UART_IER_RDA_IE_Msk);	// Rx ready interrupt
	
	NVIC_EnableIRQ(UART0_IRQn);
}

void init_UART1(uint32_t baudrate){
	SYS_UnlockReg();
	CLK_EnableModuleClock(UART1_MODULE);
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_UART_CLK_DIVIDER(1));
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB4_MFP_Msk;
	SYS->PB_L_MFP |= SYS_PB_L_MFP_PB4_MFP_UART1_RX;
	SYS->PB_L_MFP &= ~SYS_PB_L_MFP_PB5_MFP_Msk;
	SYS->PA_L_MFP |= SYS_PB_L_MFP_PB5_MFP_UART1_TX;
	SYS_LockReg();
	
	UART_Open(UART1, baudrate);
	UART_ENABLE_INT(UART1, UART_IER_RDA_IE_Msk);	// Rx ready interrupt
	
	NVIC_EnableIRQ(UART1_IRQn);
}
