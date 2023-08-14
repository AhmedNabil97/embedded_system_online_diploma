/*
 ============================================================================
 Name        : ex5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//c code to check if character is alphabet or not

#include <stdio.h>
#include <stdlib.h>


int main(void) {

	char c;
	printf("Enter the character u want to check : ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	if( (c>=65 & c<=90) || (c>=97 & c<=122) )
	{
		printf("%c is an alphabet",c);
	}
	else
		printf("%c is not alphabet",c);

}
