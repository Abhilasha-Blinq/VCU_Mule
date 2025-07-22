/*
 * gear_shifter.h
 *
 *  Created on: 05-Jul-2025
 *      Author: Rohit
 */

#ifndef INC_GEAR_SHIFTER_H_
#define INC_GEAR_SHIFTER_H_

#include"stdio.h"

#define SPEED_MODE 					0x0C
#define THROTTLE_MODE 				0x50
#define TORQUE_MODE 				0x0A
#define THROTTLE_CONTROL 			0x00

#define MC_BACKWARD_STATE			0x06
#define MC_FORWARD_STATE  			0x05
#define MC_PARKING_STATE     		0x04


#endif /* INC_GEAR_SHIFTER_H_ */
typedef enum{
	DRIVE = 0,//0
	NEUTRAL,//1
	PARKING,//2
	REVERSE//3
}state;

typedef enum{
	D = 0,//0
	N,//1
	P,//2
	R//3
}drive_state;

typedef enum{
	ON =0,
	OFF//brake is active low
}brake_state;

void drive_state_change(void);
void Gear_Interrupt_init(void);
void PortE_ISR(void);
void PortB_ISR(void);
