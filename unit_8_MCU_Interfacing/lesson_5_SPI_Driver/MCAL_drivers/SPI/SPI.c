/*
 * SPI.c
 *
 *  Created on: ٢٥‏/١٢‏/٢٠٢٣
 *      Author: Ahmed
 */

#include "SPI.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
		                                      // global variables & Auxiliary functions"

void (* SPI_arr_Irq_callback[2])(void);

/*==============================================================================================================================================================*
 * @Fn			-MCAL_SPI_Init
 * @brief 		-initialize required SPI instant with the required configuration
 * @param[in] 	-SPI_t*x
 * @param[in] 	-SPI_CONFIG_t*y
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/


void MCAL_SPI_Init(SPI_t*x,SPI_CONFIG_t*y)

{


    //set required mode master or slave
	x->SPI_CR1 &= ~(1<<2);
	x->SPI_CR1 |= (y->SPI_Mode<<2) ;


	//set communication mode
	switch(y->SPI_Communication_Mode)
	{
	case SPI_CM_Mode_2Lines_FDuplex :
	x->SPI_CR1 &= ~ ( (1<<15) | (1<<10) );
	break;
	case SPI_CM_Mode_2Lines_Receive_Only :
	x->SPI_CR1 &= ~(1<<15);
	x->SPI_CR1 |=  (1<<10);
	break;
	case SPI_CM_Mode_1Line_Receive_Only :
	x->SPI_CR1 &= ~(0b11<<14);
	x->SPI_CR1 |=  (0b10<<14);
	break;
	case SPI_CM_Mode_1Line_Transmit_Only :
	x->SPI_CR1 &= ~(0b11<<14);
	x->SPI_CR1 |=  (0b11<<14);
	break;
	default :
	break;
	}


     //set clock pre-scaler
     /*
     Bits 5:3 BR[2:0]: Baud rate control
     000: fPCLK/2
     001: fPCLK/4
 	 010: fPCLK/8
	 011: fPCLK/16
     100: fPCLK/32
	 101: fPCLK/64
	 110: fPCLK/128
	 111: fPCLK/256
	 */
	x->SPI_CR1 &= ~(0b111<<3);
	x->SPI_CR1 |= (y->SPI_Clk_Pre_Scaler<<3);


    //set clock polarity/phase
	x->SPI_CR1 &= ~(0b11);
	x->SPI_CR1 |= (y->SPI_Clk_Pol_ph);


	//set frame size
	x->SPI_CR1 &= ~(1<<11);
	x->SPI_CR1 |= (y->SPI_Frame_Size <<11);


	//set frame foramt
	x->SPI_CR1 &= ~(1<<7);
	x->SPI_CR1 |= (y->SPI_Frame_Format<<7);


	//set slave select mangment
	x->SPI_CR1 &= ~(1<<9);
    x->SPI_CR2 &= ~(1<<2);
	switch(y->SPI_SSM)
	{
	case SPI_SS_SW_Manegment :
	x->SPI_CR1 |= (1<<9);
	break;
	case SPI_SS_HW_Manegment_Output :
    x->SPI_CR2 |= (1<<2);
    break;
	case SPI_SS_HW_Manegment_Input :
	break;
	}


	//set interrupt status
	 if( y->SPI_IRQ_status )
	 {
		 //Enable global interrupt for SPI  -->  Nvic
		 if(x==SPI1)
		 {
			 NVIC_IRQ35_SPI1_ENABLE;
             SPI_arr_Irq_callback[0] =  y->SPI_Isr;
		 }
		 if(x==SPI2)
		 {
			 NVIC_IRQ36_SPI2_ENABLE;
             SPI_arr_Irq_callback[1] =  y->SPI_Isr;

		 }
		 //Enable interrupt in SPI_CR2
		 x->SPI_CR2 |= (y->SPI_IRQ_status) ;
	 }


	 //Enable SPI
	 x->SPI_CR1 |= (1<<6);

	}

