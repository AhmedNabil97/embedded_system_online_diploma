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
// c code to insert an element in an array
int main(void) {
	int list[100];
	int n;
	int element;
	int location;
	int i;
	printf("Enter the number of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=0; i<n; i++)
	{
		list[i]=i+1;
		printf("%d\t",list[i]);
	}
	printf("\n");
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);
	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);
	for(i=n; i>=location; i--)
	{
		list[i]=list[i-1];
	}
	list[location-1]=element;
	for(i=0; i<n+1;i++)
	{
		printf("%d\t",list[i]);
	}

}
