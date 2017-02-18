/*
 * lcd_adch.c
 *
 * Created: 03-12-2013 01:32:41
 *  Author: gman
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "LCD.c"
#define LCD_DATA PORTB		// In my case PORTB is the PORT from which I send data to my LCD
#define En PORTB2

int main(void)
{   DDRB=255;
	DDRC=0;
	DDRA=0;
	DDRD=0;
	init_LCD();
	_delay_ms(50);
	int Ot[6] ;
	while (1)
	{
		clear_display();
		ADMUX=0b01100000;
		ADCSRA=0b1000111;
		for(int i=0;i<6;i++)
		{   ADCSRA=0b11000111;
			while(ADCSRA&(1<<ADSC))
			{
			}
			Ot[i]=ADCH;
			ADMUX++;
		}
		
		print_integer(Ot[0]);
		print_string(" ");
		print_integer(Ot[1]);
		print_string(" ");
		print_integer(Ot[2]);
		set_DDRAM_address(0x40);
		print_integer(Ot[3]);
		print_string(" ");
		print_integer(Ot[4]);
		print_string(" ");
		print_integer(Ot[5]);
		_delay_ms(3000);
	}
}