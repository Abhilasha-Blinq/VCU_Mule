/*
 * gear_shifter.c
 *
 *  Created on: 17-Jul-2025
 *      Author: 91626
 */
#include "sdk_project_config.h"
#include "gear_shifter.h"

uint32_t int_status;
extern uint8_t gear_state;
extern uint8_t drive_status;


void Gear_Interrupt_init()
{
	/* Setup button pins interrupt
	* Set interrupt for rising edge for PE14*/

	PINS_DRV_SetPinIntSel(BTN_PORTE, BTN1_PIN, PORT_INT_FALLING_EDGE);

	PINS_DRV_SetPinIntSel(BTN_PORTB, BTN2_PIN, PORT_INT_FALLING_EDGE);

	PINS_DRV_SetPinIntSel(BTN_PORTB, BTN3_PIN, PORT_INT_FALLING_EDGE);

	PINS_DRV_SetPinIntSel(BTN_PORTB, BTN4_PIN, PORT_INT_FALLING_EDGE);

	PINS_DRV_SetPinIntSel(BTN_PORTB, BTN5_PIN, PORT_INT_FALLING_EDGE);

	/* Install buttons ISR for portE */
	INT_SYS_InstallHandler(PORTE_IRQn, &buttonE_ISR, NULL);//install interrupt hdlr for porte

	/* Install buttons ISR for portB */
	INT_SYS_InstallHandler(PORTB_IRQn, &buttonB_ISR, NULL);//install interrupt hdlr for portb

	/* Enable buttons interrupt */
	INT_SYS_EnableIRQ(PORTE_IRQn);//enable interrupt for porte

	/* Enable buttons interrupt */
	INT_SYS_EnableIRQ(PORTB_IRQn);//enable interrupt for portb

}

void buttonE_ISR()
{
  printf("portE ISR invoked\n");//ISR for PE15(sports/eco mode)

  int_status = PINS_DRV_GetPortIntFlag(BTN_PORTE);
/**TODO: Use case of Mode pin in gear shifter*/
  if(int_status & (1 << BTN1_PIN))
  	{
	//  gear_state= MODE;
  	}
  int_status &= ~(0xFFFFFFFF);

  PINS_DRV_ClearPortIntFlagCmd(BTN_PORTE);
}

void buttonB_ISR()
{
	printf("portB ISR invoked\n");
	/**Check isfr REGISTER for portb, to know which button has been pressed*/
	int_status = PINS_DRV_GetPortIntFlag(BTN_PORTB);

	if(int_status & (1 << BTN2_PIN))
	{
		gear_state= DRIVE;
	}

	else if(int_status & (1 << BTN3_PIN))
	{
		gear_state= NEUTRAL;
	}

	else if(int_status & (1 << BTN4_PIN))
	{
		gear_state= REVERSE;
	}

	else if(int_status & (1 << BTN5_PIN))
	{
		gear_state= PARKING
				;
	}

	int_status &= ~(0xFFFFFFFF);

	PINS_DRV_ClearPortIntFlagCmd(BTN_PORTB);

	drive_state_change();
}
