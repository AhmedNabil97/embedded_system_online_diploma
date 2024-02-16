/*
 * main.c
 *
 * Created: 13/12/2023 04:15:32 ص
 *  Author: Ahmed
 */ 

#include "avr/io.h"
#include "util/delay.h"
#include <avr/interrupt.h>
#include "timers.h"



#define SREG	(*(volatile unsigned char *)(0x5F))
unsigned char slots ;
typedef struct 
{
  unsigned char seg_control :4;
	}seven_seg;

#define port_pointer		((seven_seg*)(0x3B))
#define access_pointer		port_pointer->seg_control

void set_pins(void)
{
	
//set int0 & int1 pins as inputs;
DDRD &= ~(0b11<<2);

//set response pin d4 as output
DDRD |= (1<<4);

//set pir sensor pins as inputs 
DDRD &= ~(0b11<<5);

//Set timer pins
Set_timers_pins();

//set 1st nibble of portA as output to control 7-segment
DDRA = 0x0F;

}
int main()
{
slots = 3;
set_pins();
// adjust interrupt 0 & interrupt 1 to feel rising edge 
MCUCR |= (0b1111 << 0);

_delay_ms(1500);
// Enable global interrupt
SREG |= (1<<7);    
// activate External interrupt (0 & 1)   ---> PinD2 & PinD3 respectival;ly     
GICR |= (0b11<<6);


while(1)
{
	access_pointer = slots;
}

}

ISR(INT0_vect)

{
	//decrease number of available slots
	slots--;
	// open gate
	open_Entery_gate();
	//delay 30 sec
	_delay_ms(3000);
	//polling on pir1 sensor
	while(PIND & (1<<5));
	close_Entery_gate();
	//set response pin
	PORTD |= (1<<4);
	_delay_ms(20);
	PORTD &= ~(1<<4);

}

ISR(INT1_vect)
{
	//increase number of available slots
	slots++;
	// open gate
	open_Exit_gate();
	//delay 30 sec
	_delay_ms(3000);
	//polling on pir2 sensor
	while(PIND & (1<<6));
	close_Exit_gate();
	//set response pin
	PORTD |= (1<<4);
	_delay_ms(20);
	PORTD &= ~(1<<4);

}
