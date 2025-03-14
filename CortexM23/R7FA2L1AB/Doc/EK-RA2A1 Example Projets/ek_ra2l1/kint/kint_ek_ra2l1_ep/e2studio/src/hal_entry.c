/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains data structures and functions used in hal_entry.c.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include "common_utils.h"
#include "kint_ep.h"

/*
 * Private global variables
 */
/* used to capture KINT signal */
static volatile uint32_t g_kint_signal = RESET_VALUE;


void R_BSP_WarmStart(bsp_warm_start_event_t event);

/* Private functions */
static void process_row_identification(uint8_t kint_pin);
static void de_init_kint(void);

/*******************************************************************************************************************//**
 * The RA Configuration tool generates main() and uses it to generate threads if an RTOS is used.  This function is
 * called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    fsp_err_t err                       = FSP_SUCCESS;
    fsp_pack_version_t version          = {RESET_VALUE};
    volatile uint32_t captured_kint_sig = RESET_VALUE;

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);
    APP_PRINT(EP_INFO);

    /* Open KINT module */
    err = R_KINT_Open(&g_kint_ctrl, &g_kint_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n * KINT open API failed * \r\n");

        /* Trap here */
        APP_ERR_TRAP(err);
    }

    /* Enable KINT interrupt */
    err = R_KINT_Enable(&g_kint_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n * R_KINT_Enable API failed * \r\n");

        /* close KINT module */
        de_init_kint();

        /* Trap here */
        APP_ERR_TRAP(err);
    }

    APP_PRINT("\r\n ** KINT open and enabled now, Press key from keypad attached to MCU ** \r\n");

    while (true)
    {
        if (RESET_VALUE != g_kint_signal)
        {
            /*
             * Enter critical section to
             * Get local copy of KINT channel mask which contain the KINT information.
             *
             * Reason : -
             * For instance  - CPU is currently processing the keypad signal and if interrupt happens,
             * the CPU jumps to kint_callback_event() and sets the new value
             * to g_kint_signal variable.
             * After processing interrupts, the CPU returns to the previous
             * routine where the keypad signal was being processed and continue with the previous KINT event without losing it.
             */
            FSP_CRITICAL_SECTION_DEFINE;
            FSP_CRITICAL_SECTION_ENTER;

            /* get the KINT channel mask information */
            captured_kint_sig = g_kint_signal;
            g_kint_signal = RESET_VALUE;

            /* exit critical section */
            FSP_CRITICAL_SECTION_EXIT;

            switch (captured_kint_sig)
            {
#if defined (BOARD_RA6T1_RSSK)
                case CH_MASK_0:
#else
                case CH_MASK_6:
#endif
                {
                    process_row_identification(COL_A_BIT);
                }
                break;
#if defined (BOARD_RA6T1_RSSK)
                case CH_MASK_3:
#else
                case CH_MASK_7:
#endif
                {
                    process_row_identification(COL_B_BIT);
                }
                break;

                default:
                    break;
            }

            /* restore initial Row pins level, API return check performed within the macro */
            ROW_INIT_LEVEL_SET();

            captured_kint_sig = RESET_VALUE;

        }	// end if statement

        /* Wait time for key processing */
        R_BSP_SoftwareDelay(400U, BSP_DELAY_UNITS_MILLISECONDS);
    }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event) {
	if (BSP_WARM_START_POST_C == event) {
		/* C runtime environment and system clocks are setup. */

		/* Configure pins. */
		R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
	}
}

/*******************************************************************************************************************//**
 * @brief      KINT callback function.
 * @param[in]  p_args
 * @retval     None
 **********************************************************************************************************************/
void kint_callback(keymatrix_callback_args_t *p_args)
{
	if (NULL != p_args)
	{
		/* capture KINT event for a particular channel mask */
		g_kint_signal = p_args->channel_mask;
	}
}

/*******************************************************************************************************************//**
 *  @brief       Scans rows when channel mask received from KINT user callback
 *  		     presuming column connected to KINT pins
 *  @param[IN]   KINT configured pins
 *  @retval      row value
 **********************************************************************************************************************/
static void process_row_identification(uint8_t kint_pin)
{
    ioport_size_t  port_data            = PORT_RAW_DATA;
    volatile bool b_row_a_key           = false;
    volatile bool b_row_b_key           = false;
    uint8_t col_disp_pin                = RESET_VALUE;
    fsp_err_t err                       = FSP_SUCCESS;

	/* As we got the column event, scan for the row to detect the particular key press */

    /* API return check performed within the macro */
    ROW_A_LOW();

	/* Reset port_data before reading from port */
	port_data = PORT_RAW_DATA;
	VALIDATE_IO_PORT_API(err, R_IOPORT_PortRead(&g_ioport_ctrl, KEYPAD_PORT, &port_data))

	/* verify the row for this column */
	if ( ( READ_BIT(port_data, kint_pin) == READ_BIT(port_data, ROW_A_BIT) ) )
	{
		b_row_a_key = true;
	}

	/* Check KINT pin state when ROW_B P102 is set as low, API return check performed within the macro */
	ROW_A_HIGH();

	/* API return check performed within the macro */
	ROW_B_LOW();

	/* Reset port_data before reading from port */
	port_data = PORT_RAW_DATA;
	VALIDATE_IO_PORT_API(err, R_IOPORT_PortRead(&g_ioport_ctrl, KEYPAD_PORT, &port_data))

	/* verify the row for this column */
	if ( ( READ_BIT(port_data, kint_pin) == READ_BIT(port_data, ROW_B_BIT) ) )
	{
		b_row_b_key = true;
	}

    /* col_disp_pin is updated with ASCII value for column to display in RTT viewer */
    if (COL_A_BIT == kint_pin)
    {
    	col_disp_pin = COL_DISP_A_;
    }

    if (COL_B_BIT == kint_pin)
    {
    	col_disp_pin = COL_DISP_B_;
    }

	/*  On key press, detect the key by matching column state with row state.
	 *          			 *
	 *  FAULTY SCENARIO:IN case of GLITCH(which can occur) lead to false KINT event generation.
	 *	In this case KINT pin logic state will always be low regardless of row pin change.
	 *	Setting each row pins as "LOW" one by one and comparing it with KINT pin
	 *	results in both flags getting set as true. To avoid this scenario, used both flags
	 *	to validate the valid key
	 *
	 */
	if ( (true == b_row_a_key) && (false == b_row_b_key) )
	{
		APP_PRINT ("\r\n **Column %c and Row A** \r\n", col_disp_pin);
	}

	if ((true == b_row_b_key) && (false == b_row_a_key))
	{
		APP_PRINT ("\r\n **Column %c and Row B** \r\n", col_disp_pin);
	}

	/* reset row identification flags */
	b_row_b_key = false;
	b_row_a_key = false;
}

/*******************************************************************************************************************//**
 *  @brief       Close KINT modules when any API return error return value
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
static void de_init_kint(void)
{
    if (FSP_SUCCESS != R_KINT_Close(&g_kint_ctrl))
    {
    	APP_ERR_PRINT("\r\n * R_KINT_Close API failed * \r\n");
    }
}
