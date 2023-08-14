/*
 ============================================================================
 Name        : ex4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c program to reverse the elements of array using pointers
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x[15];
	int n,i;
	int*p=x;
	printf("Enter the number of elements to store in the array max(15) : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	p+=n;
	for(i=0; i<n; i++)
	{
		printf("element -%d : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&x[i]);
	}
	printf("\nthe elements of array in reverse order are : \n");
	for(i=n; i>0; i--)
	{
		printf("element -%d : %d\n",i,*--p);
	}

}
