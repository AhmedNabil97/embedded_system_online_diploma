/*
 * uart_section.c
 *
 * Created: 18/12/2023 12:20:42 ص
 * Author : Ahmed
 */ 

#include "lcd.h"
#include "uart.h"

int main(void)
{
    /* Replace with your application code */
	
	lcd_init();
	MCAL_UART_Init();
	MCAL_UART_Transmit_string("Learn-In-Depth\r");
	MCAL_UART_Transmit_string("uart section -> Ahmed Nabil\r");
	unsigned char ch = 0 ;
    int count = 0;
while(1)
{
	ch = MCAL_UART_Receive_Char();
	
  switch(count)
  {
	  
    case 16 : 
   lcd_send_command(lcd_begin_at_seconed_row);
   break;
   
   case 32 :
   lcd_send_command(lcd_clear);
   break;
   
   default:
   break;
   
  }
 
 if(ch != '\r')
 {
	 lcd_display_char(ch);
     count++;
}
else
break;
}

}