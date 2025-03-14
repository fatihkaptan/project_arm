/***********************************************************************************************************************
 * File Name    : menu_kis.c
 * Description  : Kit Information Screen.
 **********************************************************************************************************************/

/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#include <stdio.h>

#include "r_typedefs.h"
#include "r_console.h"

#include "board_cfg.h"
#include "common_init.h"
#include "common_data.h"
#include "common_utils.h"
#include "menu_kis.h"


#define MODULE_NAME     "\r\n%d. KIT INFORMATION\r\n"

#define SUB_OPTIONS     "\r\n a) Kit name:                           %s "                           \
                        "\r\n b) Kit ordering part number:           %s "                           \
                        "\r\n c) RA Device part number:              %s"                            \
                        "\r\n d) RA MCU 128-bit Unique ID (hex):     "                              \
                        "%x%x%x%x-%x%x%x%x-"                                       \
                        "%x%x%x%x-%x%x%x%x"                                        \
                        "\r\n e) RA MCU Die temperature (F/C):       %d.%d/%d.%d "  \
                        "\r\n f) Blue LED blinking frequency (Hz):   %d" \
                        "\r\n g) Blue LED blinking intensity (%%%%):    %d"
                        /* Need to double escape the % */


#define CONSOLE_REFRESH (5000)
static uint32_t s_console_update_speed = CONSOLE_REFRESH;

static char_t s_print_buffer[BUFFER_LINE_LENGTH] = {};
static uint16_t s_adc_data        = 0;
static uint16_t s_old_adc_data    = 0;

/**********************************************************************************************************************
 * Function Name: test_temprature_change
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
static void test_temprature_change(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Read die temperature */
    fsp_err = R_ADC_Read (&g_adc_ctrl, ADC_CHANNEL_TEMPERATURE, &s_adc_data);

    /* Handle error */
    if (FSP_SUCCESS != fsp_err)
    {
        print_to_console ("** R_ADC_Read API failed ** \r\n");

        SYSTEM_ERROR
    }

    if (s_old_adc_data != s_adc_data)
    {
        s_old_adc_data = s_adc_data;
        g_board_status.adc_temperature_data = s_adc_data;
    }
}
/**********************************************************************************************************************
 End of function test_temprature_change
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: update_console
 * Description  : .
 * Argument     :
 * Return Value : .
 *********************************************************************************************************************/
