/*
 * UWAC_Arduino.c
 *
 * Created: 10-3-2016 08:44:13
 * Author : Kevin Slagmolen
 */ 

#include "Util/defines.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Util/USART.h"
#include "Util/I2C.h"
#include "data_conversion.h"

FILE usart0_output = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);	// Output file for USART
FILE usart0_input = FDEV_SETUP_STREAM(NULL, USART0GetByte, _FDEV_SETUP_READ);		// Input file for USART

int main(void)
{
	/* USART INIT START */
	USART0Init();
	stdout =& usart0_output;
	stdin =& usart0_input;
	/* USART INIT STOP */

	i2c_init(); // Init I2C (TWI)

	char input[55] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // MAX STRING LENGTH BEFORE UC DOES WIERD STUFF

	#ifdef DEBUG
	printf("\n\n\n\nSTART CODE WITH THIS INPUT: %s\n\n", input); // Print the input string
	#endif // DEBUG

	int* dataToSend = fillDataArray(input); // Convert data to base4
	char* received = convertToData(dataToSend, dataLength); // Convert base4 to data

	#ifdef DEBUG
	printf("\nReceived data: %s\n\n", received); // Print the received data

	printf("Entering loop now....\n");
	#endif

    while (1) 
    {
		// Main loop
    }
}
