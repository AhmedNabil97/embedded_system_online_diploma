/*
 * timers.h
 *
 * Created: 16/02/2024 12:58:51 ص
 *  Author: Ahmed
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "avr/io.h"
#include "util/delay.h"

void open_Entery_gate(void);
void close_Entery_gate(void);
void open_Exit_gate(void);
void close_Exit_gate(void);
void Set_timers_pins(void);



#endif /* TIMERS_H_ */