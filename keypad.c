#include "Nano100Series.h"              // Device header
#include "keypad.h"
#include "lcd1602.h"
#include <stdio.h>

void keypad_init(void(*delay_ms)(uint32_t)) {
	GPIO_SetMode(PC, BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5, GPIO_PMD_INPUT);
	PC->PUEN |= (BIT4 + BIT5);

	GPIO_SetMode(PD, BIT14 + BIT15, GPIO_PMD_INPUT);
	PD->PUEN |= (BIT14 + BIT15);

	delay_ms(10);
}

int keypad_scan(int column) {
	int r = 0;

	switch (column) {
	case 0:
		GPIO_SetMode(PC, BIT0, GPIO_PMD_OUTPUT);
		PC0 = 0;
		break;
	case 1:
		GPIO_SetMode(PC, BIT1, GPIO_PMD_OUTPUT);
		PC1 = 0;
		break;
	case 2:
		GPIO_SetMode(PC, BIT2, GPIO_PMD_OUTPUT);
		PC2 = 0;
		break;
	case 3:
		GPIO_SetMode(PC, BIT3, GPIO_PMD_OUTPUT);
		PC3 = 0;
		break;
	}

	if (PC4 == 0)
		r = 1;
	else if (PC5 == 0)
		r = 2;
	else if (PC14 == 0)
		r = 3;
	else if (PC15 == 0)
		r = 4;

	GPIO_SetMode(PC, BIT0 + BIT1 + BIT2 + BIT3, GPIO_PMD_INPUT);

	if (r != 0)
		return (column << 2) + r;
	else
		return r;
}

int keypad_get(void) {
	int temp;
	char buffer[8];
	int result = 0;

	temp = keypad_scan(0);
	sprintf(buffer, "%d", temp);
	lcd_print(0x00, buffer);
	result += temp;

	temp = keypad_scan(1);
	sprintf(buffer, "%d", temp);
	lcd_print(0x04, buffer);
	result += temp;

	temp = keypad_scan(2);
	sprintf(buffer, "%d", temp);
	lcd_print(0x08, buffer);
	result += temp;

	temp = keypad_scan(3);
	sprintf(buffer, "%d", temp);
	lcd_print(0x0C, buffer);
	result += temp;

	switch (result) {
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return 'A';

	case 5:
		return '4';
	case 6:
		return '5';
	case 7:
		return '6';
	case 8:
		return 'B';

	case 9:
		return '7';
	case 10:
		return '8';
	case 11:
		return '9';
	case 12:
		return 'C';

	case 13:
		return '*';
	case 14:
		return '0';
	case 15:
		return '#';
	case 16:
		return 'D';
	}

	return -1;
}
