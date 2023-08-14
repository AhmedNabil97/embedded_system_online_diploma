/*
 ============================================================================
 Name        : ex1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c code to make function return prime number within interval of 2 numbers.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void prime_numbers(int x,int y)
{
	printf("prime numbers between %d & %d are : ",x,y);
	int i;
	int j;
	int check;
	if(x<=0 || x==1 )
		x=2;
	for(i=x; i<=y; i++)
	{
		if(i==2)
		{
			printf("%d ",i);
			continue;
		}
		for(j=2; j<i; j++)
		{
			check=0;
			if(i%j==0)
				break;
			else
				check=1;
		}
		if (check==1)
		{
			printf("%d ",i);
		}
	}

}

int main(void) {

	     int x,y;
	     printf("Enter tow number (intervals ) : ");
	     fflush(stdin); fflush(stdout);
	     scanf("%d %d",&x,&y);
	     prime_numbers(x,y);



}

