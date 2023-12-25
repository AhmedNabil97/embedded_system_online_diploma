/*
 * spi.c
 *
 * Created: 24/12/2023 07:26:23 ص
 *  Author: Ahmed
 */ 

#include "spi.h"

void MCAL_SPI_Master_Init(void)
{

//select master mode
SPI_SPCR |= (1<<4);

//configure pins directions
DDRB |= (1<<MOSI) | (1<<SCLK) | (1<<SS);
DDRB &= ~(1<<MISO);


//set clock rate Fck/16
SPI_SPCR |= (1<<SPR0);


//SPI Enable
SPI_SPCR |= (1<<6);


}
void MCAL_SPI_slave_Init(void)
{

	//select slave mode
	SPI_SPCR &= ~(1<<4);

	//configure pins directions
	DDRB |= (1<<MISO);
	DDRB &= ~ ( (1<<MOSI) | (1<<SS) | (1<<SCLK) );
	
	
	//SPI Enable
	SPI_SPCR |= (1<<6);


}
unsigned char MCAL_SPI_transmit_receive(unsigned char data_send)

{
		
	SPI_SPDR = data_send;
	while( !(SPI_SPSR & (1<<SPIF)) );
	return SPI_SPDR;
	
}
