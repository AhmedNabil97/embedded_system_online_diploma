/*
 * Dc_Motor.h
 *
 *  Created on: Oct 2, 2023
 *      Author: ahmed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "States.h"

int motor_speed;
void motor_init();
State_define(motor_idle);
State_define(motor_busy);
void (*motor_state_pointer)();
enum motor_state
{
	motor_idle_state,
	motor_busy_state
	}motor_state_id;
#endif /* DC_MOTOR_H_ */
