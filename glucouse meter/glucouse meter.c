/*
 * glucouse_meter.c
 *
 * Created: 3/28/2015 12:33:27 PM
 *  Author: RAGIL
 */ 

//header file
#include <avr/io.h>
//#define F_CPU 8000000UL
#include <util/delay.h>
#include "adc driver/adc.h"
#include "LCD DRIVER/lcd.h"

// declaration
void t0_pwm_init(void);
void SetPWMOutput(uint8_t duty);

/*
#define green PINB0
#define red  PINB1
#define ir PB2
*/
unsigned int samples[120];
/*
unsigned int glucouse[30][20]={
	{50,51,53,55,56,57,58,60,61,63,64,65,66,67,68,69,70,71,72,73},//1
	{51,52,53,54,55,56,57,59,60,62,64,66,68,69,70,71,73,75,76,77},//2
	{53,55,56,57,58,59,60,61,63,65,66,68,69,71,73,74,76,77,79,81},//3
	{55,56,57,59,61,62,63,64,66,67,69,71,74,76,77,78,79,80,82,84},//4
	{57,58,61,62,64,65,66,68,70,71,73,74,75,76,78,80,81,82,83,85},//5
	{59,60,62,63,65,67,69,70,72,74,75,77,78,80,82,84,85,87,89,90},////6
	{61,63,65,67,69,70,72,74,75,77,78,80,82,85,86,87,88,90,92,93}, //7
	{63,65,66,68,71,73,75,78,79,81,82,84,86,88,89,90,92,93,94,94},//8
	{64,67,69,71,74,76,78,80,83,85,88,90,91,92,92,93,93,94,95,96},// 9
	{66,67,70,73,75,77,79,81,83,85,88,90,91,92,92,93,93,94,95,96},// 10
	{68,70,72,75,78,79,82,84,86,87,89,90,91,92,93,94,95,96,97,97},//11
	{71,74,76,79,80,82,85,87,88,90,91,91,92,92,93,94,95,96,97,98},//12
	{73,75,77,80,81,83,86,88,90,91,91,92,93,93,94,95,96,97,98,98},//13
	{76,78,80,83,85,87,89,91,92,93,93,94,94,95,95,96,96,97,98,99},//14
	{78,80,84,86,87,89,90,91,92,93,93,94,94,95,95,96,96,97,98,99},//15
	{81,83,86,88,89,91,92,93,94,94,95,95,96,96,97,97,98,99,99,100},//16
	{84,86,88,90,91,92,93,94,95,95,95,96,96,97,97,98,99,99,100,102},//	18
	{87,88,90,91,92,93,94,94,95,96,97,98,98,99,99,100,102,104,105,106},//19
	{89,90,91,91,92,93,94,95,96,97,98,99,100,103,105,106,107,109,110,113},//20
	{91,92,93,94,95,96,97,98,99,100,102,103,105,106,108,110,112,115,116,120},//21
	{92,93,94,96,98,99,101,103,104,105,106,109,105,108,110,112,116,118,122,125},//22
	{95,97,100,103,105,109,111,114,117,119,120,124,126,129,130,132,135,136,137,138},//23
	{101,104,107,111,115,119,121,124,127,129,130,133,136,139,141,143,146,149,151,154},//24
	{103,108,112,114,117,120,123,125,128,132,134,135,138,142,145,147,149,153,155,157},//25
	{110,114,117,122,125,128,133,136,139,141,143,145,146,148,152,155,158,160,162,164},//26
	{114,118,122,125,127,130,134,137,140,145,147,149,152,155,158,162,164,167,170,173},//27
	{119,124,132,138,143,147,150,153,155,158,160,164,166,168,172,176,180,184,187,192},//28
	{123,130,136,142,149,153,157,160,164,166,169,173,177,182,186,190,195,198,202,208},//28
	{135,143,148,154,159,162,167,174,178,184,189,195,205,208,214,221,228,230,237,244},//29
	{146,155,164,171,179,186,192,198,212,225,231,243,249,253,265,274,283,289,294,300},
		};
		
*/
unsigned int min=0,max=0,sum=0,nir1=0,nir2=0,nir3=0,ratio=0,glucouseread=0;
float glux=0,earthick=0,avg=0,reddc=0,redac=0,irac=0,irdc=0,iravg=0;
int main(void)
{
	unsigned int i=0;
	DDRB=0XFF;
	DDRD=0xFF;
	DDRA=0x00;

	t0_pwm_init();
	ADC_Init();

	LCDInit(LS_NONE);
	LCDClear();
	SetPWMOutput(0);
	LCDWriteStringXY(0,0,"START");
	_delay_ms(3000);
	 LCDClear();
    //green=1;
	//red=0;
	//ir=0;
	PORTB=0X01;
	LCDClear();
	LCDWriteStringXY(0,0,"earthick check");
	_delay_ms(1500);
	for(i=0;i<20;i++)
	{
		samples[i]=(1010-ADC_Read(2)); //Photo transister BYP62-3(AN2)
		_delay_us(2);
	}
	//green=0;
	//red=1;
	//ir=0;
	PORTB=0x02;
	LCDClear();
	LCDWriteStringXY(0,0,"oxi level check");
	_delay_ms(1500);
	for(i=20;i<40;i++)
	{
		
			samples[i]=(1010-ADC_Read(2));//Photo transister BYP62-3(AN2)
			_delay_us(2);
	}
		// green=0;
		//red=1;
		//ir=0;
		PORTB=0x04;
		for(i=40;i<60;i++)
		{
			samples[i]=(1015-ADC_Read(1));//ir reciver(AN1)
			_delay_us(2);
		}
	
	PORTB=0x00;
	LCDClear();
	LCDWriteStringXY(0,0,"glucouse check");
	_delay_ms(1500);
	LCDWriteStringXY(0,1,"sample1");
		SetPWMOutput(191);
		_delay_ms(1000);
	for(i=60;i<80;i++)
	{
		samples[i]=(195-ADC_Read(0));//nir reciver(AN0)
		_delay_us(2);
	}
	_delay_ms(2000);
	LCDWriteStringXY(0,1,"sample2");
	SetPWMOutput(210);
	_delay_ms(1000);
	for(i=80; i<100; i++)
	{
		samples[i]=(210-ADC_Read(0));//nir reciver(AN0)
		_delay_us(2);
	}
	_delay_ms(2000);
	LCDWriteStringXY(0,1,"sample3");
	SetPWMOutput(255);
	_delay_ms(1000);
	for(i=100;i<120;i++)
	{
		samples[i]=(243-ADC_Read(0));//nir reciver(AN0)
		_delay_us(2);
	}
	_delay_ms(2000);
	SetPWMOutput(0);
	sum=0;
	for(i=0;i<20;i++)
	{
		sum=sum+samples[i];
	}
	avg=sum/20;
	earthick=avg;
	sum=0;
	min=samples[20];
	for(i=21;i<40;i++)
	{
		if(min>samples[i])
		{
			min=samples[i];
		}
	}
	reddc=min;
	max=samples[20];
	for(i=21;i<40;i++)
	{
		if(max<samples[i])
		{
			max=samples[i];
		}
	}
	redac=max;
	min=samples[40];
	for(i=41;i<60;i++)
	{
		if(min>samples[i])
		{
			min=samples[i];
		}
	}
	irdc=min;
	max=samples[40];
	for(i=41;i<60;i++)
	{
		if(max<samples[i])
		{
			max=samples[i];
		}
	}
	irac=max;
	sum=0;
	for(i=40;i<60;i++)
	{
		sum=sum+samples[i];
	}
	avg=sum/20;
	iravg=avg;
	sum=0;
	for(i=60;i<80;i++)
	{
		sum=sum+samples[i];
	}
	avg=sum/20;
	nir1=(avg*1000)/1270;
	
	sum=0;
	for(i=80;i<100;i++)
	{
		sum=sum+samples[i];
	}
	avg=sum/20;
	nir2=(avg*1000)/1285;
	
	sum=0;
	for(i=100;i<120;i++)
	{
		sum=sum+samples[i];
	}
	avg=sum/20;
	nir3=(avg*1000)/1305;
	nir3=avg;
	sum=(nir1+nir2+nir3);
	glux=sum/3;
	if((earthick<30)&&(redac<20)&&(reddc<20))
	{
		LCDClear();
		LCDWriteStringXY(0,0,"  Probe   not");
		LCDWriteStringXY(0,1,"   Connected");
		while(1);
	}
	earthick=((2.303*((earthick/10.10)*.012))*1000);
	ratio=(((redac/reddc)/(irac/irdc))*1000);
/*	
LCDClear();
LCDWriteIntXY(0,0,nir1,5);
LCDWriteIntXY(8,0,nir2,5);
LCDWriteIntXY(0,1,nir3,5);
_delay_ms(3000);
*/
LCDClear();
LCDWriteStringXY(0,0,"Ear thick in um");
LCDWriteIntXY(0,1,earthick,4);
_delay_ms(3000);
/*
LCDClear();
LCDWriteStringXY(0,0,"reddc");
LCDWriteIntXY(0,1,reddc,4);
_delay_ms(3000);
LCDClear();
LCDWriteStringXY(0,0,"redac");
LCDWriteIntXY(0,1,redac,4);
_delay_ms(3000);
LCDClear();
LCDWriteStringXY(0,0,"irdc");
LCDWriteIntXY(0,1,irdc,4);
_delay_ms(3000);
LCDClear();
LCDWriteStringXY(0,0,"irac");
LCDWriteIntXY(0,1,irac,4);
_delay_ms(3000);
LCDClear();
LCDWriteStringXY(0,0,"iravg");
LCDWriteIntXY(0,1,iravg,4);
_delay_ms(3000);
*/
LCDClear();
LCDWriteStringXY(0,0,"R Ratio");
LCDWriteIntXY(0,1,ratio,4);
_delay_ms(3000);
/*
LCDClear();
LCDWriteStringXY(0,0,"glux");
LCDWriteIntXY(0,1,glux,4);
_delay_ms(3000);
*/
glucouseread=((.904191*glux)-(2.16433*iravg)+(.0023*earthick)+(.00137*ratio));
LCDClear();
LCDWriteStringXY(0,0,"Glucouse ");
LCDWriteIntXY(0,1,glucouseread,4);
_delay_ms(3000);
/*
glucouseread=((0.17471*ratio)+(6.7425*glux)-(4.16934*earthick));
LCDClear();
LCDWriteStringXY(0,0,"equation 2");
LCDWriteIntXY(0,1,glucouseread,4);
_delay_ms(3000);

glucouseread=(184.6-(4.8*iravg));
LCDClear();
LCDWriteStringXY(0,0,"equation 3");
LCDWriteIntXY(0,1,glucouseread,4);
_delay_ms(3000);

glucouseread=((4*glux)-600);
LCDClear();
LCDWriteStringXY(0,0,"Glucouse 2");
LCDWriteIntXY(0,1,glucouseread,4);
_delay_ms(3000);
*/
while(1);	  
   	   

}
void t0_pwm_init()	// initialization for Phase Correct PWM signal using timer 0
{
	// WGM0[1:0]= 01, for Phase Correct PWM mode
	// COM0[1:0]= 10, to select non inveting mode
	// CS0[2:0] =101. for prescaler=1024
	
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS02)|(1<<CS00);// TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);
	DDRB|=(1<<PB3);	// selcet OC0 as output pin
	TCNT0=0;
	//TIMSK|=(1<<OCIE0);	//enable Output compare interrupt
}

void SetPWMOutput(uint8_t duty)
{
	OCR0=duty;
}