/*
 * keypad.h
 *
 * Created: 28/11/2023 08:29:18 م
 *  Author: lenovo
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "GPIO.h"

#define KEYPAD_PORT 						GPIOB->ODR
#define KEYPAD_PINS_DIRECTION 				GPIOB->CRH
#define KEYPAD_INPUT_SIGNALS 				GPIOB->IDR



typedef struct  
{
	unsigned char :8;
	unsigned char COL_1:1;
	unsigned char COL_2:1;
	unsigned char COL_3:1;
	unsigned char COL_4:1;
	unsigned char ROW_A:1;
	unsigned char ROW_B:1;
	unsigned char ROW_C:1;
	unsigned char ROW_D:1;
	
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
