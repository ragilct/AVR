/*
 * transmission_line_protection.c
 *
 * Created: 3/22/2014 10:31:20 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "util/lcd/lcd.h"
#include "util/sim300/sim300.h"
#include "util/usart/usart.h"
void Halt();
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
int temcurrent;
char current[]={'0','0','A'};
int main(void)
{
	DDRA=0x00;
	DDRB=0xFF;
	DDRD=0xff;
	DDRC=0xff;
	ADMUX=ADC_VREF_TYPE;
	ADCSRA=(1<<ADEN) | (0<<ADSC) | (1<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
	
	//Initialize LCD Module
	LCDInit(LS_NONE);
	
	//Intro Message
	LCDWriteString("welcome !");
	LCDWriteStringXY(0,1,"miniproject");
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
	

	r=SIM300SendMsg("9895245070","welcome to our project",&ref);//Change phone number to some valid value!
	
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
		int i=0;
        LCDClear();
        temcurrent=read_adc(0);
        temcurrent=((temcurrent/255)*2.1*5);
        _delay_ms(500);
        if(temcurrent>5)
        {
	        i=1;
        }
        
        current[1]=((temcurrent%10)+48);
        temcurrent=temcurrent/10;
        current[0]=(temcurrent+48);
        LCDWriteStringXY(0,0,"current =");
        LCDWriteString(current);
		if(i==1)
		{
			i=0;
			LCDClear();
			LCDWriteString("Sending Msg");
			
			uint8_t ref;
			

			r=SIM300SendMsg("9895245070","over current",&ref);//Change phone number to some valid value!
			
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
		
		if(PIND6==1)
		{
			LCDClear();
			LCDWriteString("manual off ");
			PORTC=0x0F;
		}
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
		char msg[300];
		
		r=SIM300ReadMsg(id,msg);
		
		if(r==SIM300_OK)
		{
			
			LCDWriteStringXY(0,0,msg);
			
			_delay_ms(3000);
			
			if(strcasecmp(msg,"shutdown")==0)
			{
				PORTC=0X0F;
			}
			
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
		
	}		
}
void Halt()
{
	while(1);
}