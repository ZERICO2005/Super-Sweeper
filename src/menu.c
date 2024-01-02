/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "menu.h"
#include "primeKey.h"
#include "prime2D.h"
#include "global.h"
#include "subMenu.h"

/* Menu Header */

void fadeColor();
void fadeSet();
void fadeClear();
void cursorAdjust();

void mineScale();
void execute();

#define boxPos (offset + row)


/* Menu Header */

/* Menu Data */



// struct menuBlock {
//     uint8_t type;
//     uint8_t color;

//     uint8_t min;
//     uint16_t max;

//     void* pointer;
//     void* function;
// } 
// menuBlock[64];


//255 Quit, 127-254 Special Event
//128 start game, 180 random game mode, 190 main menu update fps

//Binaries, nothing to see here, please back away now...




void blockText(uint8_t block, uint8_t y) { //Commonly used code
    gColor = 0;
    //uint16_t t = textIndex[boxIndex[block]];

    uint8_t x = 20;
    for (uint16_t s = textIndex[boxIndex[block]]; s < textIndex[boxIndex[block + 1]]; s++) {
        if (sourceText[s] == 33) { //New Line
            //text6x8(x, y, 17); //17 lolololololololololololololol
            y += 24;
            x = 20;
        } else {
            text6x8(x, y, sourceText[s]);
            x += 7;
        }
    }
}

#define GWI 22 //Game Width Index //Was intended to automatically enable and disable the cursor
/*void cursorAdjust() {
    blockMax[GWI] = cursorAllow == 1 ? 27 : 52;
	if (*blockPointer[GWI] > blockMax[GWI]) {
		*blockPointer[GWI] = blockMax[GWI];
	}
}*/

/* Fade Effect */
uint16_t* fColor;
uint8_t fR;
uint8_t fG;
uint8_t fB;
uint8_t fRMin;
uint8_t fGMin;
uint8_t fBMin;
uint8_t fRMax;
uint8_t fGMax;
uint8_t fBMax;
uint8_t phase = 0;
void fadeClear() {
    fColor = lcd_Palette;
    fColor += (row + 0xF0);
    *fColor = initialPalette[boxColor[row + offset]];
}
#define darkMax 6
void fadeSet() {
    fColor = lcd_Palette;
    fColor += (row + 0xF0);
    fR = (*fColor >> 10) & 31;
    fG = (*fColor >> 5) & 31;
    fB = (*fColor) & 31;
    
    fRMin = (fR << 1) / 5; // * 2/5
    fRMax = (fR << 3) / 5; // * 8/5
    if (fRMax < darkMax) { fRMax = darkMax;}
    if (fRMax > 31) { fRMax = 31;}

    fGMin = (fG << 1) / 5; // * 2/5
    fGMax = (fG << 3) / 5; // * 8/5
    if (fGMax <= darkMax) { fGMax = darkMax;}
    if (fGMax > 31) { fGMax = 31;}

    fBMin = (fB << 1) / 5; // * 2/5
    fBMax = (fB << 3) / 5; // * 8/5
    if (fBMax <= darkMax) { fBMax = darkMax;}
    if (fBMax > 31) { fBMax = 31;}
    // printUInt(fColor,6,16,2,56);
    // printUInt(*fColor,4,16,2,64);
}
#define fadeSpeed 16383
#define fadeSplit 8191
#define fadeShift 5

// uint8_t fCycle = 0;
// uint24_t fTimer = 0;
void fadeColor() {
    if (((uint24_t)systemTime & fadeSpeed) <= fadeSplit) {
        phase = ((uint24_t)systemTime & fadeSplit) >> fadeShift;
    } else {
        phase = 255 - (((uint24_t)systemTime & fadeSplit) >> fadeShift);
    }

    // printUInt(phase,2,16,2,80);
    fR = linearInterpolationClamp(phase,0,255,fRMin,fRMax);
    fG = linearInterpolationClamp(phase,0,255,fGMin,fGMax);
    fB = linearInterpolationClamp(phase,0,255,fBMin,fBMax);
    // printUInt(fR,2,10,2,96);
    // printUInt(fG,2,10,2,104);
    // printUInt(fB,2,10,2,112);

    // printUInt(select,2,10,2,132);
    // printUInt(number,3,10,2,140);
    *fColor = ((fR << 10) | (fG << 5) | fB);
}
/* Fade Effect */

