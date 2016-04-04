/*
 * UWAC_Arduino_2fsk.c
 *
 * Created: 1-4-2016 19:06:22
 * Author : Kevin Slagmolen
 */ 

#include "Util/defines.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Util/USART.h"
#include "Util/SPI.h"
#include "data_conversion.h"

void sendData(uint8_t dataToSend[800]); // Test function to see if the data is put on the output pin (pin 8)

FILE usart0_output = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);	// Output file for USART
FILE usart0_input = FDEV_SETUP_STREAM(NULL, USART0GetByte, _FDEV_SETUP_READ);		// Input file for USART

int counter;
uint8_t receivedData[800];

int main(void)
{
	int i;
	for (i = 0; i < 800; i++)
	{
		receivedData[i] = 0;
	}

	// init IO
	DDRB |= (1 << OUTPUT_PIN); // Set the output pin
	DDRC &= ~(1 << INPUT_PIN); // Set the input pin
	PORTC |= (1 << INPUT_PIN); // Enable pull-up resistor

	/*TCCR0A |= (1 << WGM01);		// Set the Timer Mode to CTC
	OCR0A = 0x7D;				// Set the value that you want to count to
	TIMSK0 |= (1 << OCIE0A);	//Set the ISR COMPA vect
	
	sei(); //enable interrupts

	TCCR0B |= (1 << CS02); // set prescaler to 256 and start the timer*/


	/* USART INIT START */
	USART0Init();
	stdout =& usart0_output;
	stdin =& usart0_input;
	/* USART INIT STOP */

	SPIInit(); // Init the SPI bus

	//char input[100] = "Now, this is a story all about how My life got flipped-turned upside down";
	char input[100] = "";
	printf("\n\n\n\nSTART CODE WITH THIS INPUT: %s\n\n", input); // Print the input string
		
	uint8_t* dataToSend = fillDataArray(input); // Convert data to base2

	unsigned int time;

	time = (1000 / OUTPUT_BAUDRATE) * dataLength;

	printf("Baudtime: %i\n", 1000/OUTPUT_BAUDRATE);
	printf("Time needed to send: %i ms\n", time);


	sendData(dataToSend);

	printf("datalength: %i\n", dataLength);

	char* received = convertToData(receivedData, dataLength); // Convert base2 to data

	if (received[0] == -1)
	{
		printf("Error detected...\n");
	}
	else
	{
		printf("\nReceived data: %s\n\n", received); // Print the received data
	}

	printf("Entering loop now....\n");
	PORTB &= ~(1 << OUTPUT_PIN);

	while (1)
	{
		// Main loop
	}
}

void sendData(uint8_t dataToSend[800])
{
	printf("datalength: %i\n", dataLength);


	int i;

	for (i = 0; i < dataLength; i++)
	{
		if ((dataToSend[i] && 0b1) == 0)
		{
			PORTB &= ~(1 << OUTPUT_PIN);
		}
		else
		{
			PORTB |= (1 << OUTPUT_PIN);
		}

		//printf("%i  ", i);

		_delay_ms((1000/OUTPUT_BAUDRATE)/2);

		uint8_t memes = PINC & (1 << INPUT_PIN);

		printf("%i -> %i \n",(dataToSend[i] && 0b1) , memes);

		receivedData[i] = memes;

		_delay_ms((1000/OUTPUT_BAUDRATE)/2);
	}
}