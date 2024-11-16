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



/////////////////////////////////////////////////// " Global Variables " ///////////////////////////////////////////////////////////////////////////
task_ref t1 , t2 ,t3 , t4;
Mutex_ref m1;
unsigned char t1_led = 0 , t2_led = 0 , t3_led = 0 ,t4_led = 0;
unsigned char payload[3];
/////////////////////////////////////////////////////////// /////////// ///////////////////////////////////////////////////////////////////////////


void task1_fun()
{

	static int count ;
	while(1)
	{
		t1_led ^= 1;
						count++;
				        if(count == 100)
				        {
				        Nabil_Rtos_Aquire_Mutex(&m1, &t1);
						Nabil_Activate_task(&t2);
				        }
				        if(count == 300)
				        {
				        	count = 0;
				        	Nabil_Rtos_Release_Mutex(&m1);
				        }
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void task2_fun()
{
	static int count ;
	while(1)
	{
		t2_led ^= 1;

					        count++;
					        if(count == 100 )
							Nabil_Activate_task(&t3);
					        if(count == 300)
					        {
					        	count = 0;
					        	Nabil_Terminate_task(&t2);
					        }
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void task3_fun()
{
	static int count ;
	while(1)
	{
		t3_led ^= 1;

					        count++;
					        if(count == 100 )
							Nabil_Activate_task(&t4);
					        if(count == 300)
					        {
					        	count = 0;
					        	Nabil_Terminate_task(&t3);
					        }

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void task4_fun()
{
	static int count ;
	while(1)
	{
		t4_led ^= 1;
					        count++;
					        if(count == 3)
					        {
					        	Nabil_Rtos_Aquire_Mutex(&m1, &t4);
					        }

					        if(count == 300)
					        {
					        	count = 0;
					            Nabil_Rtos_Release_Mutex(&m1);
					        	Nabil_Terminate_task(&t4);
					        }

	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)

{

	HW_INIT();
	My_RTOS_Init() ;
	t1.piriority = 3 ;
	t1.ptr_to_task = task1_fun;
	t1.stack_size = 1024 ;
	strcpy(t1.task_name , "task 1 ");
	Nabil_Rtos_Create_Task(&t1);
	/////////////////////////////
	t2.piriority = 2 ;
	t2.ptr_to_task = task2_fun;
	t2.stack_size = 1024 ;
	strcpy(t2.task_name , "task 2 ");
	Nabil_Rtos_Create_Task(&t2);
	/////////////////////////////////
	t3.piriority = 1 ;
	t3.ptr_to_task = task3_fun;
	t3.stack_size = 1024 ;
	strcpy(t3.task_name , "task 3 ");
	Nabil_Rtos_Create_Task(&t3);
	/////////////////////////////////
	t4.piriority = 0 ;
	t4.ptr_to_task = task4_fun;
	t4.stack_size = 1024 ;
	strcpy(t4.task_name , "task 4 critical");
	Nabil_Rtos_Create_Task(&t4);
	/////////////////////////////////
	m1.current_handler = NULL;
	m1.next_handler = Null;
	m1.payload = payload;
	m1.paylaod_size = 3;
	strcpy(m1.mutex_name , "mutex shared between t1 - t4");
	Nabil_Activate_task(&t1);
	Nabil_Activate_task(&t2);
	Nabil_Activate_task(&t3);
	Nabil_Activate_task(&t4);
	OS_Start();

}


