#include "Nano100Series.h"              // Device header

#define SPI0_SCK 	PE2		// SPI signal
#define SPI0_MISO PE3		// SPI signal
#define SPI0_MOSI PE4		// SPI signal
#define SPI0_CSN 	PE5		// SPI signal
#define SPI0_CE 	PE6		// this signal is active high and used to activate the chip in RX or TX mode
#define SPI0_IRQ 	PB3		// this signal is active low and controlled by three maskable interrupt sources

void init_SPI0(uint32_t);
uint8_t spi0(uint8_t);
uint8_t spi0_read_register(uint8_t);
void spi0_write_register(uint8_t, uint8_t);
