/*
 * UART.c
 *
 *  Created on: ١٩‏/١٢‏/٢٠٢٣
 *      Author: Ahemd
 */


#include "UART.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
		                                      // global variables & Auxiliary functions "

void (* arr_Irq_callback[3])(void);
uint32_t get_pclk1_freq(void);
uint32_t get_pclk2_freq(void);
uint32_t get_Hclk_freq(void);
uint32_t power_func(uint32_t x,uint32_t y);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//



/*==============================================================================================================================================================*
 * @Fn			-MCAL_UART_Init
 * @brief 		-initialize required UART instant with the required configuration
 * @param[in] 	-USART_t*x
 * @param[in] 	-UART_CONFIG_t*y
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/

void MCAL_UART_Init(USART_t*x,UART_CONFIG_t*y)

{
	//Enable UART
	x->USART_CR1 |= (1<<13);


	//assign required mode -> Tx or Rx or Both
	switch (y->Uart_Mode)
	{
	case UART_TX_ENABLE:
		x->USART_CR1 |= (1<<3);
		break;
	case UART_RX_ENABLE:
		x->USART_CR1 |= (1<<2);
		break;
	case UART_TX_RX_ENABLE:
		x->USART_CR1 |= (1<<3);
		x->USART_CR1 |= (1<<2);
		break;
	default :
		break;
	}

	//assign required data length -> 8bits or 9bits
	x->USART_CR1 &= ~(1<<12);
	x->USART_CR1 |= (y->Data_Length <<12);


	//assign required number of parity bits
	if(y->Parity_Bits == UART_PARITY_NONE)
		x->USART_CR1 &= ~(1<<10);
	else
	{
		x->USART_CR1 |= (1<<10);                                    //parity Enable
		x->USART_CR1 &= ~(1<<9);
		x->USART_CR1 |= (y->Parity_Bits <<9);
	}


	//assign number of stop bits
	x->USART_CR2 &= ~(0b11<<12);
	x->USART_CR2 |= (y->Stop_Bits <<12);


	//assign the required baud rate

/*
 Bits 31:16 Reserved, forced by hardware to 0.
 Bits 15:4 DIV_Mantissa[11:0]: mantissa of USARTDIV
 These 12 bits define the mantissa of the USART Divider (USARTDIV)
 Bits 3:0 DIV_Fraction[3:0]: fraction of USARTDIV
 These 4 bits define the fraction of the USART Divider (USARTDIV

* USARTDIV = DIV_Mantissa + (DIV_Fraction / 16)    ---> Div fraction = ( USARTDIV - DIV_Mantis )*16

* BAUD = Fck / (16*USARTDIV)    ---> USARTDIV = Fck / BAUD * 16
*/

	uint32_t F_clk , USARTDIV_mul100;

	if(x == USART1)
		F_clk = get_pclk2_freq() * 1000000;
	else
		F_clk = get_pclk1_freq() * 1000000;

	USARTDIV_mul100 = F_clk*100 / (y->Baud_Rate * 16);

	//adjust Mantissa value to the register
	x->USART_BRR &= ~(0xFFFF);
	x->USART_BRR |= ( ( USARTDIV_mul100 / 100) << 4 ) ;

	//adjust Fraction equivalent value
	x->USART_BRR |= ( (USARTDIV_mul100 % 100 ) * 16 / 100) ;

    //assign the status of flow control bits
	switch(y->Flow_Control)
	{
	case UART_FLOW_CONTROL_NONE :
		x->USART_CR3 &= ~(0b11<<8);
		break;
	case UART_FLOW_CONTROL_CTS_ENABLE :
		x->USART_CR3 |= (1<<9);
		break;
	case UART_FLOW_CONTROL_RTS_ENABLE :
		x->USART_CR3 |= (1<<8);
		break;
	case UART_FLOW_CONTROL_RTS_CTS_ENABLE :
		x->USART_CR3 |= (1<<9);
		x->USART_CR3 |= (1<<8);
		break;
	default :
		break;
	}


	//adjust interrupts status
	if(y->Irq_status)
	{
         x->USART_CR1 |= y->Irq_status ;
         if(x==USART1)
         {
        	 NVIC_IRQ37_USART1_ENABLE ;
        	 arr_Irq_callback[0] =  y->Uart_Isr;
         }
         else if(x==USART2)
         {
             NVIC_IRQ38_USART2_ENABLE ;
    	     arr_Irq_callback[1] =  y->Uart_Isr;
         }
         else if(x==USART3)
         {
        	 NVIC_IRQ39_USART3_ENABLE;
    	     arr_Irq_callback[2] =  y->Uart_Isr;
         }
	}

}


