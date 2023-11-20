/*
 * GccApplication1.c
 *
 * Created: 15/11/2023 04:01:41 
 * Author : Eng Ahmed Nabil
   description : lab3 is to enable 3 interrupts in atmega32 in 3 different modes & simulate the ISRS as outputs on 3 led connected to PORTD
 */ 


//important lines from technical reference manual of atmega32

	/* 
	
	-1- The External Interrupts : 0,1,2 is activated by the external pin INT if the " SREG I-bit " and the corresponding
	interrupt mask in the " GICR " are set.
	
	-2- register responsible for activation of int0,int1 MCUCR but for int2 MCUCSR
	  
	 -3- When an edge or logic change on the INT0,1,2 pin triggers an interrupt request, INTF1 becomes set
	  (one). If the I-bit in SREG and the INT bit in GICR are set (one), the MCU will jump to the corresponding
	  Interrupt Vector. The flag is cleared when the interrupt routine is executed.  --> so no need to clear interrupt statue cause it is cleared automatically 
	  
	  
	    */
#define F_CPU 16000000UL     
#include <avr/interrupt.h>
#include <util/delay.h>

#define INT_SREG *((volatile unsigned char*)(0x5F))
#define INT_GICR *((volatile unsigned char*)(0x5B))
#define INT_MCUCR *((volatile unsigned char*)(0x55))
#define INT_MCUCSR *((volatile unsigned char*)(0x54))
#define IO_DDRD *((volatile unsigned char*)(0x31))
#define IO_PORTD *((volatile unsigned char*)(0x32))
int i;

int main(void)
{
	INT_SREG |= (1<<7);
	INT_GICR |= (0b111<<5);
	IO_DDRD |= (0b111<<5);
	INT_MCUCR = 0b00001101;
	INT_MCUCSR &= ~(1<<6);
	while(1)
	{
		IO_PORTD = 0 ;

	}
	
}

ISR(INT0_vect)
{
	IO_PORTD |= (1<<7);
    _delay_ms(100);
}
ISR(INT1_vect)
{
	IO_PORTD |= (1<<6);
    _delay_ms(100);
}
ISR(INT2_vect)
{
	IO_PORTD |= (1<<5);
    _delay_ms(100);

}

