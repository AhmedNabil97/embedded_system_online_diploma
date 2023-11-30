/*
 * GccApplication6.c
 *
 * Created: 26/11/2023 08:47:28 م
 * Author : lenovo
 */ 

#define F_CPU 8000000UL
#include "lcd.h"
#include "keypad.h"
#include "calculator.h"

#include <util/delay.h>

int main(void) {
	lcd_init();
	_delay_ms(10);
	lcd_display_sentence("welcome to Nabil   calculator");
	_delay_ms(1500);
	lcd_send_command(lcd_clear);
	keypad_init();
	_delay_ms(10);
	calc_init();
	int i;	
	while(1)
	{
		unsigned char button = keypad_send_char();
		if(button == 'o')
		{
			calc_init();
		    continue;
		}
		lcd_display_char(button);
		_delay_ms(250);
		calc_assign_equation(button);
}
}



