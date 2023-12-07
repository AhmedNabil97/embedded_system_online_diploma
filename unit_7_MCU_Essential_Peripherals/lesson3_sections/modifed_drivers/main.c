/*
 * GccApplication6.c
 *
 * Created: 26/11/2023 08:47:28 م
 * Author : lenovo
 */

#include "GPIO.h"
#include "lcd.h"
#include "keypad.h"

void clock_init(void)
{
	GPIOA_CLK_EN() ;    //Enable clock for GPIOA
	GPIOB_CLK_EN() ;  //Enable clock for GPIOB

}

int main(void)

{
	clock_init();
	lcd_init();
	_delay_ms(10);
	lcd_display_sentence("welcome to Nabil   LCD");
	_delay_ms(50);
	lcd_send_command(lcd_clear);
	keypad_init();
	_delay_ms(10);

	while(1)
	{
		unsigned char button = keypad_send_char();
		if(button == 'o')
		{
			lcd_send_command(lcd_clear);
			continue;
		}
		lcd_display_char(button);
		_delay_ms(250);
	}
}



