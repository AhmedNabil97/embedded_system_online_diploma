/*
 * ADC.h
 *
 * Created: 11/01/2024 02:54:19 م
 *  Author: lenovo
 */ 


#ifndef ADC_H_
#define ADC_H_

//-----------------------------------------------------------------------Includes-----------------------------------------------------------------

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "utils.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

#define V_refernce					5                            //if External voltage is used the value should be modified to this macro

//-----------------------------------------------------------------------configuration_structure-----------------------------------------------------------------

typedef struct
{
	unsigned char ADC_channel;								    //this parameter should be set based on @ref ADC_channel_define
	unsigned char ADC_clk;									    //this parameter should be set based on @ref ADC_Clk_define
	unsigned char ADC_Vref_src;								    //this parameter should be set based on @ref ADC_Vref_src
	unsigned char ADC_operation_Mode;						    //this parameter should be set based on @ref ADC_operation_Mode
	unsigned char ADC_auto_trigger_source;						//this parameter should be set based on @ref ADC_auto_trigger_source_define
	unsigned char ADC_interrupt_status;							//this parameter should be set based on @ref ADC_INTERRUPT_STATUS_define
	void (*ADC_IRQ_callbk)(void);                               //this parameter should be equivalent to user ISR in case of conversion complete
}ADC_config_t;

//-----------------------------------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------reference_Macros-----------------------------------------------------------------

//@ref ADC_channel_define

#define ADC_channel_A0										0
#define ADC_channel_A1										1
#define ADC_channel_A2										2
#define ADC_channel_A3										3
#define ADC_channel_A4										4
#define ADC_channel_A5										5
#define ADC_channel_A6										6
#define ADC_channel_A7										7
//to do other combinations of both differential and differential gain

//@ref ADC_Clk_define

#define ADC_CLK_PS2											1
#define ADC_CLK_PS4											2
#define ADC_CLK_PS8											3
#define ADC_CLK_PS16										4
#define ADC_CLK_PS32										5
#define ADC_CLK_PS64										6
#define ADC_CLK_PS128										7

//NOTE : ADC clock frequency value should be within the range [50 : 200]KHZ 

//@ref @ref ADC_Vref_src

#define ADC_Vref_AREF										0
#define ADC_Vref_AVCC										1
#define ADC_Vref_Internal_2_56_V							3


//@ref ADC_operation_Mode

#define ADC_operation_mode_single_conversion				0
#define ADC_operation_mode_Free_Running						1

//@ref ADC_auto_trigger_source_define
//to do

//@ref ADC_INTERRUPT_STATUS

#define ADC_Interrupt_Disable			0
#define ADC_Interrupt_Enable			1

//-----------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------APIS-----------------------------------------------------------------

void MCAL_ADC_Init(ADC_config_t*);
unsigned short MCAL_ADC_Read_value(void);
void display_result(unsigned long long x);












#endif /* ADC_H_ */