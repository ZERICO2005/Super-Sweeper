/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "global.h"
#include "prime2D.h"
#include "menu.h"
#include "fmVideo.h"



#ifdef PLATFORM_TI84CE
	//#include "SPI.h"
void SPI_Row_Major() {
	boot_InitializeHardware();
    SPI_COMMAND(0x36);
    SPI_PARAMETER(0b00001000); // Column Major Mode and BGR bit

    SPI_COMMAND(0x2A);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0x00);
    SPI_PARAMETER(0x01); SPI_PARAMETER(0x3F);

	SPI_COMMAND(0x2B);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0x00);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0xEF);
	*(volatile uint8_t*)SPI_CR2 = 0x01;
}

void SPI_Column_Major() {
    boot_InitializeHardware();
    SPI_COMMAND(0x36);
    SPI_PARAMETER(0b00101000); // Column Major Mode and BGR bit

    SPI_COMMAND(0x2A);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0x00);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0xEF);
    
    SPI_COMMAND(0x2B);
    SPI_PARAMETER(0x00); SPI_PARAMETER(0x00);
    SPI_PARAMETER(0x01); SPI_PARAMETER(0x3F);
	*(volatile uint8_t*)SPI_CR2 = 0x01;
}
#endif

void init_routine() {
	initLCDcontroller("Super-Sweeper v" STR_N(PROGRAM_V_MAJOR) "." STR_N(PROGRAM_V_MINOR) "." STR_N(PROGRAM_V_PATCH));
	// #ifndef SWAP_X_AND_Y_CORD
	// 	SPI_Row_Major();
	// #else
	// 	SPI_Column_Major();
	// #endif
	SPI_Column_Major();
	// ((void(*)(void))0x384)();
	// SPI_FIFO_IN_OUT8 = 0x08;
	// SPI_FIFO_IN_OUT8 = 0x44;
	// SPI_FIFO_IN_OUT8 = 0x21;
	// *(volatile uint8_t*)SPI_CR2 = 0x01;

	// Timers
	timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);

	//playIntroVideo();
	// Video
	memcpy(lcd_Palette,initialPalette,256 * sizeof(uint16_t));
	lcd_UpBase = 0xD40000;
	lcd_VideoMode = lcd_BGR8bit;
}

void terminate_routine() {
	terminateLCDcontroller();
	SPI_Row_Major();
	lcd_UpBase = 0xD40000;
	lcd_VideoMode = lcd_BGR16bit;
}

int main() {
	init_routine();

	// Palette Test
	// gColor = 0;
	// for (uint24_t y = 256; y < 400; y += 9) {
	// 	for (uint24_t x = 0; x < 144; x += 9) {
	// 		fillRect(x,y,8,8);
	// 		gColor++;
	// 	}
	// }

    fpsT = 32768 / FPS; //Sets fpsTemp for settings menu
    fontSize = 7;

    menuLoop();
	
	terminate_routine();
    return 0;
}