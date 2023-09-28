/*
 * fifo.c
 *
 *  Created on: Sep 20, 2023
 *      Author: ahmed
 */

#include "Fifo.h"
#include <stdarg.h>

Fifo_status_t Fifo_init(Fifo_Buffer*p,void*address,int length)
{
	if(address == null)
		return Fifo_null;
	p->base = address;
	p->head = address;
	p->tail = address;
	p->count =0;
	p->length = length;
	return Fifo_no_error;
}
Fifo_status_t Fifo_add_item(Fifo_Buffer*p,data_type x,...)
{
	if(p->base == null)
		return Fifo_null;
	if(p->count == p->length)
		return Fifo_full;
	va_list args;
	va_start(args,1);
	switch(x)
	{

	case uint8 :
		*((unsigned char*)p->head) = va_arg(args,unsigned char*);
		p->head = (unsigned char*)p->head +1;
		p->count ++;
		break;
	case uint16 :
		*((unsigned short*)p->head) = va_arg(args,unsigned short*);
		p->head = (unsigned short*)p->head +1;
		p->count ++;
		break;
	case uint32 :
		*((unsigned int*)p->head) = va_arg(args,int);
		p->head = (unsigned int*)p->head +1;
		p->count ++;
		break;
	case uint64 :
		*((unsigned long long*)p->head) = va_arg(args,unsigned long long);
		p->head = (unsigned long long*)p->head +1;
		p->count ++;
		break;
	case sint8 :
		*((char*)p->head) = va_arg(args,char*);
		p->head = (char*)p->head +1;
		p->count ++;
		break;
	case sint16 :
		*((short*)p->head) = va_arg(args,short*);
		p->head = (short*)p->head +1;
		p->count ++;
		break;
	case sint32 :
		*((int*)p->head) = va_arg(args,int);
		p->head = (int*)p->head +1;
		p->count ++;
		break;
	case sint64 :
		*((long long*)p->head) = va_arg(args,long long);
		p->head = (long long*)p->head +1;
		p->count ++;
		break;
	case float32 :
		*((float*)p->head) = va_arg(args,double);
		p->head = (float*)p->head +1;
		p->count ++;
		break;
	case float64 :
		*((double*)p->head) = va_arg(args,double);
		p->head = (double*)p->head +1;
		p->count ++;
		break;
	default :
		break;
	}
	return Fifo_no_error;
}
Fifo_status_t Fifo_get_item(Fifo_Buffer*p,data_type x)
{
	if(p->base == null)
		return Fifo_null;
	if(p->count == 0)
		return Fifo_empty;
	switch(x)
	{

	case uint8 :
		if((unsigned char*)p->tail - (unsigned char*)p->base == p->length-1)
		{
			printf("%d\n",*((unsigned char*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((unsigned char*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (unsigned char*)p->tail +1;
		break;
	case uint16 :
		if((unsigned short*)p->tail - (unsigned short*)p->base == p->length-1)
		{
			printf("%d\n",*((unsigned short*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((unsigned short*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (unsigned short*)p->tail +1;
		break;
	case uint32 :
		if((unsigned int*)p->tail - (unsigned int*)p->base == p->length-1)
		{
			printf("%d\n",*((unsigned int*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((unsigned int*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (unsigned int*)p->tail +1;
		break;
	case uint64 :
		if((unsigned long long*)p->tail - (unsigned long long*)p->base == p->length-1)
		{
			printf("%d\n",*((unsigned long long*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((unsigned long long*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (unsigned long long*)p->tail +1;
		break;
	case sint8 :
		if((char*)p->tail - (char*)p->base == p->length-1)
		{
			printf("%d\n",*((char*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((char*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (char*)p->tail +1;
		break;
	case sint16 :
		if((short*)p->tail - (short*)p->base == p->length-1)
		{
			printf("%d\n",*((short*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((short*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (short*)p->tail +1;
		break;
	case sint32 :
		if((int*)p->tail - (int*)p->base == p->length-1)
		{
			printf("%d\n",*((int*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((int*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (int*)p->tail +1;
		break;
	case sint64 :
		if((long long*)p->tail - (long long*)p->base == p->length-1)
		{
			printf("%d\n",*((long long*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((long long*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (long long*)p->tail +1;
		break;
	case float32 :
		if((float*)p->tail - (float*)p->base == p->length-1)
		{
			printf("%d\n",*((float*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((float*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (float*)p->tail +1;
		break;
	case float64 :
		if((double*)p->tail - (double*)p->base == p->length-1)
		{
			printf("%d\n",*((double*)p->tail));
			p->tail = (p->base);
			p->count--;
			break;
		}
		printf("%d\n",*((double*)p->tail));
		if(p->count == p->length)
			p->head = p->base;
		p->count--;
		p->tail = (double*)p->tail +1;
		break;
	default :
		break;
	}
	return Fifo_no_error;
}
Fifo_status_t Fifo_status(Fifo_Buffer*p)
{
	if(p->count == 0)
		return Fifo_empty;
	if(p->base == null)
		return Fifo_null;
	if(p->count == p->length)
		return Fifo_full;
	return Fifo_no_error;
}

void Fifo_print(Fifo_Buffer*p,data_type x)
{
	if(Fifo_status(p) == Fifo_empty)
		printf("Fifo is empty \n");
	else if(Fifo_status(p) == Fifo_null)
		printf("Fifo does not Exist \n");
	else
	{
		int i;
		int j=0;
		for(i=0; i<p->count; i++)
		{
			switch(x)
			{
			case uint8 :
               if( ( ( (unsigned char*)p->tail+i ) - (unsigned char*)p->base) >=  p->length )
               {
            	   printf("%d\n",*( (unsigned char*)p->base +j));
            	   j++;
            	   break;
               }
        	   printf("%d\n",*( (unsigned char*)p->tail +i));
        	   break;
			case uint16 :
	               if( ( ( (unsigned short*)p->tail+i ) - (unsigned short*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (unsigned short*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (unsigned short*)p->tail +i));
	        	   break;
			case uint32 :
	               if( ( ( (unsigned int*)p->tail+i ) - (unsigned int*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (unsigned int*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (unsigned int*)p->tail +i));
	        	   break;
			case uint64 :
	               if( ( ( (unsigned long long*)p->tail+i ) - (unsigned long long*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (unsigned long long*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (unsigned long long*)p->tail +i));
	        	   break;
			case sint8 :
	               if( ( ( (char*)p->tail+i ) - (char*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (char*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (char*)p->tail +i));
	        	   break;
			case sint16 :
	               if( ( ( (short*)p->tail+i ) - (short*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (short*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (short*)p->tail +i));
	        	   break;
			case sint32 :
	               if( ( ( (int*)p->tail+i ) - (int*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (int*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (int*)p->tail +i));
	        	   break;
			case sint64 :
	               if( ( ( (long long*)p->tail+i ) - (long long*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (long long*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (long long*)p->tail +i));
	        	   break;
			case float32 :
	               if( ( ( (float*)p->tail+i ) - (float*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (float*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (float*)p->tail +i));
	        	   break;
			case float64 :
	               if( ( ( (double*)p->tail+i ) - (double*)p->base) >=  p->length )
	               {
	            	   printf("%d\n",*( (double*)p->base +j));
	            	   j++;
	            	   break;
	               }
	        	   printf("%d\n",*( (double*)p->tail +i));
	        	   break;
			default :
				break;
			}
		}
	}
}


