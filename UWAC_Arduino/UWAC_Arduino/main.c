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

FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART0Init();
	stdout =& usart0_str;

    while (1) 
    {
		printf("Send debug data to PC\n");

		_delay_ms(1000);
    }
}

