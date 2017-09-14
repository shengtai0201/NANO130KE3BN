#include "Nano100Series.h"              // Device header
#include "timer.h"

void init_TIMER0(uint32_t freq){
	SYS_UnlockReg();
	CLK_EnableModuleClock(TMR0_MODULE);
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HXT, NULL); 
	SYS_LockReg();
	
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, freq);
	TIMER_Start(TIMER0);
	TIMER_EnableInt(TIMER0);
	
	NVIC_EnableIRQ(TMR0_IRQn);
}
