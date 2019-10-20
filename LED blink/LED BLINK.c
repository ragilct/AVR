/*
 * LED_BLINK.c
 *
 * Created: 3/22/2014 6:01:38 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
void main(void)
{
	DDRC=0XFF;
    while(1)
    {
       PORTC=0XAA;
	   _delay_ms(1000);
	   PORTC=0X55;
	   _delay_ms(1000); 
    }
}