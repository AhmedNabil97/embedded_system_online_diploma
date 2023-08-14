/*
 ============================================================================
 Name        : ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : a c program to demonstrate how to handle the pointers in the program
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int m=29;
	printf("address of m : 0x%p \n",&m);
	printf("value of m : %d \n",m);
	int*ab=&m;
	printf("\nnow ab is assigned with the address of m.\n");
	printf("address of pointer ab : 0x%p \n",&ab);
	printf("content of pointer ab: %d \n",*ab);
	m=34;
	printf("\nnow the value m is assigned to 34 now.\n");
	printf("address of pointer ab : 0x%p \n",&ab);
	printf("content of pointer ab: %d \n",*ab);
	*ab=7;
	printf("\nthe pointer ab is assigned with the value 7 now \n");
	printf("address of m : 0x%p \n",&m);
	printf("value of m : %d \n",m);

}
