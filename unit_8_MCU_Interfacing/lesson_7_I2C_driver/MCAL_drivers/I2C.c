/*
 * I2C.C
 *
 *  Created on: ٣١‏/١٢‏/٢٠٢٣
 *      Author: lenovo
 */


#include "I2C.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------//
		                                      // global variables & Auxiliary functions "

uint32_t get_pclk1_freq(void);
void I2C_Edit_starting(I2C_t*,start_bit_status,start_bit_type);
flag_status get_flag_status(I2C_t*,I2C_Flag);
//-------------------------------------------------------------------------------------------------------------------------------------------------------------//


void MCAL_I2C_Init(I2C_t*x,I2C_CONFIG_t*y)

{

	// check for  I2C MODE
	if(y->I2C_MODE == I2C_MODE_I2C)
	{

		//adjust clock configuration :-

		/*
	  1. First set peripheral frequency

	  Bits 5:0 FREQ[5:0]: Peripheral clock frequency
      The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
      connected to APB). The FREQ field is used by the peripheral to generate data setup and
      hold times compliant with the I2C specifications. The minimum allowed frequency is 2 MHz,
      the maximum frequency is limited by the maximum APB frequency and cannot exceed
      50 MHz (peripheral intrinsic maximum limit).
      0b000000: Not allowed
      0b000001: Not allowed
      0b000010: 2 MHz
      ...
      0b110010: 50 MHz
      Higher than 0b100100: Not allowed

		 */

	x->I2C_CR2 &= ~(0x3F);
	x->I2C_CR2 |= (get_pclk1_freq());

	/*
	 2. set the value of CCR
	 Bits 11:0 CCR[11:0]: Clock control register in Fm/Sm mode (Master mode)
     Controls the SCL clock in master mode.
     Sm mode or SMBus:
     Thigh = CCR * TPCLK1
     Tlow  = CCR * TPCLK1
     SM mode is the only supported mode therefore :-
     CCR = 1/2 Tsclk / Ti2c    ----------->   CCR = I2C_FREQ  / 2 SCLK FREQ
	 */

	x->I2C_CCR &= ~(0x0FFF);
    x->I2C_CCR |= ( get_pclk1_freq() * 1000) / ( y->I2C_CLK_SPEED *2 );




    /*
     3. set the value of Tries
     Bits 5:0 TRISE[5:0]: Maximum rise time in Fm/Sm mode (Master mode)
    These bits should provide the maximum duration of the SCL feedback loop in master mode.
    The purpose is to keep a stable SCL frequency whatever the SCL rising edge duration.
    These bits must be programmed with the maximum SCL rise time given in the I2C bus
    specification, incremented by 1.
    For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
    If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
    therefore the TRISE[5:0] bits must be programmed with 09h.
    (1000 ns / 125 ns = 8 + 1)
    ----------->       value of Trise = I2C freq / 10^6   +  1
     */
    x->I2C_TRISE &= ~(0x3F);
    x->I2C_TRISE |= (get_pclk1_freq() + 1);

   /* Adjust CR1 configurations :- */

    x->I2C_CR1 &= ~(I2C_CR1_ACK | I2C_CR1_NOSTRETCH | I2C_CR1_SMBUS );
    x->I2C_CR1 |= (y->ACK_CONTROL | y->I2C_STRETCH_Status | y->I2C_MODE);

    /* Adjust address settings */

    //define the status of addressing single or dual addressing
    x->I2C_OAR2 &= ~(y->I2C_ADDRESS_SETTINGS.I2C_Adress_STATUS);
    x->I2C_OAR2 |= (y->I2C_ADDRESS_SETTINGS.I2C_Adress_STATUS);

    //define the mode of addressing 7bit or 10bit
    x->I2C_OAR1 &= ~(y->I2C_ADDRESS_SETTINGS.I2C_Adress_MODE);
    x->I2C_OAR1 |= (y->I2C_ADDRESS_SETTINGS.I2C_Adress_MODE);

    //set address ----> single address 7bit only is supported
    x->I2C_OAR1 &= ~(0x7F << 1);
    x->I2C_OAR1 |= (y->I2C_ADDRESS_SETTINGS.I2C_Address1 << 1) ;

    //check for slave mode to Enable interrupts

    if(y->I2C_SLAVE_EVENT_CALLBACK)
    {
    	/*
    	Bit 9 ITEVTEN: Event interrupt enable
    	0: Event interrupt disabled
    	1: Event interrupt enabled
    	This interrupt is generated when:
    	– SB = 1 (Master)
    	– ADDR = 1 (Master/Slave)
    	– ADD10= 1 (Master)
    	– STOPF = 1 (Slave)
    	– BTF = 1 with no TxE or RxNE event
    	– TxE event to 1 if ITBUFEN = 1
    	– RxNE event to 1if ITBUFEN = 1
    	*/

    	x->I2C_CR2 |= (I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN);
        if(x==I2C1)
        	NVIC_IRQ31_I2C1_EV_ENABLE;
        if(x==I2C2)
        	NVIC_IRQ33_I2C2_EV_ENABLE;

    }

    //Enable I2C

   x->I2C_CR1 |= I2C_CR1_PE;
	}
	else
	{
		//not supported SM bus
	}

}
void MCAL_I2C_DeInit(I2C_t*x)

{
	if(x==I2C1)
	{
		NVIC_IRQ31_I2C1_EV_DISABLE;
		NVIC_IRQ32_I2C1_ER_DISABLE;
		RCC->APB1RSTR |= (1<<21);
	}
	if(x==I2C2)
	{
		NVIC_IRQ33_I2C2_EV_DISABLE;
		NVIC_IRQ34_I2C2_ER_DISABLE;
		RCC->APB1RSTR |= (1<<22);

	}
}


