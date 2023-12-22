/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef PRIMEKEY_H
#define PRIMEKEY_H

#include "Common_Def.h"

/* Key Constants */
void keyReset(uint8_t type);
extern const uint8_t HORIZ; extern const uint8_t VERT; extern const uint8_t ALPHA; extern const uint8_t SECOND; extern const uint8_t OTHER; extern const uint8_t DEBUG; extern const uint8_t ARROW; extern const uint8_t CHORD;
extern const uint8_t hORIZ; extern const uint8_t vERT; extern const uint8_t aLPHA; extern const uint8_t sECOND; extern const uint8_t oTHER; extern const uint8_t dEBUG; extern const uint8_t aRROW; extern const uint8_t cHORD;
//uint8_t key = 0; //Compatibility

#define keyTotal 8 //Use different keyDelay values in different menus
extern uint32_t keyDelay[keyTotal]; //0 Horiz, 1 Vert, 2 Alpha, 3 Second, 4 Other, 5 Debug, 6 Arrow
extern uint32_t keyPressTime[keyTotal];

extern uint8_t keyReady; //1 Horiz, 2 Vert, 4 Alpha, 8 Second, 16 Other, 32 Debug, 64 Arrow
/* Key Constants */

/* Utilities */
void quitGame();

void shiftScreen();
/* Utilities */

/* Keyboard */

uint32_t deltaTime(uint32_t current, uint32_t previous);

void delay32K(uint32_t delay);

void keyReset(uint8_t type);

void keyPress();

#endif /* PRIMEKEY_H */