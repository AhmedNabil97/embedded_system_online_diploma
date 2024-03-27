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


int ipsr_value = 0;

void switch_to_user_access(void)
{
	__asm("MRS R2 , CONTROL");
	__asm("ORR R2 , R2 , #0x01");
	__asm("MSR CONTROL , R2");

	}
void switch_to_previledged_access(void)
{
	__asm("MRS R2 , CONTROL");
	__asm("LSR R2 , R2 , #0x01");
	__asm("LSL R2 , R2 , #0x01");
	__asm("MSR CONTROL , R2");

	}

void my_handler(void)
{

__asm("MRS %0, IPSR"
		:"=r" (ipsr_value)  );

switch_to_previledged_access();


}


int val1 = 5 ;
int val2 = 7 ;
int val3 = 0 ;
int control_value = 0;

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
    //add val1 + val2  ---> val3
    __asm("MRS %0, CONTROL"
    		:"=r" (control_value)  );

    switch_to_user_access();


	while(1)
	{
	}
}



