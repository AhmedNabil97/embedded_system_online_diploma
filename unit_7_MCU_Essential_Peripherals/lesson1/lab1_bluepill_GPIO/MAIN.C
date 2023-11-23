/**
 ******************************************************************************
 * @file           : Lab1.c
 * @author         : Eng. Ahmed Nabil
 * @brief          : toggle leds according to GPIOA inputs
 ******************************************************************************
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// GPIOA
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
// GPIOB
#define GPIOB_BASE 0x40010C00
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)


// reset & clock control registers base address
#define RCC 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC + 0x18)



void clock_init(void)
{
	RCC_APB2ENR |= (1<<2) ;    //Enable clock for GPIOA
	RCC_APB2ENR |= (1<<3) ;    //Enable clock for GPIOB

}

void gpio_init(void)
{
	//A1 & A13 should be set to floating input
	GPIOA_CRL |= (0b0100 << 4 );                 //A1 -> floating input
	GPIOA_CRH |= (0b0100 << 20 );               //A13 ->floating input
	//B1 & B13 should be set to pull/push output
	GPIOB_CRL |= (0b0010 << 4 );                 //A1 -> floating input
	GPIOB_CRH |= (0b0010 << 20 );               //A13 ->floating input
}

int main(void)
{
	clock_init();
	gpio_init();
	GPIOB_ODR |= (1<<1);
	GPIOB_ODR |= (1<<13);

	while(1)
	{
		if( ( (GPIOA_IDR & (1<<1) ) >> 1) == 0 )
		{
			GPIOB_ODR ^= (1<<1);
			while(( (GPIOA_IDR & (1<<1) ) >> 1) == 0);            //single press
		}
		if ( ( (GPIOA_IDR & (1<<13) ) >> 13) == 1 )
		{
			GPIOB_ODR ^= (1<<13) ;                               //multi-press

		}

		int i;
		for(i=0; i<255; i++);
	}

}



