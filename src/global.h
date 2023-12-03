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
#include <stdint.h>
#include "x86render.h" //Contains the windows version of everything

//#define VIDEO //Disables cutscene and saves a few bytes
#define DEVBUILD

//System specification
//#define TI84CE 
#define WINDOWS

//#ifdef WINDOWS

//#endif /* WINDOWS */


typedef uint32_t uint24_t;
typedef int32_t int24_t;
typedef uint32_t u24;
typedef int32_t i24;

typedef uint8_t u8;
typedef uint16_t u16;
//typedef uint24_t u24;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
//typedef int24_t i24;
typedef int32_t i32;
typedef int64_t i64;



#ifdef TI84CE
void* VRAM = (void*)0xD40000;
void* WRAM = (void*)0xD52C00;
void* XRAM = (void*)0xD65800;
uint24_t* frameBase = (uint24_t*)0xE30010;
volatile uint16_t* videoMode = (uint16_t*)0xE30018;
uint16_t* paletteRAM = (uint16_t*)0xE30200;

uint32_t* LCDTiming0 = (uint32_t*)0xE30000; //0x1F0A0338
uint32_t* LCDTiming1 = (uint32_t*)0xE30004; //0x0402093F
uint32_t* LCDTiming2 = (uint32_t*)0xE30008; //0x00EF7802
uint32_t* LCDTiming3 = (uint32_t*)0xE3000C; //0x00000000

uint32_t* lcd_CrsrImage = (uint32_t*)0xE30800;
uint32_t* lcd_CrsrCtrl = (uint32_t*)0xE30C00;
uint32_t* lcd_CrsrConfig = (uint32_t*)0xE30C04;
uint32_t* lcd_CrsrPalette0 = (uint32_t*)0xE30C08;
uint32_t* lcd_CrsrPalette1 = (uint32_t*)0xE30C0C;
uint32_t* lcd_CrsrXY = (uint32_t*)0xE30C10;
uint16_t* lcd_CrsrX = (uint16_t*)0xE30C10;
uint16_t* lcd_CrsrY = (uint16_t*)0xE30C12;
uint32_t* lcd_CrsrClip = (uint32_t*)0xE30C04;

#endif /* TI84CE */

enum COLORS { //Will it be used? Or will knuckles prevail
    Black,Red,Yellow,Lime,Teal,Blue,Magenta,White,
    Grey,Maroon,Brown,Green,Cyan,Navy,Purple,Silver
};

/*
** This file is a file where I dumped all the global variables so things would not break
*/

uint24_t mines = 0; //U16
int24_t flags = 54; //S16
uint24_t cleared = 0; //U16
uint8_t win = 1;
uint24_t flagColor = 1;
u8 cheater = 0;
u8 autoLoss = 0;

int24_t score = 0;

int24_t tile;

/* Parameters */

#define gameModeCount 16
uint24_t gameMode = 0;
uint24_t sizeX = 25; //Board X
uint24_t sizeY = 15; //Board Y
uint24_t chance = 54; //Refactor

/* Parameters */

/* Game Backend */

uint16_t offPos = 0; //gameMode index
uint8_t offLen = 16; //gameMode length
uint8_t marX = 29; //Array X
uint8_t marY = 19; //Array Y
int24_t posX = -15;
int24_t posY = 6;

uint8_t disX = 13; //Define spacing between squares
uint8_t disY = 13;
uint8_t padX = 3;
uint8_t padY = 2;
uint8_t font = 0;
uint8_t fontSize = 7;

/* Graphical Backend */

/* Settings */
u8 swapAlphaSecondBind = 0;
//Game Settings
u8 safeGuess = 2; //off,on,extra
u8 chording = 1; //off,on
u8 autoSolver = 0; //off,manual,automatic

//Video Settings
uint24_t displayMode = 0; //Originally videoMode
u8 accessMode = 0; //Increases Readability, Disables Quake
u8 fadeEffect = 1; //off,static,dynamic //Refactor to bgEffects
u8 fpsCounter = 1; //Debug thing
u8 cursorGraphic = 0;
u8 movieIntro = 1;

