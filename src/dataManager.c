/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Common_Def.h"
#include "dataManager.h"
#include "mineSweeper.h"

/*
0b00: Blank Tile
0b01: Flagged Tile
0b10: Question Marked Tile
0b11: Revealed Tile
*/

#define TilesPerByte (4)
#define BitsPerTile (2)

bool saveGame(
	const GameSaveFile* data,
	const uint8_t* State,
	const uint8_t* Flag
) {
	if (data == NULL || State == NULL || Flag == NULL) { return false; }

	int24_t fileHandle = ti_Open("MNSPSAV0","w");
	if (fileHandle == 0) {
		//printf("\nError: saveGame() fileHandle == 0");
		return false; // Failed to open file
	}
	if (ti_Write(data, sizeof(GameSaveFile), 1,fileHandle) != 1) {
		//printf("\nError: saveGame() ti_Write failed to write header");
		return false; // Failed to write data
	}
	uint16_t gameDataSize = (((uint16_t)data->SizeX * (uint16_t)data->SizeY) + (TilesPerByte - 1)) / TilesPerByte;
	uint8_t* gameData = (uint8_t*)malloc(gameDataSize);
	memset(gameData,0,gameDataSize); // Otherwise garbage ruins everything
	if (gameData == NULL) {
		return false; // Failed to malloc
	}
	uint16_t z = borderIndexes * (data->SizeX + 2 * borderIndexes) + borderIndexes;
	uint16_t index = 0;
	uint8_t b = 0;
	for (uint8_t y = 0; y < data->SizeY; y++) {
		for (uint8_t x = 0; x < data->SizeX; x++) {
			if (State[z] == sCLEARED) {
				gameData[index] |= (0b11 << b);
			} else {
				switch (Flag[z]) {
					case fBLANK:
						gameData[index] |= (0b00 << b);
					break;
					case fFLAG:
						gameData[index] |= (0b01 << b);
					break;
					case fQUESTION:
						gameData[index] |= (0b10 << b);
					break;
				};
			}
			b += BitsPerTile;
			if (b == TilesPerByte * BitsPerTile) {
				b = 0;
				index++;
			}
			z++;
		}
		z += 2 * borderIndexes;
	}

	if (ti_Write(gameData,1,gameDataSize,fileHandle) != gameDataSize) {
		//printf("\nError: saveGame() ti_Write failed to write game board data");
		FREE(gameData);
		return false; // Failed to write data
	}

	if (ti_Close(fileHandle) == 0) {
		return false; // Failed to close
	}

	FREE(gameData);

	return true;
}

bool loadGame(
	GameSaveFile* data,
	uint8_t* State,
	uint8_t* Flag
) {
	if (data == NULL || State == NULL || Flag == NULL) { return false; }
	int24_t fileHandle = ti_Open("MNSPSAV0","r");
	if (fileHandle == 0) {
		return false; // Failed to open file
	}
	ti_Read(data,sizeof(GameSaveFile),1,fileHandle);

	uint16_t gameDataSize = (((uint16_t)data->SizeX * (uint16_t)data->SizeY) + (TilesPerByte - 1)) / TilesPerByte;
	uint8_t* gameData = (uint8_t*)malloc(gameDataSize);
	memset(gameData,0,gameDataSize); // Otherwise garbage ruins everything
	if (gameData == NULL) {
		return false; // Failed to malloc
	}

	uint16_t z = borderIndexes * (data->SizeX + 2 * borderIndexes) + borderIndexes;
	uint16_t index = 0;
	uint8_t b = 0;
	for (uint8_t y = 0; y < data->SizeY; y++) {
		for (uint8_t x = 0; x < data->SizeX; x++) {
			switch ((gameData[index] >> b) & 0b11) {
				case 0b00:
					State[z] = sHIDDEN;
					Flag[z] = fBLANK;
				break;
				case 0b01:
					State[z] = sHIDDEN;
					Flag[z] = fFLAG;
				break;
				case 0b10:
					State[z] = sHIDDEN;
					Flag[z] = fQUESTION;
				break;
				case 0b11:
					State[z] = sCLEARED;
					Flag[z] = fBLANK;
				break;
			}
			b += BitsPerTile;
			if (b == TilesPerByte * BitsPerTile) {
				b = 0;
				index++;
			}
			z++;
		}
		z += 2 * borderIndexes;
	}

	if (ti_Close(fileHandle) == 0) {
		FREE(gameData);
		return false; // Failed to close
	}
	FREE(gameData);
	return true;
}

#undef BitsPerTile
#undef TilesPerByte