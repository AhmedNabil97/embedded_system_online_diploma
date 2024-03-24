/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "GPIO.h"
#include "EXTI.h"

void clock_init(void)
{
	GPIOB_CLK_EN() ;       //Enable clock for GPIOB
    AFIO_CLK_EN()  ;       //Enable clock for AFIO

}

void my_handler(void)
{

int i = 0;
for(i=0; i<255; i++);

}


int main(void)

{
	clock_init();
    EXTI_config_t EXIR9 ;
    EXIR9.port = GPIOB;
    EXIR9.pin_and_line_number = P9 ;
    EXIR9.interrupt_mode = rising_edge;
    EXIR9.isr_p = my_handler;
    MCAL_EXTI_Init(&EXIR9);
    MCAL_EXTI_Enable(EXTI9);
	while(1)
	{
	}
}



