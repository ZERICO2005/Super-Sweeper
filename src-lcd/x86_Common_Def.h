/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef X86_COMMON_DEF_H
#define X86_COMMON_DEF_H

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/* Platform */

#define PLATFORM_WINDOWS
//#define PLATFORM_LINUX

typedef signed _BitInt(24) int24_t;
typedef unsigned _BitInt(24) uint24_t;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint24_t u24;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int24_t i24;
typedef int32_t i32;
typedef int64_t i64;

typedef float fp32;
typedef double fp64;

/* Constants */

#define PI 		3.1415926535897932384626433832795
#define TAU 	6.2831853071795864769252867665590
#define EULER 	2.7182818284590452353602874713527

/* Functions */

	#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
	#define FREE(x) free(x); x = NULL

	// Left Circular Shift
	#define ROL(n,b) (((n) << (b)) | ((n) >> ((sizeof(n) * 8) - (b))))
	// Right Circular Shift
	#define ROR(n,b) (((n) >> (b)) | ((n) << ((sizeof(n) * 8) - (b))))

	#define valueLimit(value,minimum,maximum) { if ((value) < (minimum)) { (value) = (minimum); } else if ((value) > (maximum)) { (value) = (maximum); } }
	#define valueMinimum(value,minimum) { if ((value) < (minimum)) { (value) = (minimum); } }
	#define valueMaximum(value,maximum) { if ((value) > (maximum)) { (value) = (maximum); } }

	#define MAX(a,b) (((a) > (b)) ? (a) : (b))
	#define MIN(a,b) (((a) < (b)) ? (a) : (b))

	#define linearInterpolation(x,x0,x1,y0,y1) ( (y0) + ( (((y1) - (y0)) * ((x) - (x0))) / ((x1) - (x0)) ) )
	#define linearInterpolationClamp(x,x0,x1,y0,y1) ( ((x) <= (x0)) ? (y0) : ( ((x) >= (x1)) ? (y1) : linearInterpolation((x),(x0),(x1),(y0),(y1)) ) )

/* Time */

	int64_t getNanoTime();
	fp64 getDecimalTime();

#endif /* X86_COMMON_DEF_H */