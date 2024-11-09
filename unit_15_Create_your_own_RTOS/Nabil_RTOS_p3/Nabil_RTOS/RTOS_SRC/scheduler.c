/*
 * scheduler.c
 *
 *  Created on: ١٨‏/٠٥‏/٢٠٢٤
 *      Author: lenovo
 */

//====================================================== Header files==============================================================================
#include "Nabil_RTOS_FIFO.h"
#include "string.h"
//========================================================================================================================================


//====================================================== Global variables==============================================================================
Fifo_Buffer Nabil_Rtos_Ready_queue;
task_ref system_idle_task;
int created_tasks_number = -1;
task_ref* ready_queue[100];                                       //scheduler table
unsigned char idle_flag = 0;
//========================================================================================================================================


//====================================================== My created user data types==============================================================================
struct
{

	task_ref* OS_tasks[100];                                       //scheduler table
	unsigned int _S_MSP;
	unsigned int _E_MSP;
	unsigned int sp_locater;
	task_ref* current_task;
	task_ref* next_task;
	unsigned int no_of_created_tasks;
	enum
	{
		OS_suspended,
		OS_running
	}os_state;


}OS_control;

typedef enum
{

	Svc_activate_task = 1,
	Svc_terminate_task,
	Svc_Task_waiting_time
}SVC_ID;

//========================================================================================================================================



