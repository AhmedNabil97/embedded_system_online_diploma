/*
 * alarm_control.h
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#ifndef ALARM_CONTROL_H_
#define ALARM_CONTROL_H_

#include "States.h"

 enum
{
	idle_t,
	acting_t
	}alarm_control_id;

	state_define(idle);
	state_define(acting);

#endif /* ALARM_CONTROL_H_ */
