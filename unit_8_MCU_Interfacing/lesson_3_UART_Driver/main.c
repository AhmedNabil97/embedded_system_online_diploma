/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "UART.h"

void clock_init(void)
{
	GPIOA_CLK_EN()   ;       //Enable clock for GPIOA
	GPIOB_CLK_EN()   ;       //Enable clock for GPIOB
    USART1_CLK_EN()  ;       //Enable clock for USART1

}
unsigned char buffer;

void my_handler(void)
{

	buffer = MCAL_UART_receive_Data(USART1, polling_disable);
	MCAL_UART_Send_Data(USART1, buffer, polling_enable);


}


int main(void)

{
	clock_init();
	UART_CONFIG_t U1_config;
	U1_config.Uart_Mode = UART_TX_RX_ENABLE;
	U1_config.Baud_Rate = UART_BAUD_RATE_115200_BPS;
	U1_config.Data_Length = UART_8_BITS_DATA_LENGTH;
	U1_config.Flow_Control = UART_FLOW_CONTROL_NONE;
	U1_config.Irq_status = UART_INTERRUPT_RXNE_ENABLE;
	U1_config.Uart_Isr = my_handler;
	U1_config.Parity_Bits = UART_PARITY_NONE;
	U1_config.Stop_Bits = UART_1_STOP_BIT;
	MCAL_UART_Init(USART1, & U1_config);
	MCAL_UART_GPIO_Set_PINS(USART1);
	while(1)
	{
	}
}



