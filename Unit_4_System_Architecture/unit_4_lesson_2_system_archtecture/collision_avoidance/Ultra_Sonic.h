/*
 * Ultra_Sonic.h
 *
 *  Created on: Oct 2, 2023
 *      Author: ahmed
 */

#ifndef ULTRA_SONIC_H_
#define ULTRA_SONIC_H_
#include "States.h"
int US_distance ;
enum US_state
		{
	      US_busy
		}US_state_id;

void US_init();
State_define(US_busy_);
void (*US_state_pointer)();

#endif /* ULTRA_SONIC_H_ */
