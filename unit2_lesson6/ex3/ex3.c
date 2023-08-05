/*
 ============================================================================
 Name        : ex3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c code to add 2 complex numbers by passing struct to a function
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Scomplex
{
	float real;
	float imj;
};

struct Scomplex add_cmplx(struct Scomplex,struct Scomplex );

int main(void) {
	struct Scomplex x1,x2,sum;
	printf("for 1st complex number :\n ");
	printf("Enter real & imaginary respectively : ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&x1.real,&x1.imj);
	printf("for 2nd complex number :\n ");
	printf("Enter real & imaginary respectively : ");
	fflush(stdin); fflush(stdout);
	scanf("%f%f",&x2.real,&x2.imj);
	sum = add_cmplx(x1,x2);
	char*c;
	if(sum.imj<0)
		c="";
	else
		c="+";
	printf("sum = %.1f%s%.1fj",sum.real,c,sum.imj);
}
struct Scomplex add_cmplx(struct Scomplex x,struct Scomplex y )
{
	struct Scomplex z;
	z.real=x.real+y.real;
	z.imj=x.imj+y.imj;
	return z;

}
