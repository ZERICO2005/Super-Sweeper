/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	x86_ti84ce.h simulates libraries and functions from the CE Programming Toolchain.
**	Some functions may not be completely accurate or fully implemented.
*/

#ifndef X86_TI84CE_H
#define X86_TI84CE_H

#include "x86_Common_Def.h"

/* <sys/lcd.h> */

	extern uint8_t simulated_ram[16777216];

	#define RAM_ADDRESS(x) ((void*)&simulated_ram[x])

	#define lcd_Ram                  ((void*)&simulated_ram[0xD40000])
	#define lcd_Ram8                 ((uint8_t*)&simulated_ram[0xD40000])
	#define lcd_Ram16                ((uint16_t*)&simulated_ram[0xD40000])

	#define lcd_Timing0              (*(volatile uint32_t*)&simulated_ram[0xE30000])
	#define lcd_Timing1              (*(volatile uint32_t*)&simulated_ram[0xE30004])
	#define lcd_Timing2              (*(volatile uint32_t*)&simulated_ram[0xE30008])
	#define lcd_Timing3              (*(volatile uint24_t*)&simulated_ram[0xE3000C])
	#define lcd_UpBase               (*(volatile uint24_t*)&simulated_ram[0xE30010])
	#define lcd_UpBaseFull           (*(volatile uint32_t*)&simulated_ram[0xE30010])
	#define lcd_LpBase               (*(volatile uint24_t*)&simulated_ram[0xE30014])
	#define lcd_LpBaseFull           (*(volatile uint32_t*)&simulated_ram[0xE30014])

	#define lcd_Control              (*(volatile uint24_t*)&simulated_ram[0xE30018])
	#define lcd_VideoMode            (*(volatile uint16_t*)&simulated_ram[0xE30018])
	#define lcd_VideoBit             (*(volatile uint8_t*)&simulated_ram[0xE30018])

	#define lcd_EnableInt            (*(volatile uint8_t*)&simulated_ram[0xE3001C])
	#define lcd_IntStatus            (*(volatile uint8_t*)&simulated_ram[0xE30020])
	#define lcd_IntStatusMasked      (*(volatile uint8_t*)&simulated_ram[0xE30024])
	#define lcd_IntAcknowledge       (*(volatile uint8_t*)&simulated_ram[0xE30028])
	#define lcd_UpBaseCurr           (*(volatile uint24_t*)&simulated_ram[0xE3002C])
	#define lcd_UpBaseCurrFull       (*(volatile uint32_t*)&simulated_ram[0xE3002C])
	#define lcd_LpBaseCurr           (*(volatile uint24_t*)&simulated_ram[0xE30030])
	#define lcd_LpBaseCurrFull       (*(volatile uint32_t*)&simulated_ram[0xE30030])

	#define lcd_Palette              ((uint16_t*)&simulated_ram[0xE30200])

	#define lcd_CrsrImageLen32       256
	#define lcd_CrsrImageLen64       1024
	#define lcd_CrsrImage            ((uint8_t*)&simulated_ram[0xE30800])
	#define lcd_CrsrCtrl             (*(volatile uint8_t*)&simulated_ram[0xE30C00])
	#define lcd_CrsrConfig           (*(volatile uint8_t*)&simulated_ram[0xE30C04])
	#define lcd_CrsrPalette0         (*(volatile uint24_t*)&simulated_ram[0xE30C08])
	#define lcd_CrsrPalette1         (*(volatile uint24_t*)&simulated_ram[0xE30C0C])
	#define lcd_CrsrXY               (*(volatile uint24_t*)&simulated_ram[0xE30C10])
	#define lcd_CrsrXYFull           (*(volatile uint32_t*)&simulated_ram[0xE30C10])
	#define lcd_CrsrX                (*(volatile uint16_t*)&simulated_ram[0xE30C10])
	#define lcd_CrsrY                (*(volatile uint8_t*)&simulated_ram[0xE30C12])
	#define lcd_CrsrYFull            (*(volatile uint16_t*)&simulated_ram[0xE30C12])
	#define lcd_CrsrClip             (*(volatile uint16_t*)&simulated_ram[0xE30C04])
	#define lcd_CrsrClipX            (*(volatile uint8_t*)&simulated_ram[0xE30C04])
	#define lcd_CrsrClipY            (*(volatile uint8_t*)&simulated_ram[0xE30C05])
	#define lcd_CrsrEnableInt        (*(volatile uint8_t*)&simulated_ram[0xE30C20])
	#define lcd_CrsrIntAcknowledge   (*(volatile uint8_t*)&simulated_ram[0xE30C24])
	#define lcd_CrsrIntStatus        (*(volatile uint8_t*)&simulated_ram[0xE30C28])
	#define lcd_CrsrIntStatusMasked  (*(volatile uint8_t*)&simulated_ram[0xE30C2C])

	#define lcd_BacklightLevel       (*(volatile uint8_t*)&simulated_ram[0xF60024])

	#define LCD_WIDTH                (320)
	#define LCD_HEIGHT               (240)
	#define LCD_SIZE                 (LCD_WIDTH * LCD_HEIGHT * 2)

	#define LCD_RESX                 (320)
	#define LCD_RESY                 (240)

	void resetLCDcontroller();

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

