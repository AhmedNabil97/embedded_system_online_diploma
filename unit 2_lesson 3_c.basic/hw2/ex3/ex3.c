/*
 ============================================================================
 Name        : ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x,y,z;
	printf("Enter three numbers : ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&x,&y,&z);
	if(x>y && x>z)
	{
		printf("the largest number is : %f ",x);
	}
	else if (x<y && y>z)
	{
		printf("the largest number is : %f ",y);
	}
	else
		printf("the largest number is : %f ",z);

}
