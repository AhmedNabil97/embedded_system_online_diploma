/*
 * SPI.h
 *
 *  Created on: ٢٥‏/١٢‏/٢٠٢٣
 *      Author: Ahmed
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f103x6.h"
#include"GPIO.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

enum slave_status
{
	single_slave,
	multi_slave
	};
enum SPI_polling_status
{
	SPI_polling_enable,
	SPI_polling_disable
	};

#define TXE		1                                //Tx buffer status flag
#define RXNE    0                                //Rx buffer status flag


//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

                                                         //configuration structure


typedef struct

{

	uint8_t   SPI_Mode ;                    	    	                    //this parameter should be set based on @ref SPI_MODE_define
	uint8_t   SPI_Communication_Mode ;                    	    	        //this parameter should be set based on @ref SPI_COMMUNICATION_MODE_define
	uint8_t   SPI_Clk_Pre_Scaler ;                    	    	            //this parameter should be set based on @ref SPI_CLK_PS__define
	uint8_t   SPI_Clk_Pol_ph   ;                    	    	            //this parameter should be set based on @ref SPI_CLKPOL/PH_define
	uint8_t   SPI_Frame_Size ;                    	    	                //this parameter should be set based on @ref SPI_FRAME_SIZE_define
	uint8_t   SPI_Frame_Format ;                    	    	            //this parameter should be set based on @ref SPI_FRAME_FORMAT_define
	uint8_t   SPI_SSM ;                    	    	                        //this parameter should be set based on @ref SPI_SLAVE_SELECET_MANAGEMENT_MODE_define
	uint8_t   SPI_IRQ_status;												//this parameter should be set based on @ref SPI_INTERRUPT_STATUS_define more than 1 IR can be chosen by |
    void 	  (*SPI_Isr)(void);                                             //this parameter should be set based on user function set to handle SPI interrupt


	}SPI_CONFIG_t;


//--------------------------------------------------------------------------------------------------------------------------------------------------------------//

															 //macros configuration references



//@ref SPI_MODE_define

#define SPI_Mode_Slave	                										0
#define SPI_Mode_Master	   														1


//@ref SPI_COMMUNICATION_MODE_define

#define SPI_CM_Mode_2Lines_FDuplex											     0
#define SPI_CM_Mode_2Lines_Receive_Only                       			         1
#define SPI_CM_Mode_1Line_Transmit_Only                            			     2
#define SPI_CM_Mode_1Line_Receive_Only                                           3


//@ref SPI_CLK_PS__define

#define SPI_Clk_Pre_scaler_2													0
#define SPI_Clk_Pre_scaler_4													1
#define	SPI_Clk_Pre_scaler_8 													2
#define SPI_Clk_Pre_scaler_16													3
#define SPI_Clk_Pre_scaler_32													4
#define SPI_Clk_Pre_scaler_64													5
#define SPI_Clk_Pre_scaler_128													6
#define SPI_Clk_Pre_scaler_256													7


//@ref SPI_CLKPOL/PH_define

#define SPI_CPol_Idle_Low_1st_Edge												0b00
#define SPI_CPol_Idle_Low_2nd_Edge												0b01
#define SPI_CPol_Idle_High_1st_Edge												0b10
#define SPI_CPol_Idle_High_2nd_Edge												0b11


//@ref SPI_FRAME_SIZE_define

#define	SPI_Frame_Size_8B														0
#define	SPI_Frame_Size_16B														1


//@ref SPI_FRAME_FORMAT_define

#define SPI_Frame_Format_MSB													0
#define SPI_Frame_Format_LSB													1


//@ref SPI_SLAVE_SELECET_MANAGEMENT_MODE_define

#define SPI_SS_SW_Manegment														0
#define SPI_SS_HW_Manegment_Input												1
#define SPI_SS_HW_Manegment_Output												2


//@ref SPI_INTERRUPT_STATUS_define

#define SPI_Interrupts_disable													0
#define SPI_Interrupt_TXEIE_Enable												(1<<7)
#define SPI_Interrupt_RXNEIE_Enable												(1<<6)
#define SPI_Interrupt_TXEIE_ERRIE												(1<<5)


//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
				                                      // APIs supported by " MCAL UART driver "


void MCAL_SPI_Init(SPI_t*,SPI_CONFIG_t*);
void MCAL_SPI_DeInit(SPI_t*);
void MCAL_SPI_GPIO_Set_PINS(SPI_t*,enum slave_status);
uint16_t MCAL_SPI_Transmit_Receive(SPI_t*,uint16_t,enum SPI_polling_status );
void MCAL_SPI_Master_Transmit_only(SPI_t*,uint16_t);
uint16_t MCAL_SPI_Slave_Receive_only(SPI_t*,enum SPI_polling_status);







#endif /* SPI_H_ */
