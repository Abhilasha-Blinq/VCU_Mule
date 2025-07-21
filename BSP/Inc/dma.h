/*
 * dma.h
 *
 *  Created on: 17-Jul-2025
 *      Author: Rohit
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_

void PDB1_Init(void);
void DMA_Init(void);
void DMA_transfer(uint8_t channel, uint8_t * srcBuff, uint16_t * dstBuff, uint32_t size);
void ADC_Init(void);

#endif /* INC_DMA_H_ */
