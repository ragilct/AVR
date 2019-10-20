/******************************************************************************

                          eXtreme Electronics xAPI(TM)
						  ----------------------------
xAPI is a Powerful but easy to use C library to program the xBoard(TM)
series of AVR development board. The library has support for commonly use tasks
like:-

*LCD interfacing
*MUXED 7 segment displays.
*Remote Control
*Serial Communication
*DC Motor Controls with Speed Control
*Analog Measurement for Sensor Interface.
*Temperature Measurement.
*I2C Communication.
*EEPROM Interface
*Real Time Clock (RTC Interface)

The APIs are highly documented and easy to use even by a beginner.

For More Info Log On to 
www.eXtremeElectronics.co.in

Copyright 2008-2009 eXtreme Electronics India

                                Temperature Sensor Core
						       -------------------------
This module is used for interfacing xBoard's Inbuilt Temperature Sensor (LM35).
For More information please see supplied tutorials and videos.

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
#include <avr/io.h>
#include <util/delay.h>

#include "../../lib/adc/adc.h"
#include "lm35.h"

//This function reads and returns the current room temperature
uint8_t ReadTemperature()
{
	//Temperature
	uint8_t t;

	//Read ADC
	uint8_t adc_value1=ReadADC(3);
	_delay_loop_2(1000);
	uint8_t adc_value2=ReadADC(3);
	_delay_loop_2(1000);
	uint8_t adc_value3=ReadADC(3);
		
	uint8_t adc_value=((adc_value1+adc_value2+adc_value3)/3);

	//Convert to degree Centrigrade
	t=((adc_value/1023.00)*500.00);

	return t;
}
	
