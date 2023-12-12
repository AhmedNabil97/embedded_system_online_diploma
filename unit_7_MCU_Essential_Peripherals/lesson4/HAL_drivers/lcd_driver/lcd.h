/*
 * lcd.h
 *
 * Created: 26/11/2023 08:48:13 م
 *  Author: lenovo
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "GPIO.h"

//lcd port 

#define LCD_PORT GPIOA->ODR
#define LCD_PORT_DIRECTION GPIOA->CRL
#define LCD_INPUT GPIOA->IDR


//lcd control


#define LCD_CTRL GPIOA->ODR
#define RS 8
#define R_W 9
#define En 10


// functions

void lcd_is_busy(void);
void lcd_init(void);
void lcd_send_command(unsigned char );
void Lcd_En(void);
void lcd_display_char(unsigned char);
void lcd_display_sentence( char*);
void _delay_ms(unsigned int );

// commands

#define lcd_clear 0x1
#define lcd_return_home 0x2
#define lcd_Entery_mode 0x6
#define lcd_display_crouser_blink_on 0x0F
#define lcd_crouser_shift_right 0x14
#define lcd_crouser_shift_left 0x10
#define lcd_display_shift_right 0x1C
#define lcd_display_shift_left 0x18
#define lcd_Eight_bit_1_line 0x34
#define lcd_8_bit_2_line 0x38 
#define lcd_begin_at_first_row 0x80
#define lcd_begin_at_seconed_row 0xC0

#endif /* LCD_H_ */
