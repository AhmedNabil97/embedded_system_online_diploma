/*
 * stm32f103x6.h
 *
 *  Created on: Dec 4, 2023
 *      Author: lenovo
 */

#ifndef STM32F103X6_H_
#define STM32F103X6_H_

//Includes

#include <stdlib.h>
#include <stdint.h>

/*-------------------------------------------------------------------------------------------------------------*/
//                                 base addresses for memories

#define Flash_Memory_Base								0x08000000UL
#define System_Memory_Base								0x1FFFF000UL
#define Sram_Memory_Base								0x20000000UL
#define Peripherals_Base								0x40000000UL
#define Cortex_M3_Internal_Peripherals_Base				0x20000000UL

/*-------------------------------------------------------------------------------------------------------------*/
//                                 base addresses for AHB Peripherals
//1. RCC
#define RCC_BASE 									    0x40021000UL

/*-------------------------------------------------------------------------------------------------------------*/
//                                 base addresses for APB2 Peripherals
// 1. GPIO
//FOR Pacakge_LQFP48      --->       [ A,B FULY INCLUDED] --- C,D PARTIALLY INCLUDED --- E DOESNOT INCLUDED ]
#define GPIOA_BASE										0x40010800
#define GPIOB_BASE										0x40010C00
#define GPIOC_BASE										0x40011000
#define GPIOD_BASE										0x40011400
#define GPIOE_BASE										0x40011800
// 2. EXTI
#define EXTI_BASE										0x40010400
// 3. AFIO
#define AFIO_BASE										0x40010000

/*-------------------------------------------------------------------------------------------------------------*/
//                                    perphiral       registers
//1. GPIO
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;

}GPIO_t;

//2. RCC
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;

}RCC_t;

//3. EXTI
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_t;

//4.AFIO
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RESERVED;
	volatile uint32_t MAPR2;
}AFIO_t;

/*-------------------------------------------------------------------------------------------------------------*/
//                                    perphiral       instants

#define GPIOA										((GPIO_t*)GPIOA_BASE)
#define GPIOB										((GPIO_t*)GPIOB_BASE)
#define GPIOC										((GPIO_t*)GPIOC_BASE)
#define GPIOD										((GPIO_t*)GPIOD_BASE)
#define GPIOE										((GPIO_t*)GPIOE_BASE)
#define RCC									     	((RCC_t*)RCC_BASE)
#define EXTI										((EXTI_t*)EXTI_BASE)
#define AFIO										((AFIO_t*)AFIO_BASE)

/*-------------------------------------------------------------------------------------------------------------*/
//                                    CLOCK       ENABLE


#define GPIOA_CLK_EN()								(RCC->APB2ENR |= (1<<2))
#define GPIOB_CLK_EN()								(RCC->APB2ENR |= (1<<3))
#define GPIOC_CLK_EN()								(RCC->APB2ENR |= (1<<4))
#define GPIOD_CLK_EN()								(RCC->APB2ENR |= (1<<5))
#define GPIOE_CLK_EN()								(RCC->APB2ENR |= (1<<6))
#define AFIO_CLK_EN()								(RCC->APB2ENR |= (1<<0))


#endif /* STM32F103X6_H_ */
