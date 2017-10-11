#include "Nano100Series.h"              // Device header
#include "test.h"
#include "thermistor.h"
#include <stdio.h>
#include "lcd1602.h"
#include "nano100_pwm.h"
#include "bh1750.h"
#include "esp8266.h"
#include "default.h"
#include "keypad.h"
#include "breathe.h"
#include "step_motor.h"
#include "cc2541.h"

void test_GPIO(void) {
	GPIO_SetMode(PA, BIT12 + BIT13 + BIT14, GPIO_PMD_OUTPUT);
	PA12 = 0;	// R
	PA13 = 0;	// G
	PA14 = 0;	// B
}

// HXT = 12*10^6 Hz
// divider output frequency: x^(clk_div + 1)
// HXT / divider output frequency
void test_CLK(uint32_t clk_div) {
	SYS_UnlockReg();

	CLK_EnableCKO(CLK_CLKSEL2_FRQDIV_S_HXT, clk_div);
	SYS->PB_H_MFP &= ~(SYS_PB_H_MFP_PB12_MFP_Msk);
	SYS->PB_H_MFP |= SYS_PB_H_MFP_PB12_MFP_CKO;

	SYS_LockReg();
}

void test_TIMER0(void) {
	PA12 ^= 1;
}

void test_thermistor(int* adcv, int* adcn) {
	char buffer[64];
	int r;

	r = get_temperature();
	*adcv += r;
	*adcn += 1;

	if (*adcn > 49) {
		*adcv /= 50;
		sprintf(buffer, "%2d.%d", *adcv / 10, *adcv % 10);
		lcd_print(0x4C, buffer);

		*adcv = 0;
		*adcn = 0;
	}
}

void test_step_motor(int* adcv, int* adcn) {
	char buffer[64];
	int r;

	r = get_temperature();
	*adcv += r;
	*adcn += 1;

	if (*adcn > 9) {
		step_motor(*adcv);
		
		*adcv /= 10;
		sprintf(buffer, "%2d.%d", *adcv / 10, *adcv % 10);
		lcd_print(0x4C, buffer);

		*adcv = 0;
		*adcn = 0;
	}
	
	step_motor_running();
}

void test_cc2541(int* adcv, int* adcn, void(*delay_ms)(uint32_t)) {
	char buffer[64];
	int r;

	r = get_temperature();
	*adcv += r;
	*adcn += 1;

	if (*adcn > 49) {
		*adcv /= 50;
		sprintf(buffer, "%2d.%d", *adcv / 10, *adcv % 10);
		lcd_print(0x4C, buffer);
		
		cc2541_temp(delay_ms, buffer);

		*adcv = 0;
		*adcn = 0;
	}
}

void test_UART0(void) {
	uint32_t result = UART0->RBR;
	UART0->THR = result;

	// 由 USB 進入 UART0 的資料會是轉成十進位的值
	if (result == 49) {
		PA13 = 1;
	}
	else if (result == 48) {
		PA13 = 0;
	}
}

#define GR 42
#define GG 30
#define GB 12
int rc = 0, dr = GR, gc = 0, dg = GG, bc = 0, db = GB;
void test_pwm_led_rgb(void) {
	rc += dr;
	if (rc > 5900)
		dr = -GR;
	else if (rc < GR)
		dr = GR;

	gc += dg;
	if (gc > 5900)
		dg = -GG;
	else if (gc < GG)
		dg = GG;

	bc += db;
	if (bc > 5900)
		db = -GB;
	else if (bc < GB)
		db = GB;

	pwm0_set(rc, gc, bc);
}

static char* str_cmp(char* s, char* d) {
	while (*s) {
		if (*s++ != *d++)
			return 0;
	}

	return d;
}

static char* read_num(char* p, int* num) {
	int n = 0, tp = 0;
	uint8_t t;

	while (*p == ' ')
		p++;

	if (*p == '-') {
		tp = -1;
		p++;
	}

	do {
		t = *p - '0';
		if (t < 10) {
			n *= 10;
			n += t;
			p++;
		}
	} while (t < 10);

	if (tp == 0)
		*num = n;
	else
		*num = -n;

	if (*p == ',')
		p++;

	return p;
}

