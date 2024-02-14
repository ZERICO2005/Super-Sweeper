/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef SUBMENU_H
#define SUBMENU_H

#include "Common_Def.h"
#include "subMenu.h"

#include "global.h"
#include "prime2D.h"
#include "primeKey.h"
#include "menu.h"
#include "mineSweeper.h"

/* Declarations */

#define boxPos (offset + row)

//Main Menu


void modeSet();
void randomMode();
void quickPreset() {

}
void quickSize() {

}
void quickSkill() {

}

//General Purpose
void drawPattern();
void swapPrimaries();
//Custom Game
void changeInBoardSize();
void changeInPercent();
void changeInMineCount();
// void perCent();
// void mineCent();
// void boardCent();

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


uint24_t presetT = 5;
uint24_t sizeT = 4;
uint24_t difficT = 3;
uint24_t percent = 14;
uint24_t scoreT = 0;

uint8_t row = 0;
uint8_t offset = 0; //offset
uint8_t sector = 0;

// The following was generated from "Super CSV"

void (*menuFunction[11])() = {0,buildPattern,buildPattern,buildPattern,leadChange,versionText,0,testGraphic,0,helpText,quitGame};
uint8_t menuBack[11] = {10,0,0,0,0,0,5,5,5,0,0};
uint16_t boxIndex[12] = {0,8,16,21,28,37,43,47,54,59,60,60};
uint8_t menuRows[11] = {8,8,5,7,9,6,4,7,5,1,1};

uint8_t boxType[60] = {9,9,9,9,9,9,9,9,0,22,4,4,4,1,9,9,22,1,9,9,9,22,22,22,22,22,9,9,0,0,0,0,0,0,0,22,9,65,9,9,9,0,9,52,65,52,9,54,65,52,65,65,22,9,21,1,1,1,9,9};
uint8_t boxColor[60] = {5,11,9,12,6,2,1,8,5,8,8,8,8,7,8,8,10,14,7,8,8,8,8,8,9,8,1,8,5,8,8,8,8,8,8,10,8,1,8,8,8,7,8,9,8,8,8,11,8,8,8,12,5,8,8,8,8,9,8,8};
uint8_t boxDirect[60] = {1,1,2,3,4,5,9,0,0,0,0,0,0,0,3,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,8,0,0,0,0,0,5,0,0,0,0,0,0,5,0,0,0,0,5,0};
uint16_t textIndex[61] = {0,23,41,54,64,79,91,99,112,124,137,147,155,169,183,193,206,227,242,256,271,284,297,305,313,327,341,355,368,383,386,389,392,395,398,401,414,427,446,460,475,491,500,512,526,535,547,556,567,586,605,628,647,659,668,684,701,719,734,743,755};
void (*boxFunction[60])() = {modeSet,modeSet,0,0,0,0,0,quitGame,0,drawPattern,0,0,0,gameStart,0,0,drawPattern,randomMode,0,0,0,drawPattern,changeInBoardSize,changeInBoardSize,changeInMineCount,changeInPercent,gameStart,0,0,0,0,0,0,0,0,leadChange,0,swapPrimaries,0,0,0,0,0,0,0,0,0,videoUpdate,accessSet,0,0,0,fpsUpdate,0,0,0,0,0,0,0};
void* boxPointer[60] = {0,0,0,0,0,0,0,0,0,&gameMode,0,0,0,0,0,0,&gameMode,&gameMode,0,0,0,&gameMode,&sizeX,&sizeY,&mineCount,&percent,0,0,0,0,0,0,0,0,0,&gameMode,0,&swapAlphaSecondBind,0,0,0,0,0,&safeGuess,&chording,&autoSolver,0,&displayMode,&accessMode,&fadeEffect,&cursorGraphic,&movieIntro,&fpsT,0,&autoSaveMax,0,0,0,0,0};
uint8_t boxMin[60] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0};
uint16_t boxMax[60] = {0,0,0,0,0,0,0,0,0,16,0,0,0,0,0,0,16,0,0,0,0,16,52,27,702,50,0,0,0,0,0,0,0,0,0,16,0,1,0,0,0,0,0,2,1,2,0,3,1,2,1,1,992,0,3,0,0,0,0,0};

