#include "Nano100Series.h"              // Device header
#include "nano100_timer.h"

void init_TIMER0(uint32_t freq) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(TMR0_MODULE);
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0_S_HXT, NULL);
	SYS_LockReg();

	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, freq);
	TIMER_Start(TIMER0);

	TIMER_EnableInt(TIMER0);
	NVIC_EnableIRQ(TMR0_IRQn);
}

void init_TIMER1(uint32_t freq) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(TMR1_MODULE);
	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1_S_HXT, NULL);
	SYS->PB_H_MFP &= ~SYS_PB_H_MFP_PB9_MFP_Msk;
	SYS->PB_H_MFP |= SYS_PB_H_MFP_PB9_MFP_TMR1_EXT;
	SYS_LockReg();

	TIMER_Open(TIMER1, TIMER_TOGGLE_MODE, freq);
	TIMER_Start(TIMER1);

	TIMER_EnableInt(TIMER1);
	NVIC_EnableIRQ(TMR1_IRQn);
}
