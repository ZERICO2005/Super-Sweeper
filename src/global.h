/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef GLOBAL_H
#define GLOBAL_H

//#include <col.h>
#include "Common_Def.h"

//#define VIDEO //Disables cutscene and saves a few bytes
#define DEVBUILD

enum COLORS { //Will it be used? Or will knuckles prevail
    Black,Red,Yellow,Lime,Teal,Blue,Magenta,White,
    Grey,Maroon,Brown,Green,Cyan,Navy,Purple,Silver
};

/*
** This file is a file where I dumped all the global variables so things would not break
*/

extern uint24_t mines; //U16
extern int24_t flags; //S16
extern uint24_t cleared; //U16
extern uint8_t win;
extern uint24_t flagColor;
extern u8 cheater;
extern u8 autoLoss;

extern int24_t score;

extern int24_t tile;

/* Parameters */

#define gameModeCount 16
extern uint24_t gameMode;
extern uint24_t sizeX; //Board X
extern uint24_t sizeY; //Board Y
extern uint24_t chance; //Refactor

/* Parameters */

/* Game Backend */

extern uint16_t offPos; //gameMode index
extern uint8_t offLen; //gameMode length
extern uint8_t marX; //Array X
extern uint8_t marY; //Array Y
extern int24_t posX;
extern int24_t posY;

extern uint8_t disX; //Define spacing between squares
extern uint8_t disY;
extern uint8_t padX;
extern uint8_t padY;
extern uint8_t font;
extern uint8_t fontSize;

/* Graphical Backend */

/* Settings */
extern u8 swapAlphaSecondBind;
//Game Settings
extern u8 safeGuess; //off,on,extra
extern u8 chording; //off,on
extern u8 autoSolver; //off,manual,automatic

//Video Settings
extern uint24_t displayMode; //Originally videoMode
extern u8 accessMode; //Increases Readability, Disables Quake
extern u8 fadeEffect; //off,static,dynamic //Refactor to bgEffects
extern u8 fpsCounter; //Debug thing
extern u8 cursorGraphic;
extern u8 movieIntro;

extern uint32_t FPS; //Set to 0 for unlimited
extern uint32_t fpsT; //temp value

//Data Settings
extern u8 autoSaveMax;

#ifdef PLATFORM_TI84CE
	extern uint8_t darkMode;
#endif

/* Settings */

/* Text */
extern uint8_t guideText[511];
#define guideTextLength 511 //helpText had a naming conflict >:(

extern uint8_t pauseText[84];
#define pauseTextLength 84
extern uint8_t gameOverText[87];
#define gameOverTextLength 87
extern uint8_t winText[81];
#define winTextLength 81
extern uint8_t cheatText[16];
#define cheatTextLength 16
/* Text */

/* IO Handeling */
enum STATUS {OKAY,RESTART,QUIT,FORCEQUIT};
extern uint8_t status;
/* IO Handeling */

/* Chording/Cursor */

extern uint24_t cursorAllow;

/* Chording/Cursor */

/* Legacy */
extern const uint8_t hiddenText[43]; //SuperSweeper V:X.XX.X ZERICO2005 YYYY/MM/DD
extern const uint8_t hiddenTextLength;

extern const uint8_t blockLimits[6]; //Minus 1
//

extern uint8_t category;

extern uint8_t names[288];

extern uint16_t leaderboard[96];

//8bit Color Pallete
//0-15 EGA, 16 Orange, 17-20 Fade
//5x5 Image and Color
//Number Colors
extern const uint8_t color[28];

