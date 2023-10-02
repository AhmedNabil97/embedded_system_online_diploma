/*
 * Students.c
 *
 *  Created on: Sep 26, 2023
 *      Author: ahmed
 */

#include "Students.h"
struct Sstudents*Pt_head_list = null;                    //   head of the list is pointer to first node in list and null if list is emmpty
static unsigned int counter=0;                          //    global variable counter is to count number of nodes its value modifed during adding or deleting

int add_student()
{

	struct Sstudents* New_Student;
	if(Pt_head_list == null)                            //    check if heap space is available cause it may be full and malloc return null
	{
if(New_Student = (struct Sstudents*)malloc(sizeof(struct Sstudents)))    // check if heap space is available cause it may be full and malloc return null
		{
			printf("Enter Student Name : ");
			fflush(stdin); fflush(stdout);
			gets(New_Student->name);
			printf("Enter Student id : ");
			fflush(stdin); fflush(stdout);  
			scanf("%u",&(New_Student->id));
			printf("Enter Student height : ");
			fflush(stdin); fflush(stdout);
			scanf("%f",&(New_Student->height));
			Pt_head_list = New_Student;
			New_Student->Pnextstudent = null;
			counter++;                                                                          // modifying value of counter
			return 1;
		}
		else
		{
			printf("Error Heap is full\n");
			return 0;
		}

	}
	else
	{
		struct Sstudents* Pt_last_element = Pt_head_list;
		while(Pt_last_element->Pnextstudent)                                                        // loop to find last element in the list
		{
			Pt_last_element=Pt_last_element->Pnextstudent;
		}

		if(New_Student = (struct Sstudents*)malloc(sizeof(struct Sstudents)))
		{
			printf("Enter Student Name : ");
			fflush(stdin); fflush(stdout);
			gets(New_Student->name);
			printf("Enter Student id : ");
			fflush(stdin); fflush(stdout);
			scanf("%u",&(New_Student->id));
			printf("Enter Student height : ");
			fflush(stdin); fflush(stdout);
			scanf("%f",&(New_Student->height));
			Pt_last_element->Pnextstudent = New_Student;
			New_Student->Pnextstudent =null;
			counter++;                                                                           // modifying value of counter
			return 1;
		}
		else
		{
			printf("Error Heap is full\n");
			return 0;
		}

	}
}
int delete_student()
{
	unsigned int id;
	if(Pt_head_list)                                                            //check if list is exist 
	{
		printf("Enter the id of the student u want to delete : ");
		fflush(stdin); fflush(stdout);
		scanf("%u",&id);
		struct Sstudents* p_search = Pt_head_list;
		struct Sstudents* p_previous = null;                                     // pointer to save address of node that stored in the element that will be deleted
		if(p_search->id == id && p_search == Pt_head_list)
		{
			Pt_head_list = p_search->Pnextstudent;                                // in case id is of first node
			free(p_search);
			counter--;                                                             // modifying value of counter
			return 1;
		}

		do
		{
			p_previous = p_search;
			p_search = p_search->Pnextstudent;
			if(p_search->id == id )
			{
				p_previous->Pnextstudent = p_search->Pnextstudent;                  // in case the disired node to be  deleted is located in the middlle of the list
				free(p_search);
				counter--;
				return 1;
			}
		}
		while(p_search->Pnextstudent);

		if(p_search->id == id)
		{
			p_previous->Pnextstudent = null;                                           // in case the disired node to be  deleted is located in the last of the list
			free(p_search);
			counter--;                                                                                          // modifying value of counter
			return 1;
		}
		else
		{
			printf("\nError cannot find the id u Entered\n");                          // if there is no matched id
			return 0;
		}
	}
	else
		printf("students list is already empty there is nothing to be deleted\n***************************************\n");
	return 1;
}

int view_all()
{
	int count=1;
	if(Pt_head_list)                                                                    //check if list is exist
	{
		struct Sstudents*P_view=Pt_head_list;
		while(P_view->Pnextstudent)                                                  //loop till the end of list
		{
			printf("for record no. %d :-\n",count);
			printf("student name : %s\n",P_view->name);
			printf("student id : %u\n",P_view->id);
			printf("student height : %.2f\n",P_view->height);
			printf("****************************************\n");
			count++;
			P_view = P_view->Pnextstudent;
		}
		printf("for record no. %d :-\n",count);
		printf("student name : %s\n",P_view->name);
		printf("student id : %u\n",P_view->id);
		printf("student height : %.2f\n",P_view->height);
		printf("****************************************\n");
		return 1;
	}
	else
		printf("list is empty nothing to view\n***************************************\n");                  // if list is empty
	return 0;
}
int delete_all()
{
	if(Pt_head_list)                                                                                //check if list is exist
	{
		struct Sstudents*p_delete = Pt_head_list;                                           // pointer p_delete is to delete current node
		struct Sstudents*p_next = p_delete->Pnextstudent;                                  // pointer p_next is to store address of next node before deleting current node
		while(p_delete->Pnextstudent)
		{
			p_next=p_delete->Pnextstudent;
			free(p_delete);
			p_delete = p_next;
		}
		free(p_delete);
		printf("all items have been deleted successfully\n***************************************\n");
		Pt_head_list = null;
		counter=0;                                                                                           // modifying value of counter
		return 1;
	}
	printf("students list is already empty there is nothing to be deleted\n***************************************\n");
	return 0;
}

