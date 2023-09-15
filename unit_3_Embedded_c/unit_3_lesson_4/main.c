// c code to toggle bit(3) for GPIOF of Tm4c123 arm-cortexM4


#define SYSCTL_RCGC2_R *((volatile unsigned int*)(0x400FE000+0x108))
#define GPIO_PORTF_DIR_R *((volatile unsigned int*)(0x40025000+0x400))
#define GPIO_PORTF_DEN_R *((volatile unsigned int*)(0x40025000+0x51C))
#define GPIO_PORTF_DATA_R *((volatile unsigned int*)(0x40025000+0x3FC))





int main()


{

   volatile int i;

    SYSCTL_RCGC2_R =0X20;                                     // clock for GPIO
    for(i=0; i<500; i++);                                    // delay to make sure that the GPIO is up & running 
    GPIO_PORTF_DIR_R |= 1<<3;                               // GPIO direction is output
    GPIO_PORTF_DEN_R|= 1<<3;                               // Enable GPIO

 while(1)
{
     GPIO_PORTF_DATA_R |= 1<<3;
     for(i=0; i<20000; i++);
     GPIO_PORTF_DATA_R &= ~(1<<3);                                      // toggle pin no.3
      for(i=0; i<20000; i++);


}

}



