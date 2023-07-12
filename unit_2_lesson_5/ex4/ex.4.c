/*
 ============================================================================
 Name        : 4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : power calculation using recursion
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int pow(int n,int deg);


int main(void)
{
	int x,y;
	printf("Enter base number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf("Enter power number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&y);
	printf("%d ^ %d = %d ",x,y,pow(x,y));
}
int pow(int n,int deg)
{
	while(deg>1)
		return n*pow(n,deg-1);
}
