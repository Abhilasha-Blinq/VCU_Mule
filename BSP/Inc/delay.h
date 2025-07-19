/*
 * delay.h
 *
 *  Created on: 07-Jul-2025
 *      Author: Rohit
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

bool calculateIntValue(const pdb_timer_config_t *pdbConfig, uint32_t uSec, uint16_t *intValue);
void delay(uint32_t cnt);

#endif /* INC_DELAY_H_ */
