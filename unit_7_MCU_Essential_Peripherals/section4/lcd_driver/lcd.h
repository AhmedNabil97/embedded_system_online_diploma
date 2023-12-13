/*
 * Lcd_Amit.h
 *
 * Created: 13/12/2023 12:12:19 
 *  Author: lenovo
 */ 


#ifndef LCD_AMIT_H_
#define LCD_AMIT_H_


//lcd port 

typedef struct  
{
	unsigned char reseved :4 ;
	unsigned char Lcd_Port :4 ;
}PA_t;



#define   PORTA_base									(0x3B)
#define   Access_pointer 								((volatile PA_t*)PORTA_base)
#define   DDRA											*((volatile unsigned char*)(0x3A))
#define	  PINA                                          *((volatile unsigned char*)(0x0x39))	
#define   LCD_PORT_DIRECTION							DDRA
#define   LCD_INPUT									    PINA


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


#endif /* LCD_AMIT_H_ */