uint32_t FPS = (32768 / 1024); //Set to 0 for unlimited
uint32_t fpsT = 120; //temp value

//Data Settings
u8 autoSaveMax = 0;

/* Settings */

/* Text */
uint8_t guideText[511] = {82,110,105,94,107,32,82,112,94,94,105,94,107,32,98,108,32,90,32,111,94,107,108,98,104,103,32,104,95,32,76,98,103,94,82,112,94,94,105,94,107,33,95,104,107,32,109,97,94,32,83,98,8,4,66,68,32,112,98,109,97,32,108,94,111,94,107,90,101,32,102,104,93,94,108,32,90,103,93,33,95,94,90,109,110,107,94,108,34,32,83,104,32,105,101,90,114,35,32,104,103,94,32,92,90,103,32,108,109,90,107,109,32,90,32,106,110,98,92,100,33,96,90,102,94,32,95,107,104,102,32,109,97,94,32,102,90,98,103,32,102,94,103,110,35,32,109,97,98,108,32,98,103,92,101,110,93,94,108,33,104,105,109,98,104,103,108,32,95,104,107,32,93,98,95,95,94,107,94,103,109,32,93,98,95,95,98,92,110,101,109,98,94,108,32,90,103,93,33,105,107,94,108,94,109,108,34,32,78,103,92,94,32,98,103,32,90,32,96,90,102,94,35,32,114,104,110,107,32,104,91,99,94,92,109,98,111,94,33,98,108,32,109,104,32,108,90,95,94,101,114,32,69,101,90,96,32,26,32,90,101,101,32,109,97,94,32,76,98,103,94,108,32,25,32,91,114,33,110,108,98,103,96,32,109,97,94,32,103,110,102,91,94,107,94,93,32,109,98,101,94,108,32,90,108,32,92,101,110,94,108,32,109,104,33,95,98,96,110,107,94,32,104,110,109,32,112,97,94,107,94,32,94,90,92,97,32,76,98,103,94,32,25,32,98,108,32,101,104,92,90,109,94,93,34,33,33,84,108,94,32,64,101,105,97,90,32,109,104,32,108,94,90,107,92,97,32,90,32,109,98,101,94,35,32,2,103,93,32,109,104,32,69,101,90,96,32,26,33,90,32,109,98,101,94,35,32,88,47,32,109,104,32,102,90,107,100,32,90,32,27,32,104,103,109,104,32,90,32,109,98,101,94,35,32,87,83,0,103,33,109,104,32,92,97,104,107,93,35,32,102,104,93,94,32,109,104,32,105,90,110,108,94,35,32,90,103,93,32,93,94,101,32,109,104,32,106,110,98,109,34,33,33,72,32,97,104,105,94,32,114,104,110,32,94,103,99,104,114,32,102,114,32,96,90,102,94,32,39,38,33};
#define guideTextLength 511 //helpText had a naming conflict >:(

uint8_t pauseText[84] = {79,90,110,108,94,93,39,33,81,94,108,110,102,94,32,70,90,102,94,33,81,94,108,109,90,107,109,33,76,90,98,103,32,76,94,103,110,33,68,113,98,109,32,64,105,105,101,98,92,90,109,98,104,103,33,81,94,102,90,98,103,98,103,96,32,83,98,101,94,108,39,33,83,98,102,94,32,83,90,100,94,103,39,33};
#define pauseTextLength 84
uint8_t gameOverText[87] = {70,90,102,94,32,78,111,94,107,48,33,81,94,108,109,90,107,109,33,76,90,98,103,32,76,94,103,110,33,81,94,108,110,102,94,32,70,90,102,94,33,68,113,98,109,32,64,105,105,101,98,92,90,109,98,104,103,33,81,94,102,90,98,103,98,103,96,32,83,98,101,94,108,39,33,83,98,102,94,32,83,90,100,94,103,39,33};
#define gameOverTextLength 87
uint8_t winText[81] = {70,90,102,94,32,66,104,102,105,101,94,109,94,48,33,81,94,108,110,102,94,32,70,90,102,94,33,81,94,108,109,90,107,109,33,76,90,98,103,32,76,94,103,110,33,68,113,98,109,32,64,105,105,101,98,92,90,109,98,104,103,33,82,92,104,107,94,39,33,83,98,102,94,32,83,90,100,94,103,39,33};
#define winTextLength 81
uint8_t cheatText[16] = {88,104,110,32,66,97,94,90,109,94,93,48,32,29,39,37};
#define cheatTextLength 16
/* Text */

