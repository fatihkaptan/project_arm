/***********************************************************************************************************************
 * File Name    : kint_ep.h
 * Description  : Contains data structures and functions used in kint_ep.h
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef KINT_EP_H_
#define KINT_EP_H_

/* channel masks */
typedef enum
{
    CH_MASK_0 = 0x01,
    CH_MAKS_1 = 0x02,
    CH_MASK_2 = 0x04,
    CH_MASK_3 = 0x08,
    CH_MASK_4 = 0x10,
    CH_MASK_5 = 0x20,
    CH_MASK_6 = 0x40,
    CH_MASK_7 = 0x80
}channel_mask_t;

/* for RTT Viewer display of column number in ASCII */
typedef enum
{
    COL_DISP_A_ = 0x41,
    COL_DISP_B_ = 0x42
}col_identifier_t;

/*
 * user specific macros
 */

#define ERR_MSG_FRAME(str1, str2)       (#str1  #str2)

/* Check IO-port API return and trap error(if any error occurs) cleans up and display failure details on RTT viewer */
#define VALIDATE_IO_PORT_API(err,API)   err = API;                                          \
                                        if (FSP_SUCCESS != err)                             \
										{                                                   \
                                        	/*Close KINT Module */                          \
                                        	de_init_kint();                                 \
                                        	APP_ERR_PRINT(ERR_MSG_FRAME(#API , : Failed))    \
                                        	/* Trap here */                                 \
                                        	APP_ERR_TRAP(err);                              \
                                        }

#if defined (BOARD_RA2A1_EK)
#define KEYPAD_PORT                 (bsp_io_port_t)BSP_IO_PORT_03

/* Keypad Pin details */
#define ROW_A                       (bsp_io_port_pin_t) BSP_IO_PORT_03_PIN_01
#define ROW_B                       (bsp_io_port_pin_t) BSP_IO_PORT_03_PIN_02
#define COL_A                       (bsp_io_port_pin_t) BSP_IO_PORT_03_PIN_03
#define COL_B                       (bsp_io_port_pin_t) BSP_IO_PORT_03_PIN_04


/* Row and column bit position */
#define COL_A_BIT                   3U  /* P303 */
#define COL_B_BIT                   4U  /* P304 */
#define ROW_A_BIT                   1U  /* P301 */
#define ROW_B_BIT                   2U  /* P302 */

#elif defined (BOARD_RA6T1_RSSK)
#define KEYPAD_PORT                 (bsp_io_port_t)BSP_IO_PORT_01

/* Keypad Pin details */
#define ROW_A                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_01
#define ROW_B                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_02
#define COL_A                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_00
#define COL_B                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_03

/* Row and column bit position */
#define COL_A_BIT                   0U  /* P100 */
#define COL_B_BIT                   3U  /* P103 */
#define ROW_A_BIT                   1U  /* P101 */
#define ROW_B_BIT                   2U  /* P102 */

#else
#define KEYPAD_PORT                 (bsp_io_port_t)BSP_IO_PORT_01

/* Keypad Pin details */
#define ROW_A                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_01
#define ROW_B                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_02
#define COL_A                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_06
#define COL_B                       (bsp_io_port_pin_t) BSP_IO_PORT_01_PIN_07

/* Row and column bit position */
#define COL_A_BIT                   6U  /* P106 */
#define COL_B_BIT                   7U  /* P107 */
#define ROW_A_BIT                   1U  /* P101 */
#define ROW_B_BIT                   2U  /* P102 */

#endif



/* Row pins set as low */
#define ROW_A_LOW()                 VALIDATE_IO_PORT_API(err,\
                                        R_IOPORT_PinWrite(&g_ioport_ctrl, ROW_A, BSP_IO_LEVEL_LOW))

#define ROW_B_LOW()                 VALIDATE_IO_PORT_API(err,\
                                        R_IOPORT_PinWrite(&g_ioport_ctrl, ROW_B, BSP_IO_LEVEL_LOW))

/* Row pins set as  HIGH */
#define ROW_A_HIGH()                VALIDATE_IO_PORT_API(err,\
                                        R_IOPORT_PinWrite(&g_ioport_ctrl, ROW_A, BSP_IO_LEVEL_HIGH))

#define ROW_B_HIGH()                VALIDATE_IO_PORT_API(err,\
                                        R_IOPORT_PinWrite(&g_ioport_ctrl, ROW_B, BSP_IO_LEVEL_HIGH))

/* Set Row and column pin at initial state i.e. HIGH */
#define ROW_INIT_LEVEL_SET()        ROW_A_HIGH()\
                                    ROW_B_HIGH();

/* Read value of the bit from the variable */
#define READ_BIT(number, position)  (uint8_t)((ioport_size_t)(number >> (uint8_t)position) & 1U)

#define PORT_RAW_DATA               0xFFFF

#define EP_INFO                "\r\n\r\nThe Project demonstrates KINT module functionality for processing \r\n"\
                               "keys in a 2x2 key matrix. "\
                               "Please connect matrix keypad to MCU pins\r\nas mentioned in readme file. "\
                               "On pressing one of the keys connected\r\nto the board, the key-event"\
                               " is detected and displayed on RTTViewer\r\n\r\n\r\n"


#endif /* KINT_EP_H_ */
