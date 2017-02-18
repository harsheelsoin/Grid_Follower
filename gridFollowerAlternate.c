

#define F_CPU 16000000UL
#define checkbit(REGISTER,BIT) (REGISTER&(1<<BIT))
#define setbit(REGISTER,BIT) (REGISTER|(1<<BIT))
#define forward PORTC=0b1010;
#define LEFT PORTC=0b0010;
#define sleft PORTC=0b0110;
#define RIGHT PORTC=0b1000;
#define sright PORTC=0b1001;
#define stall PORTC=0b1111;
#include <avr/io.h>
#include <util/delay.h>
char check,direction=0,X=1,Y=1;

void left()
{
	stall;
	PORTB=0b00111111;
	_delay_ms(1000);
	check=0;
	for(char i=0;i<7;i++)
	{
		if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
		check|=(1<<i);
	}
	PORTB=check;//Displaying the output of the sensors on PORTB
	check=(check<<3);
	check=(check>>3);
	while(check!=0b11111)
	{
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		sleft;
	}
	stall;
	PORTB=0x0f;
	_delay_ms(1000);
	while(checkbit(PINA,5)!=0 && checkbit(PINA,6)!=0)
	{
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		sleft;
	}
	stall;
	PORTB=0x0f;
	_delay_ms(1000);
	if(direction==0)
	direction=3;
	else
	direction--;
	return ;
}
void right()
{
	stall;
	PORTB=0b00111111;
	_delay_ms(1000);
	check=0;
	for(char i=0;i<7;i++)
	{
		if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
		check|=(1<<i);
	}
	PORTB=check;//Displaying the output of the sensors on PORTB
	check=(check<<3);
	check=(check>>3);
	while(check!=0b11111)
	{
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		sright;
	}
	stall;
	PORTB=0x0f;
	_delay_ms(1000);
	while(checkbit(PINA,5)!=0 && checkbit(PINA,6)!=0)
	{
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		sright;
	}
	stall;
	PORTB=0x0f;
	_delay_ms(1000);
	direction++;
	if(direction==4)
	direction=0;
	return ;
}
void changedirection(char end)
{
	while(end!=direction)
	{
		switch(direction)
		{
			case 0:
			if(end==3)
			{
				left();
			}
			else if(end>direction)
			{
				right();
			}
			break;
			case 1:
			case 2:
			if(end>direction)
			{
				right();
			}
			else
			{
				left();
			}
			break;
			case 3:
			if(end==0)
			{
				right();
			}
			else if(end<direction)
			{
				left();
			}
			break;
		}
	}
	return ;
}
int follow_line()
{
	check=0;
	for(char i=0;i<7;i++)
	{
		if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
		check|=(1<<i);
	}
	PORTB=check;//Displaying the output of the sensors on PORTB
	check=(check<<3);
	check=(check>>3);
	switch(check)//switch case used for different sensors' outputs and accordingly line follower code is made
	{
		case 0b11111:
		case 0b00000:
		case 0b11011:
		forward;
		break;
		case 0b10111:
		case 0b10011:
		case 0b10000:
		case 0b10100:
		LEFT;
		break;
		case 0b00111:
		case 0b01111:
		case 0b01100:
		sleft;
		break;
		case 0b11101:
		case 0b11001:
		case 0b00001:
		case 0b00101:
		RIGHT;
		break;
		case 0b11100:
		case 0b11110:
		case 0b00110:
		sright;
		break;
		default:
		forward;
	}
	return 0;
}
void travel_node_to_node()
{
	while(1)
	{
		follow_line();
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		if(check==0)
		break;
	}
	while(1)
	{
		follow_line();
		if(checkbit(PINA,5)==0 || checkbit(PINA,6)==0)
		{
			stall;
			PORTB=0b00000011;
			_delay_ms(1000);
			break;
		}		
		
	}
	return;
}
/*void get_first_node()
{
	while(1)
	{
		follow_line();
		if(checkbit(PINA,1)>0 && checkbit(PINA,2)>0)
		break;
	}
	return;
}*/
void travelcoordinate(char x1,char y1,char x2,char y2)
{
	char dx=x2-x1;
	char dy=y2-y1;
	if(dx>0)
	changedirection(1);
	else if(dx<0)
	changedirection(3);
	while(dx!=0)
	{
		follow_line();
		if(checkbit(PINA,5)==0 || checkbit(PINA,6)==0)
		{
			if(direction==1)
			{
				travel_node_to_node();
				X++;
				dx--;
			}
			else
			{
				travel_node_to_node();
				X--;
				dx++;
			}
		}   
     }
	if(dy>0)
	changedirection(0);
	else if(dy<0)
	changedirection(2);
	while(dy!=0)
	{
		follow_line();
		if(checkbit(PINA,5)==0 || checkbit(PINA,6)==0)
		{
			if(direction==0)
			{
				travel_node_to_node();
				Y++;
				dy--;
			}
			else
			{
				travel_node_to_node();
				Y--;
				dy++;
			}
		}
	}
	return;
}
int print_direction()
{
	
	PORTB=0;
	char dr=direction;
	PORTB=direction;
	_delay_ms(1000);
	PORTB=0;
}
int main(void)
{
	DDRA=0x00;//Setting the PORTA to input so that they can read the values of the sensors
	DDRB=0xff;//Setting the PORTB to output so that LEDs can used for debugging
	DDRC=0xff;//Setting the PORTC to output so that it can be used for motor-driver
	DDRD=0xff;//Setting the PORTD to output so that it can be used for PWM going to the enable of the motor-driver
	PORTA=0xff;//Initialize the pull-up resistors
	TCCR2=0b01101101;
	OCR2=120;
	//char check=0;//temp variable for the storage of the sensor values
		/*check=0;
		for(char i=0;i<4;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}*/
		check=0;
		for(char i=0;i<7;i++)
		{
			if(checkbit(PINA,i)>0)//Checking the output of the comparators on PINA
			check|=(1<<i);
		}
		PORTB=check;//Displaying the output of the sensors on PORTB
		check=(check<<3);
		check=(check>>3);
		travel_node_to_node();
		//travelcoordinate(1,1,2,2);
		//travelcoordinate(2,2,1,1);
		changedirection(3);
		print_direction();
		changedirection(1);
		print_direction();
		//TODO:: Please write your application code
}
