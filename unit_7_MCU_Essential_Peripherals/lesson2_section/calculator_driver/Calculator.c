/*
 * Calculator.c
 *
 * Created: 29/11/2023 03:09:42 م
 *  Author: lenovo
 */ 
#include "lcd.h"
#include "keypad.h"
#include <stdlib.h>
#define F_CPU 8000000UL
#include <util/delay.h>
extern enum button_type flag;
extern char button_counters;
char operation_recived =0;
char last_press = 0;
char opeand1_counter = 0;
char opeand2_counter = 0;
unsigned char eq[12]={0};
int operand1 =0;
int operand2=0;
int result=0;

int power(int x, unsigned char y)
{
    int i , z;
	z = x;
	for(i=1; i<y; i++)
	{
		z *= x;
	}
	return z;
}
void calc_init(void)
{
    char i;
    button_counters = 0;
    for(i=0; i<12; i++)
    {
        eq[i] = 0;
    }
    operation_recived = 0;
    last_press  = 0;
    opeand1_counter = 0;
    opeand2_counter = 0;
    operand1 = 0;
    operand2 = 0;
    result = 0;    
    lcd_send_command(lcd_clear);
    _delay_ms(5);  // Adjust this delay as needed
}

void calc_assign_equation(unsigned char x)
{
    while(button_counters)
    {
        if (button_counters == 1 && (x == '=' || x == '*' || x == '/'))
        {
            lcd_send_command(lcd_begin_at_seconed_row);
            lcd_display_sentence("Error Re-try");
            _delay_ms(100);  // Adjust this delay as needed
            lcd_send_command(lcd_clear);
            return;
        }
        if(flag == number)
        {
            x -= 48;
            eq[last_press] = x;
            switch (operation_recived)
            {
                case 0 :
                    opeand1_counter ++;
                    break;
                case 1:
                    opeand2_counter ++;
                    break;
            }
            last_press ++;
            return;
        }
        else if(flag == operation )
        {
			if(button_counters > 1)
            operation_recived = 1;
            eq[last_press] = x;
            last_press ++;
            return;
        }
        else if( flag == equal)
        {
            last_press++;
			lcd_send_command(lcd_begin_at_seconed_row);
            calc_evaluate_opearand(eq);
			return;
        }
        
    }
}

void calc_evaluate_opearand(unsigned char*eq)
{
    unsigned char diff,i,j,n,n2,n3;
    for(i=1; i<=opeand1_counter; i++ )
    {
	   if(eq[0] == '-')
	       n = i;
		   else
		   n = i-1;
	   diff = opeand1_counter - i ;
		if(i == opeand1_counter)
		{
		operand1 += eq[n];
		break;
		}
		operand1 += (eq[n] * power(10,diff));
    }
	n2 = opeand1_counter+1;
	n3 = opeand2_counter+opeand1_counter;
	if(eq[0] == '-')
	{
	n2 ++;
	n3 ++;
	}
	if(eq[n2] == '-')
	{
		n2++;
		n3++;
	}
    for(i=n2; i<=n3; i++ )
    {
		
		 if( opeand2_counter==1 | i== n3)
		 {
			 operand2 += eq[i];
			 break;
		 }
        operand2 += ( eq[i]* power(10,(n3-i)));
       
    }
    calc_evaluate_result(operand1,operand2);
	return;
}
void calc_evaluate_result( int x, int y)
{
	char index = opeand1_counter;
    if(eq[0] == '-')
	{
     operand1 *= -1;
	 index ++;
	}
	if(eq[index+1]=='-')
	{
		operand2 *= -1;
	}
    switch (eq[index])
    {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
    }
    calc_send_result(result);    
	return;
}
void calc_send_result(int x)
{
	int temp;
	unsigned char result_numbers,i,diff;
	result_numbers = 0,i;
	temp = abs(x);
	if(x<0)
	{
		lcd_display_char('-');
		_delay_ms(5);
	}
	while(temp/10)
	{
		result_numbers++;
		temp/=10;
	}
	
	temp = abs(x);
	for(i=0; i<=result_numbers; i++)
	{
		diff = result_numbers - i;
		if(temp > 10 )
		temp = temp / power(10,diff);
		lcd_display_char( ( (unsigned char)temp + 48) );
		_delay_ms(5);  // Adjust this delay as needed
		temp = abs(x) % power(10,diff);
	}
	_delay_ms(100);
}
