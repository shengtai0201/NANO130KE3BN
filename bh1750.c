#include "Nano100Series.h"              // Device header
#include "nano100_i2c.h"

#include "lcd1602.h"
#include <stdio.h>

#define DEVID	0x46
#define WR		0
#define RD		1
#define ACK		0
#define NACK	1

uint8_t bh1750_write(uint8_t reg) {
	uint8_t r;

	i2c_start();
	r = i2c_write(DEVID + WR);
	r += i2c_write(reg);
	i2c_stop();

	return r;
}

int bhcnt = 0;
int bh1750_read(void) {
	uint16_t r16;

	//uint8_t tmp;
	//char buffer[64];

	bhcnt++;
	switch (bhcnt) {
	case 1:
		bh1750_write(0x10);	// Continuously H-Resolution Mode
		return -1;
	case 20:
		i2c_start();
		i2c_write(DEVID + RD);

		r16 = (uint16_t)i2c_read(ACK) << 8;

		//r16 = (uint16_t)tmp << 8;

		//tmp = i2c_read(NACK);
		//sprintf(buffer, "%d", tmp);
		//lcd_print(0x00, buffer);
		//r16 += tmp;

		r16 += i2c_read(NACK);

		i2c_stop();
		bhcnt = 0;
		return r16;
	}

	return -1;
}
