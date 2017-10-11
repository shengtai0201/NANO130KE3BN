#include "Nano100Series.h"              // Device header

void test_GPIO(void);

void test_CLK(uint32_t);

// ���խp�ɾ�
void test_TIMER0(void);

// �Q�� ADC ���� ���ӹq��
void test_thermistor(int*, int*);

void test_UART0(void);

void test_pwm_led_rgb(void);

// ���� USB �g�� UART ���o�R�O��ơA�A�Q�� PWM ���� LED's RGB
void test_uart0_led_rgb(char*);

// �H GPIO ��� I2C
void test_bh1750(void);

// ���� SW2
uint8_t test_button(int*, int*);

void test_wifi(void(*)(uint32_t));

void test_keypad(void(*)(uint32_t));

void test_sleep_apnea(int, int);

void test_step_motor(int*, int*);

void test_cc2541(int*, int*, void(*)(uint32_t));

void test_PWM1(void);