//Outdated Text
//const uint8_t text[1311] = {50,85,74,92,92,82,76,32,60,82,87,78,66,96,78,78,89,78,91,39,32,25,33,58,87,82,80,81,93,32,66,96,78,78,89,78,91,39,32,30,33,48,85,85,32,60,88,77,78,92,39,32,26,33,50,94,92,93,88,86,39,32,109,33,59,78,74,77,78,91,75,88,74,91,77,39,32,44,33,66,78,93,93,82,87,80,92,39,32,43,33,55,78,85,89,39,32,27,33,52,97,82,93,32,54,74,86,78,39,32,45,33,64,94,82,76,84,32,54,74,86,78,39,33,54,74,86,78,32,60,88,77,78,39,32,30,33,63,91,78,92,78,93,39,32,26,33,66,82,99,78,39,32,46,33,51,82,79,79,82,76,94,85,93,98,39,32,41,33,66,93,74,91,93,32,54,74,86,78,39,32,25,33,50,94,92,93,88,86,39,32,43,33,60,74,82,87,32,60,78,87,94,39,32,45,33,63,74,93,93,78,91,87,32,66,78,85,78,76,93,82,88,87,39,32,26,33,65,74,87,77,88,86,32,60,88,77,78,39,32,27,33,66,78,85,78,76,93,32,63,91,78,92,78,93,39,32,25,33,50,94,92,93,88,86,32,54,74,86,78,39,32,43,33,60,74,82,87,32,60,78,87,94,39,32,45,33,54,74,86,78,32,60,88,77,78,39,32,30,33,66,82,99,78,32,71,39,33,66,82,99,78,32,72,39,33,60,82,87,78,32,50,88,94,87,93,39,32,25,33,63,78,91,76,78,87,93,74,80,78,39,32,41,33,66,93,74,91,93,32,54,74,86,78,39,32,26,33,60,74,82,87,32,60,78,87,94,39,32,45,33,55,82,80,81,32,66,76,88,91,78,92,39,32,44,33,1,34,33,2,34,33,3,34,33,4,34,33,5,34,33,6,34,33,54,74,86,78,32,60,88,77,78,39,32,30,33,60,74,82,87,32,60,78,87,94,39,32,45,33,66,74,79,78,32,54,94,78,92,92,82,87,80,39,33,69,82,77,78,88,32,60,88,77,78,39,33,49,74,76,84,80,91,88,94,87,77,32,52,79,79,78,76,93,92,39,33,48,76,76,78,92,92,82,75,82,85,82,93,98,32,60,88,77,78,39,33,50,88,91,77,82,87,80,32,37,48,85,89,81,74,38,39,33,60,74,97,82,86,94,86,32,53,63,66,39,33,69,78,91,92,82,88,87,39,33,60,74,82,87,32,60,78,87,94,32,45,33,66,94,89,78,91,32,66,96,78,78,89,78,91,32,82,92,32,74,32,95,78,91,92,82,88,87,32,88,79,32,60,82,87,78,66,96,78,78,89,78,91,33,79,88,91,32,93,81,78,32,67,82,8,4,50,52,32,96,82,93,81,32,92,78,95,78,91,74,85,32,86,88,77,78,92,32,74,87,77,33,79,78,74,93,94,91,78,92,34,32,67,88,32,89,85,74,98,35,32,88,87,78,32,76,74,87,32,92,93,74,91,93,32,74,32,90,94,82,76,84,33,80,74,86,78,32,79,91,88,86,32,93,81,78,32,86,74,82,87,32,86,78,87,94,35,32,93,81,82,92,32,82,87,76,85,94,77,78,92,33,88,89,93,82,88,87,92,32,79,88,91,32,77,82,79,79,78,91,78,87,93,32,77,82,79,79,82,76,94,85,93,82,78,92,32,74,87,77,33,89,91,78,92,78,93,92,34,32,62,87,76,78,32,82,87,32,74,32,80,74,86,78,35,32,98,88,94,91,32,88,75,83,78,76,93,82,95,78,33,82,92,32,93,88,32,92,74,79,78,85,98,32,53,85,74,80,32,26,32,74,85,85,32,93,81,78,32,60,82,87,78,92,32,25,32,75,98,33,94,92,82,87,80,32,93,81,78,32,87,94,86,75,78,91,78,77,32,93,82,85,78,92,32,74,92,32,76,85,94,78,92,32,93,88,33,79,82,80,94,91,78,32,88,94,93,32,96,81,78,91,78,32,78,74,76,81,32,60,82,87,78,32,25,32,82,92,32,85,88,76,74,93,78,77,34,33,33,68,92,78,32,48,85,89,81,74,32,93,88,32,92,78,74,91,76,81,32,74,32,93,82,85,78,35,32,2,87,77,32,93,88,32,53,85,74,80,32,26,33,74,32,93,82,85,78,35,32,72,47,32,93,88,32,86,74,91,84,32,74,32,27,32,88,87,93,88,32,74,32,93,82,85,78,35,32,71,67,0,87,33,93,88,32,76,81,88,91,77,35,32,86,88,77,78,32,93,88,32,89,74,94,92,78,35,32,74,87,77,32,77,78,85,32,93,88,32,90,94,82,93,34,33,33,56,32,81,88,89,78,32,98,88,94,32,78,87,83,88,98,32,86,98,32,80,74,86,78,32,39,38,33,63,74,94,92,78,77,39,33,65,78,92,94,86,78,32,54,74,86,78,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,65,78,86,74,82,87,82,87,80,32,67,82,85,78,92,39,33,67,82,86,78,32,67,74,84,78,87,39,33,54,74,86,78,32,62,95,78,91,109,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,65,78,92,94,86,78,32,54,74,86,78,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,65,78,86,74,82,87,82,87,80,32,67,82,85,78,92,39,33,67,82,86,78,32,67,74,84,78,87,39,33,54,74,86,78,32,50,88,86,89,85,78,93,78,109,33,65,78,92,94,86,78,32,54,74,86,78,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,66,76,88,91,78,39,33,67,82,86,78,32,67,74,84,78,87,39,33};
//const uint24_t section[11] = {0,112,206,287,371,430,548,1059,1143,1230,1311};

