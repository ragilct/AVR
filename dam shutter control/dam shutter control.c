/*
 * dam_shutter_control.c
 *
 * Created: 1/27/2014 8:01:14 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include "util/lcd/lcd.h"
#include <util/delay.h>
void ADC_init(void)	// Initialization of ADC
{
	ADMUX=(1<<REFS0);	// AVcc with external capacitor at AREF
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// Enable ADC and set Prescaler division factor as 128
}

unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111;	// channel must be b/w 0 to 7
	ADMUX |= ch;	// selecting channel
	
	ADCSRA|=(1<<ADSC);	// start conversion
	while(!(ADCSRA & (1<<ADIF)));	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);	// clearing of ADIF, it is done by writing 1 to it
	
	return (ADC);
}
unsigned int steps[]={0x90,0x80,0xc0,0x40,0x60,0x20,0x30,0x10},waterlevel,disp,rot,i=0,k=0;
int main(void)
{  
	    DDRD=0XFF;
		LCDInit(LS_NONE);
		
		//Intro Message
		LCDWriteString("MINI PROJECT");
		LCDWriteStringXY(0,1,"START.....");
		_delay_ms(1000);
	    ADC_init();
    while(1)
	{
		waterlevel=ADC_read(0);
		LCDClear();
		LCDWriteString("water level=");
		LCDWriteInt(waterlevel,3);
		_delay_ms(1000);
		disp=ADC_read(1);
		rot=disp/51;
		
		for(;i<rot;i++)
		{
			for( ;k<7;k++)
			{
			PORTD=steps[k];
			_delay_ms(10);
			}			
			
		}
	
    }
}