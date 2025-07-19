/*
 * Throttlr_read.h
 *
 *  Created on: 07-Jul-2025
 *      Author: Rohit
 */

#ifndef INC_THROTTLE_READ_H_
#define INC_THROTTLE_READ_H_

#include "stdio.h"

#define PDLY_TIMEOUT 	30UL
#define INST_ADC_1 1
#define INST_PDB 1
#define Min_ADCch2    720
#define Max_ADCch2    1800
#define ADC_offsetch2 30

#define Min_ADCch11   2370
#define Max_ADCch11   3600
#define ADC_offsetch11 30
#define DMA_CHANNEL0	0

/** Total 32 message buffers are present including tx and rx*/
#define TX_MAILBOX  	(1UL)
#define TX_MSG_ID   	(1UL)
#define RX_MAILBOX0  	(0UL)
#define RX_MAILBOX1  	(2UL)
#define RX_MAILBOX2  	(3UL)
#define RX_MAILBOX3  	(4UL)
#define RX_MAILBOX4		(5UL)
#define RX_MSG_ID   	(2UL)



#define NULL ((void *)0)

typedef struct
 {
	  uint16_t ADC1_SE2;
	  uint16_t ADC1_SE11;
	  uint16_t ADC1_SE8;

}MYADCDMA0;


int Map(uint16_t ADC_raw,uint16_t Min_adc,uint16_t Max_adc,uint16_t offset_adc);
uint8_t Implausibility_check(int Apps1,int Apps2);


#endif /* INC_THROTTLE_READ_H_ */
