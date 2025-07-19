/*
 * CAN.c
 *
 *  Created on: 15-Jul-2025
 *      Author: 91626
 */
#include "sdk_project_config.h"
#include "CAN.h"

#define TX_MAILBOX  	(1UL)
#define TX_MSG_ID   	(1UL)
#define RX_MAILBOX0  	(0UL)
#define RX_MAILBOX1  	(2UL)
#define RX_MAILBOX2  	(3UL)
#define RX_MAILBOX3  	(4UL)
#define RX_MAILBOX4		(5UL)
#define RX_MSG_ID   	(2UL)

void CAN_ReceiveConfig1(void)
{
	flexcan_data_info_t dataInfo =
		    {
		            .data_length =8U,
		            .msg_id_type = FLEXCAN_MSG_ID_EXT,
		            .enable_brs  = false,
		            .fd_enable   = false,
		            .fd_padding  = 0U
		    };

		/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
		    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX0, &dataInfo, 0x301);
}

void CAN_ReceiveConfig2(void)
{
	flexcan_data_info_t dataInfo =
		    {
		            .data_length =8U,
		            .msg_id_type = FLEXCAN_MSG_ID_EXT,
		            .enable_brs  = false,
		            .fd_enable   = false,
		            .fd_padding  = 0U
		    };

		/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
		    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX1, &dataInfo, 0x302);
}

void CAN_ReceiveConfig3(void)
{
	flexcan_data_info_t dataInfo =
		    {
		            .data_length =8U,
		            .msg_id_type = FLEXCAN_MSG_ID_EXT,
		            .enable_brs  = false,
		            .fd_enable   = false,
		            .fd_padding  = 0U
		    };

		/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
		    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX2, &dataInfo, 0x303);
}

void CAN_ReceiveConfig4(void)
{
	flexcan_data_info_t dataInfo =
		    {
		            .data_length =8U,
		            .msg_id_type = FLEXCAN_MSG_ID_EXT,
		            .enable_brs  = false,
		            .fd_enable   = false,
		            .fd_padding  = 0U
		    };

		/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
		    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX3, &dataInfo, 0x304);
}

void CAN_ReceiveConfig5(void)
{
	flexcan_data_info_t dataInfo =
		    {
		            .data_length =8U,
		            .msg_id_type = FLEXCAN_MSG_ID_EXT,
		            .enable_brs  = false,
		            .fd_enable   = false,
		            .fd_padding  = 0U
		    };

		/* Configure RX message buffer with index RX_MSG_ID and RX_MAILBOX */
		    FLEXCAN_DRV_ConfigRxMb(INST_FLEXCAN_CONFIG_1, RX_MAILBOX4, &dataInfo, 0x305);
}

void SendCANData(uint32_t mailbox, uint32_t messageId, uint8_t * data, uint32_t len)
{
    /* Set information about the data to be sent
     *  - 1 byte in length
     *  - Standard message ID
     *  - Bit rate switch enabled to use a different bitrate for the data segment
     *  - Flexible data rate enabled
     *  - Use zeros for FD padding
     */
    flexcan_data_info_t dataInfo =
    {
            .data_length = len,
            .msg_id_type = FLEXCAN_MSG_ID_EXT,
            .enable_brs  = false,
            .fd_enable   = false,
            .fd_padding  = 0U
    };

    /* Configure TX message buffer with index TX_MSG_ID and TX_MAILBOX*/
    FLEXCAN_DRV_ConfigTxMb(INST_FLEXCAN_CONFIG_1, mailbox, &dataInfo, messageId);

    /* Execute send non-blocking */
    FLEXCAN_DRV_Send(INST_FLEXCAN_CONFIG_1, mailbox, &dataInfo, messageId, data);
}

void FlexCANInit(void)
{
    /*
     * Initialize FlexCAN driver
     *  - 8 byte payload size
     *  - FD enabled
     *  - Bus clock as peripheral engine clock
     */
    FLEXCAN_DRV_Init(INST_FLEXCAN_CONFIG_1, &flexcanState0, &flexcanInitConfig0);
}

