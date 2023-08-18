#include "uart.h"
unsigned char name[] = "Learn-in-depth >>> Ahmed Nabil";
char bss[100];
const char rod_variable = 'T';
void  main(void)
{
   uart_send_string(name);
 }