/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Common_Def.h"

#include "prime2D.h"
#include "global.h"
#include "mineSweeper.h"

void pause6x8(uint24_t xW, uint24_t yW, uint8_t lexicon);

void text6x8b4(uint24_t xW, uint24_t yW, uint8_t lexicon); //Incompatibile with 0.70.Alpha and later

uint8_t scoreSort(); //broken

void fadeIn();

void printStat(uint24_t n); //Proprietary

void scoreScreen(); //broken //I shall fix the sorting now that I can code insertion sort

void timeDisplay(uint32_t input); //systemTime - gameStartTime - gamePauseTime

void pauseScroll();

void winScreen();

void gameOver(); //160x120 screen due to poor coding

void pause();

#endif /* GAMEMENU_H */