/*
 ============================================================================
 Name        : Fifo_Buffer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Fifo.h"


int buff1[5];
int main(void) {

	Fifo_Buffer uart;
	Fifo_init(&uart,buff1,5);                                            //intializing buffer
	Fifo_add_item(&uart,sint32,10);
	Fifo_add_item(&uart,sint32,20);
	Fifo_add_item(&uart,sint32,30);
	Fifo_add_item(&uart,sint32,40);
	Fifo_add_item(&uart,sint32,50);
   Fifo_get_item(&uart,sint32);
   Fifo_get_item(&uart,sint32);
   Fifo_get_item(&uart,sint32);
   printf("***************\n");
   Fifo_add_item(&uart,sint32,22);
   Fifo_add_item(&uart,sint32,6);
   Fifo_print(&uart,sint32);
}
