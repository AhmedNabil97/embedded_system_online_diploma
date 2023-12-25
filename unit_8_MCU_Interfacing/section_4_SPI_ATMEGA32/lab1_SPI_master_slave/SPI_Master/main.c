/*
 * Spi_ATmega32.c
 *
 * Created: 24/12/2023 07:25:44 ص
 * Author : lenovo
 */ 

#include "spi.h"

int main(void)
{
	DDRA = 0xFF;
	MCAL_SPI_Master_Init();
     int data ;
	while(1)
	{
				for (data = 9; data>-1; data--)
				{
					PORTA = MCAL_SPI_transmit_receive(data) & 0x0F;
					_delay_ms(500);
				}

	
     }

}