#include "Nano100Series.h"              // Device header
#include "nrf24l01.h"
#include "nano100_spi0.h"

void nrf_init(void){
	SPI0_SCK = 0;
	SPI0_CSN = 1;
	// SCLK, MOSI, CS, CE
	GPIO_SetMode(PE, BIT2 | BIT4 | BIT5 | BIT6, GPIO_PMD_OUTPUT);
	GPIO_SetMode(PE, BIT3, GPIO_PMD_INPUT);	// MISO
	GPIO_SetMode(PB, BIT3, GPIO_PMD_INPUT);	// IRQ
	
	spi0_write_register(0x00, 0x0F);	// CONFIG, configuration register
	spi0_write_register(0x01, 0x01);	// EN_AA, enable 'auto acknowledgment' function
	spi0_write_register(0x02, 0x01);	// EN_RXADDR, enable RX addresses
	spi0_write_register(0x04, 0x33);	// SETUP_PETR, setup of automatic retransmission
	spi0_write_register(0x11, 16);	// RX_PW_P0, number of bytes in RX payload in data pipe 0
	
	SPI0_CE = 1;
}
