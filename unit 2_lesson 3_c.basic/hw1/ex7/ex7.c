/*
 ============================================================================
 Name        : ex7.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int x;
	int y;
	printf("Enter the value of x  : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf("Enter the value of y  : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&y);
	x=x+y;
	y=x-y;
	x=x-y;
	printf("\nthe value of x after swaping :%d ",x);
	printf("\nthe value of y after swaping :%d ",y);


}
