/*
 * pressure_sensor.h
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */

#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include "States.h"

 enum
{
	reading_t,
	waiting_t
	}sensor_state_id;

void sensor_init();
state_define(reading);
state_define(waiting);

#endif /* PRESSURE_SENSOR_H_ */
