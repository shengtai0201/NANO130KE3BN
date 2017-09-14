#include "Nano100Series.h"              // Device header
#include "test.h"

// HXT = 12*10^6 Hz
// divider output frequency: x^(clk_div + 1)
// HXT / divider output frequency
void setPB12CKO(uint32_t clk_div){
	SYS_UnlockReg();
	
	CLK_EnableCKO(CLK_CLKSEL2_FRQDIV_S_HXT, clk_div);
	SYS->PB_H_MFP &= ~(SYS_PB_H_MFP_PB12_MFP_Msk);
	SYS->PB_H_MFP |= SYS_PB_H_MFP_PB12_MFP_CKO;
	
	SYS_LockReg();
}

void test_TIMER0(void){
	// 0 => time-out interrupt did not occur 
	//while(TIMER_GetIntFlag(TIMER0) == 0){}
	PA12 ^= 1;
	TIMER_ClearIntFlag(TIMER0);
}
