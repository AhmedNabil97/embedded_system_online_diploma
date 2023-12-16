/*
 ============================================================================
 Name        : student_mangment_system.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "students.h"

int main(void) {
    int choice;
	void(*options[9])() =                                       //array of pointers to function
	{
			 add_student_manually,
			 add_student_file,
			 find_rl,
			 find_fn,
			 find_c,
			 tot_s,
			 del_s,
			 up_s,
			 show_s
	};
	queue_init();
	printf("{{ Welcome to student Management system }}\n");
	
	while(1)	
	{
	printf("choose the task that u want to perform :- \n");
	printf("1. add the students details manually. \n");
	printf("2. add the students details from text file. \n");
	printf("3. find the student details by roll number. \n");
	printf("4. find the student details by first name. \n");
	printf("5. find the student details by course id. \n");
	printf("6. find the total number of students. \n");
	printf("7. delete the student details by roll number. \n");
	printf("8. update the student details by roll number. \n");
	printf("9. show all informations. \n");
	printf("10. Exit\n");
	printf("Enter your choice to perform the task : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&choice);
    if(choice == 10)
    	break;
    else
    options[choice -1]();
	}

	}
