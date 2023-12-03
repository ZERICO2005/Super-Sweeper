/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef PRIME2D_H
#define PRIME2D_H
#include "x86render.h"
#include "global.h"
#include <stdint.h>

#include "prime2D_Font6x8.h"

uint8_t gColor = 0; //Graphics color

const uint16_t char3x5[28] = {
	0x7B6F, 0x749A, 0x73E7, 0x79A7, 0x49ED, 0x79CF, 0x7BCF, 0x24A7, 0x2AAA, 0x79EF, 0x5BEF, 0x7AEF, 0x624E, 0x3B6B, 0x72CF, 0x12CF, 0x5AAD, 0,0,0,0,0,0,0,0, 0x55D5, 0x7480, 0x21A7
};
const uint16_t char5x5[56] = {
	22335,1011, 4292,452, 32287,993, 29215,1008, 31909,132, 31807,1008, 31807,1009, 28959,264, 14894,465, 32319,1008, 22205,949, 19314,594, 30269,933, 26173,945, 30389,561, 29885,945, 29885,949,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	32213,686, 4228,996, 8750,128
};

// const uint8_t char6x8[768]; // See prime2D_Font6x8.h

//Debugging
const uint16_t num3x5[16] = {
	0x7B6F, 0x749A, 0x73E7, 0x79A7, 0x49ED, 0x79CF, 0x7BCF, 0x24A7, 0x7AAF, 0x79EF,
	0x5BEF, 0x7BC9, 0x724F, 0x7BE4, 0x72CF, 0x12CF
}; //Used for the printInt functions
void printInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC) { //integer to print, length, base 2-16 //Auto adjusts for signage
    uint8_t* off = (uint8_t*)VRAM + xC + (320 * yC);
    uint8_t* v = off + 320;
    len <<= 2; //len * 4
    const uint24_t x2 = 5 + len;
    const uint24_t jump = 317 - x2;
    for (uint8_t dY = 1; dY < 6; dY++) {
        for (uint24_t dX = 0; dX < x2; dX += 4) {
            *v = 0;
            v += 4;
        }
        v += jump;
    }
    v = off;
    for (uint24_t dX = 0; dX < x2; dX++) {
        *v = 0;
        v++;
    }
    v = off + 1920; // 320 * 6
    for (uint24_t dX = 0; dX < x2; dX++) {
        *v = 0;
        v++;
    }

    uint24_t* negSign = 961 + (uint24_t*)off; //Fills three pixels //1 + (3 * 320)
    *negSign = in < 0 ? 460551 : 0; //If Negative
    uint24_t j = abs(in);
    uint24_t pow = 1;
    for (uint24_t k = 0; k < len; k += 4) {
        uint16_t bitImage = num3x5[(j / pow) % base];
        uint8_t *fill = off + 321 + len - k;
        for (uint8_t y = 0; y < 5; y++) {
            for (uint8_t x = 0; x < 3; x++) {
                *fill = bitImage & 1 ? 7 : 0; //White if true
                bitImage >>= 1;
                fill++;
            }
            fill += 317; //320 - 3
        }
        pow *= base;
    }
}
void printUInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC) { //integer to print, length, base 2-16
    uint8_t* off = (uint8_t*)VRAM + xC + (320 * yC); //Something about casting off to uint8_t* adds 4 more bytes
    uint8_t* v = off + 320;
    len <<= 2; //len * 4
    const uint24_t x2 = 1 + len; //Can optomize out "1 + " for a saving of 8 bytes
    const uint24_t jump = 317 - x2;
    for (uint8_t dY = 1; dY < 6; dY++) {
        for (uint24_t dX = 0; dX < x2; dX += 4) {
            *v = 0;
            v += 4;
        }
        v += jump;
    }
    v = off;
    for (uint24_t dX = 0; dX < x2; dX++) {
        *v = 0;
        v++;
    }
    v = off + 1920; // 320 * 6
    for (uint24_t dX = 0; dX < x2; dX++) {
        *v = 0;
        v++;
    }
    uint24_t pow = 1;
    for (uint24_t k = 0; k < len; k += 4) {
        uint16_t bitImage = num3x5[(in / pow) % base];
        uint8_t* fill = off + 317 + len - k;
        for (uint8_t y = 0; y < 5; y++) {
            for (uint8_t x = 0; x < 3; x++) {
                *fill = bitImage & 1 ? 7 : 0; //White if true
                bitImage >>= 1;
                fill++;
            }
            fill += 317; //320 - 3
        }
        pow *= base;
    }
}

