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
// c code to calculate the avg of numbers Entered by the user
int main(void) {

	float numbers [100];
	float sum=0.0;
	float avg;
	int n;
	int i;
	printf("Enter the number of data : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	for(i=0; i<n; i++)
	{
		printf("%d. Enter number : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&numbers[i]);
		sum+=numbers[i];
	}
	avg = sum/n;
	printf("average = %.2f",avg);
}
