#include "Nano100Series.h"              // Device header
#include "nano100_adc.h"

void init_ADC(void) {
	SYS_UnlockReg();
	CLK_EnableModuleClock(ADC_MODULE);
	CLK_SetModuleClock(ADC_MODULE, CLK_CLKSEL1_ADC_S_HXT, CLK_ADC_CLK_DIVIDER(12));
	// ���w ADC_CH0 �� PA0 ��X
	SYS->PA_L_MFP &= ~SYS_PA_L_MFP_PA0_MFP_Msk;
	SYS->PA_L_MFP |= SYS_PA_L_MFP_PA0_MFP_ADC_CH0;
	// ���w ADC_CH1 �� PA1 ��X
	SYS->PA_L_MFP &= ~SYS_PA_L_MFP_PA1_MFP_Msk;
	SYS->PA_L_MFP |= SYS_PA_L_MFP_PA1_MFP_ADC_CH1;
	GPIO_DISABLE_DIGITAL_PATH(PA, (BIT0 + BIT1));
	SYS_LockReg();

	// �~�������J�q�D(channel 0 ~ channel 11); �����q�D(DAC0, DAC1, �����a�عq��, �����ū׷P����X, AVDD, AVSS)
	ADC_Open(ADC, ADC_INPUT_MODE_SINGLE_END, ADC_OPERATION_MODE_SINGLE_CYCLE, ADC_CH_0_MASK | ADC_CH_1_MASK | ADC_CH_15_MASK);
	ADC_POWER_ON(ADC);

	ADC_EnableInt(ADC, ADC_ADF_INT);	// ADC convert complete interrupt
	NVIC_EnableIRQ(ADC_IRQn);
}
