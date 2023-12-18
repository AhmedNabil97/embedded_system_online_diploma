/*
 * uart.c
 *
 * Created: 18/12/2023 12:21:20 
 *  Author: Ahmed
 */ 

#include "uart.h"

void MCAL_UART_Init(void)
{
   //Determine frame size 
   
   UCSRC |= (1<<7);								     //Select UCSRC REG
   UCSRC &= ~(1<<6);								 //Select Asynchronous mode
   UCSRC &= ~(0b11<<4);								 //No Parity Bits
   UCSRC &= ~(1<<3);								 //Select 1 Stop Bit
   UCSRC |= (0b11<<1);								 //Select 8-Bit Data Size
   UCSRB &= ~(1<<2);								 //Select 8-Bit Data Size
   UCSRC &= ~(1<<0);								 //No Clock Polarity For Asynchronous Mode

   //select normal speed & define baud rate
   
   UCSRA &= ~(1<<1);                                  //Normal Speed
   UBRRL = 51;                                        //set Baud Rate 9600 Bps With 8Mhz Clk Frequency For 0.2% Error
   
   //Enable Tx & Rx    
   
   UCSRB |= (0b11<<3);
   
}


void MCAL_UART_Transmit_Char(unsigned char data_out)
{
	
	while ( ! ( UCSRA & (1<<UDRE) ) ) ;
	UDR = data_out ;
	
}

unsigned char MCAL_UART_Receive_Char(void)

{
	
	if (  UCSRA & ( (1<<FE) || (1<<DOR) ) )    //if there is error return null
	   return '\0';
	  
	  while ( !( UCSRA & (1<<RXC) ) );
	   return UDR;
	   
	   return UDR ;
}

void MCAL_UART_Transmit_string(unsigned char* data_out)
{
     while (* data_out++)
	 {
	    MCAL_UART_Transmit_Char(*(data_out-1));
	 }
}