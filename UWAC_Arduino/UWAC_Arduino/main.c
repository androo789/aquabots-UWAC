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

FILE usart0_output = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);
FILE usart0_input = FDEV_SETUP_STREAM(NULL, USART0GetByte, _FDEV_SETUP_READ);
FILE usart0_io = FDEV_SETUP_STREAM(USART0SendByte, USART0GetByte, _FDEV_SETUP_RW);

int main(void)
{
	USART0Init();
	stdout =& usart0_output;
	stdin =& usart0_input;

	i2c_init();

	char tmp;
	char input[100] = "test";

	int i = 0;

	/*printf("Scanning now.\n");
	while (i < 4)
	{
		scanf("%c", &tmp);
		input[i++] = tmp;
		printf("%s\n", input);
	}*/

	int* dataToSend = fillDataArray(input);
	char* received = convertToData(dataToSend, dataLength);

	printf("\nReceived data: %s\n\n", received);

	printf("Entering loop now....\n");
    while (1) 
    {
		//printf("Send debug data to PC\n");
		/*scanf("%c", &input);
		printf("You wrote: %c\n", input);*/
    }
}