u16 getNumber(u16 index) {
	if (boxMax[index] < 255) {
		return *(uint8_t*)boxPointer[index];
	} else {
		return *(uint16_t*)boxPointer[index];
	}
};
void setNumber(u16 index, u16 value) {
	if (boxMax[index] < 255) {
		*(uint8_t*)boxPointer[index] = (uint8_t)value;
	} else {
		*(uint16_t*)boxPointer[index] = (uint16_t)value;
	}
};

void buildMenu() {

    gColor = 15;
    fillScreen();
    uint24_t j = 20;
    uint8_t pColor = 0xF0;
    for (row = 0; row < menuRows[sector]; row++) {
        gColor = boxColor[boxPos];
        initialPalette[pColor] = initialPalette[gColor];
        lcd_Palette[pColor] = initialPalette[gColor];
        gColor = pColor;
        // if (select != 0) {
        //     gColor = blockColor[select + offSec];
        // } else {
        //     gColor = 16;
        // }
        fillRect(16, j - 4, 196, 16);
        
        if (boxType[boxPos] & Value) {
            gColor = 0;
            text6x8(202, j, 29); //>>
			uint16_t value = getNumber(boxPos);
            text6x8(195, 20 + (24 * row), (value % 10));
            text6x8(188, 20 + (24 * row), ((value / 10) % 10));
            if (boxMax[boxPos] < 100) {
                text6x8(181, j, 28); //<<
            } else {
                text6x8(181, 20 + (24 * row), ((value / 100))); //Unexpected above 2599
                text6x8(174, j, 28); //<<
            }
        }
        if (boxType[boxPos] & BoolToggle) {
            gColor = row + 0xF0;
            fillRect(202, j, 6, 8);
            gColor = 0;
            if (boxMax[boxPos] < 255) {
                if (*(uint8_t*)boxPointer[boxPos] == boxMax[boxPos]) {
                    text6x8(202, j, 50);
                } else {
                    text6x8(202, j, 49);
                }
            } else {
                if (*(uint16_t*)boxPointer[boxPos] == boxMax[boxPos]) {
                    text6x8(202, j, 50);
                } else {
                    text6x8(202, j, 49);
                }
            }
        }
        // if (blockType[select + offSec]) {
        //     gColor = 0;
        //     text6x8(202, j + 4, 29); //>>
        //     text6x8(195 - dots * 5, j + 4, 28); //<<
        //     uint8_t dX = 202 - dots * 5; //8bit since it will be less than 255
        //     uint8_t dY = j + 7; //(j + 4) + 3
        //     for (uint8_t e; e < dots; e++) {
        //         fillRect(dX,dY,2,2);
        //         dX += 5;
        //     }
        //     fillRect(201 - value * 5, j + 6 ,4,4); //Highlighted one
        // }

        pColor++;
        j += 24;
    }
    row = 0;
    gColor = 0;
    blockText(sector,20);
    
    //fillRect(247,120,30,65); //Was Green
    fadeClear();
    fadeSet();
    if (menuFunction[sector] != 0) {
        (*menuFunction[sector])();
    }
}

void scroll() {
    // gColor = blockColor[number];
    // fillText(16, 16 + (24 * select), 196, 16);
    if (kb_Data[7] & kb_Down) {
        row++;
        if (row == menuRows[sector]) {
            row = 0;
        }
    } else if (kb_Data[7] & kb_Up) {
        if (row == 0) {
            row = menuRows[sector];
        }
        row--;
    }
    // gColor = 16;
    // fillText(16, 16 + (24 * select), 196, 16);
}

/*
//Unfinished
void slideReset() {
    fillRect(201 - value * 5, 20 + (24 * select), 4, 4); //Clear
    fillRect(202 - value * 5, 21 + (24 * select),2,2); //Reset
    fillRect(201 - value * 5, yCord, 4, 4); //Highlight
}
void slideHL() {
    fillRect(201 - value * 5, 20 + (24 * select), 4, 4); //Highlight
}
*/

