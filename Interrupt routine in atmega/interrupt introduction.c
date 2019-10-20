/*
 * intro.c
 *
 * Created: 1/29/2014 10:14:36 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include "util/lcd/lcd.h"
#include "util/delay.h"
#include <avr/interrupt.h>
uint8_t k=0;
int main(void)
{  DDRD=0X00;
	DDRB=0XFF;
	MCUCR=0X02;
	GICR=0X40;
	sei();
	LCDGotoXY(0,0);
	LCDWriteString("HAIII.............");
	_delay_ms(1000);
    while(1)
    {
		switch(k)
		{
			case 0: LCDClear();
			case 1: { LCDClear();
				      LCDWriteString("welcome 2 world of");
					  LCDGotoXY(0,1);
			          LCDWriteString("EMBEDDED SYSTEM");	
					  _delay_ms(1000);
			          break;
			        }
			case 2: { LCDClear();
				      LCDWriteString("MY NAME IS");
					  LCDGotoXY(0,1);
				      LCDWriteString("RAGIL.C.T");
				      _delay_ms(1000);
				      break;
			        }
			case 3: { LCDClear();
				      LCDWriteString("S8,EEB");
					  LCDGotoXY(0,1);
				      LCDWriteString("NSS ENG COLLEGE");
				      _delay_ms(1000);
				      break;
			        }	
			case 4: { LCDClear();
				      LCDWriteString("HERE WE STARTING...");
					  _delay_ms(1000);
				      LCDWriteString("   HANDS ON  ");
					  LCDGotoXY(0,1);
					  LCDWriteString("EMBEDDED SYSTEM");
				      _delay_ms(1000);
				      break;
			        }	
				default : { LCDClear();
					      break;
				        }
			}									  
							
        
    }
}
ISR (INT0_vect)
{k++;
}	