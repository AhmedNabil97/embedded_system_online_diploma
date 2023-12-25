/*
 * spi.h
 *
 * Created: 24/12/2023 07:26:10 ص
 *  Author: Ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL

//SPI registers 

#define		SPI_SPCR				(*(volatile unsigned char*)0x2D)                           //control register
#define		SPI_SPSR				(*(volatile unsigned char*)0x2E)                           //status register 
#define		SPI_SPDR				(*(volatile unsigned char*)0x2F)                           //data register


//SPI control_register pins

#define		SPIE					7                                                          //interrupt Enable
#define		SPE						6                                                          //SPI Enable
#define		DORD					5                                                          //transmit direction LSB or MSB 
#define	    MSTR					4														   //master/slave select
#define		CPOL					3														   //clock polarity
#define		CPHA					2														   //control sampling -> rising edge or falling edge 
#define     SPR1					1                                                          //control Clock rate
#define     SPR0					0                                                          //control Clock rate

//SPI output pins

#define		SS						4                                                          //slave select
#define		MOSI					5                                                          //master output slave input
#define		MISO					6                                                          //slave input master output
#define		SCLK					7                                                         //clk



//SPI APIES

void MCAL_SPI_Master_Init(void);
void MCAL_SPI_slave_Init(void);
unsigned char MCAL_SPI_transmit_receive(unsigned char);

#endif /* SPI_H_ */