/*
 * CA.h
 *
 *  Created on: Oct 1, 2023
 *      Author: ahmed
 */

#ifndef CA_H_
#define CA_H_
#include "States.h"
void(*states_pointer)();
int CA_distance;
int CA_speed;
enum CA_state
{
	CA_waiting,
	CA_driving
	}CA_state_id;

State_define(CA_waiting_);
State_define(CA_driving_);

#endif /* CA_H_ */
