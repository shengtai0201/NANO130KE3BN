#include "Nano100Series.h"              // Device header
#include "button.h"

void button_init(void) {
	GPIO_SetMode(PB, BIT2, GPIO_PMD_OPEN_DRAIN);
	PB->PUEN |= BIT2;
}