/* Legacy */

extern uint16_t initialPalette[256];

//const uint8_t CLICKABLE = 0b00000100; const uint8_t SELECT1 = 0b00000001; const uint8_t SELECT2 = 0b00000010; const uint8_t SELECT3 = 0b00000011;           red darkRed 0grey 1grey
enum guiType {Click = 1, Scroll = 2, Dial = 4, Direct = 8, Value = 16, Dot = 32, BoolToggle = 64, Text = 128};
enum GUITYPE { C = 1, F = 2, N = 4, P = 8, V = 16, D = 32, B = 64, T = 128};

/* Global */
//Video



//Graphics

//Utilities
extern uint32_t seed; //Used for random number generation //frameTime variable
extern uint32_t delta;
extern uint32_t frameStart; //When the new frame began
extern uint32_t clockMax;
extern uint32_t clockTime;

extern uint32_t systemTime;
extern uint32_t pauseTime;
extern uint32_t gameStartTime;
extern uint32_t gamePauseTime;
extern uint32_t gameFinishTime;


/* Global */

/* Library Functions */


extern uint8_t* board;
extern uint8_t* state;
extern uint24_t* search;
extern uint8_t* flag;

extern uint24_t fadeSpeed;

extern const uint16_t orderPos[18];
//344 + 16 for buffer reasons since this keeeps being a probelmy
extern const int8_t order[360];

extern const uint8_t fontArray[40];

extern uint8_t bX[18]; //Plus 4
extern uint8_t bY[18]; //Plus 4
extern uint24_t bM[18];
extern uint8_t bF[6];

///fff


extern uint8_t option;

#define RGB4bit 0x825
#define RGB8bit 0x827
#define RGB16bit 0x82D
#define BGR4bit 0x925
#define BGR8bit 0x927
#define BGR16bit 0x92D

//Broken Functions
/*

uint8_t findColor1555(uint16_t c);
uint8_t findColor888(uint8_t r, uint8_t g, uint8_t b);
uint8_t findColor565(uint16_t c);
*/


//Menu stuff



#endif /* GLOBAL_H */