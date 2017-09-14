#include "Nano100Series.h"              // Device header
#include <stdio.h>
#include "default.h"
#include "test.h"
#include "lcd1602.h"
#include "timer.h"
#include "uart.h"

void TMR0_IRQHandler(void){
	//test_TIMER0();
}

void UART0_IRQHandler(void){
	uint32_t result = UART0->RBR;
	UART0->THR = result;
	
	if(result == '1')
		PA13=1;
	
	if(result == '0')
		PA13 =0;
}

//void UART1_IRQHandler(void){
//	UART1->THR = UART1->RBR;
//}

void init(void){
	init_HCLK();
	if(SysTick_Config(SystemCoreClock / 1000) == 1){
		// Error Handling
	}
	init_TIMER0(1);
	init_UART0(9600);
}

int main(void){
	init();
	
	//setPB12CKO(15);
	GPIO_SetMode(PA, BIT12+BIT13+BIT14, GPIO_PMD_OUTPUT);
	PA12 = 0;
	PA13 = 0;
	PA14 = 0;

	printf("hello\r\n");
	
	while(1){
		delay_ms(1000);
		//test_TIMER0();
		
		if(!UART_GET_RX_EMPTY(UART0)){
			UART0->THR = UART0->RBR;
		}
	}
}
