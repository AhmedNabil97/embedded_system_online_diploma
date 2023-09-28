/*
 * lifo.c
 *
 *  Created on: Sep 28, 2023
 *      Author: ahmed
 */

/*
 * lifo.c
 *
 *  Created on: Sep 18, 2023
 *      Author: ahmed
 */
#include <stdarg.h>
#include "lifo.h"
Lifo_status_t Lifo_add_item(Lifo_Buff_t*p,data_type x,...)

{
	if(p->count == p->length)                         //check if lifo is full no items could be added
		return lifo_full;
	if(p->base == null)
		return lifo_empty;                            //check if lifo exists
	switch(x)
	{
	va_list args;
	case Char:
		va_start(args,1);
		*(char*)(p->head) = va_arg(args,char*);
		p->head = (char*)p->head +1;
		p->count++;
		break;
	case Short:
		va_start(args,1);
		*(short*)(p->head) = va_arg(args,short*);
		p->head = (short*)p->head +1;
		p->count++;
		break;
	case Int:
		va_start(args,1);
		*(int*)(p->head) = va_arg(args,int);
		p->head = (int*)p->head +1;
		p->count++;
		break;
	case Float:
		va_start(args,1);
		*(float*)(p->head) = va_arg(args,double);
		p->head = (float*)p->head +1;
		p->count++;
		break;
	case Double:
		va_start(args,1);
		*(double*)(p->head) = va_arg(args,double);
		p->head = (double*)p->head +1;
		p->count++;
		break;
	case Long:
		va_start(args,1);
		*(long long*)(p->head) = va_arg(args,long long);
		p->head = (long long*)p->head +1;
		p->count++;
		break;
	default :
		break;
	}

	return lifo_no_error;
}
Lifo_status_t Lifo_get_item(Lifo_Buff_t*p,data_type x,int index)
{
	if(p->base == p->head)
		return lifo_empty;
	if(p->base == null)
		return lifo_Null;
	switch(x)
	{
	case Char:
		printf("item no. %d : %c",index,*((char*)p->base+(index-1)));
		break;
	case Short:
		printf("item no. %d : %d",index,*((short*)p->base+(index-1)));
		break;
	case Int:
		printf("item no. %d : %d",index,*((int*)p->base+(index-1)));
		break;
	case Float:
		printf("item no. %d : %f",index,*((float*)p->base+(index-1)));
		break;
	case Double:
		printf("item no. %d : %lf",index,*((double*)p->base+(index-1)));
		break;
	case Long:
		printf("item no. %d : %u",index,*((long long*)p->base+(index-1)));
		break;
	default :
		break;
	}
	return lifo_no_error;
}

Lifo_status_t Lifo_pop_item(Lifo_Buff_t*p,data_type x)
{
	if(p->base == p->head)
		return lifo_empty;
	if(p->base == null)
		return lifo_Null;
	switch(x)
	{
	case Char:
		printf("last element : %c ",*((char*)p->head-1));
		p->count --;
		p->head = (char*)p->head -1;
		break;
	case Short:
		printf("last element : %d ",*((short*)p->head-1));
		p->count --;
		p->head = (short*)p->head -1;
		break;
	case Int:
		printf("last element : %d ",*((int*)p->head-1));
		p->count --;
		p->head = (int*)p->head -1;
		break;
	case Float:
		printf("last element : %f ",*((float*)p->head-1));
		p->count --;
		p->head = (float*)p->head -1;
		break;
	case Double:
		printf("last element : %lf ",*((double*)p->head-1));
		p->count --;
		p->head = (double*)p->head -1;
		break;
	case Long:
		printf("last element : %u ",*((long long*)p->head-1));
		p->count --;
		p->head = (long long*)p->head -1;
		break;
	default :
		break;
	}
	return lifo_no_error;

}
Lifo_status_t Lifo_init(Lifo_Buff_t*p,void*address,int length)
{
	if(address == null)
		return lifo_Null;
	p->base = address;
	p->head = p->base;
	p->length = length;
	p->count =0;
  return lifo_no_error;
}



