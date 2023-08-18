#include "uart.h"
#define DATAREG *((volatile unsigned int*const)((unsigned int*)0x101f1000))
void uart_send_string(unsigned char*str)
{
  while (*str != '\0')
{
   DATAREG = (unsigned int)(*str);
   str++;
}

}