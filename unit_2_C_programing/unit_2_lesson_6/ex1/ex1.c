/*
 ============================================================================
 Name        : sdsDAS.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : c code that allow user to store student data using structure
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
struct Sstudents
{
	char name[100];
	int roll_number;
	float marks;
};
int main(void) {
	struct Sstudents s;
	printf("Enter information of students : \n\n");
	printf("Enter the name : ");
	fflush(stdin); fflush(stdout);
	gets(s.name);
	printf("Enter the roll number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s.roll_number);
	printf("Enter marks : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&s.marks);
	printf("\n\n");
	printf("displaying information");
	printf("\n");
	printf("student Name : %s\n",s.name);
	printf("student roll number  : %d\n",s.roll_number);
	printf("student mark : %.2f\n",s.marks);
}