/*==============================================================================================================================================================*
 * @Fn			-MCAL_UART_DeInit
 * @brief 		-reset the values of USART registers to thier intial value
 * @param[in] 	-USART_t*x
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/

void MCAL_UART_DeInit(USART_t*x)

{
	if(x==USART1)
	{
		RCC->APB2ENR |= (1<<14);
		NVIC_IRQ37_USART1_DISABLE;
	}
	else if(x==USART2)
	{
		RCC->APB1RSTR |= (1<<17);
		NVIC_IRQ38_USART2_DISABLE;
	}
	else if(x==USART3)
	{
		RCC->APB1RSTR |= (1<<18);
		NVIC_IRQ39_USART3_DISABLE;
	}

	}


/*==============================================================================================================================================================*
 * @Fn			-MCAL_UART_Send_Data
 * @brief 		-Function to transmit data from uart
 * @param[in] 	-USART_t*x
 * @param[in] 	-uint16_t data_to_send
 * @param[in] 	-polling_status Polling_flag
 * @retval		-none
 * Note			-If polling is Disabled interrupt TXE must be enabled to guarantee proper behavior
 *              -When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
                the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
                because it is replaced by the parity.
                When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
*===============================================================================================================================================================*/


void MCAL_UART_Send_Data(USART_t*x,uint16_t data_to_send,enum polling_status Polling_flag)

  {
	if(Polling_flag == polling_enable)               //using polling mechanism
	{
		while(!( x->USART_SR & (1<<7) ) );
	}

	if(x->USART_CR1 & (1<<12) )                     //check for data length if 9 bits
	{
		x->USART_DR = data_to_send & (uint16_t)(0x01FF);
	}
	else
	{
		x->USART_DR = data_to_send & (uint8_t)(0xFF);
	}

	}


/*==============================================================================================================================================================*
 * @Fn			-MCAL_UART_receive_Data
 * @brief 		-Function to receive data through the uart
 * @param[in] 	-USART_t*x
 * @param[in] 	-polling_status Polling_flag
 * @retval		-uint16_t data_recived
 * Note			-If polling is Disabled interrupt RXNE must be enabled to guarantee proper behavior
 *              -When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
                the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
                because it is replaced by the parity.
                When receiving with the parity enabled, the value read in the MSB bit is the received parity bit
 *==============================================================================================================================================================*/


uint16_t MCAL_UART_receive_Data(USART_t*x,enum polling_status polling_flag)

{
	uint16_t data_recived ;
	if(polling_flag == polling_enable)                                         //using polling mechanism
	{
		while(!( x->USART_SR & (1<<5) ) );
	}

	if( x->USART_CR1 & (1<<10)  )                                           // check if parity mode is Enabled
	{
		if(x->USART_CR1 & (1<<12) )                                         //check for data length if 9 bits
		{
			data_recived =  x->USART_DR & (uint8_t)(0xFF);                  //take 8 bits only and ignore the parity bit
		}
		else
		{
			data_recived =  x->USART_DR & (uint8_t)(0x7F);                 //take 7 bits only and ignore the parity bit

		}
	}
	else
	{
		if(x->USART_CR1 & (1<<12) )                                      //check for data length if 9 bits
		{
			data_recived =  x->USART_DR & (uint16_t)(0x1FF);              //take 8 bits only and ignore the parity bit
		}
		else
		{
			data_recived =  x->USART_DR & (uint8_t)(0xFF);             //take 7 bits only and ignore the parity bit

		}
	}

	return data_recived;

}

