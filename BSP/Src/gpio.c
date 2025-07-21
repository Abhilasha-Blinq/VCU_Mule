/*
 * gpio.c
 *
 *  Created on: 17-Jul-2025
 *      Author: Rohit
 */
#include "sdk_project_config.h"
#include "gpio.h"
#include "gear_shifter.h"

void GPIO_Init()
{
	PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);

	 /* Setup button pin */
	PINS_DRV_SetPinsDirection(PTE, ~((1 << BTN1_PIN))); //configure PE15

	/** To configure PE15 as 5V input pin*/
	//PINS_DRV_SetPins(PTA, 1 << 14);

	//PINS_DRV_ClearPins(PTA, 1 << 11);

	/* Setup button pin */
	PINS_DRV_SetPinsDirection(PTB, ~((1 << BTN2_PIN)|(1 << BTN3_PIN)|(1 << BTN4_PIN)|(1 << BTN5_PIN))); //configure PB8,9,10,11

}
