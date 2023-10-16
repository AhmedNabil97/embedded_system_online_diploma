/*
 * main_algorithm.c
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#include "main_algorithm.h"
#define pressure_threshold 20

int pressure_value_m;
void (* main_state_ptr)() = state(checking);
state_define(checking)
{
	main_state_id = checking_t;
	if ( pressure_value_m > pressure_threshold)
	{
		high_pressure_detected();                             //state action
	}
}

void send_pressure_value(int value)
{
	pressure_value_m= value;

	}
