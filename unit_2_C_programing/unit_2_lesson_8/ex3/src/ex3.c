/*
 ============================================================================
 Name        : ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : C program to print a stirng in reverse using pointer
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
	char x[50];
	char*p;
	int i;
	printf("Enter string u want to reverse : ");
	fflush(stdin); fflush(stdout);
	gets(x);
	p=&x[strlen(x)];
	printf("Reverse of string is : ");
	for(i=strlen(x); i>0; i--)
	{
		printf("%c",*--p);
	}
}
