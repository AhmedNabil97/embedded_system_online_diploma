/*
 * EEPROM.c
 *
 *  Created on: ٠٣‏/٠١‏/٢٠٢٤
 *      Author: Ahmed
 */


#include "EEPROM.h"


void HAL_EEprom_init(void)
{
	I2C_CONFIG_t Master_configuration;
	Master_configuration.I2C_MODE = I2C_MODE_I2C;
	Master_configuration.I2C_CLK_SPEED = I2C_CLK_SPEED_100KHZ;
	Master_configuration.I2C_SLAVE_EVENT_CALLBACK = NULL;
	Master_configuration.I2C_STRETCH_Status = I2C_STRETCH_ENABLE;
	Master_configuration.ACK_CONTROL = I2C_ACK_ENABLE;
	MCAL_I2C_Init(I2C1, & Master_configuration);
	MCAL_I2C_GPIO_Set_Pins(I2C1);

	}
void HAL_EEprom_write_nbytes(uint16_t memory_address,uint8_t* data_to_send,uint8_t data_length)

{
	uint8_t sec_byte_address = memory_address >> 8 ;
	uint8_t fst_byte_address = (uint8_t) memory_address;
	uint8_t total_buffer[256];
	total_buffer[0] = sec_byte_address;
	total_buffer[1] = fst_byte_address;
	uint8_t i ;
	for(i=2; i < data_length+2 ; i++)
	{
		total_buffer[i] = data_to_send[i-2];
	}
	MCAL_I2C_Master_Tx(I2C1, EEPROM_slave_address, data_length +2, total_buffer, initial_start, stop_Enable);

	}
void HAL_EEprom_read_nbytes(uint16_t memory_address,uint8_t* received_data,uint8_t data_length)
{

	uint8_t sec_byte_address = memory_address >> 8 ;
	uint8_t fst_byte_address = (uint8_t) memory_address;
	uint8_t address_buffer[2];
	address_buffer[0] = sec_byte_address;
	address_buffer[1] = fst_byte_address;

	MCAL_I2C_Master_Tx(I2C1, EEPROM_slave_address, 2 , address_buffer, initial_start, stop_disable);
	MCAL_I2C_Master_Rx(I2C1, EEPROM_slave_address, data_length, received_data, repeated_start, stop_Enable);
	}
























