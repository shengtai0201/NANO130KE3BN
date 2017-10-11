#include "Nano100Series.h"              // Device header
#include "step_motor.h"
int step_motor_max = 0, step_motor_count = 0;
void step_motor_init(int max){
	GPIO_SetMode(PE, BIT7 | BIT8 | BIT9 | BIT10, GPIO_PMD_OUTPUT);
	step_motor_max = max;
}

void step_motor(int n){
	short q = 0;
	PE7 = PE8 = PE9 = PE10 = 0;
	
	switch(n & 7){
		case 0:
			q = 1 << 7;	// 0001
		  break;
		case 1:
			q = 3 << 7;	// 0011
		  break;
		case 2:
			q = 2 << 7;	// 0010
		  break;
		case 3:
			q = 6 << 7;	// 0110
		  break;
		case 4:
			q = 4 << 7;	// 0100
		  break;
		case 5:
			q = 12 << 7;	// 1100
		  break;
		case 6:
			q = 8 << 7;	// 1000
		  break;
		case 7:
			q = 9 << 7;	// 1001
		  break;
	}
	
	PE->DOUT |= q;
}

void step_motor_running(void){
	if(step_motor_count == step_motor_max){
		PE7 = PE8 = PE9 = PE10 = 0;
	} else {
		if(step_motor_count > step_motor_max)
			step_motor_count--;
		else if (step_motor_count < step_motor_max)
			step_motor_count++;
		
		step_motor(step_motor_count & 7);
	}
}
