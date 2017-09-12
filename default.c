#include "Nano100Series.h"              // Device header
#include "default.h"

void init_HCLK(void){
	SYS_UnlockReg();
	
	CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk);
	CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_HCLK_CLK_DIVIDER(1));	// CLK_HCLK_CLK_DIVIDER °Ñ¼Æ 1~16
	CLK_WaitClockReady(CLK_CLKSTATUS_HXT_STB_Msk);
	
	SYS_LockReg();
}

volatile uint32_t tick = 0;
void SysTick_Handler(){
	tick++;
}

void delay_ms(uint32_t ms){
	ms += tick;
	while(ms != tick){
	}
}
