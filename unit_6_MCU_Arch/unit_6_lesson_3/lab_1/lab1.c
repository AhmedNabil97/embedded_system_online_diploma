/**
 ******************************************************************************
 * @file           : Lab1.c
 * @author         : Eng. Ahmed Nabil
 * @brief          : toggle a bit and enable GPIOA clock
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

int main(void)
{
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