void dial(uint16_t boxOffset, uint8_t boxRow) { //uint8_t src, uint8_t des
    uint16_t box = boxOffset + boxRow;
    uint24_t yCord = 20 + (24 * row);
	u16 value = getNumber(box);
    if ((kb_Data[7] & kb_Right)) { //Right
        if (value == boxMax[box]) {
            value = boxMin[box];
        } else {
           value++;
        }
    } else if (kb_Data[7] & kb_Left) { //Left
        if (value == boxMin[box]) {
            value = boxMax[box];
        } else {
          value--;
        }
    }
	setNumber(box,value);

    if ((boxType[box] & Scroll) && boxFunction[box] != NULL) { //Function
        (*boxFunction[box])();
		value = getNumber(box); // Keeps track of any changes made by a function
    }

    gColor = boxRow + 0xF0; //16
    fillRect(188, yCord, 13, 8);
    if (boxMax[box] > 99) {
        fillRect(181, yCord, 6, 8);
        gColor = 0;
        text6x8(181, yCord, ((value / 100))); //Undefined Behaviour above 2599
    }
    gColor = 0;
    text6x8(195, yCord, (value % 10));
    text6x8(188, yCord, ((value / 10) % 10));
}

void button(uint16_t box) {
    (*boxFunction[box])();
}

void buttonToggle(uint16_t index) {
    gColor = row + 0xF0;
    fillRect(202, 20 + (24 * row), 6, 8);
    gColor = 0;
    if (boxMax[index] < 255) {
        if (*(uint8_t*)boxPointer[index] == boxMax[index]) {
            *(uint8_t*)boxPointer[index] = boxMin[index];
            text6x8(202, 20 + (24 * row), 49); // O
        } else {
            *(uint8_t*)boxPointer[index] = boxMax[index];
            text6x8(202, 20 + (24 * row), 50); // X
        }               
	} else {
		if (*(uint16_t*)boxPointer[index] == boxMax[index]) {
            *(uint16_t*)boxPointer[index] = boxMin[index];
            text6x8(202, 20 + (24 * row), 49); // O
        } else {
            *(uint16_t*)boxPointer[index] = boxMax[index];
            text6x8(202, 20 + (24 * row), 50); // X
        }
	}
}

void menuLoop() {
    //Setup
    buildMenu();
    //Code

    while (status == OKAY || true) {
        keyPress(); if (status != OKAY) { return; } //KeyPress
 
        fadeColor();
        if (kb_Data[7] & (kb_Up | kb_Down)) {
            if (keyReady & VERT) {
                keyReset(vERT);
                fadeClear();
                scroll();
                fadeSet();
            }
        }
        if (kb_Data[7] & (kb_Left | kb_Right)) {
            if ((keyReady & HORIZ) && (boxType[boxPos] & Value)) {
                keyReset(hORIZ);
                fadeClear();
                dial(offset, row);
                fadeSet();
            }
        }
        if ((kb_Data[2] & kb_Alpha) || (kb_Data[6] & kb_Enter)) {
            if ((keyReady & ALPHA) && (boxType[boxPos] & Click)) {
                keyReset(aLPHA);
                if (boxType[boxPos] & BoolToggle) { //Button Toggle
                    buttonToggle(boxPos);
                }
                if (boxFunction[boxPos] != NULL) {
                    button(boxPos); //Button
                }
                if (boxType[boxPos] & Direct) { //Direct
                    sector = boxDirect[boxPos];
                    offset = boxIndex[boxDirect[boxPos]];
                    row = 0;
                    buildMenu();
                }
            }
        }
        if (kb_Data[1] & kb_2nd) {
            if (keyReady & SECOND) {
				keyReset(sECOND);
                offset = boxIndex[menuBack[sector]]; //Different order is intentional, otherwise it will summon the RAINBOW OF ULTIMATE DOOM!!!
                sector = menuBack[sector];
                row = 0;
                buildMenu();
            }
        }
        if (keyReady & OTHER) {
            
        }
        if (keyReady & DEBUG) {
        
        }
        if (kb_Data[1] & kb_Del) {
            return; //Quit
        }
    };
    
    //Reset
}