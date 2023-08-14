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

int main(void) {
	char*p="A";
	int i;
	for(i=0; i<26; i++)
	{
		printf("%c\t",*p+i);

	}
}
