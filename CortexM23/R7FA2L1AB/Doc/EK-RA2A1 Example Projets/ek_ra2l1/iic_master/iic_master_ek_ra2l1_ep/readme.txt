/**********************************************************************************************************************
* File Name    : readme.txt
* Description  : Contains general information about Example Project and detailed instructions
**********************************************************************************************************************/

1. Project Overview:
    The example project demonstrates the typical use of the IIC master HAL module APIs.
    The project initializes IIC master module with standard rate and interfaces with PmodACL™ Board for ADXL345.

    On power up after establishing the connection of sensor with RA board, it displays accelerometer axis data on
    RTTviewer. Any API/event failure will be displayed on RTTviewer.

2. Hardware Settings:
    Hardware Connection
    *******************
    PMOD ACL has two on board connectors, J2 is used for I2C communication.

    RA6M3G_EK / RA6M3_EK
    --------
    SDA2 P511  ----> SDA (on PMOD-ACL)
    SCL2 P512  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA6M2_EK
    --------
    SCL1/P100  ----> SCL (on PMOD-ACL)
    SDA1/P206  ----> SDA (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA6M1_EK
    ---------
    SCL0/P400  ----> SCL (on PMOD-ACL)
    SDA0 P401  ----> SDA (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA6M4_EK / EK-RA6M5
    --------
    SDA0/P401  ----> SDA (on PMOD-ACL)
    SCL0/P400  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA4M1_EK
    --------
    SDA1/P206  ----> SDA (on PMOD-ACL)
    SCL1/P100  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA2A1_EK
    --------
    SDA0/P401  ----> SDA (on PMOD-ACL)
    SCL0/P000  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA6T1_RSSK
    ----------
    SDA1/P101  ----> SDA (on PMOD-ACL)
    SCL1/P100  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA2L1_EK
    --------
    SDA0/P407  ----> SDA (on PMOD-ACL)
    SCL0/P408  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA4M3_EK
    --------
    SDA0/P401  ----> SDA (on PMOD-ACL)
    SCL0/P408  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA2E1_EK
    --------
    SDA0/P401  ----> SDA (on PMOD-ACL)
    SCL0/P400  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA4M2_EK
    --------
    SDA1/P206  ----> SDA (on PMOD-ACL)
    SCL1/P205  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    RA6E1_FPB/RA4E1_FPB
    ---------
    SDA0/P401  ----> SDA (on PMOD-ACL)
    SCL0/P400  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

    MCK_RA6T2
    ---------
    SDA0/PB07  ----> SDA (on PMOD-ACL)
    SCL0/PB06  ----> SCL (on PMOD-ACL)
    VCC pin    ----> VCC (on PMOD-ACL)
    GND pin    ----> GND (on PMOD-ACL)

Note:
    For the functioning of IIC Master on all the boards except for EK-RA6M3/EK-RA6M3G,FPB-RA6E1,FPB-RA4E1, external pull up resistors of value
    3.9 or 4.7K ohms are required to be connected on I2C(SDA/SCL) lines.﻿