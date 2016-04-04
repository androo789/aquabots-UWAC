/*
 * SPI.c
 *
 * Created: 3-4-2016 11:15:43
 *  Author: Kevin Slagmolen
 */ 

#include "SPI.h"

void SPIInit()
{
	// Set MOSI, SCK as output
	DDRB |= (1 << DDB3) | (1 << DDB5);

	// Enable SPI, Master, set clock rate to fck/4
	SPCR = (1 << SPE) | (1 << MSTR);
}

void SPITransfer(unsigned char data)
{
	// Start transmission
	SPDR = data;

	// Wait for transmission to complete
	while (!(SPSR & (1 << SPIF))) ;
}