/*
 ============================================================================
 Name        : ex2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c code to add 2 distance in foot/inch sys using struct
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Sfeet_sys
{
	float feet;
	float inch;
};

struct Sfeet_sys add_dist(struct Sfeet_sys,struct Sfeet_sys);

int main(void)
{
	struct Sfeet_sys x1,x2,result;
	printf("Enter first distance :-\n");
	printf("Enter feet : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x1.feet);
	printf("Enter inch : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x1.inch);
	printf("Enter second distance :-\n");
	printf("Enter feet : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x2.feet);
	printf("Enter inch : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x2.inch);
    result = add_dist(x1,x2);
    printf("\n");
    printf("sum of distances = %.1f' - %.1f\"",result.feet,result.inch);


}
struct Sfeet_sys add_dist(struct Sfeet_sys x,struct Sfeet_sys y)
{
	struct Sfeet_sys z;
	z.feet=x.feet+y.feet;
	z.inch=x.inch+y.inch;
	if(z.inch==12)
	{
		z.inch=0;
		z.feet++;
	}
	if(z.inch>12)
	{
		z.inch-=12;
		z.feet++;
	}
	return z;
	}
