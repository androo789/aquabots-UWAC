/*
 * UWAC_Arduino_2fsk.c
 *
 * Created: 1-4-2016 19:06:22
 * Author : Kevin Slagmolen
 */ 

 
 #include "Util/defines.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Util/USART.h"
#include "data_conversion.h"

void sendData(int* dataToSend); // Test function to see if the data is put on the output pin (pin 13)

FILE usart0_output = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);	// Output file for USART
FILE usart0_input = FDEV_SETUP_STREAM(NULL, USART0GetByte, _FDEV_SETUP_READ);		// Input file for USART

int main(void)
{
	DDRB |= (1 << DDB5);

	PORTB |= (1 << DDB5);

	/* USART INIT START */
	USART0Init();
	stdout =& usart0_output;
	stdin =& usart0_input;
	/* USART INIT STOP */

	//char input[55] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // MAX STRING LENGTH BEFORE UC DOES WIERD STUFF
	//char input[55] = "test";

	char input[100] = "Now, this is a story all about how My life got flipped-turned upside down";

	#ifdef DEBUG
	printf("\n\n\n\nSTART CODE WITH THIS INPUT: %s\n\n", input); // Print the input string
	#endif // DEBUG
		
	int* dataToSend = fillDataArray(input); // Convert data to base4
	char* received = convertToData(dataToSend, dataLength); // Convert base4 to data

	#ifdef DEBUG
	printf("\nReceived data: %s\n\n", received); // Print the received data

	unsigned int time;

	time = (1000 / BAUDRATE) * dataLength;

	printf("Baudtime: %i\n", 1000/BAUDRATE);
	printf("Time needed to send: %i ms\n", time);

	PORTB &= ~(1 << DDB5);

	sendData(dataToSend);

	printf("Entering loop now....\n");
	#endif

	while (1)
	{
		// Main loop
	}
}

void sendData(int* dataToSend)
{
	int i;

	for (i = 0; i < dataLength; i++)
	{
		if (dataToSend[i] == 0)
			DDRB &= ~(1 << DDB5);
		else
			DDRB |= (1 << DDB5);

		_delay_ms(1000/BAUDRATE);
	}
}