#define PORTA *((volatile unsigned char *)(0x3B))
#define DDRA *((volatile unsigned char *)(0x3A))
#define F_CPU 8000000UL
#include <util/delay.h>
#include "utils.h"
int main(void)
{
	DDRA = 0b11111111;
	int i;
	while (1)
	{
		for(i=0; i<8; i++)
		{
			set_bit(PORTA,i);
			_delay_ms(150);

		}
		for(i=7; i>=0; i--)
		{
			clear_bit(PORTA,i);
			_delay_ms(150);

		}

	}
}
