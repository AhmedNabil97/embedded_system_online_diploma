/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "I2C.h"
#include "EEPROM.h"


void clock_init(void)
{
	GPIOB_CLK_EN()   ;       //Enable clock for GPIOB
    I2C1_CLK_EN();
}



int main(void)

{
	clock_init();
    HAL_EEprom_init();

	unsigned char write_buff[10];
	unsigned char read_buff[10];

	int i ;
	for(i=0; i<10; i++)
	{
		write_buff[i] = i*2;
	}

	HAL_EEprom_write_nbytes(0x24, write_buff, 10);
    HAL_EEprom_read_nbytes(0x24, read_buff, 10);
    while(1)
    {

    }

}


