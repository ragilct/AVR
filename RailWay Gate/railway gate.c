/*
 * railway_gate.c
 *
 * Created: 3/18/2014 10:33:50 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC = 0xFF;//All Outputs
	DDRA = 0xFF;//All Outputs
	DDRD = 0XFF;//PD0,PD1 Inputs,PD4-PD7 Outputs
	DDRB=0x00;
    
	PORTC=0X00;
	
	int i,done=0;

    while(1)
    {
		done=1;
		PORTD=0x80;
		PORTA=0X00;//Segment OFF

		if(PINB0)
		{
			
			PORTD&=0b01000000;
			while(PINB0);
			PORTA=0x01;
			_delay_ms(1000);
			PORTA=0x00;
			while(!PINB1){
				PORTD&=0x40;
				
				if(done==1)
				{
					PORTC = 0B00111010;
					_delay_ms(10000);
					PORTC=0x00;
					done=0;
					}
					}
			while(PINB2)
			{
				PORTC = 0B00110101;
				_delay_ms(10000);
				PORTC = 0B00111010;
				_delay_ms(10000);
				PORTC=0x00;
				
			}
			if(PINB1)
			{
				for(i=9;i>=0;i--)
				{
					_delay_ms(700);
					}
		    PORTA=0x01;
			_delay_ms(1000);
			PORTA=0x00;
			PORTD=0x80;
			PORTC = 0B00110101;
			_delay_ms(10000);
			PORTC = 0x00;
		}
	}

	if(PINB1){
		
		//while(PINB1);
		PORTA=0x01;
		_delay_ms(1000);
		PORTA=0x00;
		PORTD=0x40;
		while(!PINB0)
		{
            PORTD=0x40;		
			if(done==1)
			{
				PORTC = 0B00111010;
				_delay_ms(10000);
				PORTC=0x00;
				done=0;
				}
				}
		while(PINB2)
		{
			PORTC = 0B00110101;
			_delay_ms(10000);
			PORTC = 0B00111010;
			_delay_ms(10000);
			PORTC=0x00;
		}
		if(PINB0)
		{
			for(i=9;i>=0;i--)
			{
				_delay_ms(700);
				} 
				PORTA=0x01;
				_delay_ms(1000);
				PORTA=0x00;
				PORTD=0x80;
				
				PORTC = 0B00110101;
				_delay_ms(10000);
				PORTC=0x00;
				}
}

         }
		 return 0;
		 
}