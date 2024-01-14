/*
 * unit_9_lesson_2_Atmega32_ADC.c
 *
 * Created: 11/01/2024 02:52:37 AM
 * Author : Ahmed
 * brief : This application is to sense temperature in °C using LM35 sensor interfacing with Atmega32 & display results on LCD and 
 trigger buzzer if temperature >= 37°C
 */ 

#include "LCD.h"
#include "ADC.h"

extern unsigned long long Delta_value;
int actual_temperature_value ;
int main(void)
{
	lcd_init();
	
	 ADC_config_t ADC1;
	 ADC1.ADC_channel = ADC_channel_A7;
	 ADC1.ADC_clk = ADC_CLK_PS64;
	 ADC1.ADC_Vref_src = ADC_Vref_AVCC;
	 ADC1.ADC_operation_Mode = ADC_operation_mode_single_conversion;
	 ADC1.ADC_interrupt_status = ADC_Interrupt_Disable;
	 MCAL_ADC_Init(& ADC1); 
	lcd_display_sentence("Temp value : ") ;
   short ADC_reading ;
   short old_read;
   
   
while(1)
{

ADC_reading = MCAL_ADC_Read_value();

//this condition set to calibrate the differences between the accuracy of temperature sensor & ADC
if(ADC_reading == old_read | ADC_reading == old_read+1 | ADC_reading == old_read-1)

{	
continue;
}
else
{
	
old_read = ADC_reading;	

//function to delete old readings
lcd_delete_space(1,12,6);

//calibration to get accurate values
if(ADC_reading)
ADC_reading++;

unsigned long long Actual_value= Delta_value * (ADC_reading);

//actual value will be displayed with * 100 to display real temperature not measured volt 
display_result(Actual_value*100);
lcd_display_char('C');

//Extract real value
actual_temperature_value = Actual_value / 100000000;

//trigger buzzer connected to PA0 if temperature >= 37°C
if(actual_temperature_value >= 37)
{
	
DDRA |= 1;
PORTA |= 1;
}
else
{
PORTA &= ~(1<<0);
}
}
}
}
