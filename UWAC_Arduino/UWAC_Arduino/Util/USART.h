/*
 * USART.h
 *
 * Created: 10-3-2016 08:45:29
 *  Author: Kevin Slagmolen
 */ 


#ifndef USART_H_
#define USART_H_

#include "defines.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

int receiveDone;

void USART0Init(void);
int USART0SendByte(char u8Data, FILE *stream);
char USART0GetByte(FILE *stream);

#endif /* USART_H_ */