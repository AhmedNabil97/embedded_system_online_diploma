/*
 * lcd.c
 *
 * Created: 26/11/2023 08:48:35 م
 * Author: lenovo
 */ 
#include <string.h>
#include "lcd.h"

GPIO_CONFIG_t P_RS;
GPIO_CONFIG_t P_RW;
GPIO_CONFIG_t P_EN;

//global variable used as counter for loops
unsigned int i;

//function to make delay based on received argument q
void _delay_ms(unsigned int q)
{
	char j,k;
	for (k=0; k<q; k++)
	{
		for(j=0; j<255; j++);
	}


}

//function to toggle LCD Enable to perform instructions
void Lcd_En(void)
{
	LCD_CTRL |= (1<<En);
	_delay_ms(10);
	LCD_CTRL &= ~(1<<En);

}

//function to set control pins of LCD as output push/pull
void set_lcd_ctrl_mode (void)
{
	P_RS.Pin_Number = GPIO_pin8;
	P_RS.Pin_Mode = GPIO_MODE_General_purpose_output_push_pull;
	P_RS.Output_Pin_Speed = medium_speed_10Mhz;
	P_RW = P_RS;
	P_RW.Pin_Number = GPIO_pin9;
	P_EN = P_RS;
	P_EN.Pin_Number = GPIO_pin10;
	MCAL_GPIO_Init(GPIOA,&P_RS);
	MCAL_GPIO_Init(GPIOA,&P_RW);
	MCAL_GPIO_Init(GPIOA,&P_EN);

}
// Function to check if LCD is busy
void lcd_is_busy(void)
{
	MCAL_GPIO_Write_Port(GPIOA, 0);
	LCD_PORT_DIRECTION = 0X44444444;       	       // Set data direction to input for reading busy flag
	LCD_CTRL &= ~(1<<RS);   					   // Set RS low to indicate command mode
	LCD_CTRL |= (1<<R_W);   					   // Set R_W high to read data from LCD
	LCD_CTRL |= (1<<En);    					   // Enable LCD
	while( LCD_PORT & (1<<7) );       			   // Delay for stable operation
	LCD_CTRL &= ~(1<<En);     					   // Disable LCD
	LCD_PORT_DIRECTION = 0X11111111;					   // Set data direction back to output for writing data
	LCD_CTRL &= ~(1<<R_W);  					   // Set R_W low for write mode
}

//function that send commands to LCD
void lcd_send_command(unsigned char cmd)
{
	lcd_is_busy();
	for(i=0; i<8; i++)
	{
		MCAL_GPIO_Write_Pin(GPIOA, (1<<i),( ( cmd & (1<<i) )>>i ) );
	}
	LCD_CTRL &= ~(1<<RS);
	Lcd_En();
}


// Function to initialize the LCD
void lcd_init(void)
{
	_delay_ms(50);
	set_lcd_ctrl_mode();          			      			   // Set DDRB to control LCD control lines
	LCD_PORT_DIRECTION = 0X11111111;   						   // Set data direction to output for writing data
	LCD_CTRL &= ~((1<<R_W) | (1<<RS) | (1<<En));			   // Clear control lines
	_delay_ms(50);                						   	  // Delay for stable operation

	// Initialize LCD with specific commands
	lcd_is_busy();
	lcd_send_command(lcd_clear);
	lcd_is_busy();
	lcd_send_command(lcd_return_home);
	lcd_is_busy();
	lcd_send_command(lcd_Entery_mode);

	lcd_is_busy();
	lcd_send_command(lcd_8_bit_2_line);
	lcd_is_busy();
	lcd_send_command(lcd_display_crouser_blink_on);
	lcd_is_busy();
	lcd_send_command(lcd_begin_at_first_row);

}

// Function to display a character on the LCD
void lcd_display_char( unsigned char ch)
{
	lcd_is_busy();
	for(i=0; i<8; i++)
		{
			MCAL_GPIO_Write_Pin(GPIOA, (1<<i),( ( ch & (1<<i) )>>i ) );
		}
	LCD_CTRL |= (1<<RS);
	Lcd_En();
}


// Function to display a sentence on the LCD
void lcd_display_sentence( char*p)
{
	unsigned char index=0;
	lcd_is_busy();
	while(p[index])
	{
		if(index == 16)
		{
			LCD_CTRL &= ~(1<<RS);
			lcd_send_command(lcd_begin_at_seconed_row);
			Lcd_En();
			LCD_CTRL |= (1<<RS);
		}
		for(i=0; i<8; i++)
			{
				MCAL_GPIO_Write_Pin(GPIOA, (1<<i), ( ( p[index] & (1<<i) )>>i ) );
			}
		LCD_CTRL |= (1<<RS);
		Lcd_En();
		index++;
	}
}





