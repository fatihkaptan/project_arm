/**********************************************************************************************************************
* File Name    : readme.txt
* Description  : Contains general information about Example Project and detailed instructions
**********************************************************************************************************************/

1. Project Overview:
        The EP demonstrates the functionality of GPT Input capture module.GPT1 is used to generate periodic pulses of 500msec 
        duration and provided as input to GPT Input capture(GPT2).GPT2 counts the event pulse received at its input. 
        Based on the period and capture event, the time period of pulse is calculated and displayed on RTTViewer.

2. Hardware Connections:

EK-RA2A1:
Connect  P400 <--> P301

EK-RA2L1, EK-RA4M1, EK-RA4M2, EK-RA4M3, EK-RA6M1, EK-RA6M2, EK-RA6M3, EK-RA6M3G, EK-RA6M5:
Connect  P405 <--> P415

FPB-RA6E1:
Connect  P405 <--> P103

EK-RA6M4:
Connect  P105 <--> P512

RSSK-RA6T1:
Connect  P103 <--> P112

EK-RA2E1:
Connect  P500 <--> P105

EK-RA2E2:
Connect  P112 <--> P101

FPB-RA4E1:
Connect  P105 <--> P113

MCK-RA6T2:
Connect  PE14 <--> PE12

Note: Generated periodic pulse for RA2A1 is 1000msec.