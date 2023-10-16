/*
 * alarm_actuator.h
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#ifndef ALARM_ACTUATOR_H_
#define ALARM_ACTUATOR_H_

#include "States.h"
#include "driver.h"

 enum
{
	alarm_waiting_t,
	alarm_on_t,
	alarm_off_t
	}alarm_actuator_id;

void alarm_actuator_init();
state_define(alarm_waiting);
state_define(alarm_off);
state_define(alarm_on);


#endif /* ALARM_ACTUATOR_H_ */
