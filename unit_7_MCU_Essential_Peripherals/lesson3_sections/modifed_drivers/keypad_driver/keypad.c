/*
 * keypad.c
 *
 * Created: 28/11/2023 08:29:33 م
 *  Author: lenovo
 */ 
#include "keypad.h"
enum button_type flag;

button_matrix * pin = &(GPIOB->ODR);                //used to deal with port b as single pins by using Bitfields
button_matrix * pin_in = &(GPIOB->IDR);             //that will help in the implementation of keypad functions
char button_counters = 0;                           //counter for how many times buttons are pressed

void keypad_init(void)
{
	KEYPAD_PINS_DIRECTION = 0x11111111;                  //set keypad rows & columns as output
    KEYPAD_PORT = 0xFF00;                                //set all rows and columns to high state
}

//keypad contents
 unsigned char arr_intersections[4][4] = {
	'7',
	'8',
	'9',
	'/',
	'4',
	'5',
	'6',
	'*',
	'1',
	'2',
	'3',
	'-',
	'o',
	'0',
	'=',
	'+'
};

 //function to send char from keypad
 unsigned char keypad_send_char(void)
{
	while (1)
	{
		pin->COL_1 = 0;

		switch (pin_in->ROW_A)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[0][0];
		}

		switch (pin_in->ROW_B)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[1][0];
		}

		switch (pin_in->ROW_C)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[2][0];
		}

		switch (pin_in->ROW_D)
		{
			case 1:
			break;
			case 0:
			flag = on_off;
			button_counters ++;
			return arr_intersections[3][0];
		}

		pin->COL_1 = 1;
		pin->COL_2 = 0;

		switch (pin_in->ROW_A)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[0][1];
		}

		switch (pin_in->ROW_B)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[1][1];
		}

		switch (pin_in->ROW_C)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[2][1];
		}

		switch (pin_in->ROW_D)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[3][1];
		}

		pin->COL_2 = 1;
		pin->COL_3 = 0;

		switch (pin_in->ROW_A)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[0][2];
		}

		switch (pin_in->ROW_B)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[1][2];
		}

		switch (pin_in->ROW_C)
		{
			case 1:
			break;
			case 0:
			flag = number;
			button_counters ++;
			return arr_intersections[2][2];
		}

		switch (pin_in->ROW_D)
		{
			case 1:
			break;
			case 0:
			flag = equal;
			button_counters ++;
			return arr_intersections[3][2];
		}

		pin->COL_3 = 1;
		pin->COL_4 = 0;

		switch (pin_in->ROW_A)
		{
			case 1:
			break;
			case 0:
			flag = operation;
			button_counters ++;
			return arr_intersections[0][3];
		}

		switch (pin_in->ROW_B)
		{
			case 1:
			break;
			case 0:
			flag = operation;
			button_counters ++;
			return arr_intersections[1][3];
		}

		switch (pin_in->ROW_C)
		{
			case 1:
			break;
			case 0:
			flag = operation;
			button_counters ++;
			return arr_intersections[2][3];
		}

		switch (pin_in->ROW_D)
		{
			case 1:
			break;
			case 0:
			flag = operation;
			button_counters ++;
			return arr_intersections[3][3];
		}

		pin->COL_4 = 1;
	}
}
