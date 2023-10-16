/*
 * alarm_actuator.c
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#include "alarm_actuator.h"
#define alarm_timer 32000000                 //by some calculations this number is equivalent to 60sec. delay

void (*actuator_state_ptr)();
void alarm_actuator_init()
{
	alarm_actuator_id = alarm_waiting_t;
	actuator_state_ptr = state(alarm_off);
}

state_define(alarm_waiting)
{
	alarm_actuator_id = alarm_waiting_t;

}
state_define(alarm_off)
{
	alarm_actuator_id = alarm_off_t;
	Set_Alarm_actuator(1);                                //state action
	actuator_state_ptr = state(alarm_waiting);

}
state_define(alarm_on)
{
	alarm_actuator_id = alarm_on_t;
	Set_Alarm_actuator(0);                                 //state action
	Delay(alarm_timer);
	Set_Alarm_actuator(1);                                 //state action
	actuator_state_ptr = state(alarm_waiting);
}

void set_alarm_on()
{
	actuator_state_ptr = state(alarm_on);

}
void set_alarm_off()
{
	actuator_state_ptr = state(alarm_off);

}
