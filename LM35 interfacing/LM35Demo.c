/*

Description:	Program to demonstrate the use of LM35
				Temperature Sensor.
				
				The temperature is display on seven
				segment display.
________________________________________________________

Author:    ragil
Date:		14 Dec 2012
Updated: 

   
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>


#define SEVEN_SEGMENT_PORT PORTD
#define SEVEN_SEGMENT_DDR  DDRD

volatile uint8_t digits[3];

void SevenSegment(uint8_t n,uint8_t dp)
{
/*
This function writes a digits given by n to the display
the decimal point is displayed if dp=1

Note:

n must be less than 9
*/
   if(n<10)
   {
      switch (n)
      {
         case 0:
                          //.gfedcba
         SEVEN_SEGMENT_PORT=0b00111111;
         break;

         case 1:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b00000110;
         break;

         case 2:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01011011;
         break;

         case 3:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01001111;
         break;

         case 4:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01100110;
         break;

         case 5:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01101101;
         break;

         case 6:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01111101;
         break;

         case 7:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b00000111;
         break;

         case 8:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01111111;
         break;

         case 9:
                        //.gfedcba
         SEVEN_SEGMENT_PORT=0b01101111;
         break;
      }
      if(dp)
      {
         //if decimal point should be displayed

         //make 7th bit high
         SEVEN_SEGMENT_PORT|=0b10000000;
      }
   }
   else
   {
      //This symbol on display tells that n was greater than 9
      //so display can't handle it

      SEVEN_SEGMENT_PORT=0b11111101;
   }
}

void Wait()
{
   uint8_t i;
   for(i=0;i<10;i++)
   {
      _delay_loop_2(0);
   }
}

void Print(uint16_t num)
{
   /* 

   
   This function breaks apart a given integer into separate digits
   and writes them to the display array i.e. digits[]
   
   */
   uint8_t i=0;
   uint8_t j;

   if(num>9999) return;


   while(num)
   {
      digits[i]=num%10;
      i++;

      num=num/10;
   }
   for(j=i;j<4;j++) digits[j]=0;
}


void InitADC()
{
	ADMUX=(1<<REFS0);// For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(7<<ADPS0);
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=ch;

	//Start Single conversion

	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
}

void main()
{
	uint16_t adc_value;
	uint8_t t;
	
	// Prescaler = FCPU/1024
	TCCR0|=(1<<CS02);

	//Enable Overflow Interrupt Enable
	TIMSK|=(1<<TOIE0);

	//Initialize Counter

	TCNT0=0;

	//Port B[3,2,1,0] as out put
	DDRB|=0b00001111;

	PORTB=0b00000001;

	//Port D
	SEVEN_SEGMENT_DDR=0XFF;

	//Turn off all segments
	SEVEN_SEGMENT_PORT=0X00;

	//Enable Global Interrupts
	sei();

	//Enable ADC
	InitADC();

	//Infinite loop
	while(1)
	{
		//Read ADC

		adc_value=ReadADC(0);

		//Convert to degree Centrigrade
		t=adc_value/2;

		//Print to display
		Print(t);

		//Wait some time
		Wait();

	}
}

ISR(TIMER0_OVF_vect)
{
   /*

   This interrupt service routine (ISR)
   Updates the displays

   */
   static uint8_t i=0;

   if(i==3)
   {
      //If on last display then come
      //back to first.
      i=0;
   }
   else
   {
      //Goto Next display
      i++;
   }

   //Activate a display according to i
   PORTB&=(0b11110000);
   PORTB|=(1<<i);

   //Write the digit[i] in the ith display.
   SevenSegment(digits[i],0);
}