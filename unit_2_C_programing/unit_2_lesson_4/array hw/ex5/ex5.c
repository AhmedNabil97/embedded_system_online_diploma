/*
 ============================================================================
 Name        : ex5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
// c code to search an element in array
int main(void) {

	int list[100];
	int n;
	int search;
	int i;
	int ref=0;
	printf("Enter the number of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=0; i<n; i++)
	{
		list[i]=(i+1)*11;
		printf("%d\t",list[i]);
	}
	printf("\nEnter the number to be searched : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&search);
	for(i=0; i<n; i++)
	{
		if (list[i]==search)
		{
			ref=i+1;
			printf("number found at location : %d",ref);
			break;
		}
	}
	if(ref==0)
	{
		printf("the number u are searching for doesn't exist in this list");
	}

}
