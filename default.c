#include "Nano100Series.h"              // Device header
#include "default.h"
#include "string.h"

void init_HCLK(void) {
	SYS_UnlockReg();

	CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk);
	CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_HCLK_CLK_DIVIDER(1));	// CLK_HCLK_CLK_DIVIDER °Ñ¼Æ 1~16
	CLK_WaitClockReady(CLK_CLKSTATUS_HXT_STB_Msk);

	SYS_LockReg();
}

char* string_concatenation(char *left, const char *right){
	char string[16];
	char *ps = string;
	
	strcpy(string, left);
	strcat(string, right);
	
	return ps;
}
