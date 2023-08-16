/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
#include "stdio.h"
#include "stdint.h"

#define APB2ENR_BASE *(volatile uint32_t*)(0x40021000+0x18)
#define CRH_REG *(volatile uint32_t*)(0x40010800+0x04)
#define GPIOA_ODR_REG *(volatile uint32_t*)(0x40010800+0x0C)
typedef union
{
	uint32_t allports;
	struct
	{
		uint32_t :13;
		uint32_t p13 :1;
	}pin_no;

	}ODR_REG;


	volatile ODR_REG* od_pt = (volatile ODR_REG*)(0x40010800+0x0);

int main(void)
{
	int i;
	//SIT ABR BIT 2 = 1
	APB2ENR_BASE |= 1<<2;
	// SIT CRH BITS FROM 20:24 =2
	CRH_REG &= 0XFF0FFFFF;
	CRH_REG |= 1<<21;
	while(1)
	{
      od_pt->pin_no.p13=1;
      for(i=0; i<5000; i++);
      od_pt->pin_no.p13=0;
      for(i=0; i<5000; i++);


	}


}