/*==============================================================================================================================================================*
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-reset required SPI registers to thier intial values
 * @param[in] 	-SPI_t*x
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/

void MCAL_SPI_DeInit(SPI_t*x)

 {
	if(x == SPI1 )
	{
		RCC->APB2RSTR |= (1<<14);
		NVIC_IRQ35_SPI1_DISABLE;
	}
	if(x == SPI2)
	{
		RCC->APB1RSTR |= (1<<14);
		NVIC_IRQ36_SPI2_DISABLE;
	}
 }


/*==============================================================================================================================================================*
 * @Fn			-MCAL_SPI_GPIO_Set_PINS
 * @brief 		-configure Equivalent pins to act by SPI function & assign their proper configuration
 * @param[in] 	-SPI_t*x
 * @retval		-none
 * Note			-
 *=============================================================================================================================================================*/


void MCAL_SPI_GPIO_Set_PINS(SPI_t*x,enum slave_status y)

{
	GPIO_CONFIG_t SPI_GPIO_Pins_config;

//recommended configurations From TRM

/*	SPIx_SCK
	Master Alternate function push-pull
	Slave Input floating
	-------------------------------------------------------------------
	SPIx_MOSI
	Full duplex / master Alternate function push-pull
	Full duplex / slave Input floating / Input pull-up
	Simplex bidirectional data wire / master Alternate function push-pull
	Simplex bidirectional data wire/ slave Not used. Can be used as a GPIO
	-------------------------------------------------------------------
	SPIx_MISO
	Full duplex / master Input floating / Input pull-up
	Full duplex / slave (point to point) Alternate function push-pull
	Full duplex / slave (multi-slave) Alternate function open drain
	Simplex bidirectional data wire / master Not used. Can be used as a GPIO
	Simplex bidirectional data wire/ slave
	(point to point) Alternate function push-pull
	Simplex bidirectional data wire/ slave
	(multi-slave) Alternate function open drain
	-------------------------------------------------------------------
	SPIx_NSS
	Hardware master /slave Input floating/ Input pull-up / Input pull-down
	Hardware master/ NSS output enabled Alternate function push-pull
	Software Not used
	-------------------------------------------------------------------
	*/

	if(x == SPI1)
	{
		// check for device mode master or slave
		if(x->SPI_CR1 & (1<<2))
		{
			//master case configuration  :-


			//configure SClk pin           for SPI1 ---------------> PA5
			SPI_GPIO_Pins_config.Pin_Number = GPIO_pin5 ;
			SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
			SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
			MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			//Configure MOSI pin           for SPI1 ---------------> PA7
			SPI_GPIO_Pins_config.Pin_Number = GPIO_pin7;
			SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
			SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
			MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			//Configure MISO pin           for SPI1 ---------------> PA6
			if(!(x->SPI_CR1 & (1<<15)))
			{
			//used in full duplex mode only
			SPI_GPIO_Pins_config.Pin_Number = GPIO_pin6 ;
			SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
			MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);
			}

			//configure NSS pin           for SPI1 ---------------> PA4
			if( !(x->SPI_CR1 & (1<<9)) && x->SPI_CR2 & (1<<2))                      //Hardware & output Enabled

			{
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin4;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
				SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			}
			if(!(x->SPI_CR1 & (1<<9)))                                            //Hardware & output disabled
			{
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin4 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			}
			}

		else
		{
			//slave case configuration

			//configure SClk pin           for SPI1 ---------------> PA5      --------------->slave case
			SPI_GPIO_Pins_config.Pin_Number = GPIO_pin5 ;
			SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
			MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			//Configure MOSI pin           for SPI1 ---------------> PA7
			if(!(x->SPI_CR1 & (1<<15)))
			{
			//used in full duplex mode only
			SPI_GPIO_Pins_config.Pin_Number = GPIO_pin7 ;
			SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
			MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);
			}

			//Configure MISO pin           for SPI1 ---------------> PA6
			if  (y)
			{
				// multi-slave configuration whatever full duplex or simplex
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin6;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
				SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);
			}
			else
			{
				// single-slave configuration whatever full duplex or simplex
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin6;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
				SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			}

			//configure NSS pin           for SPI1 ---------------> PA4
			if( !(x->SPI_CR1 & (1<<9)))                      //Hardware management
			{
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin4 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOA, & SPI_GPIO_Pins_config);

			}

		}

	}


	if(x==SPI2)

	{
			// check for device mode master or slave
			if(x->SPI_CR1 & (1<<2))
			{
				//master case configuration  :-


				//configure SClk pin           for SPI2 ---------------> PB13
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin13 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
				SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				//Configure MOSI pin           for SPI2 ---------------> PB15
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin7;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
				SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
				MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				//Configure MISO pin           for SPI2 ---------------> PB14
				if(!(x->SPI_CR1 & (1<<15)))
				{
				//used in full duplex mode only
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin14 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);
				}

				//configure NSS pin           for SPI2 ---------------> PB12
				if( !(x->SPI_CR1 & (1<<9)) && x->SPI_CR2 & (1<<2))                      //Hardware & output Enabled

				{
					SPI_GPIO_Pins_config.Pin_Number = GPIO_pin12;
					SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
					SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
					MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				}
				if(!(x->SPI_CR1 & (1<<9)))                                            //Hardware & output disabled
				{
					SPI_GPIO_Pins_config.Pin_Number = GPIO_pin12 ;
					SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
					MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				}
				}

			else
			{
				//slave case configuration

				//configure SClk pin           for SPI2 ---------------> PB13
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin13 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				//Configure MOSI pin           for SPI2 ---------------> PB15
				if(!(x->SPI_CR1 & (1<<15)))
				{
				//used in full duplex mode only
				SPI_GPIO_Pins_config.Pin_Number = GPIO_pin15 ;
				SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
				MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);
				}

				//Configure MISO pin           for SPI2 ---------------> PB14
				if  (y)
				{
					// multi-slave configuration whatever full duplex or simplex
					SPI_GPIO_Pins_config.Pin_Number = GPIO_pin14;
					SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
					SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
					MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);
				}
				else
				{
					// single-slave configuration whatever full duplex or simplex
					SPI_GPIO_Pins_config.Pin_Number = GPIO_pin14;
					SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Alternate_function_output_push_pull;
					SPI_GPIO_Pins_config.Output_Pin_Speed = medium_speed_10Mhz;
					MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				}

				//configure NSS pin           for SPI2 ---------------> PB12
				if( !(x->SPI_CR1 & (1<<9)))                      //Hardware management
				{
					SPI_GPIO_Pins_config.Pin_Number = GPIO_pin12 ;
					SPI_GPIO_Pins_config.Pin_Mode = GPIO_MODE_Floating_input;
					MCAL_GPIO_Init(GPIOB, & SPI_GPIO_Pins_config);

				}

			}

		}


	}



