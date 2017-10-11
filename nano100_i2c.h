#include "Nano100Series.h"              // Device header

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_write(uint8_t);
uint8_t i2c_read(uint8_t);
uint8_t scan_i2c_device(void);
