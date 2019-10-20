/******************************************************************************
                        
Small Library to easily interface AVR MCUs with External SPI ADCs. This library
provides a set of fuctions to work with Microchip Inc's SPI ADC Chips like

	*MCP3204 : 12 BIT, 100ksps, 4 Channels
	*MCP3208 : 12 BIT, 100ksps, 8 Channels

Hardware:
	ATmega32 running @ 16MHz
	FUSE HIGH = 0xC9 LOW=0xFF

	MCP320X Connected to SPI Port

	CS PIN of MCP320X Connected to PD7 (Can be chaned by editing spi.h)



                                     NOTICE
									--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com

*******************************************************************************/

#ifndef _ADC_EX_H_
#define _ADC_EX_H_

void InitADCEx();
uint16_t ReadADCEx(uint8_t ch);

#endif
