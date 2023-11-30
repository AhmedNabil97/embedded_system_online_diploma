/*
 * lcd.c
 *
 * Created: 26/11/2023 08:48:35 م
 * Author: lenovo
 */ 
#include <string.h>
#include "lcd.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void Lcd_En(void)
{
	LCD_CTRL |= (1<<En);
	_delay_ms(10);
	LCD_CTRL &= ~(1<<En);

}
// Function to check if LCD is busy
void lcd_is_busy(void)
{
	PORTA = 0;
   DDRB = 14;               // Set DDRB to control LCD control lines
   LCD_PORT_DIRECTION = 0X0;   // Set data direction to input for reading busy flag
   LCD_CTRL &= ~(1<<RS);      // Set RS low to indicate command mode
   LCD_CTRL |= (1<<R_W);      // Set R_W high to read data from LCD
   LCD_CTRL |= (1<<En);       // Enable LCD
   while( (LCD_PORT & (1<<7) >> 7 ) );          // Delay for stable operation
   LCD_CTRL &= ~(1<<En);      // Disable LCD
   LCD_PORT_DIRECTION = 0XFF;  // Set data direction back to output for writing data
   LCD_CTRL &= ~(1<<R_W);     // Set R_W low for write mode
}

void lcd_send_command(unsigned char cmd)
{
	lcd_is_busy();
	LCD_PORT = cmd;
	LCD_CTRL &= ~(1<<RS);
	Lcd_En();
}


// Function to initialize the LCD
void lcd_init(void)
{
	_delay_ms(50);
    DDRB = 0x0E;                   // Set DDRB to control LCD control lines
    LCD_PORT_DIRECTION = 0XFF;     // Set data direction to output for writing data
    LCD_CTRL &= ~((1<<R_W) | (1<<RS) | (1<<En));  // Clear control lines
    _delay_ms(50);                 // Delay for stable operation

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

void lcd_display_char(unsigned char ch)
{
	lcd_is_busy();
	LCD_PORT = ch;
	LCD_CTRL |= (1<<RS);
	Lcd_En();
}

void lcd_display_sentence(unsigned char*p)
{
	char index=0;
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
	LCD_PORT = p[index];
	LCD_CTRL |= (1<<RS);
	Lcd_En();
	index++;
	}
}
	
		

      

