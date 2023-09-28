/*
 ============================================================================
 Name        : Students_data_base.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Students.h"

int main()
{
	while(1)
	{

		int(*options[9])();                                          // array of pointers to functions 
		options[0] = &add_student;
		options[1] = &delete_student;
		options[2] = &view_all;
		options[3] = &delete_all;
		options[4] = &gets_node_of_index;
		options[5] = &count_number_of_nodes;
		options[6] = &gets_node_from_end;
		options[7] = &get_the_middle;
		options[8] = &reverse_list;
		unsigned int i;
		printf("choose one of the following options :-\n");
		printf("1. -> add student :\n");
		printf("2. -> delete student :\n");
		printf("3. -> view all students :\n");
		printf("4. -> delete all students :\n");
		printf("5. -> get student by index :\n");
		printf("6. -> get number of nodes in your list :\n");
		printf("7. -> get student by index from the end :\n");
		printf("8. -> get the middle of the list :\n");
		printf("9. -> reverse the list :\n");
		fflush(stdin); fflush(stdout);
		scanf("%u",&i);
		switch(i)                                                                     //switch on user choice which option he want
		{
		case 1:
			options[0]();
			break;
		case 2:
			options[1]();
			break;
		case 3:
			options[2]();
			break;
		case 4:
			options[3]();
			break;
		case 5:
			options[4]();
			break;
		case 6:
			options[5]();
			break;
		case 7:
			options[6]();
			break;
		case 8:
			options[7]();
			break;
		case 9:
			options[8]();
			break;

		default :
			printf("\nchoose correct option from 1 : 9\n");
			break;
		}
	}
}
