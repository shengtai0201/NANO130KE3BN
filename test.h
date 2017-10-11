#include "Nano100Series.h"              // Device header

void test_GPIO(void);

void test_CLK(uint32_t);

// 測試計時器
void test_TIMER0(void);

// 利用 ADC 測試 熱敏電阻
void test_thermistor(int*, int*);

void test_UART0(void);

void test_pwm_led_rgb(void);

// 源於 USB 經由 UART 取得命令資料，再利用 PWM 控制 LED's RGB
void test_uart0_led_rgb(char*);

// 以 GPIO 實踐 I2C
void test_bh1750(void);

// 測試 SW2
uint8_t test_button(int*, int*);

void test_wifi(void(*)(uint32_t));

void test_keypad(void(*)(uint32_t));

void test_sleep_apnea(int, int);

void test_step_motor(int*, int*);

void test_cc2541(int*, int*, void(*)(uint32_t));

void test_PWM1(void);
