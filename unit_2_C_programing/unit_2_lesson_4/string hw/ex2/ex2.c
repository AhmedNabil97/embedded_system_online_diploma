/*
 ============================================================================
 Name        : ex2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
// strlen. function manually

int main(void) {
	char string [100];
	int counter=0;
	printf("Enter a string : ");
	fflush(stdin); fflush(stdout);
	gets(string);
	while(string[counter]!=0)
	{
		counter++;
	}
	printf("length of string = %d",counter);
}
