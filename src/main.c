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

void init_routine() {
	initLCDcontroller();
	// ((void(*)(void))0x384)();
	// *(volatile uint8_t*)0xF80018 = 0x08;
	// *(volatile uint8_t*)0xF80018 = 0x44;
	// *(volatile uint8_t*)0xF80018 = 0x21;
	// *(volatile uint8_t*)0xF80008 = 0x01;

	// Timers
	timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP);

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