/* IO Handeling */
enum STATUS {OKAY,RESTART,QUIT,FORCEQUIT};
uint8_t status = 0;
/* IO Handeling */

/* Chording/Cursor */

uint24_t cursorAllow = 0;

/* Chording/Cursor */

/* Legacy */
const uint8_t hiddenText[43] = { //SuperSweeper V:X.XX.X ZERICO2005 YYYY/MM/DD
	82,110,105,94,107,82,112,94,94,105,94,107,32,85,39, /* Text */
	0,34,7,7,34,2,                                      /* Version */
	32,89,68,81,72,66,78,2,0,0,5,32,                    /* Text */
	2,0,2,3,36,                                         /* Year */
	1,2,36,0,2,                                         /* Month Day */
};
const uint8_t hiddenTextLength = 43;

const uint8_t blockLimits[6] = {8,4,8,8,6,6}; //Minus 1
//

uint8_t category = 0;

uint8_t names[288] = {
	66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40,  66,68,25,76,68,26,83,68,30,66,71,48,40,40,40,40,40,40
};

uint16_t leaderboard[96] = {
	1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0,    1600,1100,700,400,0,0
};

//8bit Color Pallete
//0-15 EGA, 16 Orange, 17-20 Fade
//5x5 Image and Color
//Number Colors
const uint8_t color[28] = {
/*0*/  7, 5,11, 1,13, 9,12, 0
/*1*/, 8,14,10, 6, 4, 2, 0, 8
/*2*/, 7, 0, 0, 0, 0, 0, 0, 0
/*3*/, 0, 0, 0,13
};

