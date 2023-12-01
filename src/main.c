/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <math.h>
//#include <ti/getcsc.h>
//#include <keypadc.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/rtc.h>
//#include <fileioc.h>
//#include <ti/screen.h>
//#include <sys/timers.h>
#include <stdint.h>
#include "prime2D.h"
#include "mineSweeper.h"
#include "menu.h"
#include "global.h"
#include "video.h"
#include <string.h>
#include "x86render.h"
//#include <col.h>

/*
cd "C:\Users\erico\Documents\Programming\superSweeper"
cd "C:\Users\Eric Ross\Documents\Super-Sweeper-CE"
cd "C:\Users\\Documents\Programming\Super-Sweeper-CE"

cd "C:\Users\
\Documents\Programming\Super-Sweeper-CE"
*/
//0.71.3 2023/02/16 21:58

/*
It is CRITICAL to fix system time, something allows it to overflow randomly,abtract it so it updates when it is read by a variable or something
*/

//When were these suggestions added? Only Git knows now. 

//Implement sliders and proper preset selection

//Changed flag color to accessability mode
//Fixed percent and mines in custom and added some wack code to it
//Added video intro

//Some asm speed up in prime2D.h, 118fps to 159fps
//Font changes too in the 0.64.0 update, brought back frame base shifter thing

//finsih up the menu and get beack to school work
//Add europe text next

//Add file saving and loading
//And the silver colored mine somehow (Fixed)
//Aranges variables so settings can write to them without temp arrays
//Fix the menus
//Fix the fade effect and the timers and wrist watch clocks
//Why am I using the flagCountColor variable to toggle quake mode?
//Exiting is broken in pause menus from keys being replaced

void hidden6x8(uint24_t xW, uint24_t yW, uint8_t lexicon) {
    uint8_t* bitImage = (uint8_t*)char6x8 + (lexicon * 6);
    uint16_t* fill = (uint16_t*)VRAM + (yW * 320 + xW);
    uint8_t b = 1;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 6; x++) {
            *fill = *bitImage & b ? 16392 : *fill;
            bitImage++;
            fill++;
        }
        bitImage -= 6;
        fill += 314; // 320 - 6

        b <<= 1;
    }
}

void restore() {
    *lcd_CrsrConfig = 0x00000000;
    *lcd_CrsrCtrl = 0x00000000;
    *LCDTiming2 = (uint32_t)(*LCDTiming2 & ~(uint32_t)0x03FF0000) | (uint32_t)(240 - 1) << 16;
    *frameBase = 0xD40000;
    if (darkMode) { //Reverts to normal Mode
	/*
        ((void(*)(void))0x384)();
        *(volatile uint8_t*)0xF80018 = 0x08;
        *(volatile uint8_t*)0xF80018 = 0x44;
        *(volatile uint8_t*)0xF80018 = 0x20;
        *(volatile uint8_t*)0xF80008 = 0x01;
	*/
    }
    kb_Reset();
    *videoMode = 0x92D;
}

int main(void) {
    //printf("\nStarting\n"); fflush(stdout);
    initLCDcontroller();
    //printf("Ready\n"); fflush(stdout);
    //timer_Enable(1, TIMER_32K, TIMER_NOINT, TIMER_UP); //Restart clock
    systemTime = timer_Get(1);
    #ifdef VIDEO //Toggles video player code
        if (1) { //Video Player Code
            *videoMode = 0x925; //4bit mode 1001 0010 0101
            gColor = 0;
            fillScreen();
            uint8_t exitVideo = splashVideo();
            if (exitVideo == 1) { //If user decides to force quit program
                restore();
                return 0;
            }
            if (exitVideo == 0) {
                gColor = 0;
                fillScreen();
                delay32K(32768/3);
            }
        }
    #endif /* VIDEO */

    *videoMode = 0x927; //8bit mode 1001 0010 0111

    gColor = 0;
    for (uint24_t y = 256; y < 400; y += 9) {
        for (uint24_t x = 0; x < 144; x += 9) {
            fillRect(x,y,8,8);
            gColor++;
        }
    }

    for (u16 r = 0; r < 256; r++) {
        paletteRAM[r] = initialPalette[r];
    }

    hidden6x8(2, 230, 50);
    {
        uint24_t xW = 10;
        for (uint8_t j = 0; j < hiddenTextLength; j++) { //Change me as well
            hidden6x8(xW, 230, hiddenText[j]);
            xW += 7;
        }
    } //Hidden text
    hidden6x8(312, 230, 50);

    fpsT = 32768 / FPS; //Sets fpsTemp for settings menu
    fontSize = 7;

    menuLoop();

    restore();
    terminateLCDcontroller();
    return 0;
}