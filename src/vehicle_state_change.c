/*
 * Vehicle_state_change.c
 *
 *  Created on: 21-Jul-2025
 *      Author: Rohit
 */
#include "CAN.h"
#include "gear_shifter.h"
#include "gpio.h"

void Init_Start_Mode()
{
	Gear_Interrupt_init();

	FlexCANInit();

	CAN_ReceiveConfig1();

    CAN_ReceiveConfig2();

    CAN_ReceiveConfig3();

    CAN_ReceiveConfig4();

    CAN_ReceiveConfig5();

}


