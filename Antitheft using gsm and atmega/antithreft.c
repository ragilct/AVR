/*
 * antithreft.c
 *
 * Created: 2/2/2014 9:09:33 PM
 *  Author: RAGIL
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <util/lcd/lcd.h>
#include <util/sim300/sim300.h>
#include <util/usart/usart.h>
uint8_t GetKeyPressed();
void eeprom_write(unsigned char addres,unsigned char password);
unsigned char eeprom_read(unsigned char addres);
void sim_config();

#define KEYPAD A	//KEYPAD IS ATTACHED ON PORTA

//Don't Touch the lines below
//*******************************
#define KEYPAD_PORT PORT(KEYPAD)
#define KEYPAD_DDR 	DDR(KEYPAD)
#define KEYPAD_PIN 	PIN(KEYPAD)
//*******************************
int main(void)
{
	uint8_t key,new=1,passwoads[7],k=0;
	sim_config();
    while(1)
    {
       	_delay_loop_2(0);
       new=eeprom_read(0x5f);
       	LCDInit(LS_NONE);
        if(new==1)
			{
				LCDClear();
				LCDWriteString("Sending Msg");
				
				uint8_t ref;
				r=SIM300SendMsg("9526466096","SET PASSSWORD",&ref);//Change phone number to some valid value!
				
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
						PASSWOADORIGINAL=msg;
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
					new++;
					eeprom_write(0x5f,new);
												
				
	       	key=GetKeyPressed();	//Get the keycode of pressed key
			   passwoads[k]=key;

	       	LCDWriteIntXY(0,0,key,3);	//Print it at location 0,0 on LCD.
       	
		
    }
}
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
void eeprom_write(unsigned char addres,unsigned char password)
{
	while(EECR & (1<<EEWE));
	EEAR=addres;
	EEDR=password;
	EECR |=(1<<EEMWE);
	EECR |=(1<<EEWE);
}	
	
unsigned char eeprom_read(unsigned char addres)
{
	
	unsigned char data;
	while(EECR & (1<<EEWE));
	EEAR=addres;
	EECR |=(1<<EERE);
	data=EEDR;
	return(data);
}	
void sim_config()
{
	SIM300Cmd("AT");
	_delay_ms(1000);
	SIM300Cmd("at+CMGF=1");
	_delay_ms(1000);
}
	
	
}