/*
 ============================================================================
 Name        : ex4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x1,x2,product;
	printf("Enter tow numbers : ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&x1,&x2);
	product = x1*x2;
	printf("product : %f",product);

}