/* SPI Controller (Unimplemented) */
	//	https://wikiti.brandonw.net/index.php?title=84PCE:Ports:D000

	#define SPI_CR0                    ((volatile void*)&simulated_ram[0xF80000])
	#define SPI_CR1                    ((volatile void*)&simulated_ram[0xF80004])
	#define SPI_CR2                    ((volatile void*)&simulated_ram[0xF80008])
	#define SPI_STATUS_BITS            ((volatile void*)&simulated_ram[0xF8000C]) /* Read Only */
	#define SPI_INTERRUPT_CONTROL      ((volatile void*)&simulated_ram[0xF80010])
	#define SPI_INTERRUPT_STATUS       ((volatile void*)&simulated_ram[0xF80014]) /* Read Only */
	#define SPI_FIFO_IN_OUT            ((volatile void*)&simulated_ram[0xF80018])
	#define SPI_FIFO_IN_OUT8           (*(volatile uint8_t*)&simulated_ram[0xF80018])
	#define SPI_FIFO_IN_OUT16          (*(volatile uint16_t*)&simulated_ram[0xF80018])
	#define SPI_FIFO_IN_OUT24          (*(volatile uint24_t*)&simulated_ram[0xF80018])
	#define SPI_FIFO_IN_OUT32          (*(volatile uint32_t*)&simulated_ram[0xF80018])
	#define SPI_INSIDE_RESERVED_RANGE  ((volatile void*)&simulated_ram[0xF8001C])
	#define SPI_REVISION               ((volatile void*)&simulated_ram[0xF80060]) /* Read Only */
	#define SPI_FEATURES               (*(volatile uint32_t*)&simulated_ram[0xF80064]) /* Read Only */
	
	// Supplemental Functions
	void SPI_Row_Major();
	void SPI_Column_Major();

/* <keypadc.h> */

	extern uint8_t kb_Data[8];

	enum keypadc_h_kb {
		kb_Graph = 1    , kb_Trace = 2  , kb_Zoom = 4   , kb_Window = 8 , kb_Yequ = 16  , kb_2nd = 32   , kb_Mode = 64  , kb_Del = 128      ,
		                  kb_Sto = 2    , kb_Ln = 4     , kb_Log = 8    , kb_Square = 16, kb_Recip = 32 , kb_Math = 64  , kb_Alpha = 128    ,
		kb_0 = 1        , kb_1 = 2      , kb_4 = 4      , kb_7 = 8      , kb_Comma = 16 , kb_Sin = 32   , kb_Apps = 64  , kb_GraphVar = 128 ,
		kb_DecPnt = 1   , kb_2 = 2      , kb_5 = 4      , kb_8 = 8      , kb_LParen = 16, kb_Cos = 32   , kb_Prgm = 64  , kb_Stat = 128     ,
		kb_Chs = 1      , kb_3 = 2      , kb_6 = 4      , kb_9 = 8      , kb_RParen = 16, kb_Tan = 32   , kb_Vars = 64  ,
		kb_Enter = 1    , kb_Add = 2    , kb_Sub = 4    , kb_Mul = 8    , kb_Div = 16   , kb_Power = 32 , kb_Clear = 64 ,
		kb_Down = 1     , kb_Left = 2   , kb_Right = 4  , kb_Up = 8
	};

	void kb_Reset();
	void kb_Scan();

/* <sys/timers.h> */

	#define TIMER_32K                1  /**< Use the 32K clock for timer */
	#define TIMER_CPU                0  /**< Use the CPU clock rate for timer */
	#define TIMER_0INT               1  /**< Enable an interrupt when 0 is reached for the timer */
	#define TIMER_NOINT              0  /**< Disable interrupts for the timer */
	#define TIMER_UP                 1  /**< Timer counts up */
	#define TIMER_DOWN               0  /**< Timer counts down */

	// Rate: (0,15MHz) (1,32KHz). n is supposed to be a value between 1 and 3
	void timer_Enable(uint8_t n, uint8_t rate, uint8_t inter, uint8_t dir);
	// n is supposed to be a value between 1 and 3
	void timer_Disable(uint8_t n);
	// n is supposed to be a value between 1 and 3
	uint32_t timer_Get(uint8_t n);

/* <fileioc.h> */
	// Limited Implementation
	#define FILEIOC_DEBUG
	#ifdef FILEIOC_DEBUG
		#define printf_FileIOC(...) printf(__VA_ARGS__); fflush(stdout);
	#else
		#define printf_FileIOC(...)
	#endif
	
	#define SEEK_SET 0
	#define SEEK_CUR 1
	#define SEEK_END 2
	#ifndef EOF
		#define EOF (-1)
	#endif

	uint8_t ti_Open(const char* name, const char* mode);
	int ti_Close(uint8_t handle);
	
	size_t ti_Read(void* data, size_t size, size_t count, uint8_t handle);
	size_t ti_Write(const void* data, size_t size, size_t count, uint8_t handle);
	
	int24_t ti_PutC(char ch, uint8_t handle);
	int24_t ti_GetC(uint8_t handle);

	int24_t ti_Seek(int24_t offset, uint24_t origin, uint8_t handle);
	uint16_t ti_GetSize(uint8_t handle);
	int24_t ti_Rewind(uint8_t handle);
	void* ti_GetDataPtr(uint8_t handle);

#endif /* X86_TI84CE_H */