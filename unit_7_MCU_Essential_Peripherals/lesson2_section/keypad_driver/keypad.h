/*
 * keypad.h
 *
 * Created: 28/11/2023 08:29:18 م
 *  Author: lenovo
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define PORTD *((volatile unsigned char*)(0x32))
#define DDRD *((volatile unsigned char*)(0x31))
#define PIND *((volatile unsigned char*)(0x30))
#define KEYPAD_PORT PORTD
#define KEYPAD_PINS_DIRECTION DDRD
#define KEYPAD_INPUT_SIGNALS PIND

#define row_a 0
#define row_b 1
#define row_c 2
#define row_d 3
#define col1 4
#define col2 5
#define col3 6
#define col4 7


typedef struct  
{
	unsigned char ROW_A:1;
	unsigned char ROW_B:1;
	unsigned char ROW_C:1;
	unsigned char ROW_D:1;
	unsigned char COL_1:1;
	unsigned char COL_2:1;
	unsigned char COL_3:1;
	unsigned char COL_4:1;
	
}button_matrix;

enum button_type
{
 number,
 operation,
 equal,
 on_off
	};
void keypad_init(void);
unsigned char keypad_send_char(void);


#endif /* KEYPAD_H_ */