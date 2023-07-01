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

	float n;
	printf("Enter the number u want to check : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&n);
	if(n>0)
	{
		printf("%f is a postive number",n);

	}
	else if(n<0)
	{
		printf("%f is a negative number",n);
	}
	else
		printf("%f is neutral (zero)",n);


}
