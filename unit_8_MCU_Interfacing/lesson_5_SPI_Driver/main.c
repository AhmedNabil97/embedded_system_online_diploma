/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "UART.h"
#include "SPI.h"

//#define MCU_Master_Mode
#define MCU_Slave_Mode
uint8_t buffer;
uint8_t SPi_buffer;


void USART1_handler(void)
{

#ifdef MCU_Master_Mode

	buffer = MCAL_UART_receive_Data(USART1, polling_disable);
	MCAL_UART_Send_Data(USART1, buffer, polling_enable);
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin4, 0);
	MCAL_SPI_Master_Transmit_only(SPI1, buffer);
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin4, 1);
#endif

}

void SPI1_handler(void)
{
 #ifdef MCU_Slave_Mode
	if(SPI1->SPI_SR & (1<<RXNE))
	{
	SPi_buffer = (uint8_t)MCAL_SPI_Slave_Receive_only(SPI1, polling_disable);
	MCAL_UART_Send_Data(USART1, SPi_buffer , polling_enable);
	}
#endif
}

void clock_init(void)
{
	GPIOA_CLK_EN()   ;       //Enable clock for GPIOA
	GPIOB_CLK_EN()   ;       //Enable clock for GPIOB
	USART1_CLK_EN()  ;       //Enable clock for USART1
	SPI1_CLK_EN()    ;

}



int main(void)

{
	clock_init();

	//UART configuration

	UART_CONFIG_t U1_config;
	U1_config.Uart_Mode = UART_TX_RX_ENABLE;
	U1_config.Baud_Rate = UART_BAUD_RATE_115200_BPS;
	U1_config.Data_Length = UART_8_BITS_DATA_LENGTH;
	U1_config.Flow_Control = UART_FLOW_CONTROL_NONE;
	U1_config.Irq_status = UART_INTERRUPT_RXNE_ENABLE;
	U1_config.Uart_Isr = USART1_handler;
	U1_config.Parity_Bits = UART_PARITY_NONE;
	U1_config.Stop_Bits = UART_1_STOP_BIT;
	MCAL_UART_Init(USART1, & U1_config);
	MCAL_UART_GPIO_Set_PINS(USART1);


	//SPI configuration
	SPI_CONFIG_t SPI1_config;
	SPI1_config.SPI_Communication_Mode = SPI_CM_Mode_2Lines_FDuplex;
	SPI1_config.SPI_Frame_Size = SPI_Frame_Size_8B;
	SPI1_config.SPI_Frame_Format  = SPI_Frame_Format_MSB;
	SPI1_config.SPI_Clk_Pol_ph = SPI_CPol_Idle_High_2nd_Edge;
	SPI1_config.SPI_Clk_Pre_Scaler = SPI_Clk_Pre_scaler_8;

#ifdef MCU_Master_Mode
	SPI1_config.SPI_Mode = SPI_Mode_Master;
	SPI1_config.SPI_IRQ_status = SPI_Interrupts_disable;
	SPI1_config.SPI_Isr = NULL;
	SPI1_config.SPI_SSM = SPI_SS_SW_Manegment;
	SPI1->SPI_CR1 |= (1<<8);                                    //set ss high
	GPIO_CONFIG_t Slave_Select;
	Slave_Select.Pin_Number = GPIO_pin4;
	Slave_Select.Pin_Mode = GPIO_MODE_General_purpose_output_push_pull;
	Slave_Select.Output_Pin_Speed = medium_speed_10Mhz;
	MCAL_GPIO_Init(GPIOA, & Slave_Select);
	MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin4, 1);

#endif

#ifdef MCU_Slave_Mode
SPI1_config.SPI_Mode = SPI_Mode_Slave;
SPI1_config.SPI_IRQ_status = SPI_Interrupt_RXNEIE_Enable;
SPI1_config.SPI_Isr = SPI1_handler;
SPI1_config.SPI_SSM = SPI_SS_HW_Manegment_Input;
#endif
	MCAL_SPI_Init(SPI1, & SPI1_config);
	MCAL_SPI_GPIO_Set_PINS(SPI1, single_slave);


	while(1)
	{
	}
}


