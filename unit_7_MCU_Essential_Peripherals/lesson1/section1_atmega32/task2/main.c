#define PORTA *((volatile unsigned char *)(0x3B))
#define DDRA *((volatile unsigned char *)(0x3A))
#define PORTC *((volatile unsigned char *)(0x35))
#define DDRC *((volatile unsigned char *)(0x34))
#define PINC *((volatile unsigned char *)(0x33))

#define F_CPU 8000000UL
#include <util/delay.h>
#include "utils.h"
int main(void)
{
	DDRA = 0b11111111;                 //output mode for PORTA
	clear_bit(DDRC,0);                 //input mode for PINC0
	set_bit(PORTC,0);                  //activate pull up resistor
	int counter = 0;
	while (1)
	{
		if(!read_bit(PINC,0))
		{
			if(counter == 8)
			counter = 0;
		   toggle_bit(PORTA,counter);
		   counter++;
		   while(!read_bit(PINC,0));
		}

	}
}