/* Key Constants */
void keyReset(uint8_t type);
const uint8_t HORIZ = 1; const uint8_t VERT = 2; const uint8_t ALPHA = 4; const uint8_t SECOND = 8; const uint8_t OTHER = 16; const uint8_t DEBUG = 32; const uint8_t ARROW = 64; const uint8_t CHORD = 128;
const uint8_t hORIZ = 0; const uint8_t vERT = 1; const uint8_t aLPHA = 2; const uint8_t sECOND = 3; const uint8_t oTHER = 4; const uint8_t dEBUG = 5; const uint8_t aRROW = 6; const uint8_t cHORD = 7;
//uint8_t key = 0; //Compatibility

#define keyTotal 8 //Use different keyDelay values in different menus
uint32_t keyDelay[keyTotal] = {2304, 3072, 4096, 4096, 2730, 1638, 3072, 2730}; //0 Horiz, 1 Vert, 2 Alpha, 3 Second, 4 Other, 5 Debug, 6 Arrow
uint32_t keyPressTime[keyTotal] = {0,0,0,0,0,0,0,0};

uint8_t keyReady = 255; //1 Horiz, 2 Vert, 4 Alpha, 8 Second, 16 Other, 32 Debug, 64 Arrow
/* Key Constants */

//Primatives
void fillRect(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2) { //x start, y start, x length, y length
    uint8_t* v = (uint8_t*)VRAM + x1 + (y1 * 320);
    const uint24_t jump = 320 - x2;
    for (uint24_t dY = 0; dY < y2; dY++) {
        for (uint24_t dX = 0; dX < x2; dX++) {
            *v = gColor;
            v++;
        }
        v += jump;
    }
}
void horiz(uint24_t x1, uint24_t y, uint24_t x2) { //x start, y postion, x length
    uint8_t* z = (uint8_t*)VRAM + (x1 + x2) + (y * 320);
    for (uint8_t* fill = (uint8_t*)VRAM + x1 + (y * 320); fill < z; fill++) {
        *fill = gColor;
    }
}
void vert(uint24_t x, uint24_t y1, uint24_t y2) { //x postion, y start, y length
    uint8_t* z = (uint8_t*)VRAM + x + ((y2 + y1) * 320);
    for (uint8_t* fill = (uint8_t*)VRAM + (y1 * 320) + x; fill < z; fill += 320) {
        *fill = gColor;
    }
}
// void plot(uint24_t x, uint24_t y) { //x position, y position
//     uint8_t* fill = (uint8_t*)VRAM + x + (y * 320);
//     *fill = gColor;
// }
// void plotFast(uint8_t* z) { //Memory address
//     *z = gColor;
// }

#define plot(x,y) *((uint8_t*)VRAM + x + (y * 320)) = gColor
#define plotFast(z) *((uint8_t*)z) = gColor

// void fillScreen() { //Fills buffer 0
//     const uint24_t g = (gColor << 16) | (gColor << 8) | gColor;
//     for (uint24_t* w = (uint24_t*)VRAM; w < (uint24_t*)WRAM; w++) { //Optomized to use 24bit
//         *w = g;
//     }
// }

void fillScreen() { //Fills buffer 0
    const uint8_t g = gColor;
    for (uint8_t* w = (uint8_t*)VRAM; w < (uint8_t*)WRAM; w++) { //Optomized to use 24bit
        *w = g;
    }
}

//Text Engine
void text6x8(uint24_t xW, uint24_t yW, uint8_t lexicon) { //x position, y position, letter index
    uint8_t* bitImage = (uint8_t*)char6x8 + (lexicon * 6);
    uint8_t* fill = (uint8_t*)VRAM + (yW * 320 + xW);
    uint8_t b = 1;
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 6; x++) {
            *fill = *bitImage & b ? gColor : *fill;
            bitImage++;
            fill++;
        }
        bitImage -= 6;
        fill += 314; // 320 - 6
        b <<= 1;
    }
}

void fillText(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2) { //x start, y start, x length, y length //fillRect() that does not overwrite text
    uint8_t* v = (uint8_t*)VRAM + x1 + (y1 * 320);
    const uint24_t jump = 320 - x2;
    for (uint24_t dY = 0; dY < y2; dY++) {
        for (uint24_t dX = 0; dX < x2; dX++) {
            *v = *v ? gColor : 0;
            v++;
        }
        v += jump;
    }
}

