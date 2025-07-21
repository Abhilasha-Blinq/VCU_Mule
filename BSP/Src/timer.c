/*
 * timer.c
 *
 *  Created on: 17-Jul-2025
 *      Author: Rohit
 */

#include "sdk_project_config.h"
#include "timer.h"
#include "interrupt_manager.h"


#define LPIT_CHANNEL 0U


void PDB1_Trigger_Timer_Init()
{
	LPTMR_DRV_Init(INST_LPTMR_1, &lptmr_1_config0, false);

	/* Install IRQ handler for LPTMR interrupt */
	INT_SYS_InstallHandler(LPTMR0_IRQn, &lptmrISR, ((void *)0));

	/* Enable IRQ for LPTMR */
	INT_SYS_EnableIRQ(LPTMR0_IRQn);

	/* Start LPTMR counter */
	LPTMR_DRV_StartCounter(INST_LPTMR_1);
}

void lptmrISR(void)
{
    /* Clear compare flag */
    LPTMR_DRV_ClearCompareFlag(INST_LPTMR_1);

}

void LPIT_ISR(void)
{
	LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL));
}

void LPIT_Init(void)
{
	status_t status;
	LPIT_DRV_Init(INST_LPIT_CONFIG_1, &lpit1_InitConfig);
		        /* Initialize LPIT channel 0 and configure it as a periodic counter
		         * which is used to generate an interrupt every second.
		         */
	status = LPIT_DRV_InitChannel(INST_LPIT_CONFIG_1, LPIT_CHANNEL, &lpit1_ChnConfig0);
	DEV_ASSERT(status == STATUS_SUCCESS);

	/* Install LPIT_ISR as LPIT interrupt handler */
	INT_SYS_InstallHandler(LPIT0_Ch0_IRQn, &LPIT_ISR, NULL);

	/* Start LPIT0 channel 0 counter */
	LPIT_DRV_StartTimerChannels(INST_LPIT_CONFIG_1, (1 << LPIT_CHANNEL));
}