//====================================================== non user functions==============================================================================
void idle_task_funtion()
{
	while(1)
	{
		idle_flag ^= 1;
		__asm("WFE");
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

void My_RTOS_Create_MainStack()
{
	OS_control._S_MSP = ((unsigned int) &_estack);
	OS_control._E_MSP = OS_control._S_MSP - 3072 ;
	// align stack with 8 bytes & set PSP for tasks.
	OS_control.sp_locater = OS_control._E_MSP - 8 ;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------

enum RTOS_ERROR Nabil_Rtos_create_task_stack(task_ref*p)
{
	/* my task Frame
	 * ================ auto Stacked by the processor =================
	 * XPSR
	 * PR                   next instruction should be run within task
	 * LR                   return register value when task1 was running before switch context
	 * R12
	 * R3
	 * R2
	 * R1
	 * R0
	 *================== my frame ======================================
	 * stacking for r4-r11
	 */
	p->current_PSP = p->_S_PSP_task;
	p->current_PSP --;
	*(p->current_PSP) = 0x1000000;                        //Dummy value for initialization of XPSR b24 should be = 1 ass it works in thumb state
	p->current_PSP --;
	*(p->current_PSP) = (unsigned int)p->ptr_to_task;     //PC value will be loaded by task function
	p->current_PSP --;
	*(p->current_PSP) = 0xFFFFFFFD ;                  //Dummy value to initialize LR ---> Thread , PSP
	int i = 0;
	for(i=0 ; i<13 ; i++)
	{
		p->current_PSP --;
		*(p->current_PSP) = 0;
	}

	return NO_ERROR;
}
//-----------------------------------------------------------------------------------------------------------------------------------------

void OS_SVC_Set(SVC_ID index)
{

	switch(index)
	{
	case Svc_activate_task :
		__asm("SVC #0x1");
		break;
	case Svc_terminate_task :
		__asm("SVC #0x2");
		break;
	case Svc_Task_waiting_time :
		__asm("SVC #0x3");
		break;
	default :
		break;

	}


}

//----------------------------------------------------------------------------------------------------------------------------------------------



int test = 0;
int i = 0 ,j;
void Nabil_RTOS_update_Sch_table()
{
	task_ref* temp;
	i = 0;
	while(i<= created_tasks_number)
	{
		if(OS_control.OS_tasks[i]->task_state != suspended)
		{
			OS_control.OS_tasks[i]->task_state = waiting;
		}
		i++;

	}
	for(i=0; i < created_tasks_number ; i++)
	{
		for(j = i+1 ; j <= created_tasks_number ; j++)
		{
			if(  OS_control.OS_tasks[j]->task_state  > OS_control.OS_tasks[i]->task_state  )
			{
				temp = OS_control.OS_tasks[i];
				OS_control.OS_tasks[i] = OS_control.OS_tasks[j];
				OS_control.OS_tasks[j] = temp;
			}
			else if( OS_control.OS_tasks[j]->task_state  == OS_control.OS_tasks[i]->task_state)
			{
				test++;

				if( OS_control.OS_tasks[j]->piriority < OS_control.OS_tasks[i]->piriority )
				{
					temp = OS_control.OS_tasks[i];
					OS_control.OS_tasks[i] = OS_control.OS_tasks[j];
					OS_control.OS_tasks[j] = temp;
				}
			}
			else
				break;
		}
	}
}


//----------------------------------------------------------------------------------------------------------------------------------------------



void empty_ready_queue()
{
	int i ;
     for(i=0; i<Nabil_Rtos_Ready_queue.count; i++)
     {

    	 ready_queue[i] = NULL;
     }
     Nabil_Rtos_Ready_queue.count = 0;
     Nabil_Rtos_Ready_queue.head = Nabil_Rtos_Ready_queue.base;
     Nabil_Rtos_Ready_queue.tail = Nabil_Rtos_Ready_queue.base;

}

//----------------------------------------------------------------------------------------------------------------------------------------------

void fill_ready_queue()
{
	if(OS_control.OS_tasks[0]->task_state)
	{
		Fifo_add_item(&Nabil_Rtos_Ready_queue, OS_control.OS_tasks[0]);
		OS_control.OS_tasks[0]->task_state = ready;
		int i ;
		for(i = 1 ; i <= created_tasks_number ; i++)
		{
			if(OS_control.OS_tasks[i]->piriority == OS_control.OS_tasks[0]->piriority  && OS_control.OS_tasks[i]->task_state)
			{
				Fifo_add_item(&Nabil_Rtos_Ready_queue, OS_control.OS_tasks[i]);
				OS_control.OS_tasks[i]->task_state = ready;
			}
			else
				break;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void OS_decide_what_next()
{

	//case 1- ready queue is empty & there's only one running task
	if(Nabil_Rtos_Ready_queue.count == 0 && OS_control.current_task->task_state != suspended)
	{
		OS_control.current_task->task_state = running;
		Fifo_add_item(&Nabil_Rtos_Ready_queue, OS_control.current_task);
		OS_control.next_task = OS_control.current_task;
	}
	else if(Nabil_Rtos_Ready_queue.count)
	{
		OS_control.next_task = Fifo_get_item(&Nabil_Rtos_Ready_queue);
		OS_control.next_task->task_state = running;
		if(OS_control.current_task ->piriority == OS_control.next_task->piriority && OS_control.current_task->task_state != suspended)
		{
			Fifo_add_item(&Nabil_Rtos_Ready_queue, OS_control.current_task);
			OS_control.current_task->task_state  = ready;
		}

	}
}


//----------------------------------------------------------------------------------------------------------------------------------------------


void trigger_pendsv()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk  ;

}
void service_handler(int*ptr)
{

	// PTR = R0 which carry value of either MSP or PSP
	// from memory  layer adding 6 to  PTR let PTR points to PC which carry the next instruction after SVC call.
	ptr+=6;
	unsigned char* pc_val =  ( (unsigned char *) (*ptr));                                 //memory layer :-    													2.
	pc_val -= 2 ;            						                    //1. XPSR
	unsigned char index =  * (unsigned short*)pc_val;                   //2. PC
	switch(index)                                                       //3. LR
	{																	//4 -- 8 : R12 , R3 , R2 , R1 ,R0
	case Svc_activate_task:
	case Svc_terminate_task :
	case Svc_Task_waiting_time :
		//update SCh. table , ready queue
		Nabil_RTOS_update_Sch_table();
		empty_ready_queue();
		fill_ready_queue();
		//OS running
		if(OS_control.os_state == OS_running)
		{
			if(OS_control.current_task != & system_idle_task)
			{
				OS_decide_what_next();
				//trigger PendSv ( switch context & restore)
				trigger_pendsv();
			}
		}

		break ;
	default :
		break;
	}
}


int v ;

void update_tasks_time_waiting()
{
	for(v=0 ; v <= created_tasks_number ; v++ )
	{
		if(OS_control.OS_tasks[v]->time_waiting.blocking == enable)
		{
			OS_control.OS_tasks[v]->time_waiting.no_of_ticks --;
		}
		if(! OS_control.OS_tasks[v]->time_waiting.no_of_ticks)
		{
			OS_control.OS_tasks[v]->time_waiting.blocking = disable;
			OS_control.OS_tasks[v]->task_state = waiting;
			OS_SVC_Set(Svc_Task_waiting_time);

		}
	}
	}


//----------------------------------------------------------------------------------------------------------------------------------------------


//========================================================================================================================================





//====================================================== header functions implemntations ==============================================================================



enum RTOS_ERROR My_RTOS_Init()

{
	enum RTOS_ERROR error_status = NO_ERROR;

	//update OS mode

	OS_control.os_state = OS_suspended;

	//specify main stack & main task
	My_RTOS_Create_MainStack();



	//create OS ready queue

	if( Fifo_init(&Nabil_Rtos_Ready_queue, ready_queue, 100) != Fifo_no_error )
	{
		return Fifo_error ;
	}



	strcpy(system_idle_task.task_name,"idle task");
	system_idle_task.piriority = 255;                  //lowest priority
	system_idle_task.ptr_to_task = idle_task_funtion ;
	system_idle_task.stack_size = 1000;
	Nabil_Rtos_Create_Task(&system_idle_task);
	return error_status;
}

//---------------------------------------------------------------------------------------------------------------------------------------------

void Nabil_RTOS_Task_wait(unsigned int no_of_mSecs , task_ref*p)
{
	p->time_waiting.blocking = enable;
	p->time_waiting.no_of_ticks = no_of_mSecs ;
	Nabil_Terminate_task(p);
	}

//---------------------------------------------------------------------------------------------------------------------------------------------


enum RTOS_ERROR Nabil_Rtos_Create_Task(task_ref*p)
{
	created_tasks_number ++;
	enum RTOS_ERROR error_state = NO_ERROR;
	//check if task size exceeds stack size or no
	if( ( OS_control.sp_locater - p->stack_size ) < ( (unsigned int)&_estack - (unsigned int)&_e_heap )  )
		return OS_exceed_stack_size_error;
	p->_S_PSP_task = OS_control.sp_locater;
	p->_E_PSP_task = p->_S_PSP_task - p->stack_size;
	//Align 8 bytes for next task
	OS_control.sp_locater = p->_E_PSP_task - 8;
	//Initialize PSP task stack
	Nabil_Rtos_create_task_stack(p);
	//update task state
	p->task_state = suspended ;
	OS_control.OS_tasks[created_tasks_number] = p;
	return error_state;
}


//---------------------------------------------------------------------------------------------------------------------------------------------


enum RTOS_ERROR Nabil_Activate_task(task_ref*p)
{
	p->task_state = waiting;
	OS_SVC_Set(Svc_activate_task);
	return NO_ERROR;
}


//---------------------------------------------------------------------------------------------------------------------------------------------

enum RTOS_ERROR Nabil_Terminate_task(task_ref*p)
{
	p->task_state = suspended;
	OS_SVC_Set(Svc_terminate_task);
	return NO_ERROR;


}
void OS_Start()
 {
	//update OS state
	OS_control.os_state = OS_running;
	//activate idle task
	OS_control.current_task = & system_idle_task;
	Nabil_Activate_task(&system_idle_task);
	//start ticker
	OS_start_ticker();
	OS_SeT_PSP(OS_control.current_task->current_PSP);
	//switch from MSPto PSP
	OS_SP_Shadow_PSP;
	Switch_to_user_access;
	OS_control.current_task->ptr_to_task();

}

//========================================================================================================================================


__attribute ((naked))void PendSV_Handler(void)
{
	//save context of current task

	OS_get_PSP(OS_control.current_task ->current_PSP);
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R4"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R5"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R6"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R7"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R8"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R9"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R10"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP--;
	__asm("MOV %0, R11"
			:"=r" (*(  OS_control.current_task->current_PSP) ) );


	// restore context of next task
	OS_control.current_task = OS_control.next_task;
	OS_control.next_task = NULL;

	__asm("MOV R11, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R10, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R9, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R8, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R7, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R6, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R5, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	__asm("MOV R4, %0"
			:
			:"r" (*(  OS_control.current_task->current_PSP) ) );
	OS_control.current_task->current_PSP++;
	OS_SeT_PSP(OS_control.current_task->current_PSP);
	__asm ("BX LR");
	//store context of the previous task
}


unsigned char sys_tick_flag = 0;
void SysTick_Handler()
{

	update_tasks_time_waiting();
	sys_tick_flag ^= 1;
    OS_decide_what_next();
    trigger_pendsv();
	}

















































