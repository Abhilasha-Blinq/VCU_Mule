/*
 * startup.c
 *
 *  Created on: 21-Jul-2025
 *      Author: Rohit
 */


#include "sdk_project_config.h"
#include "gpio.h"
#include "gear_shifter.h"
#include "startup.h"
#include "interrupt_manager.h"

uint8_t vehicle_state = OFF_STATE;
extern uint8_t brake;
extern uint32_t int_status;

void Start_Button_Init()
{
	PINS_DRV_SetPinsDirection(PTC, ~((1 << START_BUTTON)));

	PINS_DRV_SetPinIntSel(BTN_PORTC, START_BUTTON, PORT_INT_FALLING_EDGE);

	/* Install buttons ISR for portC */
	INT_SYS_InstallHandler(PORTC_IRQn, &PortC_ISR, NULL);//install interrupt hdlr for portc
}

void PortC_ISR()
{
	printf("portC ISR invoked\n");

	/**TODO: Use case of Mode pin in gear shifter*/
	  int_status = PINS_DRV_GetPortIntFlag(BTN_PORTC);

	  if (int_status & (1 << START_BUTTON))
	  {

	      switch (vehicle_state)
	      {
	          case DOOR_UNLOCK_STATE:
	              if (brake == ON)
	              {
	                  vehicle_state = ACC_MODE_2;
	              }
	              else
	              {
	                  vehicle_state = ACC_MODE_1;
	              }
	              break;

	          case ACC_MODE_1:
	              /**Returning to DOOR_UNLOCK_STATE if start is pressed again*/
	              vehicle_state = DOOR_UNLOCK_STATE;

	              break;

	          case ACC_MODE_2:
	              if (brake == ON)
	              {
	                  vehicle_state = START_MODE;
	                  Init_Start_Mode();
	              }

	              else
	              {
	            	  vehicle_state = DOOR_UNLOCK_STATE;
	              }
	              break;

	          case START_MODE:
	              // Optional: Define behavior if Start button is pressed again in START_MODE
	              break;

	          default:
	              // Handle unexpected states
	              break;
	      }
	  }
	  int_status &= ~(0xFFFFFFFF);

	  PINS_DRV_ClearPortIntFlagCmd(BTN_PORTC);
}
