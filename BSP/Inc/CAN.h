/*
 * CAN.h
 *
 *  Created on: 15-Jul-2025
 *      Author: 91626
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

void FlexCANInit(void);
void SendCANData(uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len);
void CAN_ReceiveConfig1(void);
void CAN_ReceiveConfig2(void);
void CAN_ReceiveConfig3(void);
void CAN_ReceiveConfig4(void);
void CAN_ReceiveConfig5(void);


#endif /* INC_CAN_H_ */
