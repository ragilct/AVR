/******************************************************************************

Program to learn the use of Multiplexed 4x3 keypad with AVR Microcontroller.

Specific Skills Required
	>> AVR GPIO details.(http://bit.ly/aq3ouw)
	>> LCD Library.(http://bit.ly/agVUVc)
	>> Operations on bits using C.(http://bit.ly/aFqg5n)


General Skills Required
	>> AVR Studio Setup and use. (http://bit.ly/aZ43SZ)
	>> avr-gcc setup and use.


Hardware
--------
ATmega32 @ 16MHz external crystal.
Fuse Byte setting HIGH = C9 and LOW = FF (MOST IMP.)


LCD	<->	AVR Connection

	VSS ->GND
	VDD ->+5V
	VEE -> CENTER PIN OF 10K POT (OTHER TWO PIN OF POT TO +5V AND GND)
			ADJ. THE POT UNTIL YOU HAVE A CLEAR TEXT DISPLAY.

	RS ->	PD3
	RW ->	PD6
	E  ->	PB4

	DB0 -> N/C
	DB1 -> N/C
	DB2 -> N/C
	DB3 -> N/C

	DB4 -> PB0
	DB5 -> PB1
	DB6 -> PB2
	DB7 -> PB3

	LED+ ->+5V (VIA 100 OHM RES)
	LED- ->GND

KEYPAD

	COL1 ->	PA6
	COL2 ->	PA5
	COL3 ->	PA4

	ROW1 ->	PA3
	ROW2 -> PA2
	ROW3 ->	PA1
	ROW4 -> PA0

 									 NOTICE
									--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
RAGIL.C.T



******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "myutils.h"

#define KEYPAD A	//KEYPAD IS ATTACHED ON PORTA

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR 	DDR(KEYPAD)
#define KEYPAD_PIN 	PIN(KEYPAD)
//*******************************


/*******************************************

Function return the keycode of keypressed
on the Keypad. Keys are numbered as follows

[00] [01] [02]
[03] [04] [05]
[06] [07] [08]
[09] [10] [11]

Arguments:
	None

Return:
	Any number between 0-11 depending on
	keypressed.

	255 (hex 0xFF) if NO keypressed.

Precondition:
	None. Can be called without any setup.

*******************************************/
uint8_t GetKeyPressed()
{
	uint8_t r,c;

	KEYPAD_PORT|= 0X0F;

	for(c=0;c<3;c++)
	{
		KEYPAD_DDR&=~(0X7F);

		KEYPAD_DDR|=(0X40>>c);
		for(r=0;r<4;r++)
		{
			if(!(KEYPAD_PIN & (0X08>>r)))
			{
				return (r*3+c);
			}
		}
	}

	return 0XFF;//Indicate No keypressed
}
	

void main()
{
	//Wait for LCD To Start
	_delay_loop_2(0);
	
	//Now initialize the module
	LCDInit(LS_NONE);

	uint8_t key;

	while(1)
	{
		key=GetKeyPressed();	//Get the keycode of pressed key

		LCDWriteIntXY(0,0,key,3);	//Print it at location 0,0 on LCD.
	}

}

