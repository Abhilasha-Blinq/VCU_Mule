/*
 * drive_state_change.c
 *
 *  Created on: 02-Jul-2025
 *      Author: Rohit
 */

#include"stdio.h"
#include "gear_shifter.h"

uint8_t drive_status = P; /** Denotes current state of car.It is initialised in parking mode*/
uint8_t gear_state = PARKING,brake = OFF,error;
uint16_t speed_rpm_motor,wheel_rpm,speed_kmph;
uint8_t speed =0;
extern int throttle_data;
extern uint8_t mc_cmd[8];


void drive_state_change()
{
	/** gear_state-> current gear shifter position, brake-> if applied/not,
	 *  speed-> vehicle speed , throttle_data-> if throttle pressed/not,
	 *  error-> bms/motor_controller error*/

	if(gear_state == DRIVE && brake == ON && speed < 1.3 &&\
		throttle_data == 0 && error == 0)
	{
		drive_status = D;

		mc_cmd[0] =MC_FORWARD_STATE;
				mc_cmd[1] = 0x00;//Reserved
				mc_cmd[2] = 0x00;//Reserved
				mc_cmd[3] = THROTTLE_MODE;

		/*mc_cmd[0] = MC_FORWARD_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x00;//Reserved
		mc_cmd[3] = THROTTLE_MODE;*/

	}

	else if(gear_state == REVERSE && brake == ON && speed < 1.3 &&\
			 throttle_data == 0 && error == 0)
	{
		drive_status = R;

		mc_cmd[0] =MC_BACKWARD_STATE;
				mc_cmd[1] = 0x00;//Reserved
				mc_cmd[2] = 0x40;//Reserved
				mc_cmd[3] = THROTTLE_MODE;

		/*mc_cmd[0] = MC_BACKWARD_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x40;
		mc_cmd[3] = THROTTLE_MODE;*/

	}

	else if(gear_state == NEUTRAL)
	{
		drive_status = N;

		mc_cmd[0] = MC_FORWARD_STATE;//MC_PARKING_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x00;//Reserved
		mc_cmd[3] = THROTTLE_MODE;
		mc_cmd[4] = 0x00;
		mc_cmd[5] = 0x00;
		mc_cmd[6] = 0x00;
		mc_cmd[7] = 0x00;
	}

	else if(gear_state == PARKING && brake == ON && speed < 1.3 &&\
			 throttle_data == 0)
	{
		drive_status = P;

		mc_cmd[0] = MC_PARKING_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x00;//Reserved
		mc_cmd[3] = THROTTLE_MODE;
		mc_cmd[4] = 0x00;
		mc_cmd[5] = 0x00;
		mc_cmd[6] = 0x00;
		mc_cmd[7] = 0x00;
	}
}

