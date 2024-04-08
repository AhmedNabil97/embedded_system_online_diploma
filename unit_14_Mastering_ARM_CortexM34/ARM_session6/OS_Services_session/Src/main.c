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

//Global variables

extern unsigned int _estack ;
unsigned char IRQ_Flag      ;
unsigned char TaskA_Flag    ;
unsigned char TaskB_Flag    ;
int ipsr_value    =  0      ;
int val1          =  5      ;
int val2          =  7      ;
int val3          =  0      ;
int control_value =  0      ;

//Main Stack
unsigned int _S_MSP = (unsigned int) & _estack ;
unsigned int _E_MSP                            ;
//Process Stack
unsigned int _S_PSP_TA                         ;
unsigned int _E_PSP_TA                         ;
unsigned int _S_PSP_TB                         ;
unsigned int _E_PSP_TB                         ;


//Macros

#define TaskA_Stack_Size		100
#define TaskB_Stack_Size		100


#define OS_SeT_PSP(address)		__asm volatile("MOV R0 , %0 \n\t MSR PSP , R0"\
		:                                             \
													  : "r"      	(address)                         )



#define OS_SP_Shadow_MSP		__asm volatile("MRS   R0 ,    CONTROL "         );\
		__asm volatile("AND   R0 , R0 , #0XFFFFFFFD "   );\
		__asm volatile("MSR   CONTROL , R0    "         )



#define OS_SP_Shadow_PSP		__asm volatile("MRS   R0 ,    CONTROL "   );\
		__asm volatile("ORR   R0 , R0 , #0X02 "   );\
		__asm volatile("MSR   CONTROL , R0    "   )



#define OS_Generate_Exception	__asm volatile("SVC              #0x03"   )


//Functions

void clock_init(void)
{
	GPIOB_CLK_EN() ;       //Enable clock for GPIOB
	AFIO_CLK_EN()  ;       //Enable clock for AFIO

}

void switch_to_user_access(void)
{
	__asm("MRS R2 , CONTROL");
	__asm("ORR R2 , R2 , #0x01");
	__asm("MSR CONTROL , R2");

}
void switch_to_previledged_access(void)
{
	__asm("MRS R2 , CONTROL");
	__asm("LSR R2 , R2 , #0x01");
	__asm("LSL R2 , R2 , #0x01");
	__asm("MSR CONTROL , R2");

}

int TaskA(int a , int b)
{
	return a + b ;
}

int TaskB(int a , int b)
{
	return a - b ;
}


void my_handler(void)
{

	if(! IRQ_Flag)
	{
		TaskA_Flag  = 1 ;
		TaskB_Flag  = 0 ;
		IRQ_Flag    = 1 ;
	}
	else if(IRQ_Flag)
	{
		TaskA_Flag = 0 ;
		TaskB_Flag = 1 ;
		IRQ_Flag   = 0 ;

	}

}

//-----------------------------------------------------LAB2------------------------------------------------------------------------//

void service_handler(int*ptr)
{
	unsigned char* pc_val = *(ptr + 6);
	pc_val -= 2 ;
	unsigned char index =  * pc_val;
	int x = *(ptr);
	int y =  *(ptr+1);
	int z;
	switch(index)
	{
	case 1 :
		z = x + y ;
		break;
	case 2 :
		z = x - y ;
		break ;
	case 3 : z = x*y ;
	break ;
	case 4 :  SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk  ;
	break ;
	default :
		break;
	}

	__asm("MOV R5,%0"
			:
			:"r" (z) );
}

int*ptr;

__attribute__((naked))   void SVC_Handler()
{

	__asm("TST LR , 0x4 ");
	__asm("ITE EQ");
	__asm("MRSEQ R0 , MSP");
	__asm("MRSNE R0 , PSP");
	__asm("b service_handler");

}

int OS_SVC_Set(int a , int b , int index)
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
	int result ;
	__asm("MOV %0 , R5"
			:"=r" (result)
			 :  ) ;

	return result;

}

void PendSV_Handler(void)
{
  __asm("nop");
	}
//--------------------------------------------------------------------------------------------------------------------------------//

void MainOs(void)
{
	//set Main stack size = 512 bytes
	_E_MSP = _S_MSP - 512 ;

	//set task A stack size
	_S_PSP_TA = _E_MSP - 8 ;
	_E_PSP_TA = _S_PSP_TA - TaskA_Stack_Size ;

	//set task B stack size
	_S_PSP_TB = _E_PSP_TA - 8 ;
	_E_PSP_TB= _S_PSP_TB - TaskB_Stack_Size ;


	while(1)
	{
		__asm("NOP");

		if(TaskA_Flag)
		{
			//set value of PSP to start of TaskA stack
			OS_SeT_PSP(_S_PSP_TA);
			//let SP shadow --> PSP
			OS_SP_Shadow_PSP;
			//set user access
			switch_to_user_access();
			TaskA(10, 5);
			//set privilege access
			OS_Generate_Exception;
			//let SP shadow --> MSP
			OS_SP_Shadow_MSP;
			TaskA_Flag = 0 ;
		}

		else if(TaskB_Flag)
		{
			//set value of PSP to start of TaskB stack
			OS_SeT_PSP(_S_PSP_TB);
			//let SP shadow --> PSP
			OS_SP_Shadow_PSP;
			//set user access
			switch_to_user_access();
			TaskB(10, 5);
			//set privilege access
			OS_Generate_Exception;
			//let SP shadow --> MSP
			OS_SP_Shadow_MSP;
			TaskB_Flag = 0 ;

		}

	}

}

int main(void)

{

	/*SysTick_Config(100);
	clock_init();
	EXTI_config_t EXIR9 ;
	EXIR9.port = GPIOB;
	EXIR9.pin_and_line_number = P9 ;
	EXIR9.interrupt_mode = rising_edge;
	EXIR9.isr_p = my_handler;
	MCAL_EXTI_Init(&EXIR9);
	MCAL_EXTI_Enable(EXTI9);
	MainOs();
*/

	int val1 = OS_SVC_Set(10, 2, 1);     //sum
	int val2 = OS_SVC_Set(10, 2, 2);     //subtract
	int val3 = OS_SVC_Set(10, 2, 3);     // mul
	 OS_SVC_Set(10, 2, 4);               //pendsv

	while(1)
	{
	}
}



