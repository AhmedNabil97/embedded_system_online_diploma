/*
 * Dc_Motor.c
 *
 *  Created on: Oct 2, 2023
 *      Author: ahmed
 */
#include "Dc_Motor.h"
void motor_init()
{
	motor_speed =0 ;
	motor_state_id = motor_idle_state;
	motor_state_pointer = State(motor_idle);
	}
State_define(motor_idle)
{
	motor_state_id = motor_idle_state;

	}
void CA_set_speed(int s)
{
	motor_speed = s;
	motor_state_pointer = State(motor_busy);
	printf("CA--sending--speed-------------> DC Motor : %d \n",motor_speed);
	}
State_define(motor_busy)
{
	motor_state_id = motor_busy_state;
	//call pwm to make speed = motor_speed
	motor_state_pointer = State(motor_idle);

	}



