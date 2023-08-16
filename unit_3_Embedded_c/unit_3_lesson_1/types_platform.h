/*
 * types_platform.h
 *
 *  Created on: Aug 16, 2023
 *      Author: ahmed
 */

#ifndef TYPES_PLATFORM_H_
#define TYPES_PLATFORM_H_
#include "stdbool.h"

typedef _Bool boolean;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef char sint8_t;                            //types
typedef short sint16_t;
typedef int sint32_t;
typedef long long sint64_t;
typedef float float32_t;
typedef double float64_t;
typedef void* voidptr_t;
typedef const void* constvoidptr_t;
typedef volatile unsigned char vuint8_t;
typedef volatile unsigned short vuint16_t;
typedef volatile unsigned int vuint32_t;
typedef volatile unsigned long long vuint64_t;
typedef volatile char vsint8_t;
typedef volatile short vsint16_t;
typedef volatile int vsint32_t;
typedef long long vsint64_t;
typedef volatile float vfloat32_t;
typedef volatile double vfloat64_t;




#define True ((_Bool)1);		// Definitions
#define False ((_Bool)0);


#endif /* TYPES_PLATFORM_H_ */
