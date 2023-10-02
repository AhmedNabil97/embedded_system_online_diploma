/*
 * States.h
 *
 *  Created on: Oct 2, 2023
 *      Author: ahmed
 */

#ifndef STATES_H_
#define STATES_H_
#include <stdio.h>
#include "stdlib.h"

#define State_define(_State_) void _State_()  //Functions definitions
#define State(_state_) _state_               //Functions symbols


//connections
int US_send_distance(int,int);
void CA_set_speed(int);

#endif /* STATES_H_ */
