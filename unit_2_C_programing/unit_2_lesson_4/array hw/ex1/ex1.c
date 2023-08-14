/*
 ============================================================================
 Name        : ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
// c code to calculate the sum of tow matrices Entered by the user 
int main(void) {
	float matrix1 [2][2];
	float matrix2 [2][2];
	float sum [2][2];
	printf("Enter the elements of the first matrix as follow : \n");
	int i,j;
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("Enter a%d%d : ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&matrix1[i][j]);
		}
	}
	printf("Enter the elements of the second matrix as follow : \n");

	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			printf("Enter b%d%d : ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&matrix2[i][j]);
		}
	}
	printf("sum of tow matrices = \n");
	for(i=0; i<2; i++)
	{
		for(j=0; j<2; j++)
		{
			sum[i][j] = matrix1[i][j]+matrix2[i][j];
			printf("%f\t",sum[i][j]);
		}
		printf("\n");
	}


}
