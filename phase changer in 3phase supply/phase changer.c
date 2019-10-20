/*
 * phase_changer.c
 *
 * Created: 3/10/2014 4:39:45 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
void ADC_init(void)	// Initialization of ADC
{
	ADMUX=(1<<REFS0);	// AVcc with external capacitor at AREFvale 0x40 ob01000000
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//adcsra=0x870r=0b10000111
	// Enable ADC and set Prescaler division factor as 128
}

unsigned int ADC_read(unsigned char ch)
{
	unsigned int adc_value;
	unsigned char temp;
	ch= ch & 0b00000111;	// channel must be b/w 0 to 7
	ADMUX |= ch;	// selecting channel
	
	ADCSRA|=(1<<ADSC);	// start conversion
	while(!(ADCSRA & (1<<ADIF)));	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);	// clearing of ADIF, it is done by writing 1 to it
	temp=ADCL;
	adc_value=ADCH;
	adc_value=(adc_value<<8)|temp;
	return (adc_value);
}
int main(void)
{
	DDRA=0x00;
	DDRB=0xff;
	int phase1,phase2,phase3;
	ADC_init();
    while(1)
    {
        phase1=ADC_read(0);
		_delay_ms(10);
		phase2=ADC_read(1);
		_delay_ms(10);
		phase3=ADC_read(2);
		_delay_ms(10);
		if(phase1>200)
		{
			PORTB=0x01;
			
		}			
		else if(phase2>200)
		{
			PORTB=0x02;
			
		}
		else if(phase3>200)
    {
		PORTB=0x04;
		
	}
	else 
	{
	PORTB=0x01;
	}	
	}	
	}	