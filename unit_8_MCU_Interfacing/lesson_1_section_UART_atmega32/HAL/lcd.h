/*
 * lcd.h
 *
 * Created: 18/12/2023 02:50:22 ص
 *  Author: Ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_

//lcd port

#define PORTA *((volatile unsigned char*)(0x3B))
#define DDRA *((volatile unsigned char*)(0x3A))
#define PINA *((volatile unsigned char*)(0x39))
#define LCD_PORT PORTA
#define LCD_PORT_DIRECTION DDRA
#define LCD_INPUT PINA


//lcd control

#define PORTB *((volatile unsigned char*)(0x38))
#define DDRB *((volatile unsigned char*)(0x37))
#define LCD_CTRL PORTB
#define RS 1
#define R_W 2
#define En 3


// functions

void lcd_is_busy(void);
void lcd_init(void);
void lcd_send_command(unsigned char );
void Lcd_En(void);
void lcd_display_char(unsigned char);
void lcd_display_sentence(unsigned char*);


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