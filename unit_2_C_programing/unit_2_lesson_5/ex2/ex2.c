/*
 ============================================================================
 Name        : ex2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c function to calculate factorial of number using recursion
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int factorial(int x)
{
	static int r=1;
	if (x>0)
		{
		 r*=x;
		 factorial(x-1);
		}
	return r;
	}
int main(void) {

	int x;
	printf("Enter a postive integer number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	fflush(stdin); fflush(stdout);
	printf("factorial of %d = %d ",x,factorial(x));
}
