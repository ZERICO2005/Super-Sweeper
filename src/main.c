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

void init_routine() {
	initLCDcontroller("Super-Sweeper v" STR_N(PROGRAM_V_MAJOR) "." STR_N(PROGRAM_V_MINOR) "." STR_N(PROGRAM_V_PATCH));
	#ifndef SWAP_X_AND_Y_CORD
		SPI_Row_Major();
	#else
		SPI_Column_Major();
	#endif
	// ((void(*)(void))0x384)();
	// SPI_FIFO_IN_OUT8 = 0x08;
	// SPI_FIFO_IN_OUT8 = 0x44;
	// SPI_FIFO_IN_OUT8 = 0x21;
	// SPI_CR2 = 0x01;

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