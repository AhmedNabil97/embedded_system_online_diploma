/*
  * CA.c
 *
 *  Created on: Oct 1, 2023
 *      Author: ahmed
 */

#include"CA.h"
int threshold =50;
void US_set_distance (int d)
{
	CA_distance = d;
	 (CA_distance <= threshold)? (states_pointer = State(CA_waiting_)) : (states_pointer = State(CA_driving_)) ;
   //  printf("current speed = %d ---------- current distance = %d ----------so next state is : ",CA_speed,CA_distance);
	}
State_define(CA_waiting_)
{
	//set state id
	CA_state_id = CA_waiting;
	//Set speed = 0
	 CA_set_speed(0);
	 CA_speed =0;
	 printf("CA_waiting state ----- distance = %d ------- speed = %d\n",CA_distance,CA_speed);

	}

State_define(CA_driving_)
{
	CA_state_id = CA_driving;
	//set speed = 30
	 CA_set_speed(30);
	 CA_speed =30;
	 printf("CA_driving state ----- distance = %d ------- speed = %d\n",CA_distance,CA_speed);
	}
int US_send_distance(int l,int r)
{
        int random;
        random = rand() % (r - l + 1) + l;
        return random;
	}