//Outdated Text
//const uint8_t text[1311] = {50,85,74,92,92,82,76,32,60,82,87,78,66,96,78,78,89,78,91,39,32,25,33,58,87,82,80,81,93,32,66,96,78,78,89,78,91,39,32,30,33,48,85,85,32,60,88,77,78,92,39,32,26,33,50,94,92,93,88,86,39,32,109,33,59,78,74,77,78,91,75,88,74,91,77,39,32,44,33,66,78,93,93,82,87,80,92,39,32,43,33,55,78,85,89,39,32,27,33,52,97,82,93,32,54,74,86,78,39,32,45,33,64,94,82,76,84,32,54,74,86,78,39,33,54,74,86,78,32,60,88,77,78,39,32,30,33,63,91,78,92,78,93,39,32,26,33,66,82,99,78,39,32,46,33,51,82,79,79,82,76,94,85,93,98,39,32,41,33,66,93,74,91,93,32,54,74,86,78,39,32,25,33,50,94,92,93,88,86,39,32,43,33,60,74,82,87,32,60,78,87,94,39,32,45,33,63,74,93,93,78,91,87,32,66,78,85,78,76,93,82,88,87,39,32,26,33,65,74,87,77,88,86,32,60,88,77,78,39,32,27,33,66,78,85,78,76,93,32,63,91,78,92,78,93,39,32,25,33,50,94,92,93,88,86,32,54,74,86,78,39,32,43,33,60,74,82,87,32,60,78,87,94,39,32,45,33,54,74,86,78,32,60,88,77,78,39,32,30,33,66,82,99,78,32,71,39,33,66,82,99,78,32,72,39,33,60,82,87,78,32,50,88,94,87,93,39,32,25,33,63,78,91,76,78,87,93,74,80,78,39,32,41,33,66,93,74,91,93,32,54,74,86,78,39,32,26,33,60,74,82,87,32,60,78,87,94,39,32,45,33,55,82,80,81,32,66,76,88,91,78,92,39,32,44,33,1,34,33,2,34,33,3,34,33,4,34,33,5,34,33,6,34,33,54,74,86,78,32,60,88,77,78,39,32,30,33,60,74,82,87,32,60,78,87,94,39,32,45,33,66,74,79,78,32,54,94,78,92,92,82,87,80,39,33,69,82,77,78,88,32,60,88,77,78,39,33,49,74,76,84,80,91,88,94,87,77,32,52,79,79,78,76,93,92,39,33,48,76,76,78,92,92,82,75,82,85,82,93,98,32,60,88,77,78,39,33,50,88,91,77,82,87,80,32,37,48,85,89,81,74,38,39,33,60,74,97,82,86,94,86,32,53,63,66,39,33,69,78,91,92,82,88,87,39,33,60,74,82,87,32,60,78,87,94,32,45,33,66,94,89,78,91,32,66,96,78,78,89,78,91,32,82,92,32,74,32,95,78,91,92,82,88,87,32,88,79,32,60,82,87,78,66,96,78,78,89,78,91,33,79,88,91,32,93,81,78,32,67,82,8,4,50,52,32,96,82,93,81,32,92,78,95,78,91,74,85,32,86,88,77,78,92,32,74,87,77,33,79,78,74,93,94,91,78,92,34,32,67,88,32,89,85,74,98,35,32,88,87,78,32,76,74,87,32,92,93,74,91,93,32,74,32,90,94,82,76,84,33,80,74,86,78,32,79,91,88,86,32,93,81,78,32,86,74,82,87,32,86,78,87,94,35,32,93,81,82,92,32,82,87,76,85,94,77,78,92,33,88,89,93,82,88,87,92,32,79,88,91,32,77,82,79,79,78,91,78,87,93,32,77,82,79,79,82,76,94,85,93,82,78,92,32,74,87,77,33,89,91,78,92,78,93,92,34,32,62,87,76,78,32,82,87,32,74,32,80,74,86,78,35,32,98,88,94,91,32,88,75,83,78,76,93,82,95,78,33,82,92,32,93,88,32,92,74,79,78,85,98,32,53,85,74,80,32,26,32,74,85,85,32,93,81,78,32,60,82,87,78,92,32,25,32,75,98,33,94,92,82,87,80,32,93,81,78,32,87,94,86,75,78,91,78,77,32,93,82,85,78,92,32,74,92,32,76,85,94,78,92,32,93,88,33,79,82,80,94,91,78,32,88,94,93,32,96,81,78,91,78,32,78,74,76,81,32,60,82,87,78,32,25,32,82,92,32,85,88,76,74,93,78,77,34,33,33,68,92,78,32,48,85,89,81,74,32,93,88,32,92,78,74,91,76,81,32,74,32,93,82,85,78,35,32,2,87,77,32,93,88,32,53,85,74,80,32,26,33,74,32,93,82,85,78,35,32,72,47,32,93,88,32,86,74,91,84,32,74,32,27,32,88,87,93,88,32,74,32,93,82,85,78,35,32,71,67,0,87,33,93,88,32,76,81,88,91,77,35,32,86,88,77,78,32,93,88,32,89,74,94,92,78,35,32,74,87,77,32,77,78,85,32,93,88,32,90,94,82,93,34,33,33,56,32,81,88,89,78,32,98,88,94,32,78,87,83,88,98,32,86,98,32,80,74,86,78,32,39,38,33,63,74,94,92,78,77,39,33,65,78,92,94,86,78,32,54,74,86,78,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,65,78,86,74,82,87,82,87,80,32,67,82,85,78,92,39,33,67,82,86,78,32,67,74,84,78,87,39,33,54,74,86,78,32,62,95,78,91,109,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,65,78,92,94,86,78,32,54,74,86,78,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,65,78,86,74,82,87,82,87,80,32,67,82,85,78,92,39,33,67,82,86,78,32,67,74,84,78,87,39,33,54,74,86,78,32,50,88,86,89,85,78,93,78,109,33,65,78,92,94,86,78,32,54,74,86,78,33,65,78,92,93,74,91,93,33,60,74,82,87,32,60,78,87,94,33,52,97,82,93,32,48,89,89,85,82,76,74,93,82,88,87,33,66,76,88,91,78,39,33,67,82,86,78,32,67,74,84,78,87,39,33};
//const uint24_t section[11] = {0,112,206,287,371,430,548,1059,1143,1230,1311};

