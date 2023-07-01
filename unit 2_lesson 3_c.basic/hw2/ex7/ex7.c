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
// c program to calculate factorial of a number

int main(void) {
	int n;
	int factorial=1;
	int i;
	printf("Enter a number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	if(n<0)
	{
		printf("Error!!! factorial of negative number doesn't exist ");
	}
	else if(n==0)
	{

		printf("factorial 0 = %d ",factorial);

	}
	else
	{
		for(i=1; i<=n; i++)
		{
			factorial*=i;
		}
		printf("factorial %d = %d ",n,factorial);

	}

}

