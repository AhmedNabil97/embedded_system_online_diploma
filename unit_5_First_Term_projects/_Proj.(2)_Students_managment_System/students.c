/*
 * students.c
 *
 *  Created on: 23/10/2023
 *      Author: ahmed nabil
 */

#include "students.h"
int i;


void queue_init()
{
	student_queue.count = 0;
	student_queue.length = 50;
	student_queue.base = st;
	student_queue.head = st;
	fifo_status_t = fifo_empty;
}


void add_student_file()
{
	//check if queue is full or not
	if(student_queue.length == student_queue.count)
	{
		printf("[Error] : list is full\n");
		return;
	}

	//open file
	fpointer = fopen("students.txt","r");

	// Check if the file exist ]
	if(fpointer == NULL)
	{
		printf("\n [ERROR] student.txt file not found. \n");
		fifo_status_t = fifo_null;
		return;
	}

	// Reading data until the end of the file
	ll:	while(! feof(fpointer) )
	{
		if(fifo_status_t == fifo_empty)                              //adding 1st element
		{
			fscanf(fpointer,"%d",&student_queue.head->roll_number);
			fscanf(fpointer,"%s",student_queue.head->first_name);
			fscanf(fpointer,"%s",student_queue.head->last_name);
			fscanf(fpointer,"%f",&student_queue.head->gpa);
			for(i=0; i<5; i++)
			{
				fscanf(fpointer,"%d",&student_queue.head->cid[i]);

			}
			printf("[INFO] roll number %d is added successfully\n",student_queue.head->roll_number);
			fifo_status_t = fifo_not_empty;
			student_queue.count ++;
			student_queue.head ++;
		}
		fscanf(fpointer,"%d",&student_queue.head->roll_number);
		for(i=0; i<student_queue.count; i++)
		{
			//checking if roll number is taken before
			if(student_queue.head->roll_number == (student_queue.base + i)->roll_number)
			{
				printf("[Error] roll number %d is already taken\n",student_queue.head->roll_number);
				fscanf(fpointer, "%*[^\n]");                 //ignore the rest of line
				goto ll;
			}
			fscanf(fpointer,"%s",student_queue.head->first_name);
			fscanf(fpointer,"%s",student_queue.head->last_name);
			fscanf(fpointer,"%f",&student_queue.head->gpa);
			for(i=0; i<5; i++)
			{
				fscanf(fpointer,"%d",&student_queue.head->cid[i]);

			}
			printf("[INFO] roll number %d is added successfully\n",student_queue.head->roll_number);
			fifo_status_t = fifo_not_empty;
			student_queue.count ++;
			student_queue.head ++;
			if(student_queue.count == student_queue.length)
			{
				fifo_status_t = fifo_full;
				student_queue.head --;


			}
		}

	}
	//close the file
	fclose(fpointer);
	printf("[INFO] total number of students : %d\n",student_queue.count);
	printf("[INFO] you can add up to %d students\n",50);
	printf("[INFO] you can add more %d students\n",50-student_queue.count);
	printf("----------------------------------------\n");

}

