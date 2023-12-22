/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "primeKey.h"

#include "global.h"
#include "prime2D.h"

/* Key Constants */
void keyReset(uint8_t type);
const uint8_t HORIZ = 1; const uint8_t VERT = 2; const uint8_t ALPHA = 4; const uint8_t SECOND = 8; const uint8_t OTHER = 16; const uint8_t DEBUG = 32; const uint8_t ARROW = 64; const uint8_t CHORD = 128;
const uint8_t hORIZ = 0; const uint8_t vERT = 1; const uint8_t aLPHA = 2; const uint8_t sECOND = 3; const uint8_t oTHER = 4; const uint8_t dEBUG = 5; const uint8_t aRROW = 6; const uint8_t cHORD = 7;
//uint8_t key = 0; //Compatibility

uint32_t keyDelay[keyTotal] = {2304, 3072, 4096, 4096, 2730, 1638, 3072, 2730}; //0 Horiz, 1 Vert, 2 Alpha, 3 Second, 4 Other, 5 Debug, 6 Arrow
uint32_t keyPressTime[keyTotal] = {0,0,0,0,0,0,0,0};

uint8_t keyReady = 255; //1 Horiz, 2 Vert, 4 Alpha, 8 Second, 16 Other, 32 Debug, 64 Arrow
/* Key Constants */

/* Utilities */
void quitGame() { //Placeholder
	//key = 99;
    status = FORCEQUIT;
}

void shiftScreen() { //Moves the frame base around
    uint8_t change = 0;
    if (DEBUG & keyReady) {
        keyReset(dEBUG);
        if (kb_Data[4] & kb_8) { //Up
            lcd_UpBase -= 2560;
            change = 1;
        } 
        if (kb_Data[4] & kb_2) { //Down
            lcd_UpBase += 2560;
            change = 1;
        }
        if (kb_Data[5] & kb_6) { //Right
            lcd_UpBase += 8;
            change = 1;
        } 
        if (kb_Data[3] & kb_4) { //Left
            lcd_UpBase -= 8;
            change = 1;
        }
        if (kb_Data[4] & kb_5) { //Reset
            lcd_UpBase = 0xD40000;
            change = 1;
        }
        if (change) {
            printUInt(lcd_UpBase,6,16,56,2);
        }
    }
}
/* Utilities */

/* Keyboard */

uint32_t deltaTime(uint32_t current, uint32_t previous) { //Calculates delta time through overflows
    if (current >= previous) {
        return current - previous;
    }
    return ~(previous - current) + 1; //16777215 - ()
}

void delay32K(uint32_t delay) { //32768hz, overflow resiliant
    uint32_t start = timer_Get(1);
    while (deltaTime(timer_Get(1), start) < delay);
}

void keyReset(uint8_t type) {
    keyReady = keyReady & ~(1 << type);
    keyPressTime[type] = timer_Get(1);
    //recentKeyPress
}

void keyPress() { //Makes the game run at a constant FPS
    uint24_t frameDelta = 0; //stores the time between frames
    uint24_t frameTime = 0; //stores timer_Get(1)

	// static fp64 nStart = 0.0;
	// static fp64 nFinish = 0.0;
	// nFinish = getDecimalTime();
	// printf("\nTime: %.2lfms FPS: %.2lf",(nFinish - nStart) * 1000.0, 1.0 / (nFinish - nStart));
	// fflush(stdout);
	newFrame();
	do {
        frameTime = timer_Get(1); //frameTime and seed are the same so I only need to call timer_Get(1) once
        if (frameTime >= frameStart) {
            frameDelta = frameTime - frameStart;
        } else { //Overflow case
            frameDelta = (~(frameStart - frameTime)) + 1;
        }
    } while (frameDelta < FPS);
	// nStart = getDecimalTime();

    systemTime = frameTime;

	#ifdef DEBUG_FRAMERATE_COUNTER
		if (fpsCounter) {
			if (frameDelta > clockMax) { clockMax = frameDelta; } //Tracks the highest frame time
			if (deltaTime(timer_Get(1), clockTime) > (32768 / 6)) { //Displays the highest frame time every 32768/FPS seconds
				printUInt(clockMax, 5, 10, 2, 22); //Displays frame time
				printUInt(32768 / clockMax, 3, 10, 2, 31); //Displays FPS
				clockMax = 0;
				clockTime = timer_Get(1);
			}
		}
	#endif

    shiftScreen();

    frameStart = timer_Get(1);
    for (uint8_t i = 0; i < keyTotal; i++) {
        if ((deltaTime(frameStart, keyPressTime[i])) >= keyDelay[i]) {
            keyReady = keyReady | (1 << i); //Turns on a bit
        }
    }
    kb_Scan();

    seed = timer_Get(1); //temporary soultion
    if (kb_Data[1] & (kb_Graph | kb_Del)) { //temporary soultion
        status = FORCEQUIT;
    }


    return;
}
/* Keyboard */