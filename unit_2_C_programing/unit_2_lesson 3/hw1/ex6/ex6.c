/*
 ============================================================================
 Name        : ex6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	float a,b,exchange;
	printf("Enter the value of a : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&a);
	printf("Enter the value of b : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&b);
    exchange=a;
    a=b;
    b=exchange;
    printf("\nAfter swaping value of a = %f",a);
    printf("\nAfter swaping value of b = %f",b);


}
