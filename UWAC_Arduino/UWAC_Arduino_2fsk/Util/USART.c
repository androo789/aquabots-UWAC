/*
 * USART.c
 *
 * Created: 10-3-2016 08:45:41
 *  Author: Kevin Slagmolen
 */ 

#include "USART.h"

void USART0Init()
{
	receiveDone = 0;

	// Set baud rate
	UBRR0H = (uint8_t)(UBRR_BAUDRATE >> 8);
	UBRR0L = (uint8_t)UBRR_BAUDRATE;

	// Enable transmission and receiving
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

int USART0SendByte(char u8Data, FILE *stream)
{
	if (u8Data == '\n') USART0SendByte('\r', stream);

	// Wait while previous byte is completed
	while (!(UCSR0A & (1 << UDRE0)));

	// Transmit data
	UDR0 = u8Data;
	return 0;
}

char USART0GetByte(FILE *stream)
{
	while (!(UCSR0A & (1 << RXC0)));
	
	return UDR0;
}