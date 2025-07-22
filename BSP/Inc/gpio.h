/*
 * gpio.h
 *
 *  Created on: 17-Jul-2025
 *      Author: Rohit
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#define BTN1_PIN        15U //to select mode
#define BTN2_PIN        8U// drive
#define BTN3_PIN        9U//neutral
#define BTN4_PIN        10U//reverse
#define BTN5_PIN        11U//parking
#define START_BUTTON    13U//Ignition button on BCM

#define BTN_PORTB						PORTB
#define BTN_PORTE						PORTE
#define BTN_PORTC						PORTC

typedef enum
{
	OFF_STATE = 0,
	DOOR_UNLOCK_STATE,
	ACC_MODE_1,
	ACC_MODE_2,
	START_MODE,
	RUN_STATE
}Vehicle_state;


void GPIO_Init(void);
void Start_Button_Init(void);
void buttonC_ISR(void);
void Init_Start_Mode(void);

#endif /* INC_GPIO_H_ */
