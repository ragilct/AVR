/*
 * wheel_control.c
 *
 * Created: 3/31/2014 11:06:49 AM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char data;
ISR (USART_RXC_vect)
{
	data=UDR;
	PORTC=0xFF;
	_delay_ms(1000);
	PORTC=0x00;
	
}

int main(void)
{
	DDRB=0XFF;
	DDRA=0XFF;
	DDRC=0xFF;
	DDRD=0X00;
	UCSRB=(1<<RXEN)|(1<<RXCIE);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRL=103;
	sei();
	data='g';
    while(1){
		switch(data)
		{
			case 'g':{
				PORTB=0x00;
				PORTA=0x00;
				_delay_ms(100);
				PORTA=0xAA;
				PORTB=0x95;
				break;
			}
			case 's':{
				PORTB=0x00;
				PORTA=0x00;
				_delay_ms(100);
				PORTA=0x00;
				PORTB=0x00;
				break;
			}
			case 'b':{
				PORTB=0x00;
				PORTA=0x00;
				_delay_ms(100);
				PORTA=0x55;
				PORTB=0x2A;
				break;
			}
			case 'l':{
				PORTB=0x00;
				PORTA=0x00;
				_delay_ms(100);
				PORTA=0x2A;
				PORTB=0x95;
				break;
			}
			case 'r':{
				PORTB=0x00;
				PORTA=0x00;
				_delay_ms(100);
				PORTA=0x8A;
				PORTB=0x95;
				break;
			}

			
		}
	}
    return 0;
}