void MCAL_I2C_GPIO_Set_Pins(I2C_t*x)

{
	   GPIO_CONFIG_t I2C_PINS;

   if(x==I2C1)
   {

   I2C_PINS.Pin_Number = GPIO_pin6;
   I2C_PINS.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
   I2C_PINS.Output_Pin_Speed = medium_speed_10Mhz;
   MCAL_GPIO_Init(GPIOB, &I2C_PINS);

   I2C_PINS.Pin_Number = GPIO_pin7;
   I2C_PINS.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
   I2C_PINS.Output_Pin_Speed = medium_speed_10Mhz;
   MCAL_GPIO_Init(GPIOB, &I2C_PINS);
   }

   if(x==I2C2)
   {
	   I2C_PINS.Pin_Number = GPIO_pin10;
	   I2C_PINS.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
	   I2C_PINS.Output_Pin_Speed = medium_speed_10Mhz;
	   MCAL_GPIO_Init(GPIOB, &I2C_PINS);

	   I2C_PINS.Pin_Number = GPIO_pin11;
	   I2C_PINS.Pin_Mode = GPIO_MODE_Alternate_function_output_Open_drain;
	   I2C_PINS.Output_Pin_Speed = medium_speed_10Mhz;
	   MCAL_GPIO_Init(GPIOB, &I2C_PINS);

   }

   }




void MCAL_I2C_Master_Tx(I2C_t*x, uint16_t slave_address , uint8_t data_Length , uint8_t* data_to_send,start_bit_type st,stop_bit_status p )

{
	// 1. set the start bit

	I2C_Edit_starting(x,start_Enable,st);

	// 2. wait for SB = 1 that cleared by reading it from SR1 followed by writing the address to I2C DR
	while(! get_flag_status(x,SB_flag));
	x->I2C_DR = slave_address << 1 ;     //last significant bit = 0 for writing

	// 3. wait for Addr
	while(! get_flag_status(x,ADDR_flag));

	// 4. check for TRA , MSL , BUSY , TXE
	while(! get_flag_status(x,master_transmit_check));

    // 5. write data to DR
	uint8_t i = 0;
	for(i=0; i<data_Length; i++)
	{
		x->I2C_DR = data_to_send[i];
		while (! get_flag_status(x,TxE_flag));
	}

	// 6. generates stop bit
	if(p == stop_Enable)
	x->I2C_CR1 |= I2C_CR1_STOP;

	}








void MCAL_I2C_Master_Rx(I2C_t*x, uint16_t slave_address , uint8_t data_Length , uint8_t* receiving_buffer ,start_bit_type st,stop_bit_status p)

{
	uint32_t dummy_read;
	slave_address = slave_address << 1 ;
	slave_address |= 1 ;
	// 1. Generates start condition
	I2C_Edit_starting(x,start_Enable,st);

	// 2. wait for SB = 1 that cleared by reading it from SR1 followed by writing the address to I2C DR
	while(! get_flag_status(x,SB_flag));
	x->I2C_DR = slave_address ;

	// 3. wait for Addr
	while(! get_flag_status(x,ADDR_flag));
	dummy_read = x->I2C_SR2 ;

	// 4. reading data
   int8_t i ;
   for(i = data_Length-1; i>0; i--)
   {
	   while(! get_flag_status(x,RxNE_flag));
	   receiving_buffer[data_Length - i - 1] = x->I2C_DR;
   }

   // 5. send nack
   x->I2C_CR1 &= ~ (I2C_CR1_ACK);

	// 6. generates stop bit
   if(p==stop_Enable)
	x->I2C_CR1 |= I2C_CR1_STOP;
	x->I2C_CR1 |= (I2C_CR1_ACK);


}











void I2C_Edit_starting(I2C_t*x,start_bit_status St_S,start_bit_type St_T)
{

	if(St_S == start_disable)
	{
		x->I2C_CR1 &= ~(I2C_CR1_START);
		return;
	}
	else
	{
		if(St_T == repeated_start)
		{
			x->I2C_CR1 |= (I2C_CR1_START);
			return;

		}

		if(St_T == initial_start)
		{
			while(get_flag_status(x,busy_flag));
			x->I2C_CR1 |= (I2C_CR1_START);
			return;

		}
	}

	}


flag_status get_flag_status(I2C_t*x,I2C_Flag flag)
{
	uint16_t dummy_read;
	flag_status ADDR_bit;

	switch(flag)
	{
	case busy_flag :
		return (x->I2C_SR2 & I2C_SR2_BUSY) >> I2C_SR2_BUSY_Pos;
	case SB_flag :
		return (x->I2C_SR1 & I2C_SR1_SB) >> I2C_SR1_SB_Pos;
	case ADDR_flag :
		ADDR_bit = (x->I2C_SR1 & I2C_SR1_ADDR ) >> I2C_SR1_ADDR_Pos;
		return ADDR_bit;
	case master_transmit_check :
		dummy_read = x->I2C_SR2 & (0b111);
		dummy_read |= x->I2C_SR1 & (I2C_SR1_TXE) ;
		if (dummy_read == 0x87)
			return flag_set;
		else
			return flag_reset;
	case TxE_flag :
		return (x->I2C_SR1 & I2C_SR1_TXE) >> I2C_SR1_TXE_Pos ;
	case RxNE_flag :
		return (x->I2C_SR1 & I2C_SR1_RXNE) >> I2C_SR1_RXNE_Pos ;

	}
	return 0;
}



