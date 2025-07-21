/*
 * Throttle_control.c
 *
 *  Created on: 02-Jul-2025
 *      Author: Rohit
 */
#include "sdk_project_config.h"
#include "stdio.h"
/**TODO: Implement stages for ADC overrange and signal-gnd short*/


extern int temp;
void print(void)
{
	printf(" GO blinq");
}

int Map(uint16_t ADC_raw,uint16_t Min_adc,uint16_t Max_adc,uint16_t offset_adc)
{
	    temp = (((float)(ADC_raw - (Min_adc + offset_adc))) / ((float)((Max_adc - offset_adc) - (Min_adc + offset_adc)))) * 100.00;
	    if (temp < 0.00)
	    {
	        return 0;
	    }
	    else if (temp > 100.00)
	    {
	        return 100;
	    }
	    else
	    {
	        return temp;
	    }

}

/** This function will cater range and power or gnd/short or signal short*/
uint8_t Implausibility_check(int Apps1,int Apps2)
{
	if((Apps1-Apps2) >10 || ((Apps2-Apps1)>10))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


