/*
 * EEPROM.h
 *
 *  Created on: ٠٣‏/٠١‏/٢٠٢٤
 *      Author: Ahmed
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "I2C.h"

#define EEPROM_slave_address 			0x2A


void HAL_EEprom_init(void);
void HAL_EEprom_write_nbytes(uint16_t memory_address,uint8_t* data_to_send,uint8_t data_length);
void HAL_EEprom_read_nbytes(uint16_t memory_address,uint8_t* received_data,uint8_t data_length);



#endif /* EEPROM_H_ */
