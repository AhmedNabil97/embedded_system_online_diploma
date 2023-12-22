/*
 * UART.h
 *
 *  Created on: ١٩‏/١٢‏/٢٠٢٣
 *      Author: Ahmed
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f103x6.h"
#include"GPIO.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

enum polling_status
{
	polling_enable,
	polling_disable
	};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------//

                                                         //configuration structure


typedef struct

{

	uint8_t   Uart_Mode ;                    	    	        //this parameter should be set based on @ref UART_MODE_define
	uint8_t   Data_Length ; 					            	//this parameter should be set based on @ref UART_DATA_LENGTH_define
	uint8_t   Parity_Bits ; 							    	//this parameter should be set based on @ref UART_PARITY_MODE_define
	uint8_t   Stop_Bits ; 							        	//this parameter should be set based on @ref UART_STOP_BITS_define
	uint32_t  Baud_Rate ; 							    	    //this parameter should be set based on @ref UART_BAUD_RATE_define
	uint8_t   Flow_Control ; 						 		   	//this parameter should be set based on @ref UART_Flow_Control_define
	uint16_t   Irq_status ; 	    					        //this parameter should be set based on @ref UART_INTERRUPT_STATUS_define & u can choose more than 1 interrupt using |
    void 	  (*Uart_Isr)(void);                                //this parameter should be set based on user function set to handle uart interrupt


	}UART_CONFIG_t;


//----------------------------------------------------------------------------------------------------------------------------------------------------------//

														 //macros configuration references



//@ref UART_MODE_define

#define    UART_TX_ENABLE    														0
#define    UART_RX_ENABLE    														1
#define    UART_TX_RX_ENABLE    													2

//@ref UART_DATA_LENGTH_define

#define    UART_8_BITS_DATA_LENGTH    												0
#define    UART_9_BITS_DATA_LENGTH    												1

//@ref UART_PARITY_MODE_define

#define    UART_PARITY_NONE   														2
#define    UART_EVEN_PARITY    														0
#define    UART_ODD_PARITY    														1

//@ref UART_STOP_BITS_define

#define    UART_1_STOP_BIT   														0
#define    UART_0.5_STOP_BIT   									     				1
#define    UART_2_STOP_BITS   													    2
#define    UART_1.5_STOP_BITS   													3

//@ref UART_BAUD_RATE_define

#define    UART_BAUD_RATE_2400_BPS   												2400
#define    UART_BAUD_RATE_9600_BPS   												9600
#define    UART_BAUD_RATE_19200_BPS   												19200
#define    UART_BAUD_RATE_57600_BPS   												57600
#define    UART_BAUD_RATE_115200_BPS   												115200
#define    UART_BAUD_RATE_230400_BPS   												230400
#define    UART_BAUD_RATE_460800_BPS   												460900
#define    UART_BAUD_RATE_921600_BPS   									  			921600
#define    UART_BAUD_RATE_2250000_BPS   											2250000
#define    UART_BAUD_RATE_4500000_BPS   											4500000

//@ref UART_Flow_Control_define

#define    UART_FLOW_CONTROL_NONE   												0
#define    UART_FLOW_CONTROL_CTS_ENABLE  											1
#define    UART_FLOW_CONTROL_RTS_ENABLE   											2
#define    UART_FLOW_CONTROL_RTS_CTS_ENABLE   										3

//@ref UART_INTERRUPT_STATUS_define

#define    UART_INTERRUPTS_DISABLE   												0                  //No Interrupts
#define    UART_INTERRUPT_PE_ENABLE   												(1<<8)             //Parity error
#define    UART_INTERRUPT_TXE_ENABLE   												(1<<7)             //Transmit data register empty
#define    UART_INTERRUPT_TC_ENABLE   												(1<<6)             //Transmission complete
#define    UART_INTERRUPT_RXNE_ENABLE   											(1<<5)	           //Received data ready to be read



//----------------------------------------------------------------------------------------------------------------------------------------------------------//
			                                      // APIs supported by " MCAL UART driver "



void MCAL_UART_Init(USART_t*,UART_CONFIG_t*);
void MCAL_UART_DeInit(USART_t*);
void MCAL_UART_Send_Data(USART_t*,uint16_t,enum polling_status);
uint16_t MCAL_UART_receive_Data(USART_t*,enum polling_status);
void MCAL_UART_GPIO_Set_PINS(USART_t*);
void MCAL_UART_WAIT_TC (USART_t* );









#endif /* UART_H_ */
