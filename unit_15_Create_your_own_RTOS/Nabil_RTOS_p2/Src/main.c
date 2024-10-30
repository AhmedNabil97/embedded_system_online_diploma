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

task_ref t1 , t2 ,t3;
unsigned char t1_led = 0 , t2_led = 0 , t3_led = 0 ;
void task1_fun()
{
	while(1)
	{
		t1_led ^= 1;
	}
	}
void task2_fun()
{
	while(1)
		{
			t2_led ^= 1;
		}
	}

void task3_fun()
{
	while(1)
		{
			t3_led ^= 1;
		}
	}
int main(void)

{

HW_INIT();
 My_RTOS_Init() ;
t1.piriority = 0 ;
t1.ptr_to_task = task1_fun;
t1.stack_size = 1024 ;
strcpy(t1.task_name , "task 1 highest");
Nabil_Rtos_Create_Task(&t1);
/////////////////////////////
t2.piriority = 0 ;
t2.ptr_to_task = task2_fun;
t2.stack_size = 1024 ;
strcpy(t2.task_name , "task 2 lowest");
Nabil_Rtos_Create_Task(&t2);
/////////////////////////////////
t3.piriority = 0 ;
t3.ptr_to_task = task3_fun;
t3.stack_size = 1024 ;
strcpy(t1.task_name , "task 3 middle");
Nabil_Rtos_Create_Task(&t3);


Nabil_Activate_task(&t1);
Nabil_Activate_task(&t2);
Nabil_Activate_task(&t3);
OS_Start();


	while(1);

}

