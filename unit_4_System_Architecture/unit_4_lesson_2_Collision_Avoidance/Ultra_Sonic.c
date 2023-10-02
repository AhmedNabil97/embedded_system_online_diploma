/*
 * Ultra_Sonic.c

 *
 *  Created on: Oct 2, 2023
 *      Author: ahmed
 */

#include "Ultra_Sonic.h"
extern void US_set_distance(int);
void US_init()
{
	US_distance = 0;
	US_state_id = US_busy;
	US_state_pointer = State(US_busy_);
	}

State_define(US_busy_)
{
	//state id
	US_state_id = US_busy;
	//state action
     US_distance = US_send_distance(45,55);
     //send signal
     US_set_distance(US_distance);
 	printf("Ultra.sonic--sending--distance-------------> CA : %d \n",US_distance);
     //state looping
 	US_state_pointer = State(US_busy_);
	}
