/*
 * uart.h
 *
 * Created: 18/12/2023 12:21:05 ص
 *  Author: lenovo
 */ 


#ifndef UART_H_
#define UART_H_

//USART REGS

#define  UDR						 *((volatile unsigned char*)0x2C)
#define  UCSRA						 *((volatile unsigned char*)0x2B)		
#define  UCSRB						 *((volatile unsigned char*)0x2A)
#define  UCSRC						 *((volatile unsigned char*)0x40)
#define  UBRRL						 *((volatile unsigned char*)0x29)


//UART FLAGS & UCSRA BITS		

#define   RXC							7                                //Indicates if receive buffer is empty
#define   TXC							6                                //Indicates when the frame is successfully transmitted
#define   UDRE							5                                //Indicates if transmit buffer is empty
#define   FE							4                                //Indicates if there is a frame error
#define   DOR							3                                //Indicates if there is a data loss
#define   PE							2                                //Indicates if there is a parity error
#define   U2X							1                                //duplicate the baud rate or set it to normal
#define   MPCM							0                                //Enables multiprocessor communication mode




//UART APIES

void MCAL_UART_Init(void);
void MCAL_UART_Transmit_Char(unsigned char); 
unsigned char MCAL_UART_Receive_Char(void);
void MCAL_UART_Transmit_string(unsigned char* ); 


#endif /* UART_H_ */