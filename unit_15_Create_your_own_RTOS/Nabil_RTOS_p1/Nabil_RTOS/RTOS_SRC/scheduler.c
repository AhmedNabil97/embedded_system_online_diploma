/*
 * scheduler.c
 *
 *  Created on: ١٨‏/٠٥‏/٢٠٢٤
 *      Author: lenovo
 */


#include "Nabil_RTOS_FIFO.h"
#include "string.h"
Fifo_Buffer Nabil_Rtos_Ready_queue;
task_ref system_idle_task;
int created_tasks_number = -1;
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
//to do specific OS Services
void idle_task_funtion();
void service_handler(int*ptr)
{
	// PTR = R0 which carry value of either MSP or PSP
	// from memory  layer adding 6 to  PTR let PTR points to PC which carry the next instruction after SVC call.
	unsigned char* pc_val = *(ptr + 6);                                 //memory layer :-    													2.
	pc_val -= 2 ;            						                    //1. XPSR
	unsigned short index =  * (unsigned short*)pc_val;                   //2. PC
	switch(index)                                                       //3. LR
	{																	//4 -- 8 : R12 , R3 , R2 , R1 ,R0


	case 0 :                                                            //activate task
		break;
	case 1 :															//Eliminate task
		break ;
	case 2 :
		break ;
	case 3 :  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk  ; //trigger pendsv interrupt
	break ;
	default :
		break;
	}
}

void My_RTOS_Create_MainStack()
{
	OS_control._S_MSP = ((unsigned int) &_estack);
	OS_control._E_MSP = OS_control._S_MSP - 3072 ;
	// align stack with 8 bytes & set PSP for tasks.
	OS_control.sp_locater = OS_control._E_MSP - 8 ;
}

enum RTOS_ERROR My_RTOS_Init()

{
	enum RTOS_ERROR error_status = NO_ERROR;

	//update OS mode

	OS_control.os_state = OS_suspended;

	//specify main stack & main task
	My_RTOS_Create_MainStack();



	//create OS ready queue

	if( Fifo_init(&Nabil_Rtos_Ready_queue, OS_control.OS_tasks, 100) != Fifo_no_error )
	{
		return Fifo_error ;
	}



	strcpy(system_idle_task.task_name,"idle task");
	system_idle_task.piriority = 255;                  //lowest priority
	system_idle_task.ptr_to_task = idle_task_funtion ;
	system_idle_task.stack_size = 100;
	Nabil_Rtos_Create_Task(&system_idle_task);
	return error_status;
}



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


}

void idle_task_funtion()
{
	while(1)
	{
		__asm("NOP");
	}
}
void OS_SVC_Set( int index)
{

	switch(index)
	{
	case 1 :
		__asm("SVC #0x1");
		break;
	case 2 :
		__asm("SVC #0x2");
		break;
	case 3 :
		__asm("SVC #0x3");
		break;
	case 4 :
		__asm("SVC #0x4");
		break;
	default :
		break;

	}


}



void PendSV_Handler(void)
{
	//will be used in switch context
	__asm("nop");
}


void HW_Init()
{
	// initialize clock tree (RCC ---> CPU  ) 8MHZ
	// 8MHZ
	// 0.125 uS for 1 tick
	// 1 Ms. =  8000 ticks


}




















