/* Utilities */
void quitGame() { //Placeholder
	//key = 99;
    status = FORCEQUIT;
}
uint8_t linear(uint8_t y0, uint8_t y1, uint8_t x0, uint8_t x1, uint8_t x) { //Linear Interpolation algorithm
  return ((y0 * (x1 - x)) + (y1 * (x - x0))) / (x1 - x0);
}
uint8_t linear0(uint8_t y0, uint8_t y1, uint8_t x1, uint8_t x) { //x0 = 0,  Optomized Linear Interpolation algorithm
  return ((y0 * (x1 - x)) + (y1 * x)) / x1;
}

void shiftScreen() { //Moves the frame base around
    uint8_t change = 0;
    if (DEBUG & keyReady) {
        keyReset(dEBUG);
        if (kb_Data[4] & kb_8) { //Up
            *frameBase -= 2560;
            change = 1;
        } 
        if (kb_Data[4] & kb_2) { //Down
            *frameBase += 2560;
            change = 1;
        }
        if (kb_Data[5] & kb_6) { //Right
            *frameBase += 8;
            change = 1;
        } 
        if (kb_Data[3] & kb_4) { //Left
            *frameBase -= 8;
            change = 1;
        }
        if (kb_Data[4] & kb_5) { //Reset
            *frameBase = 0xD40000;
            change = 1;
        }
        if (change) {
            printUInt(*frameBase,6,16,56,2);
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

    if (fpsCounter) {
        if (frameDelta > clockMax) { clockMax = frameDelta; } //Tracks the highest frame time
        if (deltaTime(timer_Get(1), clockTime) > (32768 / 6)) { //Displays the highest frame time every 32768/FPS seconds
            printUInt(clockMax, 5, 10, 2, 22); //Displays frame time
            printUInt(32768 / clockMax, 3, 10, 2, 31); //Displays FPS
            clockMax = 0;
            clockTime = timer_Get(1);
        }
    }

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



/*
void QfillRect(uint24_t x1, uint24_t y1, uint24_t x2, uint8_t y2) {
    if (x1 >= 320) {
        printUInt(x1,8,10,200,100); printUInt(y1,8,10,200,109); printUInt(x2,8,10,200,118); printUInt(y2,3,10,200,127);
        delay32K(65536);
        return;
    }
    if (y1 >= 480) {
        printUInt(x1,8,10,200,100); printUInt(y1,8,10,200,109); printUInt(x2,8,10,200,118); printUInt(y2,3,10,200,127);
        delay32K(65536);
        return;
    }
    if (x1 + x2 >= 320) {
        printUInt(x1,8,10,200,100); printUInt(y1,8,10,200,109); printUInt(x2,8,10,200,118); printUInt(y2,3,10,200,127);
        delay32K(65536);
        return;
    }
    if (y1 + y2 >= 480) {
        printUInt(x1,8,10,200,100); printUInt(y1,8,10,200,109); printUInt(x2,8,10,200,118); printUInt(y2,3,10,200,127);
        delay32K(65536);
        return;
    }
    fillRect(x1,y1,x2,y2);
}
void Qhoriz(uint24_t x1, uint24_t y, uint24_t x2) {
    if (x1 >= 320) {
        printUInt(x1,8,10,200,140); printUInt(y,8,10,200,149); printUInt(x2,8,10,200,158);
        delay32K(65536);
        return;
    }
    if (y >= 480) {
        printUInt(x1,8,10,200,140); printUInt(y,8,10,200,149); printUInt(x2,8,10,200,158);
        delay32K(65536);
        return;
    }
    if (x1 + x2 >= 320) {
        printUInt(x1,8,10,200,140); printUInt(y,8,10,200,149); printUInt(x2,8,10,200,158);
        delay32K(65536);
        return;
    }
    horiz(x1,y,x2);
}
void Qvert(uint24_t x, uint24_t y1, uint24_t y2) {
    if (x >= 320) {
        printUInt(x,8,10,200,170); printUInt(y1,8,10,200,179); printUInt(y2,8,10,200,188);
        delay32K(65536);
        return;
    }
    if (y1 >= 480) {
        printUInt(x,8,10,200,170); printUInt(y1,8,10,200,179); printUInt(y2,8,10,200,188);
        delay32K(65536);
        return;
    }
    if (y1 + y2 >= 480) {
        printUInt(x,8,10,200,170); printUInt(y1,8,10,200,179); printUInt(y2,8,10,200,188);
        delay32K(65536);
        return;
    }
    vert(x,y1,y2);
}
*/

#endif /* PRIME2D_H */