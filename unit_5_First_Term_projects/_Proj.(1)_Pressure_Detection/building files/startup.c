/*
 * startup.c
 *
 *  Created on: Oct 15, 2023
 *      Author: ahmed
 */
extern int main();
extern unsigned int E_text;
extern unsigned int S_data;                 //symbols defined in liker_Script
extern unsigned int E_data;
extern unsigned int S_bss;
extern unsigned int E_bss;
extern unsigned int Stack_top;


void reset_handler();
void default_handler();
void NMI_handler()__attribute__((weak,alias("default_handler")));;
void H_FAULT_handler()__attribute__((weak,alias("default_handler")));;        //interrupt vector table
void MM_handler()__attribute__((weak,alias("default_handler")));;
void BUS_handler()__attribute__((weak,alias("default_handler")));;
void USAGE_FAULT_handler()__attribute__((weak,alias("default_handler")));;



    void(*vector_table[])()__attribute__((section(".vector"))) =
    {
    		(void(*)())&Stack_top,
			reset_handler,
			NMI_handler,
			H_FAULT_handler,                                     //array of pointer to function
    		MM_handler,
			BUS_handler,
			USAGE_FAULT_handler
    };



    void reset_handler()
    {
    	unsigned int i;
    	unsigned int data_size = (unsigned char*)&E_data - (unsigned char*)&S_data ;
    	unsigned char* target = (unsigned char*)&S_data;
    	unsigned char* base = (unsigned char*)&E_text;
    	for(i=0; i<data_size; i++)
    	{
    		*target++ = *base++;                         //copying .data sec from flash to ram
    	}
    	unsigned int bss_size = (unsigned char*)&E_bss - (unsigned char*)&S_bss ;
    	unsigned char* target_b = (unsigned char*)&S_bss;
    	for(i=0; i<bss_size; i++)
    	{
    		*target_b++ = 0;                          //reserve .bss section by 0
    	}
        main();
    }
    void default_handler()
    {
    	reset_handler();
    }
