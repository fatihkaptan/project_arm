/***********************************************************************************************************************
 * File Name    : common_utils.c
 * Description  : Contains macros data structures and functions used in common_utils.c for RTT rtos aware framework
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2021 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "common_utils.h"

#if (BSP_CFG_RTOS == 1)
/*
 * global variables
 */
TX_QUEUE rtt_op_data_queue;
TX_QUEUE rtt_ip_data_queue;
TX_EVENT_FLAGS_GROUP rtt_event;
TX_BYTE_POOL   byte_pool;

static CHAR *byte_pool_name = "rtt_processing_block";
static CHAR byte_memory[BYTE_POOL_SIZE] = {'\0'};
static uint8_t queue_memory_op_rtt_obj[20] = {'\0'};
static uint8_t queue_memory_ip_rtt_obj[20] = {'\0'};
#endif

UINT rtt_frameowrk_init(VOID)
{
#if (BSP_CFG_RTOS == 1)

    UINT err= TX_SUCCESS;

    err = tx_byte_pool_create(&byte_pool,byte_pool_name,(VOID *)&byte_memory[0],BYTE_POOL_SIZE);
    if (TX_SUCCESS != err)
    {
        return err;
    }

    err = tx_queue_create(&rtt_op_data_queue, (CHAR *)"rtt_op_queue", 1, &queue_memory_op_rtt_obj, sizeof(queue_memory_op_rtt_obj));
    if (TX_SUCCESS !=err)
    {
        tx_byte_pool_delete(&byte_pool);
        return err;
    }

    err = tx_queue_create(&rtt_ip_data_queue, (CHAR *)"NetX_wifi_thread_input_queue", 1, &queue_memory_ip_rtt_obj, sizeof(queue_memory_ip_rtt_obj));
    if (TX_SUCCESS !=err)
    {
        tx_byte_pool_delete(&byte_pool);
        tx_queue_delete(&rtt_op_data_queue);
    }

    return err;
#endif
}

/*
 * Can be called any where after rtt_framework_init() function call
 * for graceful clean up
 */
VOID rtt_thread_service_cleanup(VOID)
{
#if (BSP_CFG_RTOS == 1)
    tx_byte_pool_delete(&byte_pool);

    /* if any user specific queue has been added, it should be clean up as per specific EP */
    tx_queue_delete(&rtt_op_data_queue);
    tx_queue_delete(&rtt_ip_data_queue);

    /* halt */
    APP_ERR_TRAP(true);
#endif
}