void add_student_manually()
{
	//check if queue is full or not
	if(student_queue.length == student_queue.count)
	{
		printf("[Error] : list is full\n");
		return;
	}
	if(fifo_status_t == fifo_empty)                              //adding 1st element
	{
		printf("Enter student roll number : ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&student_queue.head->roll_number);
		printf("Enter student first name : ");
		fflush(stdin); fflush(stdout);
		scanf("%s",student_queue.head->first_name);
		printf("Enter student last name : ");
		fflush(stdin); fflush(stdout);
		scanf("%s",student_queue.head->last_name);
		printf("Enter student GPA : ");
		fflush(stdin); fflush(stdout);
		scanf("%f",&student_queue.head->gpa);
		printf("Enter students courses id : ");
		fflush(stdin); fflush(stdout);
		for(i=0; i<5; i++)
		{
			scanf("%d",&student_queue.head->cid[i]);

		}
		printf("[INFO] student of roll number : %d is added successfully\n",student_queue.head->roll_number);
		printf("----------------------------------------\n");
		fifo_status_t = fifo_not_empty;
		student_queue.count ++;
		student_queue.head ++;
	}
	printf("Enter student roll number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&student_queue.head->roll_number);
	//checking if roll number is taken before
	for(i=0; i<student_queue.count; i++)
	{
		if(student_queue.head->roll_number == (student_queue.base + i)->roll_number)
		{
			printf("[Error] roll number %d is already taken\n",student_queue.head->roll_number);
			printf("----------------------------------------\n");
			return;
		}
	}
	printf("Enter student first name : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",student_queue.head->first_name);
	printf("Enter student last name : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",student_queue.head->last_name);
	printf("Enter student GPA : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&student_queue.head->gpa);
	printf("Enter the course id for each course :- \n");
	for(i=0; i<5; i++)
	{
		printf("for course %d id : ",i+1);
		fflush(stdin); fflush(stdout);
		scanf("%d",&student_queue.head->cid[i]);

	}
	printf("[INFO] student of roll number : %d is added successfully\n",student_queue.head->roll_number);
	printf("----------------------------------------\n");
	fifo_status_t = fifo_not_empty;
	student_queue.count ++;
	student_queue.head ++;
	printf("[INFO] total number of students : %d\n",student_queue.count);
	printf("[INFO] you can add up to %d students\n",50);
	printf("[INFO] you can add more %d students\n",50-student_queue.count);
	printf("----------------------------------------\n");

	if(student_queue.count == student_queue.length)
	{
		fifo_status_t = fifo_full;
		student_queue.head --;
	}


}

void find_rl()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		printf("----------------------------------------\n");
		return;
	}
	int roll,j;
	char flag =0;
	printf("Enter the roll number of student u want to view : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&roll);
	for(i=0; i<student_queue.count; i++)
	{
		if( (student_queue.base + i)->roll_number == roll)
		{
			printf("for student of roll number : %d\n",(student_queue.base + i)->roll_number);
			printf("student first name : %s\n",(student_queue.base + i)->first_name);
			printf("student last name : %s\n",(student_queue.base + i)->last_name);
			printf("student GPA : %.2f\n",(student_queue.base + i)->gpa);
			printf("students courses id : ");
			for(j=0; j<5; j++)
			{
				printf("%d ",(student_queue.base + i)->cid[j]);
			}
			flag =1;
			printf("\n");
			break;
		}
	}
	if(flag ==0 )
		printf("[Error] the roll number u Entered does not exist.\n");
	printf("----------------------------------------\n");

}

void find_fn()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		return;
	}
	int j;
	char flag =0;
	char name[50];
	printf("Enter the first name of student u want to view : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",name);
	for(i=0; i<student_queue.count; i++)
	{
		if( ! stricmp( (student_queue.base + i)->first_name , name) )
		{
			printf("for student of first name : %s\n",(student_queue.base + i)->first_name);
			printf("student roll number : %d\n",(student_queue.base + i)->roll_number);
			printf("student first name : %s\n",(student_queue.base + i)->first_name);
			printf("student last name : %s\n",(student_queue.base + i)->last_name);
			printf("student GPA : %.2f\n",(student_queue.base + i)->gpa);
			printf("students courses id : ");
			for(j=0; j<5; j++)
			{
				printf("%d ",(student_queue.base + i)->cid[j]);
			}
			printf("\n");
			flag =1;
		}
	}
	if(flag ==0 )
		printf("[Error] the first name u Entered does not exist.\n");
	printf("----------------------------------------\n");
}

void find_c()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		return;
	}
	int course_id,j;
	char counter =0;
	char flag =0;

	printf("Enter the course id  : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&course_id);
	for(i=0; i<student_queue.count; i++)
	{
		for(j=0; j<5; j++)
		{
			if( (student_queue.base+i)->cid[j] == course_id )
			{
				counter++;
				flag = 1;
				printf("the student details are :-\n");
				printf("student roll number : %d\n",(student_queue.base + i)->roll_number);
				printf("student first name : %s\n",(student_queue.base + i)->first_name);
				printf("student last name : %s\n",(student_queue.base + i)->last_name);
				printf("student GPA : %.2f\n",(student_queue.base + i)->gpa);
				printf("----------------------------------------\n");
			}
		}
	}
	if(flag ==0 )
		printf("[Error] the course id you Entered does not exist.\n");
	else
		printf("[INFO] total number of students in this course = %d\n",counter);
	printf("----------------------------------------\n");

}

void tot_s()