int gets_node_of_index()
{
	if(Pt_head_list)                                                                 // check if list exist
	{
		struct Sstudents* P_loop = Pt_head_list;
		unsigned int index,i;
		printf("Enter index u want to get its information : ");
		fflush(stdin); fflush(stdout);
		scanf("%u",&index);
		if(index == 1)
		{
			printf("for record no. %d :-\n",index);
			printf("student name : %s\n",P_loop->name);
			printf("student id : %u\n",P_loop->id);
			printf("student height : %.2f\n",P_loop->height);
			printf("****************************************\n");
			return 1;
		}
		for(i=1; i<index  ; i++)                                             
		{
			if(!P_loop->Pnextstudent)                                                 
				break;                                                                               // break if reach last node            
			P_loop = P_loop->Pnextstudent;
		}
		if(P_loop->Pnextstudent == null  && index>i )
		{
			printf("wrong index please Enter number in the list range : ");                                      // in case of exceding the range of list
			return 0;
		}
		else
		{
			printf("for record no. %d :-\n",index);
			printf("student name : %s\n",P_loop->name);
			printf("student id : %u\n",P_loop->id);
			printf("student height : %.2f\n",P_loop->height);
			printf("****************************************\n");
			return 1;
		}

	}
	else
	{
		printf("list is empty there are no information to view\n");
	}
	return 0;
}
int count_number_of_nodes()
{
	printf("\nnumber of nodes in the list = %d\n",counter);
	return counter;                                                                         // return counter
}
int gets_node_from_end()
{
	if(Pt_head_list)                                                                         // check if list exist
	{
		unsigned int index,i;
		printf("Enter the number from the end u want to view its information : ");
		fflush(stdin); fflush(stdout);
		scanf("%u",&index);
		struct Sstudents* P_node = Pt_head_list;                                          // p_node will refer to required node
		struct Sstudents* P_diff = Pt_head_list;                                         // p_diff will a pointer exceeds p_node by the index so when 
                                                                                            // p_diff points to last element p_node will points to index from the end
		if(index==1)           
		{
			while(P_node->Pnextstudent)
			{                                                                            // case of index 1 then required is last element
				P_node	= P_node->Pnextstudent;                                    // set p_node to points to last element
			}                                                                          
			printf("for record no. %d 'from the end' :-\n",index);
			printf("student name : %s\n",P_node->name);
			printf("student id : %u\n",P_node->id);
			printf("student height : %.2f\n",P_node->height);
			printf("****************************************\n");
			return 1;

		}
		else if(index<=0 || index>counter)
		{
			printf("Error wrong index please Enter a number within the range of the list .\n");                       //if index not within the range of the list
			return 0;
		}
		else
		{
			for(i=1; i<index; i++)
			{
				P_diff = P_diff->Pnextstudent;                                                                        // setting differnce between 2 pointers = index
			}
			while(P_diff->Pnextstudent)
			{
				P_node = P_node->Pnextstudent;
				P_diff = P_diff->Pnextstudent;
			}
			printf("for record no. %d 'from the end' :-\n",index);
			printf("student name : %s\n",P_node->name);
			printf("student id : %u\n",P_node->id);
			printf("student height : %.2f\n",P_node->height);
			printf("****************************************\n");
			return 1;
		}
	}
	else
		printf("list is empty there are no informations to view");
	return 0;
}

int get_the_middle()
{


	if(Pt_head_list)                                                      // check if the list exist
	{ 

		if(counter <= 2)
		{
			printf("number of the list is too small there is no middle element \n");          //if no. of nodes less than 2 there will be no middle
			return 0;
		}
		struct Sstudents* P_slow = Pt_head_list;                                      // p_slow will point to the middle node
		struct Sstudents* P_fast = Pt_head_list;                                      // p_Fast will exceeds p_slow by 2 nodes
		while(P_fast && P_fast->Pnextstudent)                                         // breaks if p_fast exceeds the range in case of even no of nodes 
		{                                                                            // when p_fast points to last element p_slow will points to the middle one
			P_slow = P_slow->Pnextstudent;
			P_fast = P_fast->Pnextstudent->Pnextstudent;                           //how be p_fast exceeds p_slow
		}
		printf("the middle node is of number : %d\n",counter/2 +1);
		printf("for record no. %d :-\n",counter/2 +1);
		printf("student name : %s\n",P_slow->name);
		printf("student id : %u\n",P_slow->id);
		printf("student height : %.2f\n",P_slow->height);
		printf("****************************************\n");
		return 1;
	}
	else
		printf("list is empty there are no informations to view\n");
	return 0;
}
int reverse_list()
{
	if(Pt_head_list)                                                              // check if the list exist
	{
		if(counter == 1)                                                        // if number of nodes is 1 no need for reversing
			return 0; 
		struct Sstudents* p_previous = Pt_head_list;                           
		struct Sstudents* p_current  = p_previous->Pnextstudent;
		struct Sstudents* p_next = null;
     while(p_current)
     {
        p_next = p_current->Pnextstudent;
        p_current->Pnextstudent= p_previous;
        p_previous = p_current;
        if(!p_next)
        	break;
        p_current=p_next;

     }
     Pt_head_list->Pnextstudent=null;
     Pt_head_list = p_current;
     view_all();
     return 1;
	}
	else
	printf("list is empty there is nothing to reverse\n");
	return 0;
	}
