/*
**	Author: zerico2005 (2023-2024)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include <stdint.h>
#include <string.h>

#define PROGRAM_V_MAJOR 0
#define PROGRAM_V_MINOR 81
#define PROGRAM_V_PATCH 4

#define PLATFORM_TI84CE
//#define PLATFORM_X86

//#define DEBUG_FRAMERATE_COUNTER // Shows FPS and Frame-Time
//#define DEBUG_FRAME_SHIFT // Use the numberpad to move the screen around

#define SWAP_X_AND_Y_CORD

#ifdef PLATFORM_TI84CE
	/* Disabled Functions */
		#define newFrame()
		#define initLCDcontroller(...)
		#define terminateLCDcontroller()
	/* Includes */
		#include <ti/getcsc.h>
		#include <keypadc.h>
		#include <sys/rtc.h>
		#include <fileioc.h>
		#include <ti/screen.h>
		#include <sys/timers.h>
		#include <sys/lcd.h>

		//#include "spi_commands.h"
	/* Additional Definitions */
		#define RAM_ADDRESS(x) ((void*)(x))

		#define LCD_RESX                 (320)
		#define LCD_RESY                 (240)
		#define lcd_Ram8                 ((uint8_t*)0xD40000)
		#define lcd_Ram16                ((uint16_t*)0xD40000)
		#define lcd_VideoMode            (*(volatile uint16_t*)0xE30018)
		#define lcd_VideoBit             (*(volatile uint8_t*)0xE30018)
		#define lcd_Palette              ((uint16_t*)0xE30200)

		#define lcd_RGB1bit 0x821
		#define lcd_RGB2bit 0x823
		#define lcd_RGB4bit 0x825
		#define lcd_RGB8bit 0x827
		#define lcd_RGB16bit 0x82D

		#define lcd_BGR1bit 0x921
		#define lcd_BGR2bit 0x923
		#define lcd_BGR4bit 0x925
		#define lcd_BGR8bit 0x927
		#define lcd_BGR16bit 0x92D

		#define lcd_Video1bit 0x21
		#define lcd_Video2bit 0x23
		#define lcd_Video4bit 0x25
		#define lcd_Video8bit 0x27
		#define lcd_Video16bit 0x2D

		#define SPI_CR0                    ((volatile void*)0xF80000)
		#define SPI_CR1                    ((volatile void*)0xF80004)
		#define SPI_CR2                    ((volatile void*)0xF80008)
		#define SPI_STATUS_BITS            ((volatile void*)0xF8000C) /* Read Only */
		#define SPI_INTERRUPT_CONTROL      ((volatile void*)0xF80010)
		#define SPI_INTERRUPT_STATUS       ((volatile void*)0xF80014) /* Read Only */
		#define SPI_FIFO_IN_OUT            ((volatile void*)0xF80018)
		#define SPI_FIFO_IN_OUT8           (*(volatile uint8_t*)0xF80018)
		#define SPI_FIFO_IN_OUT16          (*(volatile uint16_t*)0xF80018)
		#define SPI_FIFO_IN_OUT24          (*(volatile uint24_t*)0xF80018)
		#define SPI_FIFO_IN_OUT32          (*(volatile uint32_t*)0xF80018)
		#define SPI_INSIDE_RESERVED_RANGE  ((volatile void*)0xF8001C)
		#define SPI_REVISION               ((volatile void*)0xF80060) /* Read Only */
		#define SPI_FEATURES               (*(volatile uint32_t*)0xF80064) /* Read Only */

		#define boot_InitializeHardware()  ((void(*)(void))0x384)(); // Used in the color invert commands

		/* Disabled Functions */
			// #define SPI_Row_Major()
			// #define SPI_Column_Major()
#else
	#include "x86_Common_Def.h"
	#include "x86_ti84ce.h"
	#include "x86_Render.h"
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#ifdef PLATFORM_TI84CE
	typedef uint24_t u24;
	typedef int24_t i24;
#endif


/* Functions */

	#define STR_M(x) #x
	#define STR_N(x) STR_M(x)

	#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
	#define FREE(x) free(x); x = NULL

	// Left Circular Shift
	#define ROL(n,b) (((n) << (b)) | ((n) >> ((sizeof(n) * 8) - (b))))
	// Right Circular Shift
	#define ROR(n,b) (((n) >> (b)) | ((n) << ((sizeof(n) * 8) - (b))))

	#define valueLimit(value,minimum,maximum) { if ((value) < (minimum)) { (value) = (minimum); } else if ((value) > (maximum)) { (value) = (maximum); } }
	#define valueMinimum(value,minimum) { if ((value) < (minimum)) { (value) = (minimum); } }
	#define valueMaximum(value,maximum) { if ((value) > (maximum)) { (value) = (maximum); } }

	#define linearInterpolation(x,x0,x1,y0,y1) ( (y0) + ( (((y1) - (y0)) * ((x) - (x0))) / ((x1) - (x0)) ) )
	#define linearInterpolationClamp(x,x0,x1,y0,y1) ( ((x) <= (x0)) ? (y0) : ( ((x) >= (x1)) ? (y1) : linearInterpolation((x),(x0),(x1),(y0),(y1)) ) )

	#define SPI_COMMAND(x) \
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = ((x) >> 6) & 0b111;\
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = ((x) >> 3) & 0b111;\
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = (x) & 0b111

	#define SPI_PARAMETER(x) \
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = (((x) >> 6) & 0b111) | 0b100;\
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = ((x) >> 3) & 0b111;\
	*(volatile uint8_t*)SPI_FIFO_IN_OUT = (x) & 0b111;

#endif /* COMMON_DEF_H */