/*
 * pwm.c
 *
 * Created: 16-01-2014 23:56:48
 *  Author: ragil
 */ 


#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define FREQ 12000000
int proportional=0,integral=0,last_proportional=0,derivative=0,position=0;	// duty cycle require
#define prescaler 8

int OCR_value; //OCR value calculation
float kp=.1,kd=1,ki=.8;

void t0_pwm_init(void);
void t2_fastpwm_init(void);
void ADC_init(void);
unsigned int ADC_read(unsigned char);

int main()
{
	t0_pwm_init();
	t2_fastpwm_init();
	ADC_init();
	sei();
	while(1){
		position=ADC_read(0);    // Replace set_point by your set point
		_delay_ms(500);
		proportional=position-125;
		integral = integral + proportional;
		derivative = proportional - last_proportional;
		last_proportional = proportional;
		OCR_value= (proportional * kp + integral * ki + derivative * kd);
		
	}
}

void t0_pwm_init()	// initialization for Phase Correct PWM signal using timer 0
{
	// WGM0[1:0]= 01, for Phase Correct PWM mode
	// COM0[1:0]= 10, to select non inveting mode
	// CS0[2:0] =010. for prescaler=8
	
	TCCR0=(1<<WGM00)|(2<<COM00)|(2<<CS00);
	DDRB|=(1<<PB3);	// selcet OC0 as output pin
	TIMSK|=(1<<OCIE0);	//enable Output compare interrupt
}

void t2_fastpwm_init()	// initialization for Phase Correct PWM signal using timer 2
{
	// WGM2[1:0]= 11, for Fast PWM mode
	// COM2[1:0]= 10, to select non inveting mode
	// CS2[2:0] =010. for prescaler=8
	
	TCCR2=(1<<WGM20)|(1<<WGM21)|(2<<COM20)|(2<<CS20);
	DDRD|=(1<<PD7);	// selcet OC2 as output pin
	TIMSK|=(1<<OCIE2);	//enable Output compare interrupt
}

ISR(TIMER0_COMP_vect)	// interrupt subroutine
{
	OCR0=OCR_value;	// put OCR value
}

ISR(TIMER2_COMP_vect)	// interrupt subroutine
{
	OCR2=OCR_value;	// put OCR value
}
void ADC_init(void)	// Initialization of ADC
{
	ADMUX=(1<<REFS0);	// AVcc with external capacitor at AREF
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// Enable ADC and set Prescaler division factor as 128
}

unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111;	// channel must be b/w 0 to 7
	ADMUX |= ch;	// selecting channel
	
	ADCSRA|=(1<<ADSC);	// start conversion
	while(!(ADCSRA & (1<<ADIF)));	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);	// clearing of ADIF, it is done by writing 1 to it
	
	return (ADC);
}