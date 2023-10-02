/*
 * Fifo.h
 *
 *  Created on: Sep 20, 2023
 *      Author: ahmed
 */

#ifndef FIFO_H_
#define FIFO_H_

#define Null (void*)0
#define null (void*)0


typedef enum {
	uint8,uint16,uint32,uint64,sint8,sint16,sint32,sint64,float32,float64
}data_type;

typedef struct
{
	void*base;
	void*head;
	void*tail;
	unsigned int count;
	unsigned int length;
}Fifo_Buffer;

typedef enum

{
	Fifo_no_error
	, Fifo_full
	, Fifo_empty
	, Fifo_null
}Fifo_status_t;

Fifo_status_t Fifo_init(Fifo_Buffer*,void*,int);
Fifo_status_t Fifo_add_item(Fifo_Buffer*,data_type,...);
Fifo_status_t Fifo_get_item(Fifo_Buffer*,data_type);
Fifo_status_t Fifo_status(Fifo_Buffer*);
void Fifo_print(Fifo_Buffer*,data_type);


#endif /* FIFO_H_ */
