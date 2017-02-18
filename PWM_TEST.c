/*
 * PWM_TEST.c
 *
 * Created: 02-12-2013 21:56:56
 *  Author: gman
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{   DDRC=255;
	DDRD=255;
	PORTD=0b00110000;
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=0b10111111;
	OCR1BL=0b11111111;
    while(1)
    {
 
	   PORTC=0b00010100;
	   _delay_ms(2000);
	   PORTC=0b00101000;
	   _delay_ms(2000);
    }
	return 0;
}