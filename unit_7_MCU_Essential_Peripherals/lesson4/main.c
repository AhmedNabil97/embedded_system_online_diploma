/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "GPIO.h"
#include "lcd.h"
#include "EXTI.h"

void clock_init(void)
{
	GPIOA_CLK_EN() ;       //Enable clock for GPIOA
	GPIOB_CLK_EN() ;       //Enable clock for GPIOB
    AFIO_CLK_EN()  ;       //Enable clock for AFIO

}

void my_handler(void)
{

	lcd_send_command(lcd_clear);
	lcd_display_sentence("IRQ EXTI 9 HAS OCCURED _|- ");
	_delay_ms(50);

}


int main(void)

{
	clock_init();
	lcd_init();
	_delay_ms(10);
	lcd_display_sentence("welcome to Nabil     LCD");
	_delay_ms(50);
	lcd_send_command(lcd_clear);
    EXTI_config_t EXIR9 ;
    EXIR9.port = GPIOB;
    EXIR9.pin_and_line_number = P9 ;
    EXIR9.interrupt_mode = rising_edge;
    EXIR9.isr_p = my_handler;
    MCAL_EXTI_Init(&EXIR9);
    MCAL_EXTI_Enable(EXTI9);
	while(1)
	{
         _delay_ms(50);
     	lcd_send_command(lcd_clear);
	}
}



