/*
 * pressure_sensor.c
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */


#include "pressure_sensor.h"
#include "driver.h"

void (*sensor_state_ptr)();    //ptr to function of sensor state
int Pressure_value;
int sensor_pull_time = 5000000;  //by some calculations this number is equivalent to 10 sec. delay 
void sensor_init()
{
	sensor_state_id = reading_t;
	sensor_state_ptr = state(reading);
	Pressure_value = 0;
}

state_define(reading)
{
	Pressure_value = getPressureVal();
	send_pressure_value(Pressure_value);                             //state action
	sensor_state_ptr = state(waiting);
}

state_define(waiting)
{
	sensor_state_id = waiting_t;
	Delay(sensor_pull_time);
	sensor_state_ptr = state(reading);
      state(reading)();

}