{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		return;
	}
	printf("[INFO] total number of students : %d\n",student_queue.count);
	printf("[INFO] you can add up to %d students\n",50);
	printf("[INFO] you can add more %d students\n",50-student_queue.count);
	printf("----------------------------------------\n");


}

void del_s()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		return;
	}
	int roll,j;
	char flag=0;
	printf("Enter the roll number of student you want to delete : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&roll);
	for(i=0; i<student_queue.count; i++)
	{
		if (  (student_queue.base + i)->roll_number == roll )
		{
			for(j=i; j<=(student_queue.count-i); j++)
			{

				if(j == student_queue.length-1)
				{
					student_queue.base[j].roll_number = 0;
					break;
				}
				student_queue.base[j] = student_queue.base[j+1];

			}
			student_queue.count--;
			flag =1;
		}
	}
	if(!flag)
		printf("[Error] the roll number you Entered does not Exist\n");
	else
	{
		printf("the student of roll number %d is deleted successfully\n",roll);
		printf("[INFO] total number of students : %d\n",student_queue.count);
		printf("[INFO] you can add up to %d students\n",50);
		printf("[INFO] you can add more %d students\n",50-student_queue.count);
	}
	printf("----------------------------------------\n");

}

void up_s()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		printf("----------------------------------------\n");
		return;
	}
	int roll,options,j,new_roll,z;
	char flag=0;
	printf("Enter the roll number to update the Entry : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&roll);
	for(i=0; i<student_queue.count; i++)
	{
		if ( (student_queue.base + i)->roll_number == roll )
		{
			flag =1;
			printf("1. First name : \n");
			printf("2. last name : \n");
			printf("3. roll number : \n");
			printf("4. GPA : \n");
			printf("5. courses : \n");
			ll: printf("Enter your choice : ");
			fflush(stdin); fflush(stdout);
			scanf("%d",&options);
			switch(options)
			{
			case 1 :
				printf("new first name : ");
				fflush(stdin); fflush(stdout);
				scanf("%s", (student_queue.base+i)->first_name);
				break;
			case 2 :
				printf("new first name : ");
				fflush(stdin); fflush(stdout);
				scanf("%s", (student_queue.base+i)->last_name);
				break;
			case 3 :
				printf("Enter new roll number : ");
				aa:	fflush(stdin); fflush(stdout);
				scanf("%d", &new_roll);
				for(z=0; z<student_queue.count; z++)
				{
					if ( (student_queue.base+z)->roll_number == new_roll )
					{
						printf("[Error] this roll number is already taken\n");
						printf("please Enter a valid roll number : ");
						goto aa;
					}

				}
				(student_queue.base+i)->roll_number =  new_roll;
				break;
			case 4 :
				printf("new GPA : ");
				fflush(stdin); fflush(stdout);
				scanf("%f", & ((student_queue.base+i)->gpa));
				break;
			case 5 :
				for(j=0; j<5; j++)
				{
					printf("for course %d id : ",j+1);
					fflush(stdin); fflush(stdout);
					scanf("%d",&student_queue.head->cid[j]);
				}
				break;
			default :
				printf("[Error] : Enter correct number : ");
				goto ll;
				break;
			}
		}

	}
	if(flag)
		printf("[INFO] updated successfully\n");
	else
		printf("[ERROR] the roll number u Entered does not exist\n");
	printf("----------------------------------------\n");
}

void show_s()
{
	if(fifo_status_t == fifo_empty)         // check if list is empty
	{
		printf("the list is empty there is no informations to show.\n");
		return;
	}
	int j;
	printf("----------------------------------------\n");

	for(i=0; i<student_queue.count; i++)
	{
		printf("student roll number : %d\n",(student_queue.base + i)->roll_number);
		printf("student first name : %s\n",(student_queue.base + i)->first_name);
		printf("student last name : %s\n",(student_queue.base + i)->last_name);
		printf("student GPA : %.2f\n",(student_queue.base + i)->gpa);
		printf("student courses id : ");
		for(j=0; j<5; j++)
		{
			printf("%d ",(student_queue.base+i)->cid[j]);
		}
		printf("\n----------------------------------------\n");
	}
	printf("[INFO] total number of students : %d\n",student_queue.count);
	printf("[INFO] you can add up to %d students\n",50);
	printf("[INFO] you can add more %d students\n",50-student_queue.count);
	printf("----------------------------------------\n");

}


