#include "Nano100Series.h"              // Device header
#include "nano100_spi0.h"
#pragma anon_unions

void init_SPI0(uint32_t bus_clock){
	SYS_UnlockReg();
	CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0_S_HCLK, NULL);
	CLK_EnableModuleClock(SPI0_MODULE);
	SYS->PE_L_MFP &= ~SYS_PE_L_MFP_PE2_MFP_Msk;
	SYS->PE_L_MFP |= SYS_PE_L_MFP_PE2_MFP_SPI0_SCLK;
	SYS->PE_L_MFP &= ~SYS_PE_L_MFP_PE3_MFP_Msk;
	SYS->PE_L_MFP |= SYS_PE_L_MFP_PE3_MFP_SPI0_MISO0;
	SYS->PE_L_MFP &= ~SYS_PE_L_MFP_PE4_MFP_Msk;
	SYS->PE_L_MFP |= SYS_PE_L_MFP_PE4_MFP_SPI0_MOSI0;
	SYS_LockReg();
	
	SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 8, bus_clock);
	SPI_EnableFIFO(SPI0, 0, 0);	// 每次接到反應
}

uint8_t spi0_transmit(uint8_t data){
	SPI0->TX0 = data;
	
	while(SPI_IS_BUSY(SPI0)){
	}
	
	return SPI0->RX0;
}

uint8_t spi0(uint8_t data){
	union{
		unsigned char v;
		struct{
			unsigned b0:1;
			unsigned b1:1;
			unsigned b2:1;
			unsigned b3:1;
			unsigned b4:1;
			unsigned b5:1;
			unsigned b6:1;
			unsigned b7:1;
		};
	} r, d;
	d.v = data;
	
	SPI0_MOSI = d.b7;
	SPI0_SCK = 1;
	r.b7 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b6;
	SPI0_SCK = 1;
	r.b6 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b5;
	SPI0_SCK = 1;
	r.b5 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b4;
	SPI0_SCK = 1;
	r.b4 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b3;
	SPI0_SCK = 1;
	r.b3 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b2;
	SPI0_SCK = 1;
	r.b2 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b1;
	SPI0_SCK = 1;
	r.b1 = SPI0_MISO;
	SPI0_SCK = 0;
	
	SPI0_MOSI = d.b0;
	SPI0_SCK = 1;
	r.b0 = SPI0_MISO;
	SPI0_SCK = 0;
	
	return r.v;
}

uint8_t spi0_read_register(uint8_t address){
	uint8_t result;
	
	SPI0_CSN = 0;
	spi0(address);
	result = spi0(0);
	SPI0_CSN = 1;
	
	return result;
}

void spi0_write_register(uint8_t address, uint8_t data){
	SPI0_CSN = 0;
	spi0(0x20 | address);
	spi0(data);
	SPI0_CSN = 1;
}
