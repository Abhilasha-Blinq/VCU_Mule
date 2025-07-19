/*
 * dma.c
 *
 *  Created on: 17-Jul-2025
 *      Author: 91626
 */
#include "sdk_project_config.h"
#include "dma.h"
#include "gear_shifter.h"
#include "Throttle_read.h"

#define GEAR_RATIO 6.43

extern uint16_t delayValue;
extern flexcan_msgbuff_t recvBuff302;
extern uint16_t speed_rpm_motor,wheel_rpm,speed_kmph ;
extern MYADCDMA0 ADC1_Sample;
extern uint8_t brake;
extern uint8_t mc_cmd[8];
extern uint8_t drive_status;

uint8_t implausiblity;
double curr_distance;
double odometer = 0;
int temp,throttle_data,map_result1,map_result2;

edma_loop_transfer_config_t loopConfig = {
    .majorLoopIterationCount = 0,
    .srcOffsetEnable = false,
    .dstOffsetEnable = false,
    .minorLoopOffset = 0,
    .minorLoopChnLinkEnable = false,
    .minorLoopChnLinkNumber = 0,
    .majorLoopChnLinkEnable = false,
    .majorLoopChnLinkNumber = 0
};

const adc_chan_config_t adConv1_ChnConfig0 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT2,
};

const adc_chan_config_t adConv1_ChnConfig1 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT11,
};

const adc_chan_config_t adConv1_ChnConfig2 = {
  .interruptEnable = false,
  .channel = ADC_INPUTCHAN_EXT8,
};

edma_transfer_config_t transferConfig = {
    .srcAddr = 0,
    .destAddr = 0,
    .srcTransferSize = EDMA_TRANSFER_SIZE_2B,
    .destTransferSize = EDMA_TRANSFER_SIZE_2B,
    .srcOffset= 4,
    .destOffset = 2,
    .srcLastAddrAdjust =0,
    .destLastAddrAdjust = 0,
    .srcModulo = EDMA_MODULO_OFF,
    .destModulo = EDMA_MODULO_OFF,
    .minorByteTransferCount = 2,
    .scatterGatherEnable = false,
    .scatterGatherNextDescAddr = 0,
   .interruptEnable = true,
    .loopTransferConfig = &loopConfig
};


void ADC_Init()
{
	ADC_DRV_Reset(INST_ADC_1);
	ADC_DRV_ConfigConverter(INST_ADC_1, &adc_config_1_ConvConfig0);
	ADC_DRV_AutoCalibration(INST_ADC_1);
	ADC_DRV_ConfigChan(INST_ADC_1, 0UL, &adConv1_ChnConfig0);
	ADC_DRV_ConfigChan(INST_ADC_1, 1UL, &adConv1_ChnConfig1);
	ADC_DRV_ConfigChan(INST_ADC_1, 2UL, &adConv1_ChnConfig2);
}

void PDB1_Init(void)
{
	PDB_DRV_Init(INST_PDB, &pdb_config_1_timerConfig0);
	PDB_DRV_Enable(INST_PDB);
	PDB_DRV_ConfigAdcPreTrigger(INST_PDB, 0UL, &pdb_config_1_adcTrigConfig0);
	PDB_DRV_ConfigAdcPreTrigger(INST_PDB, 0UL, &pdb_config_1_adcTrigConfig1);
	PDB_DRV_ConfigAdcPreTrigger(INST_PDB, 0UL, &pdb_config_1_adcTrigConfig2);

	// set PDB0 counter period to delayValue (~30us)
	PDB_DRV_SetTimerModulusValue(INST_PDB, (uint32_t) delayValue);

	PDB_DRV_LoadValuesCmd(INST_PDB);
}

void DMA_Init(void)
{
	EDMA_DRV_Init(&dmaController_State, &dmaController_InitConfig, edmaChnStateArray, edmaChnConfigArray, EDMA_CONFIGURED_CHANNELS_COUNT);
}

void DMA_transfer(uint8_t channel, uint8_t * srcBuff, uint16_t * dstBuff, uint32_t size)
{
	dma_request_source_t DmaReq;

	/* configure transfer source and destination addresses */
	transferConfig.srcAddr 				= (uint32_t)srcBuff;
	transferConfig.destAddr 			= (uint32_t)dstBuff;
	transferConfig.srcLastAddrAdjust 	= -(4 * size);
	transferConfig.destLastAddrAdjust	= -(2 * size);
	loopConfig.majorLoopIterationCount	= size;
	//transferConfig.minorByteTransferCount = size / 3 * 2;

		DmaReq = EDMA_REQ_ADC1;

	/* configure the eDMA channel for a loop transfer (via transfer configuration structure */
	EDMA_DRV_ConfigLoopTransfer(channel, &transferConfig);

	  /* select hw request */
	EDMA_DRV_SetChannelRequestAndTrigger(channel, DmaReq, false);

	/* start the channel */
	EDMA_DRV_StartChannel(channel);
}

void DMA_Callback(void *parameter, edma_chn_status_t status)
{
	(void)status;
	(void)parameter;

	speed_rpm_motor = (((recvBuff302.data[7] & 0xFF) << 8) | ((recvBuff302.data[6] & 0xFF)));

	wheel_rpm = speed_rpm_motor/GEAR_RATIO;

	speed_kmph = (wheel_rpm * 0.093027);

	curr_distance = (speed_kmph * 0.000138888889);
	odometer +=curr_distance;

	map_result1= Map(ADC1_Sample.ADC1_SE2,Min_ADCch2,Max_ADCch2,ADC_offsetch2);
	map_result2= Map(ADC1_Sample.ADC1_SE11,Min_ADCch11,Max_ADCch11,ADC_offsetch11);

	implausiblity = Implausibility_check(map_result1,map_result2);

	if(ADC1_Sample.ADC1_SE8 > 900)
	{
		brake = ON;
	 PINS_DRV_ClearPins(PTD, 1 << 16);
	}

	else
	{
		brake = OFF;
	 PINS_DRV_SetPins(PTD, 1 << 16);
	}

	if(drive_status == P || drive_status == N)
	{
		throttle_data = 0;
		mc_cmd[0] =MC_PARKING_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x00;//Reverse direction
		mc_cmd[3] = THROTTLE_MODE;
	}

	else if(drive_status == D)
	{
		throttle_data = (((map_result1 + map_result2)/2)*2.56);
		mc_cmd[0] =MC_FORWARD_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x00;//Reserved
		mc_cmd[3] = THROTTLE_MODE;
	}
	else if(drive_status == R)
	{
		throttle_data =(((map_result1 + map_result2)/2)*2.56);//(((map_result1 + map_result2)/5));
		mc_cmd[0] = MC_BACKWARD_STATE;
		mc_cmd[1] = 0x00;//Reserved
		mc_cmd[2] = 0x40;//Reverse direction
		mc_cmd[3] = THROTTLE_MODE;
	}

	mc_cmd[4] =(uint8_t)(throttle_data % 256);//throttle val rem
	mc_cmd[5] =(uint8_t)(throttle_data / 256);//throttle val quotient
	mc_cmd[6] =(uint8_t)(throttle_data % 256);
	mc_cmd[7] =(uint8_t)(throttle_data / 256);

}

