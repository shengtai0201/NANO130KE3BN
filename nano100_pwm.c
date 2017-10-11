#include "Nano100Series.h"              // Device header
#include "nano100_pwm.h"

void init_PWM0(void) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(PWM0_CH01_MODULE);
	CLK_SetModuleClock(PWM0_CH01_MODULE, CLK_CLKSEL1_PWM0_CH01_S_HXT, NULL);
	// 指定 PWM0_CH0 由 PA12 輸出
	SYS->PA_H_MFP &= ~SYS_PA_H_MFP_PA12_MFP_Msk;
	SYS->PA_H_MFP |= SYS_PA_H_MFP_PA12_MFP_PWM0_CH0;	// R
	// 指定 PWM0_CH1 由 PA13 輸出
	SYS->PA_H_MFP &= ~SYS_PA_H_MFP_PA13_MFP_Msk;
	SYS->PA_H_MFP |= SYS_PA_H_MFP_PA13_MFP_PWM0_CH1;	// G
	// 指定 PWM0_CH2 由 PA14 輸出
	SYS->PA_H_MFP &= ~SYS_PA_H_MFP_PA14_MFP_Msk;
	SYS->PA_H_MFP |= SYS_PA_H_MFP_PA14_MFP_PWM0_CH2;	// B
	SYS_LockReg();

	pwm0_on();
}

void init_PWM1(void){
	SYS_UnlockReg();
	CLK_EnableModuleClock(PWM1_CH23_MODULE);
	CLK_SetModuleClock(PWM1_CH23_MODULE, CLK_CLKSEL2_PWM1_CH23_S_HXT, NULL);
	// 指定 PWM1_CH23 由 PE1 輸出
	SYS->PE_L_MFP &= ~SYS_PE_L_MFP_PE1_MFP_Msk;
	SYS->PE_L_MFP |= SYS_PE_L_MFP_PE1_MFP_PWM1_CH3;
	SYS_LockReg();

	PWM_ConfigCaptureChannel(PWM1, 3, 50, 0);
	PWM_EnableCapture(PWM1, PWM_CH_3_MASK);
	PWM_SET_PRESCALER(PWM1, 3, 12);
	PWM_Start(PWM1, PWM_CH_3_MASK);
	
	PWM_EnableCaptureInt(PWM1, 3, PWM_FALLING_LATCH_INT_ENABLE);
	NVIC_EnableIRQ(PWM1_IRQn);
}

void pwm0_on(void) {
	PWM_ConfigOutputChannel(PWM0, 0, 1000, 30);	// R
	PWM_ConfigOutputChannel(PWM0, 1, 1000, 30);	// G
	PWM_ConfigOutputChannel(PWM0, 2, 1000, 30);	// B

	PWM_EnableOutput(PWM0, PWM_CH_0_MASK | PWM_CH_1_MASK | PWM_CH_2_MASK);

	PWM_Start(PWM0, PWM_CH_0_MASK | PWM_CH_1_MASK | PWM_CH_2_MASK);
}

void pwm0_off(void) {
	PWM_Stop(PWM0, PWM_CH_0_MASK | PWM_CH_1_MASK | PWM_CH_2_MASK);
}

// r, g, b: 0 ~ 65535
void pwm0_set(int r, int g, int b) {
	PWM_SET_CMR(PWM0, 0, r);
	PWM_SET_CMR(PWM0, 1, g);
	PWM_SET_CMR(PWM0, 2, b);
}
