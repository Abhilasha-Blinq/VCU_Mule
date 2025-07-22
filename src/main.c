/*!
** Copyright 2020 NXP
** @file main.c
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary configuration files. */
#include "sdk_project_config.h"
#include "CAN.h"

volatile int exit_code = 0;

/* User includes */
#include "stdio.h"
#include "gear_shifter.h"
#include "Throttle_read.h"
#include "interrupt_manager.h"
#include "delay.h"
#include "gpio.h"
#include "timer.h"
#include "dma.h"

#define PDLY_TIMEOUT 	30UL
#define TX_MAILBOX  	(1UL)
#define TX_MSG_ID   	(1UL)
#define RX_MAILBOX0  	(0UL)
#define RX_MAILBOX1  	(2UL)
#define RX_MAILBOX2  	(3UL)
#define RX_MAILBOX3  	(4UL)
#define RX_MAILBOX4		(5UL)
#define RX_MSG_ID   	(2UL)

uint16_t delayValue = 0;
uint8_t mc_cmd[8];
flexcan_msgbuff_t recvBuff301,recvBuff302,recvBuff303,recvBuff304,recvBuff305;
MYADCDMA0 ADC1_Sample;

void Clock_init(void)
{
	 /* Write your local variable definition here */
	 status_t status;

	/* Initialize clock module */
	status = CLOCK_DRV_Init(&clockMan1_InitConfig0);
	 DEV_ASSERT(status == STATUS_SUCCESS);

}


int main(void)
{
    /* Write your code here */
	Clock_init();

	GPIO_Init();

	PDB1_Trigger_Timer_Init();

	ADC_Init();

	if(!calculateIntValue(&pdb_config_1_timerConfig0, PDLY_TIMEOUT, &delayValue))
		{
			while(1);
		}

	 PDB1_Init();

	 DMA_Init();

	 DMA_transfer(EDMA_CHN0_NUMBER, &(ADC1->R[0]),&ADC1_Sample, 3);

	 TRGMUX_DRV_Init(INST_TRGMUX, &trgmux1_InitConfig0);

	 Start_Button_Init();

	//LPIT_Init();

    for(;;)
    {
    	delay(0x6A180);//according to 50ms
        printf("transmitted\n");
		SendCANData(TX_MAILBOX, 0x101, &mc_cmd, 8UL);
    	while(FLEXCAN_DRV_GetTransferStatus(INST_FLEXCAN_CONFIG_1,TX_MAILBOX)== STATUS_BUSY);

    	FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX0, &recvBuff301);

		FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX1, &recvBuff302);

		FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX2, &recvBuff303);

		FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX3, &recvBuff304);

		FLEXCAN_DRV_Receive(INST_FLEXCAN_CONFIG_1, RX_MAILBOX4, &recvBuff305);

   	 //delay(100);

        if(exit_code != 0)
        {
            break;
        }
    }
    return exit_code;
}


/* END main */
/*!
** @}
*/
