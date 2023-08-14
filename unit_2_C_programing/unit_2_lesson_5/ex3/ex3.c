/*
 ============================================================================
 Name        : ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c program to reverse a sentence using recursion
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char x[],int y);
int main(void) {
	char s[100];
	printf("Enter a sentence : ");
	fflush(stdin); fflush(stdout);
    gets(s);
	fflush(stdin); fflush(stdout);
	reverse(s,strlen(s));
}
void reverse(char x[],int y)
{
	if(y>0)
	{
		putchar(x[y-1]);
		reverse(x,(y-1));
	}

	}
