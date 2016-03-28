/*
 * AD9913.h
 *
 * Created: 10-3-2016 13:17:06
 *  Author: Kevin Slagmolen
 */ 
 

#ifndef AD9913_H_
#define AD9913_H_

#include "../Util/I2C.h"
#include "../Util/USART.h"

struct AD9913_settings
{
	int frequency1;
	int frequency2;
	int frequency3;
	int frequency4;

	int chipSelectPin;
};

struct AD9913_profile
{
	int profilePin0;
	int profilePin1;
	int profilePin2;
};

void initAD9913(AD9913_settings ad9913_settings);
void setOutputToProfile(AD9913_profile ad9913_profile, uint8_t profile);

#endif /* AD9913_H_ */