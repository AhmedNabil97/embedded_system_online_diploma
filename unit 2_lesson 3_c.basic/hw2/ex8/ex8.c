/*
 ============================================================================
 Name        : ex8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
// simple calculator program

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	char c;
	float x,y,result;
	printf("Enter an opertaor either (+,-,*,/) : ");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	printf("Enter tow operands : ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&x,&y);
	switch(c)
	{
	case'+':
		result = x+y;
		printf("%f %c %f = %f",x,c,y,result);
		break;
	case'-':
		result = x-y;
		printf("%f %c %f = %f",x,c,y,result);
		break;
	case'*':
		result = x*y;
		printf("%f %c %f = %f",x,c,y,result);
		break;
	case'/':
		result = x/y;
		printf("%f %c %f = %f",x,c,y,result);
		break;
	default:
		printf("error plz choose correct operator");
		break;
	}


}
