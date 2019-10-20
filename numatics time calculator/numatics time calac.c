/*
 * numatics_time_calac.c
 *
 * Created: 2/4/2014 9:23:04 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/lcd/lcd.h>
#include <util/delay.h>

int main(void)
{ unsigned long t1,t2,t3,t4,time_diff_forward,time_diff_backward;
	DDRB=0xFF;
	DDRD=0x00;
	PORTD=0xff;
	TCCR1A=0;
	TCCR1B=0X45;
     TCNT1H=0x00;
		TCNT1L=0x00;
			LCDClear();
			LCDWriteString("start... ");
			_delay_ms(1000);
			LCDWriteString("ok ");
			_delay_ms(1000);
		while((TIFR&(1<<ICF1))==0);
		t1=ICR1L*1024;
		TIFR=(1<<ICF1);
		while((TIFR&(1<<ICF1))==0);
		t2=ICR1L*1024;
		TIFR=(1<<ICF1);
		time_diff_forward=t2-t1;
		 TCNT1H=0x00;
		 TCNT1L=0x00;
		while((TIFR&(1<<ICF1))==0);
		t3=ICR1L*1024;
		TIFR=(1<<ICF1);
		while((TIFR&(1<<ICF1))==0);
		t4=ICR1L*1024;
		TIFR=(1<<ICF1);
		time_diff_backward=t4-t3;    
		LCDClear();
		LCDWriteString("forward time(us) ");  
		LCDWriteIntXY(1,1,time_diff_forward,-1);
		_delay_ms(1000);
			LCDClear();
			LCDWriteString("backward time(us) ");
			LCDWriteIntXY(1,1,time_diff_backward,-1);
			_delay_ms(1000);
		
    while(1);
}