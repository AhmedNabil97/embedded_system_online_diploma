/*
 * LCD.h
 *
 * Created: 11/01/2024 02:53:21 م
 *  Author: Ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_

//lcd port

typedef struct
{
	unsigned char reseved :4 ;
	unsigned char Lcd_Port :4 ;
}PA_t;



#define   PORTD_base									(0x32)
#define   Access_pointer 								((volatile PA_t*)PORTD_base)
#define   DDRD											*((volatile unsigned char*)(0x31))
#define	  PIND	                                        *((volatile unsigned char*)(0x0x30))
#define   LCD_PORT_DIRECTION							DDRD
#define   LCD_INPUT									    PIND


//lcd control

#define  PORTB										  *((volatile unsigned char*)(0x38))
#define  DDRB										  *((volatile unsigned char*)(0x37))
#define  LCD_CTRL									  PORTB
#define  RS											  1
#define  R_W                                          2
#define  En                                           3


// functions

void lcd_is_busy(void);
void lcd_init(void);
void lcd_send_command(unsigned char cmd );
void Lcd_En(void);
void lcd_display_char(unsigned char ch);
void lcd_display_sentence(unsigned char* p);
void my_delay(unsigned int i);
void lcd_position(int x,int y);
lcd_delete_space(int x,int y,int z);

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
#define lcd_4_bit_2_line 0x2C
#define lcd_begin_at_first_row 0x80
#define lcd_begin_at_seconed_row 0xC0
#define lcd_4_bit_mode_init 0x32
#define lcd_hide_crouser	0x0C
#define lcd_restore_crouser	0x0E





#endif /* LCD_H_ */