void chk_cmd(char* buffer, int n) {
	char *p;
	int r, g, b;
	char tmp[16];

	if (buffer[0] == '1')
		pwm0_on();
	else if (buffer[0] == '0')
		pwm0_off();

	p = str_cmp("RGB:", buffer);

	if (p > 0)
		p = read_num(p, &r);
	else
		return;

	if (p > 0)
		p = read_num(p, &g);
	else
		return;

	if (p > 0)
		p = read_num(p, &b);
	else
		return;

	sprintf(tmp, "%3d %3d %3d", r, g, b);
	lcd_print(0x00, tmp);
	pwm0_set(r, g, b);
}

char rn = 0;
void test_uart0_led_rgb(char* buffer) {
	uint32_t read_buffer = UART0->RBR;

	buffer[rn++] = read_buffer;
	rn &= 127;
	lcd_print(0x07, "1");
	if (read_buffer == 13) {
		lcd_print(0x07, "2");
		chk_cmd(buffer, rn);
		rn = 0;
	}
}

void test_bh1750(void) {
	char buffer[8];
	int r = bh1750_read();

	if (r > 0) {
		sprintf(buffer, "%4d", r);
		lcd_print(0x47, buffer);
	}
}

//int realease_button = 0;
uint8_t test_button(int* status, int* realease_time) {
	*realease_time += 1;

	switch (*status) {
	case 0:
		if (PB2 == 0) {
			*status = 1;
		}
		break;
	case 1:
		if (PB2 == 1) {
			*status = 0;
		}
		else if (PB2 == 0) {
			*status = 2;
		}
		break;
	case 2:
		*status = 3;
		if (*realease_time < 30) {
			return 4;
		}
		return 1;
	case 3:
		if (PB2 == 1) {
			*status = 4;
		}
		if (*realease_time == 300) {
			return 3;
		}
		break;
	case 4:
		if (PB2 == 0) {
			*status = 3;
		}
		if (PB2 == 1) {
			*status = 5;
		}
		break;
	case 5:
		*status = 0;
		return 2;
	}

	return 0;
}

void test_wifi(void(*delay_ms)(uint32_t)) {
	esp8266_start(delay_ms, "ssid", "password", "server_ip", 80);
	esp8266_close(delay_ms);
}

int previous_keypad_result = -1;
void test_keypad(void(*delay_ms)(uint32_t)) {
	char buffer[1];
	int result = keypad_get();

	if (previous_keypad_result != result) {
		previous_keypad_result = result;
		if (result != -1) {
			sprintf(buffer, "%c", result);
			lcd_print(0x00, buffer);
		}
	}

	delay_ms(1000);
}

int main_time_count = 0;
WavePoint *first_wave_point = NULL;
void test_sleep_apnea(int max_count, int value){
	if(main_time_count < max_count){
		first_wave_point = set_wave_point(value);
		main_time_count++;
	}else{
    Breathe *first_breathe = NULL;
    if (first_wave_point != NULL) {
        init_breathe(55, BREATHE_NONE, first_wave_point);
        first_wave_point = first_wave_point->next;
        while (first_wave_point != NULL) {
            first_breathe = set_breathe(first_wave_point);
            first_wave_point = first_wave_point->next;
        }
    }

    while (first_breathe != NULL) {
        printf("begin:%d, end:%d, type:%d\n", first_breathe->begin, first_breathe->end, first_breathe->type);
        first_breathe = first_breathe->next;
    }
		
		free_breathe();
		free_wave_point();
		
		init_wave_point();
		first_wave_point = set_wave_point(value);
		
		main_time_count = 0;
	}
}

int irdecode(uint16_t code){
	switch(code){
		case 0x6897:
			return 0;
		case 0x30CF:
			return 1;
		case 0x18E7:
			return 2;
		case 0x7A85:
			return 3;
		case 0x10EF:
			return 4;
		case 0x38C7:
			return 5;
		case 0x5AA5:
			return 6;
		case 0x42BD:
			return 7;
		case 0x4AB5:
			return 8;
		case 0x52AD:
			return 9;
	}
	
	return -1;
}

int previous_capture = 0, current_capture = 0;
void test_PWM1(void){
	uint16_t signal_length, received, ir;
	uint32_t code;
	char buffer[1];
	
	previous_capture = current_capture;
	current_capture = PWM_GET_CAPTURE_FALLING_DATA(PWM1, 3);
	
	signal_length = previous_capture - current_capture;
	if(signal_length < 500 || signal_length > 2500)
		received = 0;
	else {
		code <<= 1;
		code += (signal_length > 1500);
		received++;
		if(received == 32){
			ir = irdecode(code);
			sprintf(buffer, "%d", ir);
			lcd_print(0x00, buffer);
			
			received = 0;
		}
	}
}
