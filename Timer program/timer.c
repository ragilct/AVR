/*
 * timer.c
 *
 * Created: 2/15/2014 9:42:08 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include "util/lcd/lcd.h"
//int binrtoint(uint16_t d);
int main(void)
{
	 unsigned int t1,t2,t3,t4;
	 unsigned int time_diff_forward,time_diff_backward;
	unsigned char tb[]={'0','0','0','0','0','0','0','0'},tf[]={'0','0','0','0','0','0','0','0'};
	DDRA=0xff;
	DDRD=0x00;
	DDRC=0xff;
	PORTD=0xff;
	TCCR1A=0;
	TCCR1B=0X45;
	TCNT1H=0x00;
	TCNT1L=0x00;
	LCDInit(LS_NONE);
	LCDClear();
	LCDWriteString(" start... ");
	PORTC=0x01;
	_delay_ms(5000);
	PORTC=0x00;
	LCDGotoXY(1,1);
	LCDWriteString("ok ");
	while((TIFR&(1<<ICF1))==0);
	_delay_ms(20);
	while((TIFR&(1<<ICF1))==0);
	t1=ICR1;
	TIFR=(1<<ICF1);
	while((TIFR&(1<<ICF1))==0);
	_delay_ms(20);
	while((TIFR&(1<<ICF1))==0);
	t2=ICR1;
	TIFR=(1<<ICF1);
	time_diff_forward=t2-t1;
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	TCCR1B=0x45;
	while((TIFR&(1<<ICF1))==0);
	_delay_ms(20);
	while((TIFR&(1<<ICF1))==0);
	t3=ICR1;
	TIFR=(1<<ICF1);
	while((TIFR&(1<<ICF1))==0);
	_delay_ms(20);
	while((TIFR&(1<<ICF1))==0);
	t4=ICR1;
	TIFR=(1<<ICF1);
	time_diff_backward=t4-t3;
	time_diff_forward=(time_diff_forward*128);
	time_diff_backward=(time_diff_backward*128);
	tf[7]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[6]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[5]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[4]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[3]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[2]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[1]=((time_diff_forward%10)+48);
	time_diff_forward=time_diff_forward/10;
	tf[0]=time_diff_forward+48;
	tb[7]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[6]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[5]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[4]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[3]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[2]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[1]=((time_diff_backward%10)+48);
	time_diff_backward=time_diff_backward/10;
	tb[0]=time_diff_backward+48;
	
	LCDClear();
	LCDWriteString(" forwardtime(us) ");
	LCDGotoXY(8,1);
	LCDWriteString(tf);
	_delay_ms(10000);
	LCDClear();
	LCDWriteString("backwardtime(us)");
	LCDGotoXY(8,1);
	LCDWriteString(tb);
	_delay_ms(5000);
	 while(1);
}
