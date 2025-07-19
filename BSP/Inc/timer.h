/*
 * timer.h
 *
 *  Created on: 17-Jul-2025
 *      Author: 91626
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void lptmrISR(void);
void PDB1_Trigger_Timer_Init(void);
void LPIT_ISR(void);

#endif /* INC_TIMER_H_ */
