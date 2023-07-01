/*
 ============================================================================
 Name        : ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	printf("Enter the integer u want to check : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	if(n%2==0)
		printf("%d is Even ",n);
	else
		printf("%d is odd ",n);
}
