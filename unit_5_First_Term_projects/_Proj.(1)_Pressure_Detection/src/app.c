/*
 ============================================================================
 Name        : Pressure_Detection.c
 Author      : Eng.Ahmed Nabil Mahmoud
 Version     :
 Copyright   : 
 Description : high pressure detection  
 ============================================================================
 */

#include "pressure_sensor.h"
#include "main_algorithm.h"
#include "alarm_control.h"
#include "alarm_actuator.h"

extern void (*sensor_state_ptr)();
extern void (* main_state_ptr)();
extern void (*alarm_control_ptr)();
extern void (*actuator_state_ptr)();


void setup()
{
      GPIO_INITIALIZATION ();
	sensor_init();
	alarm_actuator_init();
	}
int main()
{
	setup();
	while(1)
	{
		sensor_state_ptr();
		main_state_ptr();
		alarm_control_ptr();
		actuator_state_ptr();
	}
}
