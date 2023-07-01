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

int main(void) {

	char x;
	printf("Enter character : ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&x);
	printf("ASCII VALUE OF %c : %d  ",x,x);

}
