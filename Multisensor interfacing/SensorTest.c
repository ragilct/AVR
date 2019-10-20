/*********************************************************************

                 xBoard(TM) v2.0 Sample Programs

               ------------------------------------


Description : 	Simple Utility to View 3 sensor readings on LCD Screen.
				Sensors Must be connected to ADC0,ADC1,ADC2

Author      : ragil

                   
**********************************************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

void InitADC()
{
   ADMUX=(1<<REFS0);                                  	// For Aref=AVcc;
   ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);    //Rrescalar div factor =128

}

uint16_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;  
   ADMUX&=0b11100000;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it

   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}

void Wait()
{
   uint8_t i;
   for(i=0;i<20;i++)
      _delay_loop_2(0);
}


void main()
{
   uint16_t adc_result[3];	//Array

   //Wait for LCD to Startup
   _delay_loop_2(0);

   //Initialize LCD
   LCDInit(LS_BLINK|LS_ULINE);
   LCDClear();

   //Initialize ADC
   InitADC();

   //Welcome and Intro
   LCDWriteString("xBoard Sensor");
   LCDWriteStringXY(0,1,"Test Utility");
   
   Wait();
   Wait();
   Wait();
   Wait();

   LCDClear();
   LCDWriteString("S#1  S#2  S#3 ");

   while(1)
   {
      adc_result[0]=ReadADC(0);           // Read Analog value from channel-0
	  adc_result[1]=ReadADC(1);           // Read Analog value from channel-1
	  adc_result[2]=ReadADC(2);           // Read Analog value from channel-2

      LCDWriteIntXY(0,1,adc_result[0],4); //Print the value 
	  LCDWriteIntXY(5,1,adc_result[1],4); //Print the value 
	  LCDWriteIntXY(10,1,adc_result[2],4); //Print the value 

      Wait();
   }
}
