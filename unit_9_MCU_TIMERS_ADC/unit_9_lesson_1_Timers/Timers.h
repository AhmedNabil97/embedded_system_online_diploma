/*
 * Timers.h
 *
 * Created: 08/01/2024 11:54:12 م
 *  Author: lenovo
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

//-----------------------------------------------------------------------Includes-----------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utils.h"
 
//-----------------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------configuration_structure-----------------------------------------------------------------

typedef struct  
{
   unsigned char Timer_mode;								    //this parameter should be set based on @ref TIMER_MODE_define                     
   unsigned char Timer_clk;									    //this parameter should be set based on @ref TIMER_Clk_define
   unsigned char Timer_compare_value;						    //this parameter should be set based on user requirements
   unsigned char Timer_interrupt_Status;						//this parameter should be set based on @ref TIMER_INTERRUPT_STATUS_define
   void (*Timer_CM_callbk)(void);                               //this parameter should be equivalent to user ISR in case of compare match
   void (*Timer_OVF_callbk)(void);								//this parameter should be equivalent to user ISR in case of Timer overflow					
}Timer_config_t;

//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------reference_Macros-----------------------------------------------------------------

//@ref TIMER_MODE_define
	
#define Timer_Mode_Normal									0
#define Timer_Mode_CTC										1


//@ref TIMER_Clk_define

#define Timer_CLK_STOP										0
#define Timer_CLK_NO_PS										1
#define Timer_CLK_PS8										2
#define Timer_CLK_PS64										3
#define Timer_CLK_PS256										4
#define Timer_CLK_PS1024									5
#define Timer_CLK_EXT_FALLING								6		
#define Timer_CLK_EXT_RISING								7		


//@ref TIMER_INTERRUPT_STATUS_define

#define Timer_Interrupt_Disable								0
#define Timer_Interrupt_OVF_Enable							1
#define Timer_Interrupt_CM_Enable							2
#define Timer_Interrupt_OVF_CM_Enable						3

//-----------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------APIS-----------------------------------------------------------------

void MCAL_Timer0_Init(Timer_config_t*);
void MCAL_Timer0_stop(void);
void MCAL_Timer0_Restart(void);
void MCAL_Set_compare_value(unsigned char);
void MCAL_Set_Counter_value(unsigned char);
unsigned char MCAL_Get_compare_value(void);
unsigned char MCAL_Get_Counter_value(void);
unsigned char MCAL_Get_OverFLows_number(void);
















#endif /* TIMERS_H_ */