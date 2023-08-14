/*
 ============================================================================
 Name        : ex4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Sstudent
{
	int roll_number;
	char name[50];
	float mark;
};

int main(void)

{
	int i;
	printf("Enter information of students :-\n");
	struct Sstudent x[10];
	for(i=0; i<10; i++)
	{
		x[i].roll_number=i+1;
		printf("for roll number : %d\n",x[i].roll_number);  //data Entery
		printf("Enter Name : ");
		fflush(stdin); fflush(stdout);
		gets(x[i].name);
		printf("Enter marks : ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&x[i].mark);
		printf("\n");
	}
	printf("\ndisplaying students information :-\n");
	for(i=0; i<10; i++)
	{
		printf("information for roll number %d\n",x[i].roll_number);
		printf("name : %s\n",x[i].name);
		printf("marks : %f\n",x[i].mark);
	}

}