uint8_t sourceText[755] = {66,101,90,108,108,98,92,32,76,98,103,94,82,112,94,94,105,94,107,39,32,25,33,74,103,98,96,97,109,32,82,112,94,94,105,94,107,39,32,30,33,64,101,101,32,76,104,93,94,108,39,32,26,33,66,110,108,109,104,102,39,32,48,33,75,94,90,93,94,107,91,104,90,107,93,39,32,44,33,82,94,109,109,98,103,96,108,39,32,43,33,71,94,101,105,39,32,27,33,68,113,98,109,32,70,90,102,94,39,32,45,33,80,110,98,92,100,32,70,90,102,94,39,33,70,90,102,94,32,76,104,93,94,39,32,30,33,79,107,94,108,94,109,39,32,26,33,82,98,115,94,39,32,46,33,67,98,95,95,98,92,110,101,109,114,39,32,41,33,82,109,90,107,109,32,70,90,102,94,39,32,25,33,66,110,108,109,104,102,39,32,43,33,76,90,98,103,32,76,94,103,110,39,32,45,33,79,90,109,109,94,107,103,32,82,94,101,94,92,109,98,104,103,39,32,26,33,81,90,103,93,104,102,32,76,104,93,94,39,32,27,33,80,110,98,92,100,32,70,90,102,94,39,32,25,33,66,110,108,109,104,102,32,70,90,102,94,39,32,43,33,76,90,98,103,32,76,94,103,110,39,32,45,33,70,90,102,94,32,76,104,93,94,39,32,30,33,82,98,115,94,32,87,39,33,82,98,115,94,32,88,39,33,76,98,103,94,32,66,104,110,103,109,39,32,25,33,79,94,107,92,94,103,109,90,96,94,39,32,41,33,82,109,90,107,109,32,70,90,102,94,39,32,26,33,76,90,98,103,32,76,94,103,110,39,32,45,33,71,98,96,97,32,82,92,104,107,94,108,39,32,44,33,1,34,33,2,34,33,3,34,33,4,34,33,5,34,33,6,34,33,70,90,102,94,32,76,104,93,94,39,32,30,33,76,90,98,103,32,76,94,103,110,39,32,45,33,82,112,90,105,32,64,101,105,97,90,32,90,103,93,32,2,103,93,33,70,90,102,94,32,82,94,109,109,98,103,96,108,33,85,98,93,94,104,32,82,94,109,109,98,103,96,108,33,67,90,109,90,32,76,90,103,90,96,94,102,94,103,109,33,85,94,107,108,98,104,103,39,33,76,90,98,103,32,76,94,103,110,32,45,33,82,90,95,94,32,70,110,94,108,108,98,103,96,33,66,97,104,107,93,98,103,96,33,64,110,109,104,32,82,104,101,111,94,107,33,81,94,109,110,107,103,32,45,33,85,98,93,94,104,32,76,104,93,94,33,64,92,92,94,108,108,98,91,98,101,98,109,114,32,76,104,93,94,33,65,90,92,100,96,107,104,110,103,93,32,68,95,95,94,92,109,108,33,66,110,107,108,104,107,32,70,107,90,105,97,98,92,32,37,64,101,105,97,90,38,33,68,103,90,91,101,94,32,76,104,111,98,94,32,72,103,109,107,104,33,76,90,113,98,102,110,102,32,69,79,82,33,81,94,109,110,107,103,32,45,33,64,110,109,104,32,82,90,111,94,32,66,104,110,103,109,33,66,101,94,90,107,32,64,110,109,104,32,82,90,111,94,108,33,66,101,94,90,107,32,75,94,90,93,94,107,91,104,90,107,93,33,66,101,94,90,107,32,64,101,101,32,67,90,109,90,33,81,94,109,110,107,103,32,45,33,76,90,98,103,32,76,94,103,110,32,45,33};

/* Main Menu */

void modeSet() {
	gameMode = row; //It does the job
}

// Randomly chooses a gameMode that is not the current gameMode
void randomMode() {
    srand(seed);
	uint24_t newGameMode = rand() % (gameModeCount); // Base 1 indexing, refactor/fix this later
	gameMode = (newGameMode == gameMode) ? ((newGameMode + 1) % (gameModeCount)) : newGameMode;
    gColor = 0xF0;
    fillRect(188, 20 + (0 * 24), 14, 8); //Clears characters
    gColor = Black;
    text6x8(195, 20 + (0 * 24), (gameMode % 10));
    text6x8(188, 20 + (0 * 24), ((gameMode / 10) % 10));
    drawPattern();
}

/* Main Menu */

/* General Purpose */

void gameStart() {
    gameLoop();
    row = 0;
    if (status != FORCEQUIT) {
        buildMenu();
    }
}

