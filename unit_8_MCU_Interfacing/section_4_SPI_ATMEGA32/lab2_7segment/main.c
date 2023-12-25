/*
 * 7segments_SPI.c
 *
 * Created: 24/12/2023 12:46:47 م
 * Author : Ahmed
 */ 

#include "spi.h"

void Execute(unsigned char cmd , unsigned char data)
{
 
 //put SS to low to start packet
  PORTB &= ~(1<<SS);	
  
 //send command first
  SPI_SPDR = cmd;
  
  //wait till command transmit 
   while( !(SPI_SPSR & (1<<SPIF)) );
   
   //send data 
   SPI_SPDR = data;
   
    //wait till Data transmit
    while( !(SPI_SPSR & (1<<SPIF)) );
     

   //set SS to high to endpacket
   PORTB |= (1<<SS);

   
}


int main(void)
{
		
		MCAL_SPI_Master_Init();
		Execute(0x09 , 0xFF);  // Decode all display
		Execute(0x0A , 0xFF);  // Max intensity
		Execute(0x0B , 0xF7);  // Set scan limit
		Execute(0x0C , 0x01);  // Turn on display
		unsigned int i,y=0,z=0;
		while(1)
		{
     for(i=1; i<=8; i++)
 {
	 if (y > 9 )
	 {
		 if(i+z>7)
		 {
		 z=0;
		 break;
		 }
		 Execute(i+z,y/10);
		 Execute(i+z+1,y%10);
		 _delay_ms(500);
		 y++;
		 z++;
		 continue;
	 }
	Execute(i,y);
	_delay_ms(500);
	y++;
  }

}

}