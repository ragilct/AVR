/*
 * solar_tracking_system.c
 *
 * Created: 3/4/2014 6:38:58 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include "util/delay.h"

void ADC_init(void)	// Initialization of ADC
{
	ADMUX=0x00;
	ADMUX=(1<<REFS0);	// AVcc with external capacitor at AREFvale 0x40 ob01000000
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//adcsra=0x870r=0b10000111
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

int main(void)
{
   ADC_init();
   DDRB=0xFF;
   DDRC=0x00;
   DDRD=0xFF;
   DDRA=0x00;
	 int top,bottum,error;
    while(1)
    {
       bottum= ADC_read(0);
	   _delay_ms(100);
       top=ADC_read(1);
	  _delay_ms(100);
	  error=top-bottum;
       if(error>25)
       {
	       PORTD=0x09;
       }
       if(error<-25)
       {
	       PORTD=0x0A;
       }
	   else
	   {
		   PORTD=0x00;
	   }		    
    }
}