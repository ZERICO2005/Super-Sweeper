/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "Common_Def.h"

struct GameSaveFile {
	uint8_t Version[4];
	uint32_t TimeElapsed;
	uint32_t Score;
	uint32_t Seed;
	uint8_t SizeX;
	uint8_t SizeY;
	uint16_t CursorPos;
	uint8_t GameState;
	uint8_t GameMode;
}; typedef struct GameSaveFile GameSaveFile;

bool saveGame(
	const GameSaveFile* data,
	const uint8_t* State,
	const uint8_t* Flag
);

bool loadGame(
	GameSaveFile* data,
	uint8_t* State,
	uint8_t* Flag
);

#endif /* DATAMANAGER_H */