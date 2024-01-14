/*
 * unit9_lesson1_Timer.c
 *
 * Created: 08/01/2024 07:37:42 م
 * Author : Ahmed
 */ 

#include "Timers.h"

void Timer0_CMP_VAL_ISR(void)
{
PORTA = ~PORTA;
}
int main(void)
{
	
	DDRA = 0xFF;
	Timer_config_t test;
	test.Timer_mode = Timer_Mode_CTC;
	test.Timer_compare_value = 0x0F;
	test.Timer_clk = Timer_CLK_PS8;
	test.Timer_interrupt_Status = Timer_Interrupt_CM_Enable;
	test.Timer_CM_callbk = Timer0_CMP_VAL_ISR;
	
	MCAL_Timer0_Init(& test);
    /* Replace with your application code */
    while (1) 
    {
    }
}

