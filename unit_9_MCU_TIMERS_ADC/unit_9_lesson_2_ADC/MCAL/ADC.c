/*
 * ADC.c
 *
 * Created: 11/01/2024 02:54:31 م
 *  Author: Ahmed
 */ 


#include "ADC.h"

//-----------------------------------------------------------------------Global_variables-----------------------------------------------------------------

void(*ADC_ISR)(void);
unsigned int V_delta = V_refernce;
unsigned long long Delta_value;
unsigned long long val ;
unsigned char diff;

//-------------------------------------------------------------------------------------------------------------------------------------------

unsigned long long power(int x, unsigned char y)
{
	unsigned long long i , z;
	z = x;
	for(i=1; i<y; i++)
	{
		z *= x;
	}
	return z;
}



void display_result(unsigned long long x)
{
	if(x==0)
	{
	lcd_display_char('0');
	_delay_ms(50);
	return;
	}
	unsigned long long temp;
	unsigned char result_numbers,i;
	result_numbers = 0;
	temp = x ;
	while(temp/10)
	{
		result_numbers++;
		temp/=10;
	}
	temp = x;
	val = 10000000000;
	if(! (x/val) )
	{
	lcd_display_sentence("0.");
	val /=10;
	for(; !(x/val); )
	{
	lcd_display_char('0');
	val /= 10;
	}
	}
	else if((x % 10000000000 == 0))
	{
	x /= 10000000000;
	temp = x;
    lcd_display_char( ( (unsigned char)temp + 48) );
   _delay_ms(100);
   return ;
	}
  else
  {
	  	for(i=0; i<=1; i++)
	  	{
			  //if(i==1)
			  //lcd_display_char('.');
		  	diff = result_numbers - i;
		  	if(temp > 10 )
		  	temp = temp / power(10,diff);
		  	lcd_display_char( ( (unsigned char)temp + 48) );
		  	_delay_ms(5);  // Adjust this delay as needed
		  	temp = x % power(10,diff);
	  	}
	  	_delay_ms(100);
        return;
  }
	for(i=0; i<=1; i++)
	{
		diff = result_numbers - i;
		if(temp > 10 )
		temp /= power(10,diff);
		lcd_display_char( ( (unsigned char)temp + 48) );
		_delay_ms(5);  // Adjust this delay as needed
		temp = (unsigned long long) (x % power(10,diff));
	}
	_delay_ms(100);
}







//-----------------------------------------------------------------------APIS-----------------------------------------------------------------

void MCAL_ADC_Init(ADC_config_t*y)
{
	//set reference voltaege source
	
	ADMUX &= ~(0b11<<6);
	ADMUX |= (y->ADC_Vref_src << 6);
	
	// Enable ADC channel 
	
	// set selected channel to be input
	Clear_bit(DDRA,y->ADC_channel);
	
	ADMUX |= y->ADC_channel;
	
	// set clock pre scaler 
	
	ADCSRA &= ~(0b111);
	ADCSRA |= y->ADC_clk;
	
	// modify interrupt status 
	
	if(y->ADC_interrupt_status)
	{
	
	ADC_ISR = y->ADC_IRQ_callbk;
	ADCSRA |= y->ADC_interrupt_status;
	Set_bit(S_Reg,7);
	
	}
	
	// Enable ADC
	Set_bit(ADCSRA,ADEN);
	Delta_value = (V_delta * 10000000000) / 1024; 
	
}
unsigned short MCAL_ADC_Read_value(void)
{
	//set start conversion bit
    Set_bit(ADCSRA,ADSC);	
	if(ADC_ISR)
	{
		//if interrupt Enable
		return ADC;
	}
	else
	{
	   //polling mechanism till conversion Ended
	   while(! Read_bit(ADCSRA,ADIF))
	    //clear ADIF by writing 1 for the next conversion
	  //  Set_bit(ADCSRA,ADIF);
	  	_delay_us(10);
	    Set_bit(ADCSRA,ADIF);
	   return ADC;
	   
	}
}
