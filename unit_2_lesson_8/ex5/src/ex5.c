/*
 ============================================================================
 Name        : ex5.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : C program to show a pointer to an array which contents is array of pointers to structure
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
struct employee
{
	char *name;
	int id;
};
int main(void)
{
	int i;
	struct employee arr[3]	;          // definition of array of struct
	struct employee (*Sp[3]);          // definition of array of pointers to struct
	for(i=0; i<3; i++)
	{
		Sp[i]=&arr[i];                 // assign addresses of each struct to an equivalent pointer
	}

	struct employee(*(*Ptr_arr)[]);     // definition to a pointer to array of pointers called Sp to struct
	Ptr_arr=&Sp;                        // assign address of array to the pointer

	(*Sp)->id=1002;                     //assign values to struct member using array of pointers
	(*Sp)->name="Alex";

	printf("name of employee 1 : %s\n",(*(*Ptr_arr))->name);   // access the members of struct using another way by pointer to array
	printf("id of employee 1 : %d\n",(*(*Ptr_arr))->id);

	(*(*(Ptr_arr)+1))->name="ahmed";                      // access the 2nd member of array of pointers through which we access the 2nd member
	(*(*(Ptr_arr)+1))->id=1300;                           // array of structure using ptr to array of pointers


	printf("name of employee 2 : %s\n",(*(Sp+1))->name); // access the 2nd member of array of pointers through which we access the 2nd member
	printf("id of employee 2 : %d\n",(*(Sp+1))->id);      // by using array of pointers to struct
}
