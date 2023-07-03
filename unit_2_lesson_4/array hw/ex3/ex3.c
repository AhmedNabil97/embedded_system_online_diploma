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
// c code outs the transpose of matrix Entered by the user who specify the demensions too
int main(void) {

	int row,column;
	int i,j;
	float matrix[10][10];
	printf("Enter rows & columns of the matrix : ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&row,&column);
	printf("Enter the Elements the matrix as follow : \n");
	for(i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			printf("Enter element a%d%d : ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&matrix[i][j]);
		}
	}
	printf("the Entered matrix = \n");
	for(i=0; i<row; i++)
	{
		for(j=0; j<column; j++)
		{
			printf("%.2f\t",matrix[i][j]);
		}
		printf("\n");

	}
	printf("the transpose of the entered matrix = \n");
	for(i=0; i<column; i++)
	{
		for(j=0; j<row; j++)
		{
			printf("%.2f\t",matrix[j][i]);
		}
		printf("\n");
	}




}