/*==============================================================================================================================================================*
 * @Fn			-void MCAL_UART_GPIO_Set_PINS
 * @brief 		-configure GPIO pins to act by USART functions
 * @param[in] 	-USART_t*x
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/

void MCAL_UART_GPIO_Set_PINS(USART_t*x)

 {
    /*Recommended configurations
	- USARTx_TX(1) Full duplex          -->     Alternate function push-pull
	- USARTx_RX Full duplex Input       -->    floating / Input pull-up
	- USARTx_RTS Hardware flow control  -->    Alternate function push-pull
    - USARTx_CTS Hardware flow control  -->    Input floating/ Input pull-up
    */

	GPIO_CONFIG_t Uart_pins;

	if(x==USART1)
	{
		/*
		- PA9    -->  USART1_TX
		- PA10   -->  USART1_RX
		- PA11   --> USART1_CTS
		- PA12   --> USART1_RTS
		*/

		Uart_pins.Pin_Number = GPIO_pin9;
		Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
		Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
		MCAL_GPIO_Init(GPIOA, &Uart_pins);

		Uart_pins.Pin_Number = GPIO_pin10;
		Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
		MCAL_GPIO_Init(GPIOA, &Uart_pins);

		//check if flow control [CTS , RTS] is Enabled
		if(USART1->USART_CR3 & (1<<9) )
		{
			Uart_pins.Pin_Number = GPIO_pin11;
			Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
			MCAL_GPIO_Init(GPIOA, &Uart_pins);
		}
		if(USART1->USART_CR3 & (1<<8) )
				{
					Uart_pins.Pin_Number = GPIO_pin12;
					Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
					Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
					MCAL_GPIO_Init(GPIOA, &Uart_pins);
				}
	}


	if(x==USART2)
		{
			/*
			- PA0   -->  USART2_CTS
			- PA1   -->  USART2_RTS
			- PA2   -->  USART2_TX
			- PA3   -->  USART2_RX
			*/

			Uart_pins.Pin_Number = GPIO_pin2;
			Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
			Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
			MCAL_GPIO_Init(GPIOA, &Uart_pins);

			Uart_pins.Pin_Number = GPIO_pin3;
			Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
			MCAL_GPIO_Init(GPIOA, &Uart_pins);

			//check if flow control [CTS , RTS] is Enabled
			if(USART2->USART_CR3 & (1<<9) )
			{
				Uart_pins.Pin_Number = GPIO_pin0;
				Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOA, &Uart_pins);
			}
			if(USART2->USART_CR3 & (1<<8) )
					{
						Uart_pins.Pin_Number = GPIO_pin1;
						Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
						Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
						MCAL_GPIO_Init(GPIOA, &Uart_pins);
					}
		}



	if(x==USART3)
			{
				/*
				- PB10   -->  USART3_TX
				- PB11   -->  USART3_RX
				- PD11   -->  USART3_CTS
				- PD12   -->  USART3_RTS
				*/

				Uart_pins.Pin_Number = GPIO_pin10;
				Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
				Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOB, &Uart_pins);

				Uart_pins.Pin_Number = GPIO_pin11;
				Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOB, &Uart_pins);

				//check if flow control [CTS , RTS] is Enabled
				if(USART3->USART_CR3 & (1<<9) )
				{
					Uart_pins.Pin_Number = GPIO_pin11;
					Uart_pins.Pin_Mode = GPIO_MODE_Floating_input;
					MCAL_GPIO_Init(GPIOD, &Uart_pins);
				}
				if(USART3->USART_CR3 & (1<<8) )
						{
							Uart_pins.Pin_Number = GPIO_pin12;
							Uart_pins.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
							Uart_pins.Output_Pin_Speed = medium_speed_10Mhz;
							MCAL_GPIO_Init(GPIOD, &Uart_pins);
						}
			}

	}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

void MCAL_UART_WAIT_TC (USART_t * USARTx )
{
	// wait till TC flag is set in the SR
	while( ! (USARTx->USART_SR & 1<<6 ));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

uint32_t get_Hclk_freq(void)
{
	//assume sysclk = 8Mhz
	/*	Bits 7:4 HPRE: AHB prescaler
	Set and cleared by software to control the division factor of the AHB clock.
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512
	 */


	uint8_t Hclk_Prescaler = ( ( RCC->CFGR & (0b1111 << 4) ) >> 4 ) ;
	if(Hclk_Prescaler < 0b1000)
		return 8;

	if(Hclk_Prescaler <= 0b1011 )
		return 8/power_func(2, Hclk_Prescaler-7);
	else
		return 8/power_func(2, Hclk_Prescaler-6);


}


uint32_t get_pclk1_freq(void)
{
	/*Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB low-speed clock
(PCLK1).
Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16
	 */

	uint8_t Apb1_Prescaler = ( ( RCC->CFGR & (0b111 << 8) ) >> 8 ) ;
	if(Apb1_Prescaler < 0b100)
		return get_Hclk_freq();
	else
		return get_Hclk_freq()/power_func(2, Apb1_Prescaler-3);

}


uint32_t get_pclk2_freq(void)
{
	/*Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB high-speed clock
	(PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16
	 */

	uint8_t Apb2_Prescaler = ( ( RCC->CFGR & (0b111 << 11) ) >> 11 ) ;
	if(Apb2_Prescaler < 0b100)
		return get_Hclk_freq();
	else
		return get_Hclk_freq()/power_func(2, Apb2_Prescaler-3);

}


uint32_t power_func(uint32_t x,uint32_t y)
{
	uint32_t result =1 ;
	uint8_t i;
	for(i=0; i<y; i++)
	{
		result *= x;
	}
	return result;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                         Isr


void USART1_IRQHandler(void)
{
	arr_Irq_callback[0]();
	}

void USART2_IRQHandler(void)
{
	arr_Irq_callback[1]();
	}

void USART3_IRQHandler(void)
{
	arr_Irq_callback[2]();
	}




















