/*
 * SPI.h
 *
 * Created: 3-4-2016 11:15:34
 *  Author: Kevin Slagmolen
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#include "defines.h"

void SPIInit(void);
void SPITransfer(unsigned char data);

#endif /* SPI_H_ */