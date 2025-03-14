/**********************************************************************************************************************
* File Name    : readme.txt
* Description  : Contains general information about Example Project and detailed instructions
**********************************************************************************************************************/

1. Project Overview:

	This example project demonstrates configuration of the DAC, AGT, and DTC to generate a continuous sinusoid signal. The
	user will define the samples per period and frequency in Hz of the desired output wave in JLink RTT Viewer. The 
	samples per period is used to compute and store 1 period of the sinusoid in a look up table (LUT), and the frequency is 
	used to set the	AGT period to the appropriate sampling rate. The AGT generates an interrupt which triggers the DTC to 
	transfer the next value of the LUT to the DADR0 register.  
	
	The output sinusoid wave will oscillate between the minimum and maximum DAC values at the user-specified samples per period
	and frequency.
	
2. Hardware Requirements:
	
	  i. Renesas RA board (EK-RA2A1, EK-RA2L1, EK-RA4M2, or EK-RA6M4)
	 ii. 1x micro-USB cable
	iii. PC with USB port and JLink RTT Viewer software
	
3. Hardware Connections:

	Connect micro-USB cable between J10 on RA board and USB port on PC. 

	The following pin connections are required to capture the output signal from the DAC:
	* RA2L1, RA4M2, RA6M4:
		P014 is DA0 ouput
	* RA2A1:
		P500 is DA12_0 ouptut
	
	
NOTE: 
	JLink RTT Viewer only supports integer values for user input.

	
	
