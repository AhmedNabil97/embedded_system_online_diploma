/**
 ******************************************************************************
 * @file           : Lab2.c
 * @author         : Eng. Ahmed Nabil
 * @brief          : toggle a bit and Adjust the following values to buses clocks
 * SYSCLK ---> 8MHZ
 * AHB    ---> 8MHZ
 * APB1   ---> 4MHZ
 * APB2   ---> 2MHZ
 ******************************************************************************
 */

typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
// reset & clock control registers base address
#define RCC 0x40021000
// register that is responsible for enable clock for APB2 Peripherals including GPIOA
#define RCC_APB2ENR *(volatile uint32_t *)(RCC + 0x18)
// register that is responsible for clocks configuration
#define RCC_CFGR (volatile uint32_t *)(RCC + 0x04)
typedef struct
{
	vuint32_t SW : 2 ;
	vuint32_t SWS : 2 ;
	vuint32_t HPRE : 4 ;
	vuint32_t PPRE1 : 3 ;
	vuint32_t PPRE2 : 3 ;
	vuint32_t ADCPRE : 2 ;
	vuint32_t PLL_SRC : 1;
	vuint32_t PLL_XTPRE : 1;
	vuint32_t PLL_MULL : 4;
	vuint32_t USB_PRE : 1;
	vuint32_t         : 1;
	vuint32_t MCO : 3 ;

	}RCC_CFGR_bits;



int main(void)
{
	// clocks configuration to set required Frequencies
	RCC_CFGR_bits* clock_config = RCC_CFGR ;
	clock_config->SW = 0;
	clock_config->PPRE1 = 4;
	clock_config->PPRE2 = 5;

	// Enable clock for GPIOA
	RCC_APB2ENR |= 1<<2;
	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	while(1)
	{
		GPIOA_ODR |= 1<<13 ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
		GPIOA_ODR &= ~(1<<13) ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
	}

}


