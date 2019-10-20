/*
 * LOGIC_TESTER.c
 *
 * Created: 3/10/2014 9:06:11 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <D:/ragin/CHIP/WINDOWS/MY PROJECTS/EMBEDDED/AVR and 8051/atmel studio6/LOGIC TESTER/LOGIC TESTER/lcd/lcd.h>



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

int main(void)
{
	DDRC=0xFF;
	//Wait for LCD To Start
	uint8_t k=0,l=0,m=0,n=0,o=0,p=0,q=0,r=0,s=0,t=0,u=0,v=0;
	//Now initialize the module
	LCDInit(LS_NONE);
	uint8_t key,key1;
	LCDGotoXY(0,0);
	LCDWriteString("ENTER IC NAME");
	_delay_ms(1000);
    while(1)
    {
		key=GetKeyPressed();	//Get the keycode of pressed key
       switch(key)
	   {
		   case 00://AND
		   {
			   DDRB=0b00100100;
			   DDRD=0b11001001;
			   PORTB=0b00000000;
			   PORTD=0b10000000;
			   if(PINB2==0)
			      k=1;
				  else
				  k=0;
			   if(PINB5==0)
			     l=1;
			   else
			    l=0;
				if(PIND0==0)
				m=1;
				else
				m=0;
				if(PIND3==0)
				n=1;
				else
				n=0;
				_delay_ms(1000);
				PORTB=0b00001001;
				PORTD=0b10100100;
				if(PINB2==0)
				o=1;
				else
				o=0;
				if(PINB5==0)
				p=1;
				else
				p=0;
				if(PIND0==0)
				q=1;
				else
				q=0;
				if(PIND3==0)
				r=1;
				else
				r=0;
				_delay_ms(1000);
				PORTB=0b00011011;
				PORTD=0b10110110;
				if(PINB2==1)
				s=1;
				else
				s=0;
				if(PINB5==1)
				t=1;
				else
				t=0;
				if(PIND1==1)
				u=1;
				else
				u=0;
				if(PIND4==1)
				v=1;
				else
				v=0;
				_delay_ms(100);
				
				if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
				{
					LCDClear();
			        LCDGotoXY(0,0);
					LCDWriteString("AND GATE is good");
					_delay_ms(1000);
				}
				else
				{
					LCDClear();
					LCDGotoXY(0,0);
					LCDWriteString("AND GATE is  bad");
					_delay_ms(1000);	
				}				
				
		       	break;	
			}	
			case 01://NAND
			{
			DDRB=0b00100100;
			DDRD=0b11001001;
			PORTB=0b00000000;
			PORTD=0b10000000;
			if(PINB2==1)
			k=1;
			else
			k=0;
			if(PINB5==1)
			l=1;
			else
			l=0;
			if(PIND0==1)
			m=1;
			else
			m=0;
			if(PIND3==1)
			n=1;
			else
			n=0;
			_delay_ms(1000);
			PORTB=0b00001001;
			PORTD=0b10100100;
			if(PINB2==1)
			o=1;
			else
			o=0;
			if(PINB5==1)
			p=1;
			else
			p=0;
			if(PIND0==1)
			q=1;
			else
			q=0;
			if(PIND3==1)
			r=1;
			else
			r=0;
			_delay_ms(1000);
			PORTB=0b00011011;
			PORTD=0b10110110;
			if(PINB2==0)
			s=1;
			else
			s=0;
			if(PINB5==0)
			t=1;
			else
			t=0;
			if(PIND0==0)
			u=1;
			else
			u=0;
			if(PIND3==0)
			v=1;
			else
			v=0;
			_delay_ms(1000);
			
			if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
			{   LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("NAND GATE is OK");
				_delay_ms(1000);
			}
			else
			{	LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("NAND GATE is bad");
				_delay_ms(1000);
			}
			
			break;
		}
		case 02://0r
		{	
		DDRB=0b00100100;
		DDRD=0b11001001;
		PORTB=0b00000000;
		PORTD=0b10000000;
		if(PINB2==0)
		k=1;
		else
		k=0;
		if(PINB5==0)
		l=1;
		else
		l=0;
		if(PIND0==0)
		m=1;
		else
		m=0;
		if(PIND3==0)
		n=1;
		else
		n=0;
		_delay_ms(1000);
		PORTB=0b00001001;
		PORTD=0b10100100;
		if(PINB2==1)
		o=1;
		else
		o=0;
		if(PINB5==1)
		p=1;
		else
		p=0;
		if(PIND0==1)
		q=1;
		else
		q=0;
		if(PIND3==1)
		r=1;
		else
		r=0;
		_delay_ms(1000);
		PORTB=0b00011011;
		PORTD=0b10110110;
		if(PINB2==1)
		s=1;
		else
		s=0;
		if(PINB5==1)
		t=1;
		else
		t=0;
		if(PIND0==1)
		u=1;
		else
		u=0;
		if(PIND3==1)
		v=1;
		else
		v=0;
		_delay_ms(1000);
		
		if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		{   LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("OR GATE is OK");
			_delay_ms(1000);
		}
		else
		{   LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("OR GATE is bad");
			_delay_ms(1000);
		}
		
		break;
	 }
	 case 03://NOR
	 {	
		 DDRB=0b00001001;
		 DDRD=0b11100100;
		 PORTB=0b00000000;
		 PORTD=0b10000000;
		 if(PINB0==1)
		 k=1;
		 else
		 k=0;
		 if(PINB3==1)
		 l=1;
		 else
		 l=0;
		 if(PIND2==1)
		 m=1;
		 else
		 m=0;
		 if(PIND5==1)
		 n=1;
		 else
		 n=0;
		 _delay_ms(1000);
		 PORTB=0b00010010;
		 PORTD=0b10001001;
		 if(PINB0==0)
		 o=1;
		 else
		 o=0;
		 if(PINB3==0)
		 p=1;
		 else
		 p=0;
		 if(PIND2==0)
		 q=1;
		 else
		 q=0;
		 if(PIND5==0)
		 r=1;
		 else
		 r=0;
		 _delay_ms(1000);
		 PORTB=0b00110110;
		 PORTD=0b10011011;
		 if(PINB0==0)
		 s=1;
		 else
		 s=0;
		 if(PINB6==0)
		 t=1;
		 else
		 t=0;
		 if(PIND2==0)
		 u=1;
		 else
		 u=0;
		 if(PIND5==0)
		 v=1;
		 else
		 v=0;
		 _delay_ms(1000);
		 
		 if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		 {	 LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("NOR GATE is OK");
			 _delay_ms(1000);
		 }
		 else
		 {   LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("NOR GATE is bad");
			 _delay_ms(1000);
		 }
		 
		 break;
	 }
	 case 04://XOR
	 {
		 DDRB=0b00100100;
		 DDRD=0b10001001;
		 PORTB=0b00000000;
		 PORTD=0b10000000;
		 if(PINB2==0)
		 k=1;
		 else
		 k=0;
		 if(PINB5==0)
		 l=1;
		 else
		 l=0;
		 if(PIND0==0)
		 m=1;
		 else
		 m=0;
		 if(PIND3==0)
		 n=1;
		 else
		 n=0;
		 _delay_ms(1000);
		 PORTB=0b00001001;
		 PORTD=0b10100100;
		 if(PINB2==1)
		 o=1;
		 else
		 o=0;
		 if(PINB5==1)
		 p=1;
		 else
		 p=0;
		 if(PIND0==1)
		 q=1;
		 else
		 q=0;
		 if(PIND3==1)
		 r=1;
		 else
		 r=0;
		 _delay_ms(1000);
		 PORTB=0b00011011;
		 PORTD=0b10110110;
		 if(PINB2==0)
		 s=1;
		 else
		 s=0;
		 if(PINB5==0)
		 t=1;
		 else
		 t=0;
		 if(PIND0==0)
		 u=1;
		 else
		 u=0;
		 if(PIND3==0)
		 v=1;
		 else
		 v=0;
		 _delay_ms(1000);
		 
		 if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		 {	 LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("XOR GATE is OK");
			 _delay_ms(1000);
		 }
		 else
		 {   LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("XOR GATE is bad");
			 _delay_ms(1000);
		 }
		 
		 break;
	 }
	 case 05://XNOR
	 {
		DDRB=0b00001100;
		DDRD=0b10001100;
		PORTB=0b00000000;
		PORTD=0b10000000;
		if(PINB2==1)
		k=1;
		else
		k=0;
		if(PINB3==1)
		l=1;
		else
		l=0;
		if(PIND2==1)
		m=1;
		else
		m=0;
		if(PIND3==1)
		n=1;
		else
		n=0;
		_delay_ms(1000);
		PORTB=0b00010001;
		PORTD=0b10010010;
		if(PINB2==0)
		o=1;
		else
		o=0;
		if(PINB3==0)
		p=1;
		else
		p=0;
		if(PIND2==0)
		q=1;
		else
		q=0;
		if(PIND3==0)
		r=1;
		else
		r=0;
		_delay_ms(1000);
		PORTB=0b00110011;
		PORTD=0b10110011;
		if(PINB2==0)
		s=1;
		else
		s=0;
		if(PINB3==0)
		t=1;
		else
		t=0;
		if(PIND2==0)
		u=1;
		else
		u=0;
		if(PIND3==0)
		v=1;
		else
		v=0;
		_delay_ms(1000);
		
		if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		{   LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("XNOR GATE is OK");
			_delay_ms(1000);
		}
		else
		{   LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("XNOR GATE is bad");
			_delay_ms(1000);
		}
		
		break;
	}
	 case 06://NOT
	 {
		 DDRB=0b00101010;
		 DDRD=0b10101010;
		 PORTB=0b00000000;
		 PORTD=0b10000000;
		 if(PINB1==1)
		 k=1;
		 else
		 k=0;
		 if(PINB3==1)
		 l=1;
		 else
		 l=0;
		 if(PINB5==1)
		 m=1;
		 else
		 m=0;
		 if(PIND2==1)
		 n=1;
		 else
		 n=0;
		 if(PIND4==1)
		 o=1;
		 else
		 o=0;
		 if(PIND6==1)
		 p=1;
		 else
		 p=0;
		 _delay_ms(1000);
		 PORTB=0b00010101;
		 PORTD=0b10101010;
		 if(PINB1==0)
		 k=1;
		 else
		 k=0;
		 if(PINB3==0)
		 l=1;
		 else
		 l=0;
		 if(PINB5==0)
		 m=1;
		 else
		 m=0;
		 if(PIND2==0)
		 n=1;
		 else
		 n=0;
		 if(PIND4==1)
		 o=1;
		 else
		 o=0;
		 if(PIND6==1)
		 p=1;
		 else
		 p=0;
		 _delay_ms(1000);
		 
		 if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1))
		 {	 LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("NOT GATE is OK");
			 _delay_ms(1000);
		 }
		 else
		 {	 LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("NOT GATE is bad");
			 _delay_ms(1000);
		 }
		 
		 break;
	 }
	 case 07://3input AND
	 {
		DDRB=0b00100000;
		DDRD=0b10010001;
		PORTB=0b00000000;
		PORTD=0b10000000;
		if(PINB5==0)
		k=1;
		else
		k=0;
		if(PIND1==0)
		l=1;
		else
		l=0;
		if(PIND4==0)
		m=1;
		else
		m=0;
		_delay_ms(1000);
		PORTB=0b00000001;
		PORTD=0b10100100;
		if(PINB5==0)
		n=1;
		else
		n=0;
		if(PIND0==0)
		o=1;
		else
		o=0;
		if(PIND4==0)
		p=1;
		else
		p=0;
		_delay_ms(1000);
	PORTB=0b00001111;
	PORTD=0b10001100;
	if(PINB5==0)
	q=1;
	else
	q=0;
	if(PIND0==0)
	r=1;
	else
	r=0;
	if(PIND4==0)
	s=1;
	else
	s=0;
	_delay_ms(1000);
	PORTB=0b00011111;
	PORTD=0b10101110;
	if(PINB5==1)
	t=1;
	else
	t=0;
	if(PIND0==1)
	u=1;
	else
	u=0;
	if(PIND4==1)
	v=1;
	else
	v=0;
	_delay_ms(1000);
		if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		{	 LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("3 INPUT AND is");
			LCDGotoXY(0,1);
			LCDWriteString("     OK ");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("3 INPUT AND is ");
			LCDGotoXY(0,1);
			LCDWriteString("     BAD ");
			_delay_ms(1000);
		}
		
		break;
	 } 
	  case 0X08://3 input NAND
	{
		DDRB=0b00100000;
		DDRD=0b10010001;
		PORTB=0b00000000;
		PORTD=0b10000000;
		if(PINB5==1)
		k=1;
		else
		k=0;
		if(PIND0==1)
		l=1;
		else
		l=0;
		if(PIND4==1)
		m=1;
		else
		m=0;
		_delay_ms(1000);
			PORTB=0b00000001;
			PORTD=0b10100100;
		if(PINB5==1)
		n=1;
		else
		n=0;
		if(PIND0==1)
		o=1;
		else
		o=0;
		if(PIND4==1)
		p=1;
		else
		p=0;
		_delay_ms(1000);
		PORTB=0b00001111;
		PORTD=0b10001100;
		if(PINB5==1)
		q=1;
		else
		q=0;
		if(PIND0==1)
		r=1;
		else
		r=0;
		if(PIND4==1)
		s=1;
		else
		s=0;
		_delay_ms(1000);
		PORTB=0b00011111;
		PORTD=0b10101110;
		if(PINB5==0)
		t=1;
		else
		t=0;
		if(PIND0==0)
		u=1;
		else
		u=0;
		if(PIND4==0)
		v=1;
		else
		v=0;
		_delay_ms(1000);
		if((k==1)&&(l==1)&&(m==1)&&(n==1)&&(o==1)&&(p==1)&&(q==1)&&(r==1)&&(s==1)&&(t==1)&&(u==1)&&(v==1))
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString(" 3 INPUT NAND is ");
			LCDGotoXY(0,1);
			LCDWriteString("        OK ");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("3 INPUT NAND is ");
			LCDGotoXY(0,1);
			LCDWriteString("     BAD ");
			_delay_ms(1000);
		}
		
		break;
	}
	case 10://deatails
	{
	_delay_ms(1000);
	key1=GetKeyPressed();
	_delay_ms(1000);
	switch(key1)
	{
		case 00:
		{
			if((k==1)&&(o==1)&&(s==1))
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 1 is good");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 1 is bad");
			_delay_ms(1000);
	    }
		if((l==1)&&(p==1)&&(t==1))
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 2 is good");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 2 is bad");
			_delay_ms(1000);
		}
		if((m==1)&&(q==1)&&(u==1))
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 3 is good");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 3 is bad");
			_delay_ms(1000);
		}
		if((n==1)&&(r==1)&&(v==1))
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 4 is good");
			_delay_ms(1000);
		}
		else
		{	LCDClear();
			LCDGotoXY(0,0);
			LCDWriteString("GATE 4 is bad");
			_delay_ms(1000);
		}
		_delay_ms(100);
		break;
	 }
	 case 01:
	 {
		 if((k==1)&&(o==1)&&(s==1))
		 {	 LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(p==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(q==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if((n==1)&&(r==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }	
	 case 02:
	 {
		 if((k==1)&&(o==1)&&(s==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(p==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(q==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if((n==1)&&(r==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }	
	 
	 case 03:
	 {
		 if((k==1)&&(o==1)&&(s==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(p==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(q==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if((n==1)&&(r==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }
	 case 04:
	 {
		 if((k==1)&&(o==1)&&(s==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(p==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(q==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if((n==1)&&(r==1)&&(v==1))
		 {	LCDClear();		
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }
	 case 05:
	 {
		 if((k==1)&&(o==1)&&(s==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(p==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(q==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if((n==1)&&(r==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }
	 case 06:
	 {
		 if(k==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if(l==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if(m==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 if(n==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 4 is bad");
			 _delay_ms(1000);
		 }
		 if(o==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 5 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 5 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 if(p==1)
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 6 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 6 is bad");
			 _delay_ms(1000);
		 }
		 break;
	 }
	 case 07:
	 {
		 if((k==1)&&(n==1)&&(q==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(o==1)&&(r==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(p==1)&&(s==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }
	
	case 0X08:
	 {
		 if((k==1)&&(n==1)&&(q==1)&&(t==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 1 is bad");
			 _delay_ms(1000);
		 }
		 if((l==1)&&(o==1)&&(r==1)&&(u==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 2 is bad");
			 _delay_ms(1000);
		 }
		 if((m==1)&&(p==1)&&(s==1)&&(v==1))
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is good");
			 _delay_ms(1000);
		 }
		 else
		 {	LCDClear();
			 LCDGotoXY(0,0);
			 LCDWriteString("GATE 3 is bad");
			 _delay_ms(1000);
		 }
		 _delay_ms(100);
		 break;
	 }
	 }
	 break;
	 }	 	 
		
    }
	
}}