void  update_console()
{
    if (0 == ( --s_console_update_speed))
    {
        volatile float64_t mcu_temp_f    = 0.00;
        volatile float64_t mcu_temp_c    = 0.00;
        volatile float64_t tmp           = 0.00;
        int16_t  wn_mcu_temp_f           = 0;
        int16_t  wn_mcu_temp_c           = 0;
        int16_t d                        = 0;
        uint16_t fr_mcu_temp_f           = 0;
        uint16_t fr_mcu_temp_c           = 0;
        int16_t r                        = 0;
        bsp_unique_id_t const * p_uid    = R_BSP_UniqueIdGet();


        sprintf(s_print_buffer, "%s%s", gp_clear_screen, gp_cursor_home);
        print_to_console(s_print_buffer);

        sprintf(s_print_buffer, MODULE_NAME, g_selected_menu);
        print_to_console(s_print_buffer);


        s_console_update_speed = CONSOLE_REFRESH * 100;

        test_temprature_change();

        /* Update temperature */
        s_adc_data = g_board_status.adc_temperature_data;

        fsp_err_t  err;
        adc_info_t  adc_info_rtn;

        err = R_ADC_InfoGet( &g_adc_ctrl, &adc_info_rtn);

        if (0xFFFFFFFF == adc_info_rtn.calibration_data)
        {
            /* Unable to read TSN cal value - not supported */
            err = FSP_ERR_UNSUPPORTED;
        }

        if (FSP_SUCCESS == err)
        {
            /* Cast as compiler will assume calc is int */
            mcu_temp_c = (float64_t)( (float64_t)((int16_t)s_adc_data - ( (int16_t)adc_info_rtn.calibration_data
                    - (int16_t)TSN_CAL_OFFEST_COUNTS_AT_125DEG_TO_0DEG_C))
                    / TSN_ADC_COVERSION_SLOPE_COUNTS_PER_DEG_C);

            /* Cast as compiler will assume calc is int */
            mcu_temp_f = (float64_t)( (float64_t)((int16_t)s_adc_data - ( (int16_t)adc_info_rtn.calibration_data
                    - (int16_t)TSN_CAL_OFFEST_COUNTS_AT_257DEG_TO_0DEG_F))
                    / TSN_ADC_COVERSION_SLOPE_COUNTS_PER_DEG_F);
        }
        else
        {
            mcu_temp_f       = 0.00;
            mcu_temp_c       = 0.00;
        }


        /* Conversion ADC temperature in celsius */
        tmp = mcu_temp_c * 100.0;

        /* Cast as compiler will assume calc is int */
        d = (int16_t)(mcu_temp_c / 1.00f);

        /* Truncate the mantissa to leave only the integer part */
        r = (int16_t)(tmp / 1.00f);

        /* Truncate the mantissa to leave only the integer part */
        r = (int16_t)(r % (d * 100));

        wn_mcu_temp_c =  d;
        fr_mcu_temp_c = abs(r);

        /* Conversion ADC temperature in Fahrenheit */
        tmp = mcu_temp_f * 100.0;

        /* Cast as compiler will assume calc is int */
        d = (int16_t)(mcu_temp_f / 1.00f);

        /* Truncate the mantissa to leave only the integer part */
        r = (int16_t)(tmp / 1.00f);

        /* Truncate the mantissa to leave only the integer part */
        r = (int16_t)(r % (d * 100));

        wn_mcu_temp_f =  d;
        fr_mcu_temp_f = abs(r);

        /* Cast from portable types to native types expected by printf */
        sprintf (s_print_buffer, SUB_OPTIONS, FULL_NAME, PART_NUMBER, DEVICE_NUMBER,  p_uid->unique_id_bytes[0],
                p_uid->unique_id_bytes[1],  p_uid->unique_id_bytes[2],  p_uid->unique_id_bytes[3],
                p_uid->unique_id_bytes[4],  p_uid->unique_id_bytes[5],  p_uid->unique_id_bytes[6],
                p_uid->unique_id_bytes[7],  p_uid->unique_id_bytes[8],  p_uid->unique_id_bytes[9],
                p_uid->unique_id_bytes[10], p_uid->unique_id_bytes[11], p_uid->unique_id_bytes[12],
                p_uid->unique_id_bytes[13], p_uid->unique_id_bytes[14], p_uid->unique_id_bytes[15],
                wn_mcu_temp_f, fr_mcu_temp_f,
                wn_mcu_temp_c, fr_mcu_temp_c,
                g_pwm_rates_data[g_board_status.led_frequency],
                g_pwm_dcs_data[g_board_status.led_intensity]
        );
        print_to_console(s_print_buffer);

        sprintf(s_print_buffer, MENU_RETURN_INFO);
        print_to_console(s_print_buffer);

        STATUS_CLEAR(STATUS_UPDATE_FREQ_INFO);
        STATUS_CLEAR(STATUS_UPDATE_INTENSE_INFO);
    }
}
/**********************************************************************************************************************
 End of function update_console
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function Name: kis_display_menu
 * Description  : .
 * Return Value : .
 *********************************************************************************************************************/
test_fn kis_display_menu(void)
{
    int8_t c = -1;

    printf("\r\n");
    s_console_update_speed = 1;

    STATUS_SET(STATUS_DISPLAY_MENU_KIS);

    while (0 != c)
    {
        update_console();
        if (check_for_input_from_console())
        {
            c = input_from_console();
            if (' ' == c)
            {
                break;
            }
        }
    }

    STATUS_CLEAR(STATUS_DISPLAY_MENU_KIS);
    return (0);
}
/**********************************************************************************************************************
 End of function kis_display_menu
 *********************************************************************************************************************/


