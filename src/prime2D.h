/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef PRIME2D_H
#define PRIME2D_H

#include "Common_Def.h"
#include "prime2D.h"
#include "prime2D_Font6x8.h"

extern uint8_t gColor; //Graphics color

extern const uint16_t char3x5[28];
extern const uint16_t char5x5[56];

// const uint8_t char6x8[768]; // See prime2D_Font6x8.h

//Debugging
extern const uint16_t num3x5[16]; //Used for the printInt functions
void printInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC); //integer to print, length, base 2-16 //Auto adjusts for signage
void printUInt(int24_t in, uint8_t len, uint8_t base, uint24_t xC, uint24_t yC); //integer to print, length, base 2-16

void fillRect(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2); //x start, y start, x length, y length

void horiz(uint24_t x1, uint24_t y, uint24_t x2); //x start, y postion, x length

void vert(uint24_t x, uint24_t y1, uint24_t y2); //x postion, y start, y length

#define plot(x,y) lcd_Ram8[(x) + ((y) * 320)] = gColor
#define plotFast(z) lcd_Ram8[z] = gColor

void fillScreen(); //Fills buffer 0

//Text Engine
void text6x8(uint24_t xW, uint24_t yW, uint8_t lexicon); //x position, y position, letter index

void fillText(uint24_t x1, uint24_t y1, uint24_t x2, uint24_t y2); //x start, y start, x length, y length //fillRect() that does not overwrite text

#endif /* PRIME2D_H */