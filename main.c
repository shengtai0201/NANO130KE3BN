#include "Nano100Series.h"              // Device header
#include "default.h"
#include "test.h"
#include "nano100_timer.h"
#include "nano100_uart.h"
#include <stdio.h>
#include "lcd1602.h"
#include "nano100_adc.h"
#include "nano100_pwm.h"
#include "nano100_i2c.h"
#include "button.h"
#include "keypad.h"
#include "breathe.h"
#include "step_motor.h"
#include "cc2541.h"

volatile uint32_t tick = 0;
void SysTick_Handler() {
	tick++;
}

void delay_ms(uint32_t delay) {
	delay += tick;
	while (delay != tick) {
	}
}

void TMR0_IRQHandler(void) {
	TIMER_ClearIntFlag(TIMER0);

	//test_TIMER0();
	
	//test_sleep_apnea(500, 4096);
}

int adcv = 0, adcn = 0;
void TMR1_IRQHandler(void) {
	TIMER_ClearIntFlag(TIMER1);

	//test_thermistor(&adcv, &adcn);
	//test_step_motor(&adcv, &adcn);
	test_cc2541(&adcv, &adcn, delay_ms);
	//test_pwm_led_rgb();
	test_bh1750();
}


//char uart0_buffer[128];
void UART0_IRQHandler(void) {
	//test_UART0();
	//test_uart0_led_rgb(uart0_buffer);
	UART1->THR = UART0->RBR;
}

void UART1_IRQHandler(void) {
	UART0->THR = UART1->RBR;
}

void ADC_IRQHandler(void) {
	ADC_CLR_INT_FLAG(ADC, ADC_ADF_INT);

	ADC_STOP_CONV(ADC);
}

void PWM1_IRQHandler(void){
	test_PWM1();
	PWM_ClearCaptureIntFlag(PWM1, 3, PWM_FALLING_LATCH_INT_FLAG);
}

void init(void) {
	test_GPIO();
	//test_CLK(15);
	init_HCLK();
	SysTick_Config(SystemCoreClock / 1000);
	init_TIMER0(1);
	init_TIMER1(100);
	init_UART0(115200);
	init_UART1(115200);
	lcd_init();
	init_ADC();
	//init_PWM0();
	i2c_init();
	button_init();
	//keypad_init(delay_ms);
	//init_wave_point();
	//step_motor_init(3);
	init_PWM1();
	cc2541_init(delay_ms);
}

//int button_click = 0;
//int status = 0, realease_time = 0;
int main(void) {
	//char buffer1[64], buffer2[64], buffer3[64];
	//int click;//, test;
	init();

	//test_TIMER0();
	//test_TIMER0();
	//printf("bad before\r\n");
	//printf("AT\r\n");
	lcd_print(0x40, "Hello1");
	//test_wifi(delay_ms);
	//test_bluetooth(delay_ms);

	while (1) {
		//test_keypad(delay_ms);	// keypad ¦C 2, 3 Ãa±¼¤F		
		//PA12 = ~PA12;
		//printf("bad loop\r\n");

//		click = test_button(&status, &realease_time);
//		if(click == 1){
//			button_click++;
//			
//			sprintf(buffer1, "%d", button_click);
//			lcd_print(0x00, buffer1);
//			sprintf(buffer2, "%d", status);
//			lcd_print(0x04, buffer2);
//			sprintf(buffer3, "%d", realease_time);
//			lcd_print(0x08, buffer3);
//		} 
//		if(click == 3){
//			button_click = 0;
//			status = 0;
//			
//			sprintf(buffer1, "%d", button_click);
//			lcd_print(0x00, buffer1);
//			sprintf(buffer2, "%d", status);
//			lcd_print(0x04, buffer2);
//			sprintf(buffer3, "%d", realease_time);
//			lcd_print(0x08, buffer3);
//		}

		//status <<= 1;
		//status += PB2;
		//status &= 3;

		//PA12 = ~PB2;
		delay_ms(1000);
	}
}
