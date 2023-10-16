/*
 * alarm_control.c
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */


#include "alarm_control.h"
void (*alarm_control_ptr)() = state(idle);

state_define(idle)
{
	alarm_control_id = idle_t;
	set_alarm_off();
	}
state_define(acting)
{
	alarm_control_id = acting_t;
	set_alarm_on();                                   //state action
	alarm_control_ptr = state(idle);
	}

void high_pressure_detected()
{
   alarm_control_ptr = state(acting);

	}
