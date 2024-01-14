/*
 * utils.h
 *
 * Created: 11/01/2024 09:37:56 م
 *  Author: lenovo
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define Set_bit(port,bit)				(port |= (1<<bit) )
#define Clear_bit(port,bit)				(port &= ~(1<<bit) )
#define Toggle_bit(port,bit)			(port ^= (1<<bit) )
#define Read_bit(port,bit)				((port & (1<<bit)) >> bit )


#define S_Reg						   (*(unsigned char*)0x5F)



#endif /* UTILS_H_ */