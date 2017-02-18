/*
 * line_follower_with_pwm.c
 *
 * Created: 02-12-2013 23:46:47
 *  Author: gman
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{   DDRA=0;
	DDRC=255;
	DDRD=255;
	PORTD=0b00110000;
	ADCSRA=0b10000111; 
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=0b10111111;
	OCR1BL=0b10111111;
	float Ot[5];
	int s[5];
	float Th[5]={230.5,145.5,143.5,154,230};
	
    while(1)
    {  
		ADMUX=0b01100000;
		for(int i=0;i<5;i++)
		{   ADCSRA=0b11000111;
			while(ADCSRA&(1<<ADSC))
			{
			}
			Ot[i]=ADCH;
			if(Ot[i]>Th[i])
			{s[i]=1;}
			else
			{s[i]=0;}
			ADMUX++;
		}
		int in=((s[0]*16)+(s[1]*8)+(s[2]*4)+(s[3]*2)+(s[4]));
		switch(in)
		{
			case 0b00100:
			case 0b01110:
			case 0b01010:
			case 0b10101:
			{
				PORTC=0b00010100;
				break;
			}
			case 0b10000:
			case 0b11000:
			case 0b11100:
			case 0b10100:
			case 0b11110:

			{   OCR1AL=0b01111111;
				OCR1BL=0b01111111;
				PORTC=0b00011000;
				break;
			}
			case 0b00001 :
			case 0b00011 :
			case 0b00111 :
			case 0b00101 :
			case 0b01111 :
			{   OCR1AL=0b01111111;
				OCR1BL=0b01111111;
				PORTC=0b00100100;
				break;
			}
			case 0b01100 :
			case 0b01000 :
			{    OCR1AL=0b01111111;
				OCR1BL=0b01111111;
				PORTC=0b00010000;
				break;
			}
			case 0b00010:
			case 0b00110:
			{   OCR1AL=0b01111111;
				OCR1BL=0b01111111;
				PORTC=0b00000100;
				break;
			}
			default:
			{
				PORTC=0b00010100;
				break;
			}
		}
	}
}