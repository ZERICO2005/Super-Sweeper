/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef SUBMENU_H
#define SUBMENU_H

#include <stdint.h>
#include "global.h"
#include "prime2D.h"
#include "primeKey.h"
#include "menu.h"

/* Declarations */

//Main Menu
void modeSet();
void randomMode();
void quickPreset();
void quickSize();
void quickSkill();

//General Purpose
void drawPattern();
void swapPrimaries();
//Custom Game
void perCent();
void mineCent();
void boardCent();

void custom_SizePercent();
void custom_Mines();

//Settings
void settingsMenu();
void videoUpdate();
void fpsUpdate();
void accessSet();

void versionText();
void testGraphic();

void buildMenu();

//Things
void leadChange();
void gameStart();
//What?
void helpText();
void buildPattern();

/* Declarations */


extern uint24_t presetT;
extern uint24_t sizeT;
extern uint24_t difficT;
extern uint24_t percent;
extern uint24_t scoreT;

extern uint8_t row;
extern uint8_t offset; //offset
extern uint8_t sector;

extern void (*menuFunction[11])();
extern uint8_t menuBack[11];
extern uint16_t boxIndex[12];
extern uint8_t menuRows[11];

extern uint8_t boxType[60];
extern uint8_t boxColor[60];
extern uint8_t boxDirect[60];
extern uint16_t textIndex[61];
extern void (*boxFunction[60])();
extern void* boxPointer[60];
extern uint8_t boxMin[60];
extern uint16_t boxMax[60];

extern uint8_t sourceText[755];

/* Main Menu */

void modeSet();
void randomMode();

/* Main Menu */

/* General Purpose */

void gameStart();

void drawPattern();
void buildPattern(); //Draws it too

/* General Purpose */

/* Custom Game Menu */

/*
uint24_t getPercent(uint24_t amountMines);
uint24_t getMines(uint24_t amountPercent);
void setMines(uint24_t mines0);
void setPercent(uint24_t percent0);

void custom_SizePercent();

void custom_Mines();
*/

void boardCent();

void perCent();

void mineCent();


/* Custom Game Menu */

/* Leaderboard */

void leadChange();

/* Leaderboard */


/* Settings Interface */
void fadeClear();
void fadeSet();
void swapPrimaries();

void versionText();

#define testGY 17 //Man this looks bad
void testGraphic();

void accessSet();

void settingsMenu(); //Places Hidden Text and draws test palette

void videoUpdate(); //Requires an Update

/* Settings Interface*/

/* Functions */

void fpsUpdate();
/* Functions */

/* Help */
void helpText();

/* Help */

#endif /* SUBMENU_H */