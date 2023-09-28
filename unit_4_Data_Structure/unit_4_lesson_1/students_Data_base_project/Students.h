/*
 * Students.h
 *
 *  Created on: Sep 26, 2023
 *      Author: ahmed
 */

#ifndef STUDENTS_H_
#define STUDENTS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define null (void*)0
struct Sstudents
{
	char name[50];
	unsigned int id;
	float height;
	struct Sstudents*Pnextstudent;
	};


int add_student();
int delete_student();
int view_all();
int delete_all();
int gets_node_of_index();
int count_number_of_nodes();
int gets_node_from_end();
int get_the_middle();
int reverse_list();
#endif /* STUDENTS_H_ */
