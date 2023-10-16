/*
 * Sates.h
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#ifndef STATES_H_
#define STATES_H_

#include <stdio.h>

// functions definitions
#define state_define(_func_) void _func_()
#define state(_func_) _func_


// interfaces functions between modules
void send_pressure_value(int value);
void high_pressure_detected();
void set_alarm_on();
void set_alarm_off();

#endif /* STATES_H_ */
