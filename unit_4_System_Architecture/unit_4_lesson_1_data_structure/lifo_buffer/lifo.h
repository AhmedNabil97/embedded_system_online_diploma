
/*
 * lifo.h
 *
 *  Created on: Sep 18, 2023
 *      Author: ahmed
 */

#ifndef LIFO_H_
#define LIFO_H_
#define Null (void*)0
#define null (void*)0


typedef struct
{
	unsigned int length;
	void* base;                                            //buffer elements
	void* head;
	unsigned int count;
	}Lifo_Buff_t;

typedef enum
{
Char,Short,Int,Float,Double,Long    // this will be defined by user to allow buffer for various data types
}data_type;

typedef enum
{
    lifo_no_error,lifo_full,lifo_empty,lifo_Null

	}Lifo_status_t;

Lifo_status_t Lifo_add_item(Lifo_Buff_t*,data_type,...);
Lifo_status_t Lifo_get_item(Lifo_Buff_t*,data_type,int);
Lifo_status_t Lifo_pop_item(Lifo_Buff_t*,data_type);
Lifo_status_t Lifo_init(Lifo_Buff_t*,void*,int);



#endif /* LIFO_H_ */


