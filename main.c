#include "Nano100Series.h"              // Device header
#include "default.h"
#include "lcd1602.h"

void init(void){
	if(SysTick_Config(SystemCoreClock / 1000) == 1){
		// Error Handling
	}
}

int main(void){
	init();
	
	GPIO_SetMode(PA, BIT12+BIT13+BIT14, GPIO_PMD_OUTPUT);
	PA12 = 1;
	PA13 = 0;
	PA14 = 0;
	
	while(1){
		
	}
}