/* Legacy */

uint16_t initialPalette[256] = {
    /*0*/  /*1*/  /*2*/  /*3*/  /*4*/  /*5*/  /*6*/  /*7*/  /*8*/  /*9*/  /*A*/  /*B*/  /*C*/  /*D*/  /*E*/  /*F*/
/*0*/ 0x0000,0x7C00,0x7FE0,0x03E0,0x03FF,0x001F,0x7C1F,0x7FFF,0x1CE7,0x3C00,0x3DE0,0x01E0,0x01EF,0x000F,0x3C0F,0x5EF7
/*1*/,0x79E0,0x0210,0x0210,0x0210,0x0210,0x0210,0x1084,0x6000,0x7800,0x1400,0x0421,0x5294,0x5EE0,0x0000,0x0000,0x0000
/*2*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*3*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*4*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*5*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*6*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*7*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*8*/,0x7800,0x1400,0x7BC0,0x14A0,0x03C0,0x00A0,0x7BDE,0x294A,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*9*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*A*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*B*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*C*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*D*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*E*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
/*F*/,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000 /* Menu fade effect */
};

//const uint8_t CLICKABLE = 0b00000100; const uint8_t SELECT1 = 0b00000001; const uint8_t SELECT2 = 0b00000010; const uint8_t SELECT3 = 0b00000011;           red darkRed 0grey 1grey
enum guiType {Click = 1, Scroll = 2, Dial = 4, Direct = 8, Value = 16, Dot = 32, BoolToggle = 64, Text = 128};
enum GUITYPE { C = 1, F = 2, N = 4, P = 8, V = 16, D = 32, B = 64, T = 128};

/* Global */
//Video



//Graphics

//Utilities
uint32_t seed = 0; //Used for random number generation //frameTime variable
uint32_t delta = 0;
uint32_t frameStart = 0; //When the new frame began
uint32_t clockMax = 0;
uint32_t clockTime = 0;

uint32_t systemTime;
uint32_t pauseTime;
uint32_t gameStartTime;
uint32_t gamePauseTime;
uint32_t gameFinishTime;


/* Global */

/* Library Functions */


#ifdef TI84CE
uint8_t* board = (uint8_t*)0xD5E000;
uint8_t* state = (uint8_t*)0xD5F000;
uint24_t* search = (uint24_t*)0xD60000;
uint8_t* flag = (uint8_t*)0xD62000;
#endif /* TI84CE */

#ifdef WINDOWS
uint8_t board[56*31];
uint8_t state[56*31];
uint24_t search[56*31];
uint8_t flag[56*31];
#endif /* WINDOWS */

uint24_t fadeSpeed = 0;

