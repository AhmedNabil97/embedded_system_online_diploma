/*
 * Timers.c
 *
 * Created: 08/01/2024 11:54:29 م
 *  Author: Ahmed
 */ 


#include "Timers.h"

//-----------------------------------------------------------Global_Variables------------------------------------------------------------------

unsigned char overflows_num;
Timer_config_t configurations_buffer;

//---------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------APIS------------------------------------------------------------------------------

void MCAL_Timer0_Init(Timer_config_t*x)
{
	
	configurations_buffer = *x;
    //set timer_mode
	switch (x->Timer_mode)
	{
	case Timer_Mode_Normal : 
	Clear_bit(TCCR0,WGM00);
	Clear_bit(TCCR0,WGM01);
	break;
	case Timer_Mode_CTC : 
	Set_bit(TCCR0,WGM01);
	Clear_bit(TCCR0,WGM00);
    break;
	default : 
	break;
	}
	
	
	//set compare value 
	OCR0 = x->Timer_compare_value;
	
	//set interrupt status
	if(x->Timer_interrupt_Status)
	{
	  Set_bit(S_Reg,7);
	  TIMSK &= ~(0b11);
	  TIMSK |= x->Timer_interrupt_Status;	
	}
	
	
	//set Clk
	TCCR0 &= ~(0b111);
	TCCR0 |= x->Timer_clk;
	
}
void MCAL_Timer0_stop(void)
{
     	TCCR0 &= ~(0b111);
 
}
void MCAL_Timer0_Restart(void)
{
		TCCR0 &= ~(0b111);
    	TCCR0 |= configurations_buffer.Timer_clk;

}

void MCAL_Set_compare_value(unsigned char Cmp_value)
{
   OCR0 = Cmp_value;
}
void MCAL_Set_Counter_value(unsigned char counter_value)
{
   TCNT0 = counter_value;
}
unsigned char MCAL_Get_compare_value(void)
{
	return OCR0;
}
unsigned char MCAL_Get_Counter_value(void)
{
return TCNT0;
}
unsigned char MCAL_Get_OverFLows_number(void)
{
	return overflows_num;
}

//---------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------ISR------------------------------------------------------------------------------


ISR(TIMER0_COMP_vect)
{
 configurations_buffer.Timer_CM_callbk();
}
ISR(TIMER0_OVF_vect)
{
	overflows_num ++;
	configurations_buffer.Timer_OVF_callbk();
}