/*==============================================================================================================================================================*
 * @Fn			-MCAL_SPI_Transmit_Receive
 * @brief 		-function to allow simultaneous full duplex communication
 * @param[in] 	-SPI_t*x
 * @param[in] 	-uint16_t data_to_send
 * @retval		-uint16_t
 * Note			-if polling status is disabled interrupt will be Enabled automatically
 *=============================================================================================================================================================*/


uint16_t MCAL_SPI_Transmit_Receive(SPI_t*x,uint16_t data_to_send,enum SPI_polling_status y)

 {


           if(y == SPI_polling_enable)
          while(!(x->SPI_SR & 1<<TXE));
    	  x->SPI_DR = data_to_send;
          if(y == SPI_polling_enable)
    	  while(!(x->SPI_SR & 1<<RXNE));
          return x->SPI_DR;




 }




void MCAL_SPI_Master_Transmit_only(SPI_t*x,uint16_t data_to_send)
{
	  x->SPI_DR = data_to_send;
	  while(!(x->SPI_SR & 1<<TXE));

	}
uint16_t MCAL_SPI_Slave_Receive_only(SPI_t*x,enum SPI_polling_status y)
{
	if(y==SPI_polling_enable)
	{
  	  while(!(x->SPI_SR & 1<<RXNE));
        return x->SPI_DR;

	}
	return x->SPI_DR;
	}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
//                                                         Isr


void SPI1_IRQHandler(void)

{
	SPI_arr_Irq_callback[0]();

	}

void SPI2_IRQHandler(void)

{
	SPI_arr_Irq_callback[1]();

	}

