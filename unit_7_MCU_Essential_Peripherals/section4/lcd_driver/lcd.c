/*
 * Lcd_Amit.c
 *
 * Created: 13/12/2023 12:12:44 
 *  Author: AHMED
 */
 

#include "Lcd_Amit.h"


void my_delay(unsigned int i)
{
  volatile  unsigned int k,j;
  for(k=0; k<i; k++)
  {
     for(j=0; j<255; j++);
  }
}
void Lcd_En(void)
{
	LCD_CTRL |= (1<<En);
	my_delay(20);
	LCD_CTRL &= ~(1<<En);

}

lcd_send_first_command(unsigned char cmd1)
{
	my_delay(50);
	Access_pointer->reseved = (cmd1 & 0x0F);
	Access_pointer->Lcd_Port = ( (cmd1 & 0xF0) >> 4 );
	LCD_CTRL &= ~(1<<RS);
	Lcd_En();
}

// Function to check if LCD is busy
void lcd_is_busy(void)
{
my_delay(50);
LCD_CTRL &= ~(1<<RS);
}

void lcd_send_command(unsigned char cmd)
{
	lcd_is_busy();
	Access_pointer->Lcd_Port = ( (cmd & 0xF0) >> 4);                    // Send higher nibble
	LCD_CTRL &= ~(1<<RS);
	Lcd_En();
	 Access_pointer->Lcd_Port = (cmd & 0x0F);                            // Send Lower nibble
	Lcd_En();
}


// Function to initialize the LCD
void lcd_init(void)
{
	Access_pointer->reseved = 0;
	my_delay(50);
    DDRB = 0x0E;										  	    // Set DDRB to control LCD control lines as outputs
    LCD_PORT_DIRECTION = 0XF0;							 	    // Set data direction to output for writing data
    LCD_CTRL &= ~((1<<R_W) | (1<<RS) | (1<<En));		 		// Clear control lines
   lcd_is_busy();
	lcd_send_command(lcd_4_bit_mode_init);
	lcd_is_busy();
	lcd_send_command(lcd_4_bit_2_line);
	lcd_is_busy();
	lcd_send_command(lcd_clear);
	lcd_is_busy();
	lcd_send_command(lcd_return_home);
	lcd_is_busy();
    lcd_send_command(lcd_Entery_mode);
	lcd_is_busy();
	lcd_send_command(lcd_display_crouser_blink_on);
	lcd_is_busy();
	lcd_send_command(lcd_begin_at_first_row);
    
}

// Function to display a character on the LCD

void lcd_display_char(unsigned char ch)
{
	lcd_is_busy();	
	LCD_CTRL |= (1<<RS);	
	Access_pointer->Lcd_Port = ( (ch & 0xF0) >> 4);                    // Send higher nibble
	Lcd_En();
	Access_pointer->Lcd_Port = (ch & 0x0F);                            // Send Lower nibble
    Lcd_En();
}

void lcd_display_sentence(unsigned char*p)
{
	char index=0;
	while(p[index])
	{
		lcd_is_busy();
		if(index == 16)
		{
		lcd_send_command(lcd_begin_at_seconed_row);
		}
	lcd_display_char(p[index]);
	index++;
	}
}
	
		

      

