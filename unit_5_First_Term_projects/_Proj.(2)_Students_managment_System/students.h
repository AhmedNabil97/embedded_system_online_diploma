/*
 * students.h
 *
 *  Created on: 23/10/2023
 *      Author: ahmed nabil
 */

#ifndef STUDENTS_H_
#define STUDENTS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sinfo
{
    unsigned int roll_number;
	char first_name[50];
	char last_name[50];
    float gpa;
    unsigned int cid[5];
	}st[50];

	 enum
	{
		fifo_full,
		fifo_empty,
		fifo_not_empty,
		fifo_null
	}fifo_status_t;

 struct Fifo
{
		struct sinfo * base;
		struct sinfo * head;
		unsigned char count;
		unsigned char length;
		}student_queue;


FILE *fpointer;

// function to initialize Fifo and assign it array of students struct
void queue_init();

// function to add students details from text file
void add_student_file();

// function to add students details manually by the user
void add_student_manually();

// function to find students details by student's roll number
void find_rl();

// function to find students details by student's first name
void find_fn();

// function to find students details by course id they are applied in
void find_c();

// function to find total number of students and number of students can be added to the list
void tot_s();

// function to delete student details by student's roll number
void del_s();

// function to update students details by student's roll number
void up_s();

// function to display all students informations in the list
void show_s();

#endif /* STUDENTS_H_ */
