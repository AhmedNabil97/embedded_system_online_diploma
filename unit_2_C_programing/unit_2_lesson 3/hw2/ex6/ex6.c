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
//c program to calculate the sum of numbers from 1 to n

int main(void) {
	int n;
	int sum=0;
	int i;
	printf("Enter number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=1; i<=n; i++)
	{
		sum+=i;
	}

	printf("the sum from 1 to %d = %d",n,sum);

}
