/**
 ******************************************************************************
 * @file           : Lab2.c
 * @author         : Eng. Ahmed Nabil
 * @brief          : Enable EXTI0 in stm32f103xxx
 ******************************************************************************
 */

typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// GPIO
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOx_CRL *(volatile uint32_t *)(GPIOA_BASE)


// reset & clock control registers base address
#define RCC 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC + 0x18)
#define RCC_CFGR (volatile uint32_t *)(RCC + 0x04)
#define RCC_CR *(volatile uint32_t *)(RCC)

//EXTI
#define EXTI_BASE 0x40010400
#define EXTI_IMR *(volatile uint32_t *)(EXTI_BASE + 0x00)                 //masking control
#define EXTI_RTSR *(volatile uint32_t *)(EXTI_BASE + 0x08)               //trigger Rising edge selection
#define EXTI_PR *(volatile uint32_t *)(EXTI_BASE + 0x14)                //set 1 to clear interrupt request

//NVIC
#define NVIC_ISER0 *(volatile uint32_t *)(0xE000E100)

void clock_init(void)
{
	RCC_APB2ENR |= (1<<2) ;    //Enable clock for GPIOA
	RCC_APB2ENR |= (1<<0) ;    //Enable clock for AFIO

	}

void gpio_init(void)
{
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	}

int main(void)
{
	clock_init();
	gpio_init();
	//Enable line 0 in External interrupt register
	EXTI_IMR |= (1<<0);
	//Triggering rising edge for line 0 in EXTI
	EXTI_RTSR |= (1<<0);
    // floating input reset
	GPIOx_CRL &= ~(0b11<<0);
	GPIOx_CRL |= (1<<2);
	GPIOx_CRL &= ~(1<<3);
	//Enable interrupt no.6 in NVIC
	NVIC_ISER0 |= (1<<6);

}

void EXTI0_IRQHandler(void)
{
	// function will called if External interrupt happen on line 0 that will be routing to pin 0 PORTA
	// Interrupt will be triggered as rising edge
	// handling is by toggling pin A 13
	GPIOA_ODR ^= 1<<13 ;
	// clear pending request for line 0
	EXTI_PR |= (1<<0);

	}


