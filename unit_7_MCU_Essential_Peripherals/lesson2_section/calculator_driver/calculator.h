/*
 * calculator.h
 *
 * Created: 29/11/2023 03:09:25 م
 *  Author: lenovo
 */ 


#ifndef CALCULATOR_H_
#define CALCULATOR_H_

void calc_init(void);
void calc_assign_equation(unsigned char);
void calc_char_to_int(unsigned char);
void calc_evaluate_opearand(unsigned char*);
void calc_evaluate_result( int, int);
void calc_send_result( int);


#endif /* CALCULATOR_H_ */