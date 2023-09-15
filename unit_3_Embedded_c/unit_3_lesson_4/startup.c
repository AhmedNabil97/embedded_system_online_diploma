// startup.c
//Eng. : Ahmed Nabil

extern int main();
extern unsigned int _E_TEXT;
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_BSS;
extern unsigned int _E_BSS;


void reset_handler();
void deafult_handler()
{
	reset_handler();
}
void NMI_handler() __attribute__((weak,alias("deafult_handler")));;
void H_fault_handler()__attribute__((weak,alias("deafult_handler")));;
void MM_handler()__attribute__((weak,alias("deafult_handler")));;
void BUS_handler()__attribute__((weak,alias("deafult_handler")));;
void USAGE_fault_handler()__attribute__((weak,alias("deafult_handler")));;


static unsigned int stack_top[256];

void (*const arr_pTo_func_Vectors[])() __attribute__((section(".vectors")))  =
{
		(void(*)()) ((unsigned int)stack_top + sizeof(stack_top)),
		&reset_handler,
		&NMI_handler,
		&H_fault_handler,
		&MM_handler,
		&BUS_handler,
		&USAGE_fault_handler


};

int i;
void reset_handler()
{
	unsigned int data_Size = (unsigned int)&_E_DATA -(unsigned int) &_S_DATA ;
	unsigned char * base = (unsigned char*)&_E_TEXT;
	unsigned char * target = (unsigned char*)&_S_DATA;                          // copying data sec from rom to ram
	for(i=0; i<data_Size; i++)
	{
		*target++ = *base++;
	}



	unsigned int bss_Size = (unsigned int)&_E_BSS -(unsigned int) &_S_BSS ;
	unsigned char * bss_target = (unsigned char*)&_S_BSS;                       // intializing bss sec by zeros in ram

	for(i=0; i<bss_Size; i++)
	{
		*bss_target++ = (unsigned char)0;
	}


	main();                                                                     // jump to main
}



