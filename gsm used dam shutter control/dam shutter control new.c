/*
 * dam_shutter_control_new.c
 *
 * Created: 3/14/2014 8:20:07 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "util/lcd/lcd.h"
#include "util/sim300/sim300.h"
#include "util/usart/usart.h"


void Halt();
ISR(TIMER1_COMPA_vect)
{
	OCR1AH = 0x27;
	OCR1AL = 0x0F;
	
}
void eeprom_write(char add,int data)
{
	while(EECR&(1<<EEWE));
	EEAR=add;
	EEDR=data;
	EECR|=(1<<EEMWE);
	EECR|=(1<<EEWE);
}
int eeprom_read(char addr)
{
	while(EECR&(1<<EEWE));
	EEAR=addr;
	EECR|=(1<<EERE);
	return(EEDR);
	}
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (1<<ADLAR))

// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
	ADMUX=adc_input | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCH;
}


int main(void)
{
	int position,k=0,l=0,m=0,n=0,o=0,p=0;
	 char massage[15];
	char msg[50];
	int save,data,mass;
	// ADC initialization
	// ADC Clock frequency: 250.000 kHz
	// ADC Voltage Reference: AVCC pin
	// ADC Auto Trigger Source: Free Running
	// Only the 8 most significant bits of
	// the AD conversion result are used
	ADMUX=ADC_VREF_TYPE;
	ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
	SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
	DDRD=0XFF;
	DDRA=0x00;
	DDRB=0xFF;
	DDRC=0xFF;
	TCCR1A = 0x40;
	OCR1AH = 0x27;
	OCR1AL = 0x0F;
	TIMSK = 0x04;
	TCCR1B = 0x09;
	sei();
	//Initialize LCD Module
	LCDInit(LS_NONE);
	LCDClear();
	eeprom_write(0x5F,0);
	//Intro Message
	LCDWriteString("welcome !");
	_delay_ms(1000);
	
	LCDClear();
	
	
	//Initialize SIM300 module
	LCDWriteString("Initializing ...");
	int8_t r= SIM300Init();
	
	_delay_ms(1000);
	
	//Check the status of initialization
	switch(r)
	{
		case SIM300_OK:
		LCDWriteStringXY(0,1,"OK !");
		break;
		case SIM300_TIMEOUT:
		LCDWriteStringXY(0,1,"No response");
		Halt();
		case SIM300_INVALID_RESPONSE:
		LCDWriteStringXY(0,1,"Inv response");
		Halt();
		case SIM300_FAIL:
		LCDWriteStringXY(0,1,"Fail");
		Halt();
		default:
		LCDWriteStringXY(0,1,"Unknown Error");
		Halt();
	}
	
	_delay_ms(1000);
	
	//IMEI No display
	LCDClear();
	
	char imei[16];
	
	r=SIM300GetIMEI(imei);
	
	if(r==SIM300_TIMEOUT)
	{
		LCDWriteString("Comm Error !");
		Halt();
	}
	
	LCDWriteString("Device IMEI:");
	LCDWriteStringXY(0,1,imei);
	
	_delay_ms(1000);
	
	//Manufacturer ID
	LCDClear();
	
	char man_id[48];
	
	r=SIM300GetManufacturer(man_id);
	
	if(r==SIM300_TIMEOUT)
	{
		LCDWriteString("Comm Error !");
		Halt();
	}
	
	LCDWriteString("Manufacturer:");
	LCDWriteStringXY(0,1,man_id);
	
	_delay_ms(1000);
	
	//Manufacturer ID
	LCDClear();
	
	char model[48];
	
	r=SIM300GetModel(model);

	if(r==SIM300_TIMEOUT)
	{
		LCDWriteString("Comm Error !");
		Halt();
	}
	
	LCDWriteString("Model:");
	LCDWriteStringXY(0,1,model);
	
	_delay_ms(1000);
	

	
	//Check Sim Card Presence
	LCDClear();
	LCDWriteString("Checking SIMCard");
	
	_delay_ms(1000);
	
	r=SIM300IsSIMInserted();
	
	if (r==SIM300_SIM_NOT_PRESENT)
	{
		//Sim card is NOT present
		LCDWriteStringXY(0,1,"No SIM Card !");
		
		Halt();
	}
	else if(r==SIM300_TIMEOUT)
	{
		//Communication Error
		LCDWriteStringXY(0,1,"Comm Error !");
		
		Halt();
	}
	else if(r==SIM300_SIM_PRESENT)
	{
		//Sim card present
		LCDWriteStringXY(0,1,"SIM Card Present");
		
		_delay_ms(1000);
	}
	
	//Network search
	LCDClear();
	LCDWriteStringXY(0,0,"SearchingNetwork");
	_delay_ms(1000);
	
	uint8_t		nw_found=0;
	uint16_t	tries=0;
	uint8_t		x=0;
	
	while(!nw_found)
	{
		r=SIM300GetNetStat();
		
		if(r==SIM300_NW_SEARCHING)
		{
			LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
			LCDWriteStringXY(x,1,"%1");
			LCDGotoXY(17,1);
			
			x++;
			
			if(x==16) x=0;
			
			_delay_ms(50);
			
			tries++;
			
			if(tries==600)
			break;
		}
		else
		break;
		
	}
	LCDClear();
	
	if(r==SIM300_NW_REGISTERED_HOME)
	{
		LCDWriteString("Network Found");
	}
	else
	{
		LCDWriteString("Cant Connt to NW!");
		Halt();
	}
	
	_delay_ms(1000);
	
	LCDClear();
	
	//Show Provider Name
	char pname[32];
	r=SIM300GetProviderName(pname);
	
	if(r==0)
	{
		LCDWriteString("Comm Error !");
		Halt();
	}
	
	LCDWriteString(pname);
	
	_delay_ms(1000);
	
	//Send MSG
	LCDClear();
	LCDWriteString("Sending Msg");
	
	uint8_t ref;
	

	r=SIM300SendMsg("8891767374","welcome to our project",&ref);//Change phone number to some valid value!
	
	if(r==SIM300_OK)
	{
		LCDWriteStringXY(0,1,"Success");
		LCDWriteIntXY(9,1,ref,3);
	}
	else if(r==SIM300_TIMEOUT)
	{
		LCDWriteStringXY(0,1,"Time out !");
	}
	else
	{
		LCDWriteStringXY(0,1,"Fail  !");
	}
	
	_delay_ms(2000);
	
	
	
    while(1)
    {
		position=PINA;
		switch(position)
		{
	        case 0xF6:
			{  
				massage[3]="80ft";
				LCDClear();
				LCDGotoXY(0,0);
			    LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("80ft");
				_delay_ms(1000);
				break;
			}	
			case 0xF7:
			{			
			  massage[3]="85ft";
			  LCDClear();
			  LCDGotoXY(0,0);
			  LCDWriteString("water level");
			  LCDGotoXY(0,1);
			  LCDWriteString("85ft");
			  _delay_ms(1000);
			  break;
			}
			case 0xF8:
			{
				k=0;
				massage[3]="90ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("90ft");
				_delay_ms(1000);
				if(k==0)
				{
					k=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]-48)*100)+((msg[1]-48)*10)+((msg[2]-48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{							
							
						 save=eeprom_read(0x5F);
						 data=mass-save;
						 switch(data)
						 {
							 case 25:
							 {
								 PORTC=0x07;
								 _delay_ms(50);
								 PORTC=0x00;
								 break;
							 }							
								 
							 case 50:
							 {
								PORTC=0x07;
								_delay_ms(100);
								PORTC=0x00;
								break; 
							 }
							 case 75:
							 {
								 PORTC=0x07;
								 _delay_ms(150);
								 PORTC=0x00;
								 break;
							 }	
							 case 100:
							 {
								 PORTC=0x07;
								 _delay_ms(50);
								 PORTC=0x00;
								 break;
							 }
							 }							 																					
						 }
							 						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
					
				}
				break;
			}	
			case 0xF9:
			{
				massage[3]="95ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("95ft");
				_delay_ms(1000);
				if(l==0)
				{
					l=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]-48)*100)+((msg[1]-48)*10)+((msg[2]-48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{
							
							save=eeprom_read(0x5F);
							data=mass-save;
							eeprom_write(0x5F,mass);
							switch(data)
							{
								case 25:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
								
								case 50:
								{
									PORTC=0x03;
									_delay_ms(100);
									PORTC=0x00;
									break;
								}
								case 75:
								{
									PORTC=0x03;
									_delay_ms(150);
									PORTC=0x00;
									break;
								}
								case 100:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
							}
						}
						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
				}					
					
				break;
			}	
			case 0xFA:
			{
				massage[3]="100ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("100ft");
				_delay_ms(1000);
				if(m==0)
				{
					m=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]+48)*100)+((msg[1]+48)*10)+((msg[2]+48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{
							
							save=eeprom_read(0x5F);
							data=mass-save;
							eeprom_write(0x5F,mass);
							switch(data)
							{
								case 25:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
								
								case 50:
								{
									PORTC=0x03;
									_delay_ms(100);
									PORTC=0x00;
									break;
								}
								case 75:
								{
									PORTC=0x03;
									_delay_ms(150);
									PORTC=0x00;
									break;
								}
								case 100:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
							}
						}
						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
				}					
					
				break;
			}
			case 0xFB:
			{
				massage[3]="105ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("105ft");
				_delay_ms(1000);
				if(n==0)
				{
					n=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]-48)*100)+((msg[1]-48)*10)+((msg[2]-48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{
							
							save=eeprom_read(0x5F);
							data=mass-save;
							eeprom_write(0x5F,mass);
							switch(data)
							{
								case 25:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
								
								case 50:
								{
									PORTC=0x03;
									_delay_ms(100);
									PORTC=0x00;
									break;
								}
								case 75:
								{
									PORTC=0x03;
									_delay_ms(150);
									PORTC=0x00;
									break;
								}
								case 100:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
							}
						}
						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
					
				}					
				break;
			}	 
			case 0XFC:
			{
				massage[4]="110ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("110ft");
				_delay_ms(1000);
				if(o==0)
				{
					o=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]-48)*100)+((msg[1]-48)*10)+((msg[2]-48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{
							
							save=eeprom_read(0x5F);
							data=mass-save;
							eeprom_write(0x5F,mass);
							switch(data)
							{
								case 25:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
								
								case 50:
								{
									PORTC=0x03;
									_delay_ms(100);
									PORTC=0x00;
									break;
								}
								case 75:
								{
									PORTC=0x03;
									_delay_ms(150);
									PORTC=0x00;
									break;
								}
								case 100:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
							}
						}
						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
					
				}					
				break;
			} 
			case 0XFD:
			{
				massage[3]="120ft";
				LCDClear();
				LCDGotoXY(0,0);
				LCDWriteString("water level");
				LCDGotoXY(0,1);
				LCDWriteString("120ft");
				_delay_ms(1000);
				if(p==0)
				{
					p=1;
					LCDClear();
					LCDWriteString("Sending Msg");
					
					uint8_t ref;
					

					r=SIM300SendMsg("8891767374",massage,&ref);//Change phone number to some valid value!
					
					if(r==SIM300_OK)
					{
						LCDWriteStringXY(0,1,"Success");
						LCDWriteIntXY(9,1,ref,3);
					}
					else if(r==SIM300_TIMEOUT)
					{
						LCDWriteStringXY(0,1,"Time out !");
					}
					else
					{
						LCDWriteStringXY(0,1,"Fail  !");
					}
					
					_delay_ms(2000);
					uint8_t id;
					
					UFlushBuffer();
					
					
					LCDClear();
					
					LCDWriteStringXY(0,0,"Waiting for msg");
					
					x=0;
					int8_t vx=1;
					
					while(SIM300WaitForMsg(&id)!=SIM300_OK)
					{
						LCDWriteStringXY(0,1,"%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0%0");
						LCDWriteStringXY(x,1,"%1");
						LCDGotoXY(17,1);
						
						x+=vx;
						
						if(x==15 || x==0) vx=vx*-1;
					}
					
					LCDWriteStringXY(0,1,"MSG Received    ");
					
					_delay_ms(1000);
					
					//Now read and display msg
					LCDClear();
					
					
					r=SIM300ReadMsg(id,msg);
					
					if(r==SIM300_OK)
					{
						mass=(((msg[0]-48)*100)+((msg[1]-48)*10)+((msg[2]-48)));
						if(mass==0)
						{
							
							PORTC=0x05;
							_delay_ms(250);
							PORTC=0x00;
						}
						else
						{
							
							save=eeprom_read(0x5F);
							data=mass-save;
							eeprom_write(0x5F,mass);
							switch(data)
							{
								case 25:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
								
								case 50:
								{
									PORTC=0x03;
									_delay_ms(100);
									PORTC=0x00;
									break;
								}
								case 75:
								{
									PORTC=0x03;
									_delay_ms(150);
									PORTC=0x00;
									break;
								}
								case 100:
								{
									PORTC=0x03;
									_delay_ms(50);
									PORTC=0x00;
									break;
								}
							}
						}
						
						LCDWriteStringXY(0,0,msg);
						
						_delay_ms(3000);
						
					}
					else
					{
						LCDWriteString("Err Reading Msg !");
						
						_delay_ms(3000);
						
					}
					
					//Finally delete the msg
					if (SIM300DeleteMsg(id)!=SIM300_OK)
					{
						LCDWriteString("Err Deleting Msg !");
						
						_delay_ms(3000);
					}
					
				}
											
					
				break;
			}
		}	
		
    }
	
}
void Halt()
{
	while(1);
}