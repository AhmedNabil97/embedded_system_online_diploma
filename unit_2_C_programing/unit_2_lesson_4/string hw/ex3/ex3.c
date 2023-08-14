/*
 ============================================================================
 Name        : ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//c code to inverse string

int main(void) {
	char string[100];
	int i;
	int length;
	char temp;
	printf("Enter the string : ");
	fflush(stdin); fflush(stdout);
	gets(string);
	length = strlen(string);
   for(i=0; i<(length/2); i++)
	{
		temp=string[i];
		string[i]=string[length-i-1];
		string[length-1-i]=temp;
	}
	printf("reverse string is : %s",string);
}
