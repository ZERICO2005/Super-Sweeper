/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Common_Def.h"

#include "prime2D.h"
#include "global.h"
#include "gameMenu.h"
//#include <col.h>

#define borderIndexes 2
//Graphic numbers
#define gMine 25
#define gFlag 26
#define gQuestion 27

#define currentTime (systemTime - gameStartTime - gamePauseTime)
void gameControl(); //Temporary May 23

/*
//legacy
const uint8_t seg7[18] = {0b1011111,0b0000011,0b1110110,0b1110011,0b0101011,0b1111001,0b1111101,0b1000011,0b1111111,0b1111011,0b1101111,0b0111101,0b1011100,0b0110111,0b1111100,0b1101100,0b0000000,0b0100000};
//Characters: HEX,_,-
void displaySeg7(uint24_t i, uint8_t d, uint8_t b, uint24_t x, uint24_t y);*/

uint8_t alphaBind();
uint8_t secondBind();

enum tileStates {sHIDDEN = 0, sCLEARED = 1, sVOID = 255};
enum tileDrawCodes {tCLEAR = 0, tSELECT = 1, tFLAG = 2};
enum tileFlagCodes {fBLANK = 0, fFLAG = 1, fQUESTION = 2};

struct dataSeg7 {
    uint8_t digits;
    uint24_t x;
    uint24_t y;
    uint8_t offC;
    uint8_t onC;
};

extern struct dataSeg7 timeLCD;
extern struct dataSeg7 scoreLCD;
extern struct dataSeg7 flagLCD;

extern const uint8_t seg7[18];
//Characters: HEX,_,-
//void displaySeg7(uint24_t i, uint8_t d, uint8_t b, uint24_t x, uint24_t y) { //Number, Digits, X-2, Y-2
void displaySeg7(uint24_t i, uint8_t b, struct dataSeg7* lcd); //Number, Digits, X-2, Y-2

void buildSeg7(
	uint24_t input, uint8_t base, struct dataSeg7* lcd, uint8_t digits, uint24_t x, uint24_t y,
	uint8_t bgC, uint8_t borC, uint8_t offC, uint8_t onC
); //Number, Digits, Base, x, y, ptr, Colors: backGround, border, off, on

void quake();

enum expressionCode { eHAPPY = 0, eSAD = 1, eNULL = 2, eCHORD = 3, eNORMAL = 4, eSHADES = 5, eXX = 6, eSLEEP = 7 };
void expression(unsigned char e); //Updates the smiley face

void flash(); //uint8_t x

void flagDraw(uint8_t symbol, uint24_t xP, uint24_t yP);

/* 
//Legacy, keep this function around
void flagCount();
*/

//uint8_t lcdColor[20] = {0x60}; //0x70
//        flagLCD.onC = color[((plags / 100) % 10)] & 7;
//        flagLCD.offC = color[((plags / 100) % 10)] | 8;

//Slow, but its the only way to do signed flag counts for now
void flagCount(); //Add a color number mode for nostalga

void glyph(int16_t space, uint8_t symbol);

void fillTile(int16_t space, int8_t mode);

extern uint24_t item; //U16
extern uint24_t max; //U16
void floodFill();

/*
// Attempt at making it faster
bool mineCheck(int24_t tileM);
*/


// Legacy
bool mineCheck(int24_t tileM);

void mineGenerate();


/*
// Attempt at making it constant time O(1)
void mineGenerate();
*/

void chord();
extern uint8_t gridType[25];
void cursorSetup();

void drawGame();

extern const uint8_t fontList[];
void fontCheck(); //Plus 4

void resetGame();

//8x8: 0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010            ,0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111,    0b11111111,0b11111111,0b11111111,0b10111111,0b11111111,0b11111111,0b11101111,0b11111111,0b11111111,0b11111011,0b11111111,0b11111111,0b11111110,0b11111111,0b11111111,0b11111111    ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010
//New Line: ,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010,0b10101010

extern uint8_t autoCheck;
void autoChord();

void autoSolve();

extern uint8_t chordCheck;
void gameLoop();

void gameControl();

#endif /* MINESWEEPER_H */