void drawPattern() {
    gColor = 15;
    for (int24_t y = 0; y < 65; y += 13) {
        for (int24_t x = 0; x < 65; x += 13) {
            if (!(x == 26 && y == 26)) {
                fillRect(240 + x, 18 + y, 10, 10);
            }
        }
    }

    offPos = orderPos[gameMode];
    offLen = orderPos[gameMode + 1] - orderPos[gameMode];
    gColor = 16;
    int24_t u;
    int24_t v;
    for (int24_t i = 0; i < offLen; i += 2) {
        u = order[offPos + i] * 13; //Probably more memory effeicent than an algorithm
        v = order[offPos + i + 1] * 13;
		#ifndef SWAP_X_AND_Y_CORD
			uint8_t *fillR = lcd_Ram8 + ((44 * LCD_RESX) + 266 + (LCD_RESX * v) + u);
		#else
			uint8_t *fillR = lcd_Ram8 + (44 + (266 * LCD_RESY) + v + (u * LCD_RESY));
		#endif
		if (*fillR == 0) { //Draws a 3 if 2 is already there
		    fillRect(266 + u, 44 + v , 10, 10);
            gColor = 0;
            text6x8(268 + u, 45 + v, 3); //3
            gColor = 16;
		} else if (*fillR == 16) { //draws a two if a repeat is detected
            fillRect(266 + u, 44 + v , 10, 10);
            gColor = 0;
            text6x8(268 + u, 45 + v, 2); //2
            gColor = 16;
        } else {
            fillRect(266 + u, 44 + v , 10, 10);
        }
    }
}

void buildPattern() { //Draws it too
    for (int24_t i = 239; i < 304; i += 13) {
        gColor = (7);
        vert(i, 17, 64);
        gColor = (0);
        vert(i + 11, 17, 64);
    }
    for (int24_t i = 17; i < 82; i += 13) {
        gColor = (7);
        horiz(239, i, 64);
        gColor = (0);
        horiz(239, i + 11, 64);
    }
    for (int24_t i = 16; i < 94; i += 13) {
        gColor = (8);
        horiz(238, i, 66);
    }
    for (int24_t i = 238; i < 316; i += 13) {
        gColor = (8);
        vert(i, 16, 66);
    }
    gColor = 1; //Draws the mine in the middle
    fillRect(266, 44, 10, 10);
    gColor = 0;
    text6x8(268,45,25);
    gColor = 7;
	plot(270,47);
	plot(269,48);

    drawPattern();
}

/* General Purpose */

/* Custom Game Menu */

bool followPercentageOnResize = true; // Otherwise resizing the board follows Mine Count

void changeInBoardSize() {
	if (followPercentageOnResize == true) {
		changeInPercent();
	} else {
		changeInMineCount();
	}
}

void changeInPercent() { // Sets Mine Count based on Percentage of Mines
	uint24_t boardSize = sizeX * sizeY;
	mineCount = (boardSize * percent) / 100;
	if (mineCount < 8) {
		mineCount = 8;
	} else if (mineCount > boardSize / 2) { // >50% Mines
		mineCount = boardSize / 2;
	}
	{
		const uint24_t yCord = 20 + (24 * 3);
		gColor = 0xF3;
		fillRect(181, yCord, 20, 8);
		gColor = 0;
		text6x8(195, yCord, (mineCount % 10));
		text6x8(188, yCord, ((mineCount / 10) % 10));
		text6x8(181, yCord, ((mineCount / 100))); // Undefined above 2599
		// if (mineCount > 100) {
		// 	text6x8(181, yCord, ((mineCount / 100))); // Undefined above 2599
		// 	text6x8(174, yCord, 0x1C); // << Symbol
		// } else {
		// 	text6x8(181, yCord, 0x1C); // << Symbol
		// }
	}
	followPercentageOnResize = true;
}

void changeInMineCount() { // Sets Percentage of Mines based on Mine Count
	uint24_t boardSize = sizeX * sizeY;
	percent = (mineCount * 100) / boardSize;
	if (percent < 5) {
		percent = 50;
		changeInPercent();
	} else if (percent > 50) {
		percent = 5;
		changeInPercent();
	}
	{
		const uint24_t yCord = 20 + (24 * 4);
		gColor = 0xF4;
		fillRect(188, yCord, 13, 8);
		gColor = 0;
		text6x8(195, yCord, (percent % 10));
		text6x8(188, yCord, ((percent / 10) % 10));
	}
	followPercentageOnResize = false;
}

/* Custom Game Menu */

/* Leaderboard */

