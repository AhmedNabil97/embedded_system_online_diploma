/*
 *
 * Created: 12/12/2023 08:47:28 م
 * Author : Ahmed Nabil
 */

#include "GPIO.h"
#include "EXTI.h"
#include "ARMCM3.h"
#include "core_cm3.h"
#include "system_ARMCM3.h"
#include "Nabil_RTOS_FIFO.h"
#include <string.h>

task_ref t1 , t2;
void task1_fun()
{
	int i = 5 ;
	while(1)
	{
	i++;
	}
	}
void task2_fun()
{
	int k = 0 ;
	while(1)
	{
	k++;
	}
	}
int main(void)

{

HW_Init();

 My_RTOS_Init() ;
t1.piriority = 0 ;
t1.ptr_to_task = task1_fun;
t1.stack_size = 1024 ;
strcpy(t1.task_name , "task 2 highest");
Nabil_Rtos_Create_Task(&t1);
/////////////////////////////
t2.piriority = 1 ;
t2.ptr_to_task = task2_fun;
t2.stack_size = 1024 ;
strcpy(t2.task_name , "task 2 lowest");
Nabil_Rtos_Create_Task(&t2);

	while(1);

}

