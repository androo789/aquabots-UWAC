/*
 * defines.h
 *
 * Created: 10-3-2016 08:45:15
 *  Author: Kevin Slagmolen
 */ 


#ifndef DEFINES_H_
#define DEFINES_H_

#define F_CPU			16000000UL
#define USART_BAUDRATE	9600
#define UBRR_VALUE		(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#endif /* DEFINES_H_ */