const uint16_t orderPos[18] = {
	0,16,32,48,64,80,96,112,128,144,152,176,200,232,264,288,312,344
};
//344 + 16 for buffer reasons since this keeeps being a probelmy
const int8_t order[360] = {
	-1,1,0,1,1,1,-1,0,1,0,-1,-1,0,-1,1,-1,
	-1,2,1,2,-2,1,-2,-1,2,1,2,-1,-1,-2,1,-2,
	0,2,0,1,0,-1,0,-2,-2,0,-1,0,1,0,2,0,
	-2,2,2,2,-1,1,1,1,-1,-1,1,-1,-2,-2,2,-2,
	2,2,2,-2,-2,2,-2,-2,1,0,-1,0,0,1,0,-1,
	-1,2,2,1,1,-2,-2,-1,1,0,-1,0,0,1,0,-1,
	1,1,1,2,-1,-1,-1,-2,-2,1,-1,1,2,-1,1,-1,
	-2,1,-1,1,2,1,1,1,-2,-1,-1,-1,2,-1,1,-1,
	1,1,1,-1,-1,1,-1,-1,2,0,1,0,-1,0,-2,0,
	-1,0,1,0,0,1,0,-1,
	-1,1,0,1,1,1,-1,0,1,0,-1,-1,0,-1,1,-1, -1,0,1,0,0,1,0,-1,
	-1,1,0,1,1,1,-1,0,1,0,-1,-1,0,-1,1,-1, -1,-1,1,1,-1,1,1,-1,
	0,2,0,1,0,-1,0,-2,-2,0,-1,0,1,0,2,0, -2,2,2,2,-1,1,1,1,-1,-1,1,-1,-2,-2,2,-2,
	-1,1,0,1,1,1,-1,0,1,0,-1,-1,0,-1,1,-1, -1,2,1,2,-2,1,-2,-1,2,1,2,-1,-1,-2,1,-2,
	-1,0,1,0,0,1,0,-1, 2,2,2,-2,-2,2,-2,-2,1,0,-1,0,0,1,0,-1,
	-1,0,1,0,0,1,0,-1, 0,2,0,1,0,-1,0,-2,-2,0,-1,0,1,0,2,0,
	0,2,0,1,0,1,0,-1,0,-1,0,-2, 2,0,1,0,1,0,-1,0,-1,0,-2,0, 1,1,1,-1,-1,1,-1,-1
};

const uint8_t fontArray[40] = {
	0,0,0,1,1,2,2,2,  6,8,8,8,10,9,11,13,  8,8,10,8,10,11,13,13,  1,2,2,1,2,1,2,3,  1,1,2,1,2,1,2,2
};

uint8_t bX[18] = {14,20,24,29,32,34,  34,36,40,47,54,56,  14,24,32,34,40,54}; //Plus 4
uint8_t bY[18] = {14,14,16,19,20,22,  25,28,29,29,29,31,  14,16,20,25,29,29}; //Plus 4
uint24_t bM[18] = {10,18,30,54,72,90,  108,136,180,240,300,3,  10,30,72,108,180,300};
uint8_t bF[6] = {7,7,7,7,7,7};

///fff


uint8_t option = 0;

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

uint8_t findColor1555(uint16_t c) {
    i8 r = (c & 0x7C00) >> 10;
    i8 g = (c & 0x03E0) >> 4;
    g += (c & 0x8000) ? 1 : 0;
    i8 b = (c & 0x001F);

    u8 best = 0x00;
    u16 low = 0xFFFF;
    for (u8 i = 0; i < 0xF0; i++) { //Avoids temp color zone
        u16 col = paletteRAM[i];
        i8 r0 = (col & 0x7C00) >> 10;
        i8 g0 = (col & 0x03E0) >> 4;
        g0 += (c & 0x8000) ? 1 : 0;
        i8 b0 = (col & 0x001F);
        u16 dif = (abs(r - r0) * abs(r - r0)) + (abs(g - g0) * abs(g - g0)) + (abs(b - b0) * abs(b - b0));
        if (dif < low) {
            low = dif;
            best = i;
        }
    }
    return best;
}
uint8_t findColor888(uint8_t r, uint8_t g, uint8_t b) {
    u8 i = (g & 0x04) >> 2;
    r >>= 3;
    g >>= 2;
    b >>= 3;
    return findColor1555((i << 15) + (r << 10) + (g << 5) + b);
}
uint8_t findColor565(uint16_t c) {
    uint8_t r = (c & 0xF800) >> 11;
    uint8_t g = (c & 0x07C0) >> 6;
    uint8_t b = (c & 0x001F);
    uint8_t i = (c & 0x0020) >> 5;
    return findColor1555((i << 15) + (r << 10) + (g << 5) + b);
}
*/


//Menu stuff



#endif /* GLOBAL_H */