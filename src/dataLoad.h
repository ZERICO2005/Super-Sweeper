/*
**	Author: zerico2005 (2023)
**	Project: Super-Sweeper-0.77.1
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef DATALOAD_H
#define DATALOAD_H

#include <global.h>
#include <prime2D.h>
#include <stdint.h>
#include <mineSweeper.h>

// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //
// OUTDATED IMPORT FROM LAPTOP //

uint8_t data[8000];

void loadUserData(uint8_t input) {
    uint8_t prgm;
    //Load AppVar
    unsigned char txt[7] = "SWPDAT";
    // unsigned char num[4];
    // sprintf(num, "%03d", input);
    // prgm = ti_Open(strcat(txt, num), "r");
    prgm = ti_Open(txt, "r");

    ti_Seek(0, SEEK_SET, prgm); //Seeks to the required data
    ti_Read(&data, 3, 8000, prgm);

    uint8_t* rom = data;
    uint16_t* blit = 0xD44B00; // ((320 - 168) / 4) + ((240 - 126) * 80)
    uint8_t b = 1;
    for (uint24_t y = 0; y < 8000; y++) { //(320*200) / 8
        b = 1;
        for (uint8_t x = 0; x < 8; x++) {
            *blit = *rom & b ? 0xFFFF : 0x0000;
            blit++;
            b <<= 1;
        }
        rom++;
    }

    ti_Close(prgm);
    prgm = 0;
}

void saveGame(void* ptr) {
    ptr[0] = (uint8_t)gameMode;
    ptr[1] = (uint8_t)sizeX;
    ptr[2] = (uint8_t)sizeY;
    ptr[3] = (uint24_t)tile;
    ptr[6] = (uint24_t)chance;
    ptr[9] = (uint24_t)flags;
    ptr[12] = (uint24_t)score;
    ptr[15] = (uint32_t)(systemTime.full - gameStartTime.full - gamePauseTime.full);
    uint24_t i = 19;
    uint24_t z = marX * 2 + borderIndexes;
    for (uint8_t y = 0; y < sizeY; y++) {
        for (uint8_t x = 0; x < sizeX; x++) {
            uint8_t b = state[z] == 255 ? 3 : state[z];
            b += flag[z] == gFlag ? 4 : 0;
            b += flag[z] == gQuestion ? 8 : 0;
            b += board[z] == gMine ? 16 : 0;
            ptr[i] = b;
            i++;
            z++;
        }
        z += borderIndexes * 2;
    }
}

void loadGame(void* ptr) {
    gameMode = ptr[0];
    sizeX = ptr[1];
    sizeY = ptr[2];
    tile = ptr[3];
    chance = ptr[6];
    flags = ptr[9];
    score = ptr[12];
    gameStartTime.full = systemTime.full - ptr[15];

    uint24_t i = 19;
    uint24_t z = marX * 2 + borderIndexes;
    for (uint8_t y = 0; y < sizeY; y++) {
        for (uint8_t x = 0; x < sizeX; x++) {
            board[z] = ptr[i] & 16 ? gMine : 0; 
            uint8_t b = state[z] == 255 ? 3 : state[z];
            b += flag[z] == gFlag ? 4 : 0;
            b += flag[z] == gQuestion ? 8 : 0;
            b += board[z] == gMine ? 16 : 0;
            ptr[i] = b;
            i++;
            z++;
        }
        z += borderIndexes * 2;
    }
}

#endif /* DATALOAD_H */