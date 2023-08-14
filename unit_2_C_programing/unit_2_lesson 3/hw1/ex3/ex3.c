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

int main(void) {

	int x1,x2,sum;
	printf("Enter tow integers : ");
	fflush(stdin); 	fflush(stdout);
	scanf("%d %d",&x1,&x2);
	sum=x1+x2;
	printf("sum = %d",sum);

}
