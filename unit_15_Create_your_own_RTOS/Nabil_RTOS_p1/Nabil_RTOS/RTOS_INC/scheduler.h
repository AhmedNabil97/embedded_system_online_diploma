/*
 * scheduler.h
 *
 *  Created on: ١٨‏/٠٥‏/٢٠٢٤
 *      Author: lenovo
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "Cortex_MX_OS_Porting.h"
typedef struct
{
	unsigned int stack_size  ;
	unsigned char piriority  ;
	void(*ptr_to_task)()     ;
	unsigned int _S_PSP_task ;    //not entered by the user
	unsigned int _E_PSP_task ;    //not entered by the user
	unsigned int* current_PSP;    //not entered by the user
	char  task_name[40]      ;
	enum
		{
			suspended,
			waiting,
			ready,
			running
		}task_state;

		struct
	{
		enum
		{
			enable,
			disable
		}blocking;
		unsigned int no_of_ticks;
	}time_waiting;     //blocking based on time yes or no and the period.
}task_ref;
#define data_type task_ref*

enum RTOS_ERROR
{
	NO_ERROR,
	OS_fifo_error
	,
	OS_exceed_stack_size_error
}OS_error;

void HW_Init();
enum RTOS_ERROR My_RTOS_Init();
enum RTOS_ERROR Nabil_Rtos_Create_Task(task_ref*);
enum RTOS_ERROR Nabil_Rtos_create_task_stack(task_ref*);
#endif /* INC_SCHEDULER_H_ */