void leadChange() {
    {
        int24_t m = 0;
        uint8_t gameMod = 0; //using gameMode may be unsafe at this time, alas gameMod
        for (int24_t y = 44; y <= 16 + ((7) * 24); y += 24) {
            int24_t x = 20;
            gColor = m + 0xF1; //0xF0 + 1
            fillRect(41, 44 + (24 * m), 48, 8);
            gColor = 0;
            text6x8(x + 21, y, names[m * 3 + (gameMod * 18)]);
            text6x8(x + 28, y, names[m * 3 + 1 + (gameMod * 18)]);
            text6x8(x + 35, y, names[m * 3 + 2 + (gameMod * 18)]);
            text6x8(x + 49, y, ((leaderboard[m + (gameMod * 6)] / 1000) % 10));
            text6x8(x + 56, y, ((leaderboard[m + (gameMod * 6)] / 100) % 10));
            text6x8(x + 63, y, ((leaderboard[m + (gameMod * 6)] / 10) % 10));
            text6x8(x + 70, y, (leaderboard[m + (gameMod * 6)] % 10));
            m++;
        }
    }
}

/* Leaderboard */


/* Settings Interface */
void fadeClear();
void fadeSet();
void swapPrimaries() {
    if (boxColor[boxPos] == Red) {
        boxColor[boxPos] = Blue;
    } else {
        boxColor[boxPos] = Red;
    }
    fadeClear();
    fadeSet();
}

void versionText() {
    uint24_t x = 83;
    for (uint8_t j = 15; j < 21; j++) {
        text6x8(x, 116, hiddenText[j]);
        x += 7;
    }
    x = 139;
    for (uint8_t j = 33; j < 43; j++) {
        text6x8(x, 116, hiddenText[j]);
        x += 7;
    }
}

#define testGY 17 //Man this looks bad
void testGraphic() {
    gColor = Grey; // Grey
    horiz(217,testGY,98);
    horiz(217,testGY+13,98);
    vert(217,testGY+1,12);
    vert(314,testGY+1,12);
    gColor = 0x1C;
    fillRect(218,testGY+1,96,12);
    gColor = Black;
    text6x8(220,testGY+3,gMine);
    text6x8(228,testGY+3,gFlag);
    gColor = White;
    plot(222,testGY+5);
    plot(221,testGY+6);
    gColor = Red;
    fillRect(228,testGY+4,4,3);
    uint24_t x = 236;
    for (uint8_t i = 0; i < 10; i++) {
        gColor = color[i];
        text6x8(x,testGY+3,i);
        x += i > 1 ? 8 : 7;
    }
}

void accessSet() {
	//Placeholder
}

void settingsMenu() { //Places Hidden Text and draws test palette
    //Deprecated
}

void videoUpdate() { //Requires an Update

    if (displayMode & 2 && darkMode == 0) {
        darkMode = 1;
		#ifdef PLATFORM_TI84CE
			((void(*)(void))0x384)();
			*(volatile uint8_t*)0xF80018 = 0x08;
			*(volatile uint8_t*)0xF80018 = 0x44;
			*(volatile uint8_t*)0xF80018 = 0x21;
			*(volatile uint8_t*)0xF80008 = 0x01;
		#endif
    } else if (displayMode < 2 && darkMode == 1) {
        darkMode = 0;
		#ifdef PLATFORM_TI84CE
			((void(*)(void))0x384)();
			*(volatile uint8_t*)0xF80018 = 0x08;
			*(volatile uint8_t*)0xF80018 = 0x44;
			*(volatile uint8_t*)0xF80018 = 0x20;
			*(volatile uint8_t*)0xF80008 = 0x01;
		#endif
	}

    if (displayMode & 1) {
        lcd_VideoMode = lcd_RGB8bit;
    } else {
        lcd_VideoMode = lcd_BGR8bit;
    }
    gColor = 0xF0;
    fillRect(195, 20, 6, 8);
    gColor = 0;
    text6x8(195, 20, displayMode);
    delay32K(7936); //10240 - 2304
    keyReset(hORIZ);
}

/* Settings Interface*/

/* Functions */

void fpsUpdate() {
    FPS = 32768 / fpsT;
}

/* Functions */

/* Help */
void helpText() {
    gColor = 0x0B; //Dark green
    fillRect(12,40,296,184);
    gColor = 0;
    uint24_t x = 16;
    uint8_t y = 44;
    for (uint16_t j = 0; j < guideTextLength; j++) {
        if (guideText[j] == 33) { //New Line
            x = 16;
            y += 12;
        } else {
            text6x8(x, y, guideText[j]);
            x += 7;
        }
    }
}

/* Help */

#endif /* SUBMENU_H */