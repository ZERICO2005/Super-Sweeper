/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef MENU_H
#define MENU_H

#include "Common_Def.h"
#include "menu.h"
#include "primeKey.h"
#include "global.h"
#include "subMenu.h"



/* Menu Header */

// void fadeColor();
// void fadeSet();
// void fadeClear();
// void cursorAdjust();

// void mineScale();
// void execute();


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




void blockText(uint8_t block, uint8_t y);

#define GWI 22 //Game Width Index //Was intended to automatically enable and disable the cursor
/*void cursorAdjust() {
    blockMax[GWI] = cursorAllow == 1 ? 27 : 52;
	if (*blockPointer[GWI] > blockMax[GWI]) {
		*blockPointer[GWI] = blockMax[GWI];
	}
}*/

/* Fade Effect */
extern uint16_t* fColor;
extern uint8_t fR;
extern uint8_t fG;
extern uint8_t fB;
extern uint8_t fRMin;
extern uint8_t fGMin;
extern uint8_t fBMin;
extern uint8_t fRMax;
extern uint8_t fGMax;
extern uint8_t fBMax;
extern uint8_t phase;

void fadeClear();

void fadeSet();

// uint8_t fCycle = 0;
// uint24_t fTimer = 0;
void fadeColor();
/* Fade Effect */

u16 getNumber(u16 index);

void setNumber(u16 index, u16 value);

void buildMenu();

void scroll();

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

void dial(uint16_t boxOffset, uint8_t boxRow);

void button(uint16_t box);

void buttonToggle(uint16_t index);

void menuLoop();

#endif /* MENU_H */