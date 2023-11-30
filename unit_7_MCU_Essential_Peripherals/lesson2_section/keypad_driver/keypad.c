/*
 * keypad.c
 *
 * Created: 28/11/2023 08:29:33 م
 *  Author: lenovo
 */ 
#include "keypad.h"
enum button_type flag;
button_matrix * pin = (volatile unsigned char*)(0x32);
button_matrix * pin_in = (volatile unsigned char*)(0x30);
char button_counters = 0;

void keypad_init(void)
{
	KEYPAD_PINS_DIRECTION = 0xFF;
    KEYPAD_PORT = 0xFF;
   KEYPAD_PINS_DIRECTION = 0xF0;
   
}

char arr_intersections[4][4] = {
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
