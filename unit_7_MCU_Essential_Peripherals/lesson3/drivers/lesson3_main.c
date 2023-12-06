/**
 ****************************************************************************
 * @file           : Lab1.c
 * @author         : Eng. Ahmed Nabil
 * @brief          : toggle leds according to GPIOA inputs
 ****************************************************************************
 */



#include "stm32f103x6.h"
#include "GPIO.h"


void clock_init(void)
{
	GPIOA_CLK_EN() ;    //Enable clock for GPIOA
	GPIOB_CLK_EN() ;  //Enable clock for GPIOB

}

void gpio_init(void)
{
	GPIO_CONFIG_t PA1;
	GPIO_CONFIG_t PA13;
	GPIO_CONFIG_t PB1;
	GPIO_CONFIG_t PB13;

	//A1 & A13 should be set to floating input
	PA1.Pin_Number = GPIO_pin1;
	PA1.Pin_Mode = GPIO_MODE_Floating_input;

	PA13.Pin_Number = GPIO_pin13;
	PA13.Pin_Mode = GPIO_MODE_Floating_input;


	MCAL_GPIO_Init(GPIOA,&PA1);                  //A1 -> floating input
	MCAL_GPIO_Init(GPIOA,&PA13);                 //A13 ->floating input

	//B1 & B13 should be set to pull/push output
	PB1.Pin_Number = GPIO_pin1;
	PB1.Pin_Mode = GPIO_MODE_General_purpose_output_push_pull;
	PB1.Output_Pin_Speed = medium_speed_10Mhz;

	PB13.Pin_Number = GPIO_pin13;
	PB13.Pin_Mode = GPIO_MODE_General_purpose_output_push_pull;
	PB13.Output_Pin_Speed = medium_speed_10Mhz;

	MCAL_GPIO_Init(GPIOB,&PB1);                  //	B1 -> output-push/pull
	MCAL_GPIO_Init(GPIOB,&PB13);                 //B13 ->  output-push/pull


}

int main(void)
{

	clock_init();
	gpio_init();
	MCAL_GPIO_Write_Pin(GPIOB,GPIO_pin1,1);
	MCAL_GPIO_Write_Pin(GPIOB,GPIO_pin13,1);

	while(1)
	{
		if( MCAL_GPIO_Read_Pin(GPIOA,GPIO_pin1) == 0 )
		{
			MCAL_GPIO_Toggle_Pin(GPIOB,GPIO_pin1);
			while( MCAL_GPIO_Read_Pin(GPIOA,GPIO_pin1) == 0);            //single press
		}
		if ( MCAL_GPIO_Read_Pin(GPIOA,GPIO_pin13) == 1 )
		{
			MCAL_GPIO_Toggle_Pin(GPIOB,GPIO_pin13);                     //multi-press

		}

		char i;
		for(i=0; i<200; i++);
	}

}
